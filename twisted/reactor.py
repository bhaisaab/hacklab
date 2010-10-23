from twisted.internet import reactor
import time

count = 0

def funct(i, j):
  print time.strftime("%H-%M-%S"), " i= ", i, " j= ", j
  global count
  count += 1
  if count <= 10:
    reactor.callLater(1, funct, i*10, j)
  else:
    reactor.stop()
  print "out: ", i, " c = ", count

reactor.callLater(1, funct, 1, 2)
reactor.run()

print "Over!"
