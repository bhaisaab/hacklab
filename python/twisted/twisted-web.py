from twisted.internet import protocol, reactor, defer
from twisted.web.client import getPage
from twisted.protocols.basic import LineReceiver

class Protocol(LineReceiver):
    def connectionMade(self):
        self.transport.write('enter url: ')
        
    def lineReceived(self, line):
        print "Got: ", line
        d = self.factory.getPage(line.strip())
        d.addCallback(self._writeOut).addErrback(self._errOut)

    def _writeOut(self, line):
        print "Writing: ", line
        self.transport.write(line)
        self.transport.loseConnection()
        
    def _errOut(self, result):
        self.transport.write('404: %s\r\n' % (result.getErrorMessage(),))
        self.connectionMade()

class Factory(protocol.ServerFactory):
    protocol = Protocol
    def getPage(self, page):
        return getPage(page)

def startServer():
    reactor.listenTCP(50000, Factory())
    reactor.run()

if __name__=='__main__':
    startServer()
