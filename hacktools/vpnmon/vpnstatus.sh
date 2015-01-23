#!/bin/bash
for((i=0;i<16;i++))
do count=`cat /var/log/openvpn/status$i.log | grep CLIENT_ | wc -l`; echo "server$i: $count"; done
