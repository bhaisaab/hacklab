import netifaces

for interface in netifaces.interfaces():
  print "INFO for ", interface,":\n", netifaces.ifaddresses(interface), "\n\n"
