#! /bin/bash

# This script must be ran as root

# find the uuid for the cellular connection to Golan Telecom
conn_uuid=$(nmcli -t --fields name,uuid connection show|grep Golan|awk '{split($0, a, ":"); print a[2]}')
# connect the connection.
nmcli connection up $conn_uuid
