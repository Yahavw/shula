import zmq

from txzmq import ZmqEndpoint, ZmqFactory, ZmqSubConnection

from rpi.config import TREENAME, zmq_ip, ZMQ_PORT, local_configs

## publisher
_context = zmq.Context()
_pub_socket = _context.socket(zmq.PUB)
_pub_socket.bind("tcp://*:{}".format(ZMQ_PORT))


def zmq_publish(msg):
    message = "{this_tree_name} {msg}".format(
        this_tree_name=TREENAME, msg=msg)
    print('publising "{}" to peers via 0mq'.format(message))
    _pub_socket.send(message)


###### subscriber, for twisted ######
zf = ZmqFactory()
subscriber = ZmqSubConnection(zf)

def _create_endpoint(treename):
    return ZmqEndpoint("connect", "tcp://{}:{}".format(
        local_configs['other_trees'][treename], ZMQ_PORT))

_endpoints = [_create_endpoint(treename) for
              treename in local_configs['connect_to']]

subscriber.addEndpoints(_endpoints)

# in `main.py`, specific behavior is configured, such as:
# subscriber.subscribe("othertreename")
# subscriber.gotMessage = handle_incoming_zmq_msg
