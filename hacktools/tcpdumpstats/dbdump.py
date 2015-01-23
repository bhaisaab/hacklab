#!/usr/bin/env python
# coding: utf-8

import sqlite3 as sql
import os, sys

try:
  ipIndex = sys.argv.index('IP')
except:
  sys.exit()

if ipIndex > 0:
  srcIp = '.'.join(sys.argv[ipIndex+1].split('.')[:4]).split(':')[0]
  dstIp = '.'.join(sys.argv[ipIndex+3].split('.')[:4]).split(':')[0]
  length = long(sys.argv[sys.argv.index('length')+1])
else:
  sys.exit()

up, down = 0, 0

if srcIp[:3] == "10." and dstIp[:3] == "10.":
  sys.exit()
if srcIp[:3] == "10.":
  up = length
elif dstIp[:3] == "10.":
  down = length

dbms_file = "/usr/bin/ntopper/ips.sqlite3"

createTable = False
if not os.path.exists(dbms_file):
  createTable = True

con = sql.connect(dbms_file)
try:
  cur = con.cursor()
  if createTable:
    cur.execute("CREATE TABLE Users(ip text primary key, up integer, down integer)")
  for cip in (srcIp, dstIp):
    cur.execute("SELECT * FROM Users WHERE ip='%s'" % cip)
    row = cur.fetchone()
    if row:
      up += long(row[1])
      down += long(row[2])
      cur.execute("UPDATE Users SET up=%ld AND down=%ld WHERE ip='%s'" % (up, down, cip))
    else:
      cur.execute("INSERT INTO Users VALUES('%s', %d, %d)" % (cip, up, down))
  con.commit()
except sql.Error, e:
  if con:
    con.rollback()
  print "SQLite3.x Error: %s" % e.args[0]
  sys.exit(1)
finally:
  if con:
    con.close()
