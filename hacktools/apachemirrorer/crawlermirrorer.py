#This hack downloads directories served by apache
import re, os
import urllib, urllib2

baseUrl = ""

def readFeed(url):
  print "Requesting url", url
  if url != None:
    request = urllib2.Request(url);
    response = urllib2.urlopen(request)
    rawFeed = response.read()
    return rawFeed

def saveFile(fileName, url):
  f = open(fileName, 'w')
  rawFeed = readFeed(url);
  f.write(rawFeed)
  f.close()
  print "File saved in: %s" % fileName

data = readFeed(baseUrl)
urls = re.findall("""href="(.*?)">(.*?)/</a>""", data)

#mkdir first
for url in urls:
  print "Making dir", url[1]
  os.mkdir(url[1])

for url in urls:
  print "Processing", url[1]
  d = readFeed(baseUrl+url[0])
  suburls = re.findall("""href="(.*?)">(.*?)</a>""", d)[5:]
  for suburl in suburls:
    saveFile(url[1]+"/"+suburl[1], baseUrl+url[0]+suburl[0])
