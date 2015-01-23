# Light weight, asynchronous proxy server that plays with requested URL
# Better than the Squid3/url-rewriter hack most use :)
# Cheers, Rohit Yadav <rohityadav89@gmail.com>
#!/usr/bin/env python

import sys
import urlparse
from twisted.web import proxy, http
from twisted.internet import reactor
from twisted.python import log
log.startLogging(sys.stdout)

class BHUProxyRequest(proxy.Request):
    proxyURI = "10.5.41.2"
    proxyPort = 8080
    def __init__(self, channel, queued, reactor=reactor):
        http.Request.__init__(self, channel, queued)
        self.reactor = reactor
    def process(self):
        if not 'https' in self.uri[:6]:
            if "?" in self.uri: rest = self.uri + "&bhu"
            else: rest = self.uri + "?bhu"
        else: rest = self.uri
        host = urlparse.urlparse(self.uri)[1]
        headers = self.getAllHeaders().copy()
        if 'host' not in headers:
            headers['host'] = host
        self.content.seek(0, 0)
        s = self.content.read()
        clientFactory = proxy.ProxyClientFactory(self.method, rest, self.clientproto, headers, s, self)
        self.reactor.connectTCP(self.proxyURI, self.proxyPort, clientFactory)

class BHUProxy(http.HTTPChannel):
    requestFactory = BHUProxyRequest

class ProxyFactory(http.HTTPFactory):
    #protocol = proxy.Proxy # for simple proxy
    protocol = BHUProxy
 
reactor.listenTCP(8080, ProxyFactory())
reactor.run()
