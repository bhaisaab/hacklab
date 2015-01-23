#!/usr/bin/env python
##############################################################################
# buzzackup - google buzz backup tool
# author: rohityadav, hack'd just before `rm buzz-account` ];] buzz s**ks
# notes: ain't elegant, just one night's hacking, enjoy!
# help: python buzzackup.py --help
###############################################################################

import xml.etree.ElementTree as ET
from django.utils.encoding import smart_str
from calendar import month_name
from common import readFeed, readFeedFromFile, namespace, namespace_thr, namespace_likers, namespace_buzz, namespace_activity, apiPrefix, backupLogFile

def exportHtmlFeed(directory, htmlOutputFileName):
    f = open(htmlOutputFileName, 'w')
    f.write("<html><head><meta http-equiv=Content-Type content=\"text/html; charset=UTF-8\">")
    f.write("<link rel=\"stylesheet\" href=\"buzzout.css\" type=\"text/css\" media=\"screen\" />")

    log = open(directory + backupLogFile, 'r')
    info = log.readline().split(', ')

    offset = 0
    handle = info[0]
    fileCount = int(info[1])
    fileCounter = 0
    nick = info[2]
    totalEntries = int(info[3][:-1])

    f.write("<title>Buzzackup of %s<title></head><body>" % nick)
    f.write("<h1>Buzz by %s {%d}!</h1>" % (nick, totalEntries))

    print "Crawling Google network for buzz feeds...\nFound %d buzz posts for %s" % (totalEntries, nick)
    print "Processing buzz feed..."

    while fileCounter < fileCount:
        feedFile = directory + 'buzzackup-%s-%d.xml' % (handle, fileCounter)
        data = readFeedFromFile(feedFile)
        entries = ET.XML(data).findall(namespace + "entry")
        processFeeds(f, entries, offset, totalEntries)
        offset += len(entries)
        fileCounter += 1
    f.write('</body></html>')
    f.close()

    print "Exported to HTML output:", htmlOutputFileName
    
def processFeeds(f, entries, offset, totalEntries):
    entryNumber = 0
    for entry in entries:
        #Buzz post starts        
        f.write("<div class=\"buzz\">")
        
        #Process post date
        entryDate = entry.findall(namespace + 'updated')[0].text.split('T')[0].split('-')
        prettyDate = "%s %s %s " % (entryDate[2], month_name[int(entryDate[1])], entryDate[0])
        f.write("<div class=\"postdate\"><b>" + prettyDate + "</b></div>")

        #Process post content
        post = entry.findall(namespace + 'content')[0].text
        f.write("<div class=\"post\">" + smart_str(post) + "</div>")
        
        #Process attachments
        f.write("<div class=\"attachments\">")
        attachments = entry.findall(namespace_activity + 'object')[0].findall(namespace_buzz + 'attachment')

        for attachment in attachments:
            if attachment.findall(namespace + 'title'):
                title = attachment.findall(namespace + 'title')[0].text + "<br>"
            else: title = ""
            if attachment.findall(namespace + 'content'):
                content = attachment.findall(namespace + 'content')[0].text
            else: content = ""
            href = ""
            links = attachment.findall(namespace + 'link')
            for link in links:
                if link.get('rel') == 'alternate':
                    href = link.get('href')
            f.write("<div class=\"attachment\"><b><a href=\"%s\">%s</a></b>%s</div>" % (href, smart_str(title), smart_str(content)))
        f.write("</div")
        #Process Links
        postId = entry.findall(namespace + 'id')[0].text
        links = entry.findall(namespace + 'link')
        f.write("<div class=\"links\">")

        #Process likers feed
        for link in links:
            if link.get('rel') == (namespace_buzz[1:-1] + '#liked'):
                likeFeedUrl = 'http' + link.get('href')[5:] + '&max-results=100&bhu'
                rawLikedFeed = readFeed(likeFeedUrl)
                likersTree = ET.XML(rawLikedFeed)
                likeCounter = 0
                totalLikes = link.get(namespace_buzz + 'count')
                if int(totalLikes) != 0:
                    f.write("<div class=\"likers\"><strong>Liked by</strong> [%s]: " % totalLikes)
                    likers = likersTree.findall(namespace_likers + 'entry')
                    for liker in likers:
                        likerName = liker.findall(namespace_likers + 'displayName')[0].text
                        likerUri = liker.findall(namespace_likers + 'profileUrl')[0].text
                        f.write("<a href=\"%s\">%s</a>" % (likerUri, smart_str(likerName)))
                        likeCounter += 1
                        if likeCounter != len(likers):
                            f.write(", ")
                    f.write("</div>")
 
        #Process comment feed
        for link in links:
            if link.get('rel') == 'replies':
                replyCount = link.get(namespace_thr + 'count')
                if int(replyCount) != 0:
                    f.write("<div style=\"color:#111;\" class=\"comments\"><b>Comments(%s)</b><br>" % replyCount)
                    replyFeedUrl = 'http' + link.get('href')[5:] + '&bhu'
                    rawReplyFeed = readFeed(replyFeedUrl)
                    comments = ET.XML(rawReplyFeed).findall(namespace + 'entry')
                    for comment in comments:
                        f.write("<div style=\"margin-left:20px;\" class=\"comment\">")
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
        print "Progress: (%d/%d) %d%%" % (entryNumber + offset, totalEntries, (entryNumber + offset) * 100 / totalEntries)
    
def testmain():
    htmlOutputFileName = "buzzout-%s.html" % 'rohityadav89'
    exportHtmlFeed("./backup/", htmlOutputFileName)

if __name__ == '__main__':
    testmain()
