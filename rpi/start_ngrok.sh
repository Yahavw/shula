#! /bin/bash

# using ngrok in the backgroun, make sure our port 25656 is open for tcp connections (for zmq)
/home/pi/ngrok tcp 25656 -log=stdout -config=/home/pi/.ngrok2/ngrok.yml &

# wait for ngrok to establish connection
sleep 15

# get the current public url
echo $(curl 127.0.0.1:4040/api/tunnels 2>/dev/null | json_pp 2>/dev/null | egrep -o 'tcp:[^"]*')
