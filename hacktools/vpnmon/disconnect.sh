#!/bin/bash
 
status="DISCONNECT|`date`|$common_name|$trusted_ip:$trusted_port|$ifconfig_pool_local_ip:$ifconfig_pool_remote_ip|$bytes_received|$bytes_sent"
echo $status >> /var/log/openvpn/disconnect.log
/etc/openvpn/updateuserdata.py $common_name $bytes_received $bytes_sent 
exit 0;
