widget_methods = {
    'allowed_formats': ['get_text', 'set_text', 'changed']
}

import gettext
from gettext import gettext as _
gettext.textdomain('gopu')

import logging
logger = logging.getLogger('gopu')

from gopu_lib.PreferencesDialog import PreferencesDialog

class PreferencesGopuDialog(PreferencesDialog):
    __gtype_name__ = "PreferencesGopuDialog"

    def finish_initializing(self, builder): # pylint: disable=E1002
        """Set up the preferences dialog"""
        super(PreferencesGopuDialog, self).finish_initializing(builder)

        # populate the dialog from the preferences dictionary
        # using the methods from widget_methods
        self.widget_methods = widget_methods
        self.set_widgets_from_preferences() # pylint: disable=E1101

        # Code for other initialization actions should be added here.
