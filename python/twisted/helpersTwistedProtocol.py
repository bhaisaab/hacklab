from twisted.internet import reactor, protocol
from twisted.protocols.basic import LineReceiver

class WebProtocol(LineReceiver):
  def dataReceived(self, data):
    print data
  def connectionMade(self):
    self.transport.write("HEAD / HTTP/1.0\r\n")
    self.transport.write("Host: localhost\r\n\r\n")

class ClientFactory(protocol.ClientFactory):
  protocol = WebProtocol
  def clientConnectionFailed(self, connector, reason):
    print reason.getErrorMessage()
    reactor.stop()

reactor.connectTCP('localhost', 80, ClientFactory())
reactor.run()
