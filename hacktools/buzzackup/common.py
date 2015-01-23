#!/usr/bin/env python
##############################################################################
# buzzackup - google buzz backup tool
# author: rohityadav, hack'd just before `rm buzz-account` ];] buzz s**ks
# notes: ain't elegant, just one night's hacking, enjoy!
# help: python buzzackup.py --help
###############################################################################

import urllib2
import xml.etree.ElementTree as ET
from ConfigParser import SafeConfigParser
from optparse import OptionParser
from django.utils.encoding import smart_str
from calendar import month_name

#Log filename
backupLogFile = 'backup.log'
#Namespaces
namespace = "{http://www.w3.org/2005/Atom}"
namespace_thr = "{http://purl.org/syndication/thread/1.0}"
namespace_likers = "{http://portablecontacts.net/ns/1.0}"
namespace_buzz = "{http://schemas.google.com/buzz/2010}"
namespace_activity = "{http://activitystrea.ms/spec/1.0/}"
#API urls
apiPrefix = "http://www.googleapis.com/buzz/v1/"
feedUrl = apiPrefix + "activities/%s/@public?max-results=100&bhu"

def readFeed(url):
    if url != None:
        request = urllib2.Request(url);
        response = urllib2.urlopen(request)
        rawFeed = response.read()
        return rawFeed

def readFeedFromFile(fileName = 'buzzackup.xml'):
    f = open(fileName, 'r')
    data = f.read()
    f.close()
    return data
