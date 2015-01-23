import tornado.httpserver, tornado.ioloop, tornado.options, tornado.web, os.path, random, string
from tornado.options import define, options

define("port", default=4444, help="run on the given port", type=int)

class Application(tornado.web.Application):
    def __init__(self):
        handlers = [
            (r"/", IndexHandler),
            (r"/upload", UploadHandler),
            (r"/p", GetPatchHandler)
        ]
        tornado.web.Application.__init__(self, handlers)
        
class IndexHandler(tornado.web.RequestHandler):
    def get(self):
        self.render("upload_form.html")

class GetPatchHandler(tornado.web.RequestHandler):
    def get(self):
        if os.path.exists('p/'+self.get_argument('id')):
            self.set_header ('Content-Type', 'application/force-download')
            self.set_header ('Content-Disposition', 'attachment; filename='+self.get_argument('id')+'-cloudstack.patch')
            fp = open('p/'+self.get_argument('id'))
            data = fp.read()
            fp.close()
            self.write(data)
        else:
            self.write("Patch does not exist.<br>Valid ids:<br>" + '<br>'.join(os.listdir('p/')))

class UploadHandler(tornado.web.RequestHandler):
    def post(self):
        pcontent = self.get_argument('content')
        fname = ''.join(random.choice(string.ascii_lowercase + string.digits) for x in range(6))
        output_file = open("p/" + fname, 'w')
        output_file.write(pcontent)
        output_file.close()
        self.finish("http://patchbin.baagi.org/p?id=" + fname)
        
def main():
    http_server = tornado.httpserver.HTTPServer(Application())
    http_server.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()
    
if __name__ == "__main__":
    main()
