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

namespace = "{http://www.w3.org/2005/Atom}"
namespace_thr = "{http://purl.org/syndication/thread/1.0}"
namespace_likers = "{http://portablecontacts.net/ns/1.0}"
feedUrl = "https://www.googleapis.com/buzz/v1/activities/%s/@public"
feedUrl2 = "http://buzz.googleapis.com/feeds/%s/public/posted"

def readFeed(url):
    if url != None:
        request = urllib2.Request(url);
        response = urllib2.urlopen(request)
        rawFeed = response.read()
        return rawFeed
    return None

def readFeedFromFile(fileName = 'buzzackup.xml'):
    f = open(fileName, 'r')
    data = f.read()
    f.close()
    return data

def importBuzzFeed(nick, fileName):
    print "Getting raw feed from Google Buzz service"
    f = open(fileName, 'w')
    rawFeed = readFeed(feedUrl % nick);
    print rawFeed
    f.write(rawFeed)
    f.close()
    print "Raw feed saved as file: %s" % (fileName)

def exportHtmlFeed(feedFileName, htmlOutputFileName, handle, nick, reverse = False):
    data = readFeedFromFile(feedFileName)
    entries = ET.XML(data).findall(namespace + "entry")
    if reverse: entries.reverse()

    f = open(htmlOutputFileName, 'w')
    f.write('<html><head><title>Buzzackup of %s<title></head><body>' % nick)
    f.write("<h1>Buzz by %s {%d}!</h1>" % (nick ,len(entries)))

    entryNumber = 1
    print "Crawling Google network for buzz... Found %d buzz posts for %s" % (len(entries), nick)
    for entry in entries:
        print "Processing buzz post. Progress: (%d/%d) %d%%" % (entryNumber, len(entries), entryNumber * 100 / len(entries)) 
        f.write("<div class=\"buzz\">")
        entryDate = entry.findall(namespace + 'updated')[0].text.split('T')[0].split('-')
        prettyDate = "%s %s %s " % (entryDate[2], month_name[int(entryDate[1])], entryDate[0])
        f.write("<strong>" + prettyDate + "</strong>")
        post = entry.findall(namespace + 'content')[0].text
        f.write("<div class=\"post\">" + smart_str(post) + "</div>")
        postId = entry.findall(namespace + 'id')[0].text.replace('/', ':')
        likedUrl = "https://www.googleapis.com/buzz/v1/activities/" + handle + "/@self/" + postId + "/@liked"
        rawLikedFeed = readFeed(likedUrl)
        likersTree = ET.XML(rawLikedFeed )
        totalLikes = likersTree.findall(namespace_likers + 'totalResults')[0].text
        likeCounter = 0
        if int(totalLikes) != 0:
            print "Hmm... [%s] likes on your post" % totalLikes
            f.write("<div style=\"color:#666;\" class=\"likers\">Liked by [%s]: " % totalLikes)
            likers = likersTree.findall(namespace_likers + 'entry')
            for liker in likers:
                likerName = liker.findall(namespace_likers + 'displayName')[0].text
                likerUri = liker.findall(namespace_likers + 'profileUrl')[0].text
                f.write("<a href=\"%s\">%s</a>" % (likerUri, smart_str(likerName)))
                likeCounter += 1
                if likeCounter != len(likers):
                    f.write(", ")
            f.write("</div>")
        links = entry.findall(namespace + 'link')
        f.write("<div class=\"links\">")
        for link in links:
            if link.get('rel') == 'enclosure':
                f.write("<a href=\"" + smart_str(link.get('href')) + "\">" + smart_str(link.get('title')) + "</a><br>")
            if link.get('rel') == 'replies':
                replyCount = entry.findall(namespace_thr + 'total')[0].text
                if int(replyCount) != 0:
                    f.write("<div class=\"comments\">Comments(%s)<br>" % replyCount)
                    rawReplyFeed = readFeed(link.get('href')) 
                    comments = ET.XML(rawReplyFeed).findall(namespace + 'entry')
                    for comment in comments:
                        f.write("<div style=\"margin-left:30px;\" class=\"comment\">")
                        reply = comment.findall(namespace + 'content')[0].text
                        author = comment.findall(namespace + 'author')[0]
                        authorName = author.findall(namespace + 'name')[0].text
                        authorUri = author.findall(namespace + 'uri')[0].text
                        commentDate = entry.findall(namespace + 'updated')[0].text.split('T')[0].split('-')
                        prettyDate = "%s %s %s " % (commentDate[2], month_name[int(commentDate[1])], commentDate[0])
                        f.write("<a href=\"%s\">%s</a> (%s) - %s" % (authorUri, smart_str(authorName), prettyDate, smart_str(reply)))
                        f.write("</div>")
                    f.write("</div>")
        f.write("</div></div><br>")
        entryNumber += 1
        
    f.write('</body></html>')
    f.close()

    print "Exported to HTML output:", htmlOutputFileName
    
def main():
    parser = OptionParser()
    parser.add_option("-i", "--id", dest="handle", default="rohityadav89", help="Your Google Buzz Profile id/handle")
    parser.add_option("-n", "--nick", dest="nick", default="Rohit Yadav", help="Your Name")
    parser.add_option("-f", "--feedfile", dest="fileName", default="", help="Specify a xml feed file as input")
    parser.add_option("-o", "--htmlfile", dest="outputFileName", default="", help="Output xml feed file")
    parser.add_option("-d", dest="download", action="store_true", default=False, help="Enable to fetch the feed. Default to use fetched file.")
    parser.add_option("-e", dest="export", action="store_true", default=False, help="Enable to parse a pre-fetched xml feed file.")
    (options, args) = parser.parse_args()

    handle = options.handle
    nick = options.nick
    if options.fileName == "":
        fileName = "buzzackup-%s.xml" % handle

    if options.outputFileName == "":
        htmlOutputFileName = "buzzout-%s.html" % handle

    if options.download:
        importBuzzFeed(handle, fileName)

    if options.export:
        exportHtmlFeed(fileName, htmlOutputFileName, handle, nick)

if __name__ == '__main__':
    main()
