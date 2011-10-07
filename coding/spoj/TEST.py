#!/usr/bin/env python
import sys
L = sys.stdin.read().splitlines()
for l in L:
  if l == '42': break
  print l

#r = ''
#while True:
#  p = sys.stdin.read(1)
#  if p != '\n':
#    r += p
#    continue
#  if r == '42': break
#  print r
#  r = ''

#num = int(sys.stdin.readline())
#while num ^ 42:
#  print(num)
#  num = int(sys.stdin.readline())
