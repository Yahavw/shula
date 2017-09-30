#! /bin/bash

# This is the startup (systemd) script for the tree project.
# THIS MUST BE RAN AS root, FOR THE `connect_golan.sh ` SCRIPT TO WORK.
# contact avi.rei@gmail.com or nirbadt@gmail.com for details and support.

# connect to the internet via Golan Telecom cellular modem
echo "connecting to cellular network"
# retry to connect until 3 pings are successful
until ping -c 3 google.com  # -I ppp0 # 8.8.4.4
do
    bash -x /home/pi/shula/rpi/connect_golan.sh || wvdial 3gconnect &
done
echo "connected"


echo "starting ngrok to be able to recieve zeromq connectoins"
# ngrok has a local api endpoint on port 4040, get the ephemeral tcp address from it
until curl 127.0.0.1:4040/api/tunnels 2>/dev/null | json_pp 2>/dev/null | egrep -o 'tcp:[^"]*'
do
    su -c "bash -x /home/pi/shula/rpi/start_ngrok.sh" pi
done
our_address=$(curl 127.0.0.1:4040/api/tunnels 2>/dev/null | json_pp 2>/dev/null | egrep -o 'tcp:[^"]*')
echo "ngrok started successfully. address is $our_address"
echo $our_address > /tmp/ngrok-tcp-addr


# start the python program that will connect to th peer(s)
echo "starting the python program"
cd /home/pi/shula/ && su -c "python -c 'from rpi.main import start; start()'" pi
