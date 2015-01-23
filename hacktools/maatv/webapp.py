#!/usr/bin/env python

import tornado.ioloop
import tornado.web
from linkextractor.py import *

class IndexHandler(tornado.web.RequestHandler):
    def get(self):
        self.write(genSerialIndexHtml())

class SerialHandler(tornado.web.RequestHandler):
    def get(self):
        serial = self.get_argument("serial",None)
        self.write(getEpisodeList(serial))

class VideoHandler(tornado.web.RequestHandler):
    def get(self):
        episode = self.get_argument("episode",None)
        self.write(getVideoEmbeds(episode))

application = tornado.web.Application([
    (r"/", IndexHandler),
    (r"/episodes", SerialHandler),
    (r"/watch", VideoHandler)
])

if __name__ == "__main__":
    application.listen(8888)
    tornado.ioloop.IOLoop.instance().start()
