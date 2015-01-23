#!/usr/bin/env python
# coding: utf-8
try:
  import cPickle as pickle
except:
  import pickle

import datetime, time
now = datetime.datetime.now()

def parse(data, token="|"):
  return data.split(token)

def size(b):
  tag = 'B'
  if b/1024 > 0:
    b/=1024.0
    tag = 'KB'
  if b/1024 > 0:
    b/=1024.0
    tag = 'MB'
  if b/1024 > 0:
    b/=1024.0
    tag = 'GB'
  return "%0.6F %s" % (b, tag)

status_logfile = '/var/log/openvpn/status.log'
users_datafile = "/etc/openvpn/users.data"
users_offline_datafile = "/etc/openvpn/users-offline.data"
stats_logfile = '/var/log/openvpn/stats.log'
stats_html = '/var/www/html/stats.html'

f = open(status_logfile, 'r')
data = (f.read()).split('\n')
f.close()

#received is bytes received from clients, uploaded
#sent is bytes sent to clients, or downloaded
try:
  users_data = pickle.load(open(users_datafile, "rb"))
  users_offline = pickle.load(open(users_offline_datafile, "rb"))
except:
  print "Shucks, user loading failed"
  users = {}
#  users_offline = {}

users = {}
connected_users = 0
total_bandwidth = 0
for line in data:
  if line[:11] == "CLIENT_LIST":
    pdata = parse(line, ',')
    if pdata[1] == "UNDEF": continue
    connected_users += 1
    if pdata[1] in users:
      users[pdata[1]]['up'] += long(pdata[4])
      users[pdata[1]]['down'] += long(pdata[5])
    else:
      users[pdata[1]] = {'up': long(pdata[4]), 'down': long(pdata[5])}
    users[pdata[1]]['real_ip'] = (pdata[2]).split(":")[0]
    users[pdata[1]]['virt_ip'] = pdata[3]
    users[pdata[1]]['conn_since'] = pdata[6]
    users[pdata[1]]['bandwidth'] = ((long(pdata[5])+long(pdata[4]))/(time.time() - float(pdata[7])))/1024.0
    total_bandwidth += (8 * users[pdata[1]]['bandwidth'] * 1024)/1000000 #Mbits/s

users = dict(users_data.items() + users_offline.items() + users.items())

print "Users = ",  connected_users, len(users)
print "Total bandwidth is", total_bandwidth, " Mbps"

sent = 0
received = 0
userrows = ""

for key in users.keys():
  if key == "UNDEF": continue
  sent += users[key]['down']
  received += users[key]['up']
  if 'real_ip' in users[key].keys():
    userrows += "<tr><td>%s</td><td>%s</td><td>%s</td> <td>%F</td>  <td>%s</td><td>%s</td><td>%s</td></tr>" % (key, size(users[key]['down'])[:-3], size(users[key]['up'])[:-3], users[key]['bandwidth'], users[key]['real_ip'], users[key]['virt_ip'],users[key]['conn_since'])
  else:
    userrows += "<tr><td>%s</td><td>%s</td><td>%s</td><td></td><td></td><td></td><td></td></tr>" % (key, size(users[key]['down'])[:-3], size(users[key]['up'])[:-3])
  

userdata = """<table id="userstats" cellpadding="0" cellspacing="0" border="0" class="table table-striped table-bordered">
<thead>
<tr>
  <th>User</th>
  <th>Download (in GiB)</th>
  <th>Upload (in GiB)</th>
  <th>Avg. Bandwidth (in kiB/s)</th>
  <th>LAN IP</th>
  <th>VPN IP</th>
  <th>Connected since</th>
</tr></thead>
<tbody>%s</tbody></table>""" % (userrows)

