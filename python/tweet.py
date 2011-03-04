#!/usr/bin/python

# Tweet using this app :D
# Author: Rohit Yadav
# Usage: tweet <password> <msg>


import urllib.request
import sys

def tweet(msg, username, password):
  password_manager = urllib.request.HTTPPasswordMgr()
  password_manager.add_password("Twitter API", "http://twitter.com/statuses", username, password)
  http_handler = urllib.request.HTTPBasicAuthHandler(password_manager)
  page_opener = urllib.request.build_opener(http_handler)
  urllib.request.install_opener(page_opener)
  params = urllib.parse.urlencode( {'status': msg} )
  resp = urllib.request.urlopen("http://twitter.com/statuses/update.json", params)
  resp.read()

tweet( sys.argv[2], 'vadaytihor', sys.argv[1] )

