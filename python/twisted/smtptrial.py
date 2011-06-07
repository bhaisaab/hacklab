from twisted.mail import smtp
from twisted.internet import reactor
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

import sys

msg = MIMEMultipart('alternative')
msg['Subject'] = 'bla bla'
msg['From'] = 'Rohit<rohit@localhost>'
msg['To'] = 'Rohit <rohit@hotbuffer.com>'
f = 'bob@example.com'
t = ['joe@example.com']
html='''<html><body> Yo man wasssup...</body></html>'''
msg.attach( MIMEText(html, 'html') )

def ehandler(error):
    print >> sys.stderr, error.getErrorMessage()
    reactor.stop

def shandler(tup):
    print tup
    reactor.stop()

smtp_client = smtp.sendmail('smtp example.com', f, t, msg.as_string())
smtp_client.addCallback(shandler).addErrback(ehandler)
reactor.run()
