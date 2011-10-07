import optparse

import gettext
from gettext import gettext as _
gettext.textdomain('gopu')

import gtk
from gopu import GopuWindow
from gopu_lib import set_up_logging, preferences, get_version

def parse_options():
    """Support for command line options"""
    parser = optparse.OptionParser(version="%%prog %s" % get_version())
    parser.add_option(
        "-v", "--verbose", action="count", dest="verbose",
        help=_("Show debug messages (-vv debugs gopu_lib also)"))
    (options, args) = parser.parse_args()

    set_up_logging(options)

def main():
    'constructor for your class instances'
    parse_options()

    # preferences
    default_preferences = {
    'allowed_formats': ".ogv .avi .flv .mp4 .ogg .mp3",
    }
    preferences.update(default_preferences)
    # user's stored preferences are used for 2nd and subsequent sessions
    preferences.db_connect()
    preferences.load()

    # Run the application.    
    window = GopuWindow.GopuWindow()
    window.show()
    gtk.main()
    
    preferences.save()
