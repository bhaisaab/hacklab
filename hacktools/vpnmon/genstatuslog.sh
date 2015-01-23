#!/bin/bash
rm -f /var/log/openvpn/status.log
cat /var/log/openvpn/status*.log  > /var/log/openvpn/status.log
/etc/openvpn/updatestats.py
