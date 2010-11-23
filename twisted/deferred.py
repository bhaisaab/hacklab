from twisted.internet import reactor, defer

class doMath:
  def defer_add(self, a, b):
    try:
      self.deferred_obj.callback(float(a) + float(b))
      try:
        self.deferred_obj.callback(10+90)
      except Exception as e:
        print "err=", e
    except ValueError as v:
      self.deferred_obj.errback(v)
    print "out of def fun()"

  def add(self, a, b):
    self.deferred_obj = defer.Deferred()
    reactor.callLater(2, self.defer_add, a, b)
    return self.deferred_obj

def genO(result):
    print "hey ya: ", result

def genE(failure):
    print "ooooops: ", failure

dm = doMath()

d = dm.add(10, 100)
d.addCallback(lambda r: r+30.0)
d.addCallback(genO).addErrback(genE)

reactor.callLater(10, reactor.stop)
reactor.run()
