import glob

from serial import Serial

from twisted.internet import reactor
from twisted.internet.serialport import SerialPort
from twisted.protocols import basic

from rpi.sounds import play_local_sound, play_remote_sound
from rpi.peers import zmq_publish

arduino = None

def write_to_arduino(msg):
    print("writing to arduino: {}".format(msg))
    arduino.write(msg + "\n")   # TODO: consider unifying line terminators
    arduino.flush()


def find_tty():
    return next(glob.iglob("/dev/ttyACM*"))


def __zmq_print(message):
    "for debugging only"
    print("s1: got {}".format(message))


def handleOtherTreeMessage(message):
    try:
        source_tree, sensor_no, value = message.strip().split()
    except ValueError:
        print("got a BAD message from 0mq: {!r}".format(message))
    else:
        print("got a GOOD message from 0mq: {!r}".format(message))
        if int(value) > 0:      # FIXME: handle not only as binaries
            play_remote_sound(int(sensor_no))
        write_to_arduino("{} {}".format(sensor_no, value))


### serial listener from arduino
class ArduinoReceiver(basic.LineOnlyReceiver):
    # delimiter = b'\n'           # \r\n is used by Serial.println

    def lineReceived(self, line):
        print("Line received from serial: {!r}".format(line))
        try:
            sensor_no, value = map(int, line.strip().split())
        except ValueError:
            print("got a bad message from serial: {}".format(line))
            return
        play_local_sound(sensor_no)
        zmq_publish("{}".format(line))
        print("lineReceived done")


def start(tty=None):
    """
    run with $ python -c 'from rpi.main import start; start()'
    tty is for testing (with socat, for example)
    """
    # listen to arduino
                                # "/dev/pts/{}".format(28)
    SerialPort(ArduinoReceiver(), tty or find_tty(), reactor, 115200)

    # configure arduino for writing
    global arduino
    arduino = Serial(tty or find_tty(), 115200)

    from rpi.peers import subscriber
    subscriber.subscribe("tree2")  # CONFIGURE ME
    subscriber.gotMessage = handleOtherTreeMessage

    reactor.run()