if now.strftime("%M") == "00":
  print "Fetching new chart"
  new_stats = "%ld|%s|%s|%s\n" % (connected_users, now.strftime("%H:%M"), size(sent), size(received))
  f = open(stats_logfile, 'a+')
  f.write(new_stats)
  f.close()

  f = open(stats_logfile, 'r')
  data = (f.read()).split('\n')[:-1]
  f.close()
  if len(data) > 24:
    data = data[-24:]
    f = open(stats_logfile, 'w')
    f.write('\n'.join(data))
    f.write('\n')
    f.close()

  activity = ""
  labels = ""
  labels_pos = ""
  pos = 0
  total_pos = len(data)
  if total_pos > 1:
    delta = 23.0/(total_pos-1)
  else: delta = 0
  for line in data:
    pdata = parse(line)
    if pdata[0] == '': continue
    activity += "%s,"%pdata[0]
    labels += "%s|"%pdata[1]
    labels_pos += '%0.3f,'%(pos)
    pos+=delta

  def saveChart(url):
    import urllib2
    if url != None:
      request = urllib2.Request(url);
      response = urllib2.urlopen(request)
      rawData = response.read()
      f = open("/var/www/html/chart.png", 'w')
      f.write(rawData)
      f.close()

  chart_url = """http://chart.apis.google.com/chart?chxl=0:|%s&chxp=0,%s&chxr=0,0,23|1,0,2000&chxs=0,676767,11.5,0,lt,676767&chxt=x,y&chs=1000x200&cht=lc&chco=0080009F,008000BE&chds=0,100,0,2000&chd=t:0,0|%s&chg=25,50&chls=0.75|1.5&chma=|0,10&chm=o,008000,1,-1,6|b,00AA005D,0,1,0""" % (labels[:-1], labels_pos[:-1], activity[:-1])
  saveChart(chart_url)

html = """
<!DOCTYPE html>
<html lang="en">
<head>

<meta http-equiv="content-type" content="text/html; charset=utf-8" />
<title>VPN Stats</title>
<meta name="viewport" content="width=device-width, initial-scale=1.0">

<link rel="stylesheet" type="text/css" href="css/bootstrap.min.css">
<style>
  body {
    padding-top: 60px; /* 60px to make the container go all the way to the bottom of the topbar */
   }
</style>
<link rel="stylesheet" type="text/css" href="css/style.css"/>
<link rel="stylesheet" type="text/css" href="css/bootstrap-responsive.min.css">
<script type="text/javscript">

</script>
<script src="js/jquery.min.js"></script>
<script src="js/jquery.dataTables.min.js"></script>
<script src="js/bootstrap.min.js"></script>

<script type="text/javascript" charset="utf-8">
  /* Table initialisation */
  $(document).ready(function() {
    $('#userstats').dataTable( {
      "bPaginate": false,
      "aaSorting": [[ 3, "desc" ]],
      "sDom": "<'row'<'span12'f>r><'row'<'span12'i>t<'span6'p>>"
    } );
  } );
</script>

</head>
<body>

    <div class="navbar navbar-fixed-top">
      <div class="navbar-inner">
        <div class="container">
          <a class="btn btn-navbar" data-toggle="collapse" data-target=".nav-collapse">
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </a>
          <a class="brand" href="#">ITBHU VPN Service</a>
          <div class="nav-collapse">
            <ul class="nav">
              <li><a href="/">Home</a></li>
              <li class="active"><a href="/stats.html">Stats</a></li>
            </ul>
          </div><!--/.nav-collapse -->
        </div>
      </div>
    </div>

<div class="container" align="center">
<h1>VPN Stats: %s</h1>
<h3>Last updated on: %s</h3>
<img src="chart.png" width="1000" height="200" alt="" />
<p>x-axis: time in hours | y-axis: number of active users at that hour</p>
<h3>%s downloaded | %s uploaded | %0.3F Mbps momentary ∑bandwidth</h3>
<h3>%ld/%ld active users</h3>
%s
<br>
<footer>
  <p>Maintained by WMG, IT-BHU</p>
</footer>
<br>
</div>
</body></html>""" % (now.strftime("%d/%m/%Y"), now.ctime(), size(sent), size(received), total_bandwidth, connected_users, len(users), userdata)

f = open(stats_html, 'w')
f.write(html)
f.close()

print "Total connected users", connected_users, "/", len(users)

if now.strftime("%H%M") == "0000":
  for logfile in ["/var/log/openvpn/disconnect.log", "/var/log/openvpn/connect.log"]:
    f = open(logfile, 'w')
    f.write("")
    f.close()

  new_users = {}
  for key in users.keys():
    new_users[key] = {'up': 0, 'down': 0}
  pickle.dump(new_users, open(users_datafile, "wb"))
else:
  new_users = {}
  for key in users.keys():
    new_users[key] = {'up': users[key]['up'], 'down': users[key]['down']}
  #print new_users
  pickle.dump(new_users, open(users_datafile, "wb"))
