# sudo aptitude install python-xmpp python-dnspython
import xmpp
 
# Google Talk constants
FROM_GMAIL_ID = "your-id@gmail.com"
GMAIL_PASS = "put-your-pass-here"
GTALK_SERVER = "gmail.com"
 
jid=xmpp.protocol.JID(FROM_GMAIL_ID)
C=xmpp.Client(jid.getDomain(),debug=[])

if not C.connect((GTALK_SERVER,5222)):
    raise IOError('Can not connect to server.')

print '[1] Connect to jabber server'

if not C.auth(jid.getNode(),GMAIL_PASS):
    raise IOError('Can not auth with server.')

print '[2] Auth ok'

C.sendInitPresence(requestRoster=1)

def myPresenceHandler(con, event):
   if event.getType() == 'unavailable':
     print event.getFrom().getStripped()
 
C.RegisterHandler('presence', myPresenceHandler)
while C.Process(1):
  pass
