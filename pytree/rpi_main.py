from twisted.internet import reactor
from twisted.internet.serialport import SerialPort
from twisted.protocols import basic
from txzmq import ZmqEndpoint, ZmqFactory, ZmqSubConnection
 

### zmq listener
def zmq_print(*args):
    print("s1: got {}".format(args))


def gotZmqMessage(*args):
    try:
        source_tree, sensor_no, value = args[0].split()
    except ValueError:
        print("got a bad message from 0mq: {!r}".format(args))
    else:
        if value:
            play_remote_sound(sensor_no)
        write_to_arduino("{} {}".format(sensor_no, value))

zf = ZmqFactory()
endpoint = ZmqEndpoint("connect", "tcp://127.0.0.1:1212")
subscriber = ZmqSubConnection(zf, endpoint)
subscriber.subscribe("1")  # CONFIGURE ME
subscriber.gotMessage = zmq_print


### serial listener
class Receiver(basic.LineOnlyReceiver):
    delimiter = b'\n'

    def lineReceived(self, line):
        print("Line received: {!r}".format(line))
        zmq_publish("{us} {line}".format())


SerialPort(Receiver(), "/dev/pts/{}".format(28), reactor, 9600)

reactor.run()
