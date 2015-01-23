#!/usr/bin/env python

try:
  import cPickle as pickle
except:
  import pickle

import sys
users_datafile = "/etc/openvpn/users-offline.data"

try:
  users = pickle.load(open(users_datafile, "rb"))
except:
  users = {}

user = sys.argv[1]
if user == "init":
  for key in users.keys():
    users[key]['up'] = 0
    users[key]['down'] = 0
  print "User db reset"
elif sys.argv[2] == "clear":
  users[user]['down'] = 0
  users[user]['up'] = 0
  print "Clearing user data ", user
elif user in users:
  users[user]['up']   += long(sys.argv[2])
  users[user]['down'] += long(sys.argv[3])
else:
  users[user] = {'up': long(sys.argv[2]), 'down': long(sys.argv[3])}

pickle.dump(users, open(users_datafile, "wb"))
