import time
import sys

import stomp

class MyListener(object):
    def on_error(self, headers, message):
        print 'received an error %s' % message

    def on_message(self, headers, message):
        print 'received a message %s' % message

conn = stomp.Connection()
# set_listner for python 3.x, add_listner for 2.5+
conn.add_listener(MyListener())
conn.start()
conn.connect()

conn.subscribe(destination='/queue/test', ack='auto')

conn.send('hello '.join(sys.argv[1:]), destination='/queue/test')

time.sleep(2)
conn.disconnect()
