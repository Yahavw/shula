# The tracker is a simple "server" using the super simple zmq REQ-REP model
# It receives as REQuests the addresses of zmq "tree" nodes, and serves all
# the (other) addresses that it has as a REPly

import zmq

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:26822")

addresses = set()
print "starting the server"
while True:
    address = socket.recv()
    print 'got a (new?) address: {}'.format(address)
    addresses.add(address)
    print 'addresses: {!r}'.format(addresses)
    socket.send(' '.join(addresses - {address}))
