var http = require('http');
var os = require('os');
var ifaces = os.networkInterfaces();
var myips = "";

Object.keys(ifaces).forEach(function (ifname) {
  var alias = 0;

  ifaces[ifname].forEach(function (iface) {
    if ('IPv4' !== iface.family || iface.internal !== false) {
      return;
    }

    if (alias >= 1) {
      myips += " " + ifname + ":" + alias + " :: " + iface.address;
    } else {
      myips += " " + ifname + " :: " + iface.address;
    }
    ++alias;
  });
});

var handleRequest = function(request, response) {
  console.log('Received request for URL: ' + request.url);
  response.writeHead(200);
  response.end('Hello Giles! internal info: ' + myips);
};
var www = http.createServer(handleRequest);
www.listen(8080);
