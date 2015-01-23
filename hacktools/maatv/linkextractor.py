import re, os
import urllib, urllib2, cookielib
from BeautifulSoup import BeautifulSoup

base_url="http://www.apnicommunity.com/india-forum/"

def readFeed(url):
  if url != None:
    request = urllib2.Request(url)
    try:
      response = urllib2.urlopen(request)
    except urllib2.URLError, e:
      return ""
    except urllib2.HTTPError, e:
      return ""
    rawFeed = response.read()
    return rawFeed

def getSerialList(url):
  data = readFeed(url)
  links = re.findall("""<a href="http://www.apnicommunity.com/[a-zA-z0-9_-]*/">[a-zA-Z 0-9-_,&@'".<>#=]*</a>""", data)
  soup = BeautifulSoup("".join(links))
  anchors = soup.findAll('a', href=True)
  return anchors

def genSerialIndexHtml():
  global base_url
  page = """<html><body><center>%s</center></body></html>"""
  body_html = ""
  anchors = getSerialList(base_url)
  goFlag = True
  for link in anchors:
    if goFlag:
      if "Star Plus" in link: goFlag = False
    else:
      body_html += ("<h3><a href='/episodes?serial=%s'>%s</a></h3>" % (link['href'], link.text))
  page = page % body_html
  return page

def getEpisodeList(url):
  html = readFeed(url)
  soup = BeautifulSoup(html)
  anchors = soup.findAll('a', href=True)
  page = """<html><body><center>%s</center></body></html>"""
  body_html = ""
  for a in anchors:
    if a.text != "" and ('watch' in a.text or 'Watch' in a.text) and a.has_key('class') and url in a['href']:
      body_html += ("<h2><a href='/watch?episode=%s'>%s</a></h2><br>" % (a['href'], a.text))
  return page % body_html

def processVideoLink(url):
  html = readFeed(url)
  soup = BeautifulSoup(html)
  anchors = soup.findAll('embed')
  link = ""
  if len(anchors) > 0: link = anchors[0]['src'].split('?')[0]
  return link

def getVideoEmbeds(url):
  html = readFeed(url)
  soup = BeautifulSoup(html)
  anchors = soup.findAll('a', href=True)
  rawlinks = []
  for a in anchors:
    if a.text != "" and ('part' in a.text or 'Part' in a.text):
      processedLink = processVideoLink(a['href'])
      rawlinks.append({'href':processedLink, 'text':a.text})
  dailymotionLinks = []
  embed_html = """ <h3>%s</h3><br><object type="application/x-shockwave-flash" id="player01" data="%s" width="720" height="480"><param name="movie" value="%s"><param name="quality" value="high"><param name="bgcolor" value="#ffffff"></object><br> """
  all_embed = ""
  for r in rawlinks:
   if 'dailymotion' in r['href']:
     dailymotionLinks.append(r)
     all_embed += (embed_html % (r['text'], r['href'], r['href']))
  return """<html><body><center><h1><a href='%s'>View Actual Forum Post</a></h1><br>%s</center></body></html>""" % (url, all_embed)

