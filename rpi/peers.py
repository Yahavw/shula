from time import sleep
import zmq

from txzmq import ZmqEndpoint, ZmqFactory, ZmqSubConnection

from rpi.config import ZMQ_PORT, local_configs, TRACKER

## publisher
_context = zmq.Context()
_pub_socket = _context.socket(zmq.PUB)
_pub_socket.bind("tcp://*:{}".format(ZMQ_PORT))


def zmq_publish(msg):
    print('publishing "{}" to peers via 0mq'.format(msg))
    _pub_socket.send(msg)


###### publish our address, wait for at least 1 from server ######
with open('/tmp/ngrok-tcp-addr', 'r') as f:
    our_address = f.read().strip()

if not our_address.startswith('tcp://'):
    import sys
    print 'failed getting our ngrok address from /tmp/ngrok-tcp-addr'
    sys.exit(1)

print 'connecting to tracker and waiting for peer/s'
req_socket = _context.socket(zmq.REQ)
req_socket.connect(TRACKER)
while True:
    req_socket.send(our_address)
    other = req_socket.recv()   # BLOCKING
    if other:                   # we're not alone!
        print 'got peer: {}'.format(other)
        break
    sleep(5)                    # don't flood the server

###### subscriber, for twisted ######
zf = ZmqFactory()
subscriber = ZmqSubConnection(zf)

def _create_endpoint(address):
    return ZmqEndpoint("connect", address)

_endpoints = [_create_endpoint(addr) for addr in other.split(' ')]

subscriber.addEndpoints(_endpoints)

# in `main.py`, specific behavior is configured, such as:
# subscriber.subscribe("othertreename")
# subscriber.gotMessage = handle_incoming_zmq_msg
