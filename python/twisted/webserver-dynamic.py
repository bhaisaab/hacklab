from twisted.web.server import Site
from twisted.web.resource import Resource
from twisted.internet import reactor
from twisted.web.static import File
import sys
import cgi

class formatResponse(Resource):
  def __init__(self, url):
    Resource.__init__(self)
    self.url = cgi.escape(url)
  def render_GET(self, request):
    return "You passed in url:\r\n %s" % (self.url)
  def getChild(self, url, request):
    print "getChild asked for: ", url
    return formatResponse(self.url + '/' + url)


class myResource(Resource):
  def getChild(self, url, request):
    return formatResponse(url)

root = myResource()
root.putChild("", File(sys.argv[0]))

factory = Site(root)

reactor.listenTCP(8080, factory)
reactor.run()
