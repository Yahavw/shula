import zmq

from txzmq import ZmqEndpoint, ZmqFactory, ZmqSubConnection

from rpi.config import TREENAME, zmq_ip, ZMQ_PORT

## publisher
_context = zmq.Context()
_pub_socket = _context.socket(zmq.PUB)
_pub_socket.bind("tcp://*:{}".format(ZMQ_PORT))


def zmq_publish(sensor_no, value):
    _pub_socket.send("{} {} {}".format(TREENAME, sensor_no, value))


###### subscriber, for twisted ######
zf = ZmqFactory()
endpoint = ZmqEndpoint("connect", "tcp://{}:{}".format(zmq_ip, ZMQ_PORT))
subscriber = ZmqSubConnection(zf, endpoint)

# in `main.py`, specific behavior is configured, such as:
# subscriber.subscribe("othertreename")
# subscriber.gotMessage = handle_incoming_zmq_msg
