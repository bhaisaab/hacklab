#!/bin/bash
 
status="CONNECT|`date`|$common_name|$trusted_ip:$trusted_port|$ifconfig_pool_local_ip:$ifconfig_pool_remote_ip"
echo $status >> /var/log/openvpn/connect.log
exit 0;
