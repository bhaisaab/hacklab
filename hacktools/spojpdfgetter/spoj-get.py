# Social Network Profile crawler and data miner
# Author: Rohit Yadav <rohityadav89 AT gmail.com>
# One of my original awesome hacks :) Logins inside a social networking site,
# crawls the profiles based on some rule and saves the pages and logs out.
# Next data miner for some information, exports as a CSV file for using with
# spreadsheet program.

import re, os
import urllib2

links = []

start = 0
add = 50
while start <= 2000:
  url = 'http://www.spoj.pl/problems/classical/sort=0,start=%d' % start
  print url
  p = urllib2.urlopen(url)
  start+=add
  data = p.read()
  results = re.findall("""<a href="/problems/[A-Z]*/">&nbsp;<b>""", data)
  for result in results:
    links.append( 'http://www.spoj.pl' + re.findall("""/problems/[A-Z]*/""", result)[0][:-1] + '.pdf' )

f = open('links.txt', 'w')
for link in links:
  f.write('%s\n' % link)
f.close()

#in shell do:
#q=`cat links.txt`
#for l in $q; do wget $l; done;
