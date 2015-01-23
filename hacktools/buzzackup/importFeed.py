#!/usr/bin/env python
##############################################################################
# buzzackup - google buzz backup tool
# author: rohityadav, hack'd just before `rm buzz-account` ];] buzz s**ks
# notes: ain't elegant, just one night's hacking, enjoy!
# help: python buzzackup.py --help
###############################################################################

import xml.etree.ElementTree as ET
from common import readFeed, readFeedFromFile, namespace, feedUrl

def importRawFeed(fileName, url):
    f = open(fileName, 'w')
    rawFeed = readFeed(url);
    f.write(rawFeed)
    f.close()
    print "Raw feed saved in: %s" % fileName
    return rawFeed

def importBuzzFeed(handle, fileName, url = feedUrl, stock = 0):
    if url == feedUrl: url = url % handle
    print "Getting raw Google Buzz feed from:", url

    totalFiles = 0
    totalEntries = 0
    gotLinks = False

    while True:
        rawFeed = importRawFeed(fileName % stock, url)
        tree = ET.XML(rawFeed)
        links = tree.findall(namespace + "link")
        totalFiles += 1
        totalEntries += len(tree.findall(namespace + "entry"))

        for link in links:
            if link.get('rel') == 'next':
                stock += 1 
                url = 'http' + link.get('href')[5:] + '&bhu'
                gotLinks = True
                break
            else:
                gotLinks = False
        if not gotLinks: break
    return (totalFiles, totalEntries) 
  
def testmain():    
    handle = 'rohityadav89'
    nick = 'Rohit Yadav'
    fileName = "buzzackup-%s-%s.xml" % (handle, '%d')
    (totalFiles, totalEntries) = importBuzzFeed(handle, fileName, feedUrl % handle)
    print "Buzz feed backedup in %d files, total posts found are: %d" % (totalFiles, totalEntries)

if __name__ == '__main__':
    testmain()
