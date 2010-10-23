# To start and daemonize the app, log to twistd.log: twistd -y <tac-file>
# To start, not daemonize and log output to cmd: twistd -noy <tac-file>
from twisted.application import internet, service
import webx

application = service.Application('Example-HTTP-Server')

svc = internet.TCPServer(8080, webx.factory)
svc.setServiceParent(service.IServiceCollection(application))
