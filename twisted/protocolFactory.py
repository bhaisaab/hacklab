from twisted.internet import reactor, protocol

class SomeProtocol(protocol.Protocol):
  def dataReceived(self, data):
    print data
    reactor.stop()
  def connectionMade(self):
    self.transport.write("HEAD / HTTP/1.0\r\n")
    self.transport.write("Host: localhost\r\n\r\n")

class ProtoFactory(protocol.ClientFactory):
  protocol = SomeProtocol
  def clientConnectionFailed(self, connector, reason):
    print reason.getErrorMessage()
    reactor.stop()

# connecting to my apache server on localhost :)
reactor.connectTCP("localhost", 80, ProtoFactory())
reactor.run()
