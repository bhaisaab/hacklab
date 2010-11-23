''' To test inject config injection capabilities
WSGI inject middleware  example, requires Python 2.5+.
Run and then open http://127.0.0.1:8000/ in a browser.
'''

import inject
from inject.middleware import WsgiInjectMiddleware
from wsgiref.simple_server import make_server

class Config(object):       
    def __init__(self):
        # Just to demostrate application scope.
        self.title = 'my web app testing @inject'
        self.version = '0.1'
# The configuration will be instantiated
# only once, when injected.
Config = inject.appscope(Config)

class Controller(object):
    @inject.param('config', Config)
    def body(self, config):
        return 'This is %s, v.%s.' % (config.title, config.version)
# The controller will be instantiated only
# once per request, when injected.
Controller = inject.reqscope(Controller)

class Controller2(Controller):  # Inherits the default scope.
    def header(self):
        return 'Hello, World!'

    def footer(self):
        return 'Bye.'

class MyApp(object):
    def __call__(self, environ, start_response):
        start_response('200 OK', [('Content-Type','text/html')])
        yield self.header()
        yield '<br />'
        yield self.body()
        yield '<br />'
        yield self.footer()
        yield '<br />'

    @inject.param('controller', Controller2)
    def header(self, controller):
        return controller.header()

    @inject.param('controller', Controller2)
    def body(self, controller):
        return controller.body()

    @inject.param('controller', Controller2)
    def footer(self, controller):
        return controller.footer()

myapp = MyApp()
myscopedapp = WsgiInjectMiddleware(myapp)

httpd = make_server('', 8000, myscopedapp)
print 'Sample HTTP server on port 8000...'
httpd.serve_forever()
