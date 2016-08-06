import glob

from twisted.internet import reactor
from twisted.internet.serialport import SerialPort
from twisted.protocols import basic

from rpi.config import TREENAME
from rpi.sounds import play_local_sound, play_remote_sound
from rpi.peers import zmq_publish, subscriber


def write_to_arduino(msg):
    pass
    # arduino =
    # arduino.write(msg)
    # arduino.flush()


def find_tty():
    return next(glob.iglob("/dev/ttyACM*"))


def zmq_print(message, tag):
    print("s1: got {}".format((message, tag)))


def handleOtherTreeMessage(message, tag):
    try:
        source_tree, sensor_no, value = message.strip().split()
    except ValueError:
        print("got a bad message from 0mq: {!r}, tag: {!r}".format(
            message, tag))
    else:
        if int(value) > 0:      # FIXME: handle not only as binaries
            play_remote_sound(sensor_no)
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
        zmq_publish("{} {}".format(TREENAME, line))


if __name__ == '__main__':
    import pudb; pudb.set_trace()
    subscriber.subscribe("")  # CONFIGURE ME
    subscriber.gotMessage = zmq_print

                                # "/dev/pts/{}".format(28)
    SerialPort(ArduinoReceiver(), find_tty(), reactor, 9600)

    reactor.run()
