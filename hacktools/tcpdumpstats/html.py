#!/usr/bin/env python
# coding: utf-8
import os, sys, datetime, time
import sqlite3 as sql

now = datetime.datetime.now()

def size(s):
  return '%0.4F' % (s/(1024.0*1024.0))

stats_html = '/var/www/stats/index.html'
dbms_file = "/usr/bin/ntopper/ips.sqlite3"

con = sql.connect(dbms_file)
try:
  cur = con.cursor()
  cur.execute("SELECT * FROM Users")
  data = cur.fetchall()
except sql.Error, e:
  print "SQLite3.x Error: %s" % e.args[0]
  sys.exit(1)
finally:
  if con:
    con.close()

users = {}
localUserCount = 0
for row in data:
  if row[0][:3] == "10.": localUserCount += 1
  users[str(row[0])] = {'up':row[1], 'down':row[2]}
sent = 0
received = 0
userrows = ""

def getHostel(key):
  hostels = {'10.18': "Shivalik Hostel", '10.17': "Vindhyachal Hostel", '10.15': "Girl Hostel", '10.14': "Boys Hostel-2", '10.11': "Admin Block", '10.13': "KVK", '10.12': "Mushroom Block", '10.19': "Library", '10.20': "Tissue Culture", '10.16': "Lecture Theatre", '10.23': "Guest House", '10.24': "Scientific Hostel", '10.21': "Professor Colony", '10.22': "Health Center"}
  if key[:3] == "10.":
    return hostels[key[:5]]
  else:
    return ""

for key in users.keys():
  sent += users[key]['down']
  received += users[key]['up']
  hostelName = getHostel(key)
  userrows += "<tr><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr>" % (key, hostelName, size(users[key]['down']), size(users[key]['up']))

userdata = """<table id="userstats" cellpadding="0" cellspacing="0" border="0" class="table table-striped table-bordered">
<thead>
<tr>
  <th>IP</th>
  <th>Location</th>
  <th>Download (MB)</th>
  <th>Upload (MB)</th>
</tr></thead>
<tbody>%s</tbody></table>""" % (userrows)

html = """
<!DOCTYPE html>
<html lang="en">
<head>

<meta http-equiv="content-type" content="text/html; charset=utf-8" />
<title>Traffic Stats</title>
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
      "aaSorting": [[ 2, "desc" ]],
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
          <a class="brand" href="#">BHU RGSC powered by WMG</a>
          <div class="nav-collapse">
            <ul class="nav">
              <li><a href="/stats/"></a></li>
            </ul>
          </div><!--/.nav-collapse -->
        </div>
      </div>
    </div>

<div class="container" align="center">
<br>
<h1>Traffic Stats</h1>
<h3>Last updated on: %s</h3>
<p>x-axis: time in hours | y-axis: number of active users at that hour</p>
<h3>%s MB downloaded | %s MB uploaded | 10 MBps ∑bandwidth</h3>
<h3>%ld local IPs</h3>
%s
<br>
<footer>
  <p>Maintained by WMG, IT-BHU</p>
</footer>
<br>
</div>
</body></html>""" % (now.ctime(), size(sent), size(received), localUserCount, userdata)

f = open(stats_html, 'w')
f.write(html)
f.close()
