import gettext
from gettext import gettext as _
gettext.textdomain('gopu')

import sys
import os
import gtk
import logging
from quickly import prompts
from quickly.widgets.dictionary_grid import DictionaryGrid
from quickly.widgets.media_player_box import MediaPlayerBox
import goocanvas

logger = logging.getLogger('gopu')

from gopu_lib import Window, preferences, helpers
from gopu.AboutGopuDialog import AboutGopuDialog
from gopu.PreferencesGopuDialog import PreferencesGopuDialog

# See gopu_lib.Window.py for more details about how this class works
class GopuWindow(Window):
    __gtype_name__ = "GopuWindow"
    
    def finish_initializing(self, builder): # pylint: disable=E1002
        """Set up the main window"""
        super(GopuWindow, self).finish_initializing(builder)

        self.AboutDialog = AboutGopuDialog
        self.PreferencesDialog = PreferencesGopuDialog

        # Code for other initialization actions should be added here.
        preferences.connect('changed', self.on_preferences_changed)

        self.allowed_formats = preferences['allowed_formats'].split(' ')

        self.player = MediaPlayerBox(True)
        self.player.remove(self.player.controls)
        open_button = gtk.ToolButton()
        open_button.set_stock_id(gtk.STOCK_OPEN)
        open_button.show()
        open_button.connect("clicked", self.openbutton_clicked_event)
        self.player.controls.insert(open_button, 0)
        self.ui.hbox1.pack_start(self.player.controls, True)

        self.player.connect("end-of-file", self.play_next_file)
        self.player.show()
        self.ui.hpaned1.add2(self.player)

        self.goocanvas = goocanvas.Canvas()
        self.goocanvas.show()

        logo_file = helpers.get_media_file("background.png")
        logo_file = logo_file.replace("file:///","")
        logo_pb = gtk.gdk.pixbuf_new_from_file(logo_file)
        root_item=self.goocanvas.get_root_item()
        goocanvas.Image(parent=root_item, pixbuf=logo_pb,x=20,y=20)

        self.song_text = goocanvas.Text(parent=root_item,text="", x=5, y=5)
        self.song_text.set_property("font","Ubuntu")
        self.song_text.scale(2,2)

    def play_next_file(self, widget, file_uri):
        #get a reference to the current grid
        grid = self.ui.scrolledwindow1.get_children()[0]

        #get a gtk selection object from that grid
        selection = grid.get_selection()

        #get the selected row, and just return if none are selected
        model, rows = selection.get_selected_rows()
        if len(rows) == 0:
            return

        #calculate the next row to be selected by finding
        #the last selected row in the list of selected rows
        #and incrementing by 1
        next_to_select = rows[-1][0] + 1

        #if this is not the last row in the last
        #unselect all rows, select the next row, and call the
        #play_file handle, passing in the now selected row
        if next_to_select < len(grid.rows):
            selection.unselect_all()
            selection.select_path(next_to_select)
            self.play_file(self,grid.selected_rows)

    def openbutton_clicked_event(self, widget, data=None):
        #let the user choose a path with the directory chooser
        response, path = prompts.choose_directory()
    
        #make certain the user said ok before working
        if response == gtk.RESPONSE_OK:
            #make one list of support formats
            formats = self.allowed_formats

            #make a list of the supported media files
            media_files = []
            #iterate through root directory 
            for root, dirs, files in os.walk(path):
                #iterate through each file
                for f in files:
                    #check if the file is a supported formats
                    for format in formats:
                        if f.lower().endswith(format):
                            #create a URI in a format gstreamer likes
                            file_uri = "file://" + os.path.join(root,f)

                            #add a dictionary to the list of media files
                            media_files.append({"File":f,"uri":file_uri, "format":format})

            #remove any children in scrolled window
            for c in self.ui.scrolledwindow1.get_children():
                self.ui.scrolledwindow1.remove(c)

            #create the grid with list of dictionaries
            #only show the File column
            media_grid = DictionaryGrid(media_files, keys=["File"])

            #hook up to the selection_changed event
            media_grid.connect("selection_changed", self.play_file)

            #show the grid, and add it to the scrolled window
            media_grid.show()
            self.ui.scrolledwindow1.add(media_grid)

    def play_file(self, widget, selected_rows, data=None):
        self.player.stop()
        format = selected_rows[0]["format"]
        current_visual = self.ui.hpaned1.get_child2()

        #check if the format of the current file is audio
        if format in [".ogg", ".mp3"]:
            self.song_text.set_property("text",selected_rows[0]["File"])
            #if it is audio, see if the current visual is
            #the goocanvas, if it's not, do a swapperoo
            if current_visual is not self.goocanvas:
                self.ui.hpaned1.remove(current_visual)
                self.ui.hpaned1.add2(self.goocanvas)
        else:
            #do the same thing for the player
            if current_visual is not self.player:
                self.ui.hpaned1.remove(current_visual)
                self.ui.hpaned1.add2(self.player)

        #go ahead and play the file
        self.player.uri = selected_rows[-1]["uri"]
        self.player.play()

    def on_preferences_changed(self, widget, data=None):
        logging.debug('main window received preferences changed')
        for key in data:
            logging.debug('preference changed: %s = %s' % (key, preferences[key]))

