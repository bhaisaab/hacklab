import time
import sys

import stomp

class MyListener(object):
    def on_error(self, headers, message):
        print 'received an error %s...' % message

    def on_message(self, headers, message):
        print 'received a message %s...' % message

conn = stomp.Connection()
# set_listner for python 3.x, add_listner for 2.5+
conn.add_listener(MyListener())
conn.start()
conn.connect()

conn.subscribe(destination='/queue/vmc', ack='auto')

conn.send("yoyo-wassup", destination='/queue/vmc')

time.sleep(3)
conn.disconnect()
