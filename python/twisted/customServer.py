from twisted.internet import protocol, reactor
from twisted.protocols.basic import LineReceiver

class MyProtocol(LineReceiver):
  def connectionMade(self):
    self.factory.connection_count += 1
    self.transport.write('Welcome to Z0rk server: %d!\r\n' % self.factory.connection_count)
  def lineReceived(self, line):
    self.transport.write('Thanks you for your: %s\r\n' % line)
    self.transport.loseConnection()
  def connectionLost(self, reason):
    self.factory.connection_count -= 1
    print reason.getErrorMessage()
    #reactor.stop()

class MyFactory(protocol.ServerFactory):
  protocol=MyProtocol
  connection_count=0

reactor.listenTCP(50000, MyFactory())
reactor.run()
