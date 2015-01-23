#!/usr/bin/env python
# baagichhaap: Takes your decent photo and makes it Baagi!
# dependency: webpy, opencv
# example deployment using nginx and fcgi gateway: spawn-fcgi -d /var/www/baagi.org/chhaap/ -f /var/www/baagi.org/chhaap/index.py -a 127.0.0.1 -p 9000
# author: bhaisahab

import web, os
from baagime import detectObjects

urls = ('/', 'Upload', '/remove/(.*)', 'Remove')
static_dir = './static/'
web.config.debug = True

class Upload:
  def GET(self):
    if not os.path.exists(static_dir):
      os.mkdir(static_dir)

    imgList = ""
    for img in os.listdir(static_dir):
      imgList += """<a href='/static/%s' ><img width='400' src='/static/%s'/></a>
                    <a href='/remove/?filename=%s'><strong>delete-me</strong></a><br>""" % ((img,) * 3)

    web.header("Content-Type", "text/html; charset=utf-8")
    return """<html><head></head><body>
              <p><a href="https://github.com/baagi/baagichhaap">BaagiChhaap</a>
              (small files with no spaces in the filename and no obscene photos please :)</p>
              <form method="POST" enctype="multipart/form-data" action="">
              <input type="file" name="baagipic" />
              <br><input type="submit" value="BaagiChhaap Me!"/>
              </form>%s</body></html>""" % (imgList)

  def POST(self):
    webinputs = web.input(baagipic={})
    if 'baagipic' in webinputs:
      filepath = webinputs.baagipic.filename.replace('\\', '/')
      filename = filepath.split('/')[-1]
      fout = open(static_dir + filename, 'w')
      fout.write(webinputs.baagipic.file.read())
      fout.close()
      detectObjects(static_dir + filename)
    raise web.seeother('/')

class Remove:
  def GET(self, filename):
    try:
      os.remove('./static/' + web.input()['filename'])
      result_str = "Deleted file: %s" % web.input()['filename']
    except:
      result_str = "No such filename found!"
    return """<html><body>%s, <a href='/'>go back</a>
              </body></html>""" % result_str

if __name__ == "__main__":
  app = web.application(urls, globals()) 
  web.wsgi.runwsgi = lambda func, addr=None: web.wsgi.runfcgi(func, addr)
  app.run()

