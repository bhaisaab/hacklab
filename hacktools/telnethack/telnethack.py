# Telnet Over HTTP by Rohit Yadav <rohityadav89@gmail.com>
# Pwns switches like the admins can take away our Internet freedom, thanks pk for the hint... 
# This is not a hack, just re-routing of HTTP reqs :)

import sys, string, time
import SocketServer
import telnetlib
import socket
import base64

command_prompt = ">"
t = telnetlib.Telnet()
host = "10.1.1.2" # The switch we want to piggyback on :)
passwd = "cmc"
timeout = 15
proxyAuth = "Proxy-Authorization: Basic %s\r\n\r\n" % base64.encodestring("itp127:itp127")

class HttpOverTelnetHandler(SocketServer.StreamRequestHandler):
  def handle(self):
    reqs = self.rfile.readline().strip().split('\r\n')
    http_req = ""
    for req in reqs:
      if not "Accept" in req: # Ugly hack to fix Firefox guts
        http_req += (req + '\r\n')
    global proxyAuth
    http_req += proxyAuth  # Base64 auth :P
    self.data = http_req
    print "%s requesting URI: %s" % (self.client_address[0], reqs[0])
    http_data = telnet_tunnel(self.data)
    if len(http_data) == 0:
      print "Error, unable to load [%s]: %s" % (time.ctime(), reqs[0])
      self.request.send("Oops Error! Contact rohit. \nServer time: %s\n" % time.ctime())
    else:
      self.wfile.write(http_data)

def telnet_tunnel(request):
  global t, command_prompt, host, passwd, timeout
#  sock = t.get_socket()

  t.write("telnet 10.1.1.10 80 /noecho /quiet\n") # Pwn proxy4 ;)
  response = t.read_until("\n", timeout)

  t.write(request)
  response = t.read_until(command_prompt, timeout)[:-len(command_prompt)]
  return response

def telnet_init():
  global t, command_prompt, host, passwd, timeout
  t.open(host)
  passwd_prompt = "Password: "
  response = t.read_until(passwd_prompt, timeout)
  if not string.count(response, passwd_prompt):
    print "Password error!"
    sys.exit()
  t.write(passwd + "\n")
  response = t.read_until(command_prompt, timeout)
  if not string.count(response, command_prompt):
    print "Login error!"
    return 0
  print response
  command_prompt = response # We're in!

def main():
  print "Http Over Telnet! Thanks to pk for the hint.\nAuthor: Rohit Yadav\n"
  HOST, PORT = "localhost", 9090
  server = SocketServer.TCPServer((HOST, PORT), HttpOverTelnetHandler, False)
  server.allow_reuse_address = True # Prevent 'cannot bind to address' errors on restart
  server.server_bind()     # Manually bind, to support allow_reuse_address
  server.server_activate() # (see above comment)
  telnet_init()
  server.serve_forever()
 
if __name__ == "__main__":
  main()

