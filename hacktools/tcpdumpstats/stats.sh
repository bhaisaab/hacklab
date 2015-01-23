#!/bin/bash
#tcpdump -i eth1 -n | grep 'IP.*length [0-9^\n]*' | while read args; do python /usr/bin/ntopper/dbdump.py $args; done;

rm ntopdump*
wget -q "http://localhost:3000/dumpData.html?language=python&view=long" -O ntopdump.py
python /usr/bin/ntopper/genstats.py
