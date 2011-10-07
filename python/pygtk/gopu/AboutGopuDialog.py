import gettext
from gettext import gettext as _
gettext.textdomain('gopu')

import logging
logger = logging.getLogger('gopu')

from gopu_lib.AboutDialog import AboutDialog

# See gopu_lib.AboutDialog.py for more details about how this class works.
class AboutGopuDialog(AboutDialog):
    __gtype_name__ = "AboutGopuDialog"
    
    def finish_initializing(self, builder): # pylint: disable=E1002
        """Set up the about dialog"""
        super(AboutGopuDialog, self).finish_initializing(builder)

        # Code for other initialization actions should be added here.

