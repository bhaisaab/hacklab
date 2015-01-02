#!/usr/bin/env python

import couchdb
import tornado.auth
import tornado.escape
import tornado.ioloop
import tornado.options
import tornado.web
import os, time, sys

server = None
db = None

class MainHandler(tornado.web.RequestHandler):
  def get(self):
    self.render("index.html", currentDate=time.strftime("%Y-%m-%d"))

class SearchHandler(tornado.web.RequestHandler):
  def get(self):
    #res = "%s %s %s %s %s" % (self.get_argument("emails"), self.get_argument("date"), self.get_argument("duration"), self.get_argument("start_time"), self.get_argument("city"))
    #print "yo", res
    #global db
    #code = """function(doc){ if (doc.date == %s && doc.time == %s) { map([doc.date,doc.time], doc); } }""" % (self.get_argument("date"), self.get_argument("start_time"))
    #results = db.query(code)
    #print results
    self.write("""[{text:"Amy",grade:5},{text:"Angeline",grade:26}]""")

  def post(self): pass

def initDB():
  global server, db
  server = couchdb.Server() # Default localhost:5984, firewalled
  try:
    db = server.create("bootcamp")
  except Exception:
    db = server["bootcamp"]

if __name__ == "__main__":
  #initDB()
  settings = dict(
    static_path = os.path.join(os.path.dirname(__file__), "static"),
    template_path = os.path.join(os.path.dirname(__file__), "templates")
  )
  application = tornado.web.Application(
    [
      (r"/", MainHandler),
      (r"/search", SearchHandler),
    ], **settings
  )
  application.listen(6969)
  tornado.ioloop.IOLoop.instance().start()
