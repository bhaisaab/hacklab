from twisted.web.server import Site
from twisted.web.resource import Resource
from twisted.internet import reactor
from twisted.web.static import File
import sys

root = Resource()
root.putChild("", File(sys.argv[0]))
factory = Site(root)
reactor.listenTCP(8080, factory)
reactor.run()
