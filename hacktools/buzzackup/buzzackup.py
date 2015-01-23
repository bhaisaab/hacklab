#!/usr/bin/env python
##############################################################################
# buzzackup - google buzz backup tool
# author: rohityadav, hack'd just before `rm buzz-account` ];] buzz s**ks
# notes: ain't elegant, just one night's hacking, enjoy!
# help: python buzzackup.py --help
###############################################################################

from ConfigParser import SafeConfigParser
from optparse import OptionParser
from common import backupLogFile
from importFeed import importBuzzFeed
from exportFeed import exportHtmlFeed
    
def main():
    parser = OptionParser()
    parser.add_option("-p", "--profile", dest="profile", default="rohityadav89", help="Your Google Buzz Profile id")
    parser.add_option("-n", "--name", dest="nick", default="Rohit Yadav", help="Your Name")
    parser.add_option("--dir", dest="dir", default="./", help="Specify backup directory")
    parser.add_option("-d", dest="download", action="store_true", default=False, help="Enable to fetch the feed only. Default to use fetched file.")
    parser.add_option("-e", dest="export", action="store_true", default=False, help="Enable to export a static html file containing the feed only.")
    (options, args) = parser.parse_args()

    profile = options.profile
    nick = options.nick
    directory = options.dir
    fileName = directory + "buzzackup-%s-%s.xml" % (profile, '%d')

    if options.download:
        (totalFiles, totalEntries) = importBuzzFeed(profile, fileName)
        f = open(directory + backupLogFile, 'aw')
        f.write("%s, %s, %s, %s\n" % (profile, totalFiles, nick, totalEntries))
        f.close()
        print "Buzz feed backedup in %d files, total posts found are: %d" % (totalFiles, totalEntries)

    if options.export:
        htmlOutputFileName = "buzzout-%s.html" % profile
        exportHtmlFeed(directory, htmlOutputFileName)

main()
