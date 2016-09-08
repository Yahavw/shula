import glob
import platform

from serial import Serial

from twisted.internet import reactor
from twisted.internet.serialport import SerialPort
from twisted.protocols import basic

from rpi.config import TREENAME
from rpi.peers import zmq_publish
from rpi.sounds import play_local_sound, play_remote_sound


arduino = None


def write_to_arduino(msg):
    print("writing to arduino: {}".format(msg))
    arduino.write(msg + "\n")   # TODO: consider unifying line terminators
    arduino.flush()


def find_tty():
    os_name = platform.system()
    if os_name == "Linux":
        return next(glob.iglob("/dev/ttyACM*"))
    elif os_name == "Darwin":   # OSX
        return next(glob.iglob("/dev/cu.usbmodem*"))
    elif os_name == "Windows":
        return _find_win_serial_port()
    else:
        # unsupported OS
        raise NotImplementedError


def _find_win_serial_port():
    for i in range(100):
        try:
            port = "COM{}}".format(i)
            s = Serial(port)
            s.close()           # release serial
            return port
        except:
            pass
    raise RuntimeError


def __zmq_print(message):
    "for debugging only"
    print("s1: got {}".format(message))


def handleOtherTreeMessage(message):
    try:
        source_tree, sensor_no, r,g,b = message.strip().split()
    except ValueError:
        print("got a BAD message from 0mq: {!r}".format(message))
    else:
        print("got a GOOD message from 0mq: {!r}".format(message))
        if int(r) > 0:      # FIXME: handle not only as binaries
            play_remote_sound(int(sensor_no))
        write_to_arduino("{} {} {} {}".format(sensor_no,r,g,b))


# serial listener from arduino
class ArduinoReceiver(basic.LineOnlyReceiver):
    # delimiter = b'\n'           # \r\n is used by Serial.println

    def lineReceived(self, line):
        print("Line received from serial: {!r}".format(line))
        try:
            sensor_no, r,g,b = map(int, line.strip().split())
        except ValueError:
            print("got a bad message from serial: {}".format(line))
            return
        if line:               # FIXME: handle not only as binaries
            
		rgbValue = str(r) + str(g) + str(b)
		if rgbValue == "25410":
			play_local_sound(0)
		if rgbValue == "1271280":
			play_local_sound(1)
		if rgbValue == "02541":
			play_local_sound(2)
		if rgbValue == "0127128":
			play_local_sound(3)
		if rgbValue == "10254":
			play_local_sound(4)
		if rgbValue == "1280127":
			play_local_sound(5)
		
	     #play_local_sound(rgbValue)
	     #print("RGB: ")
		#print(rgbValue)
        zmq_publish("{} {}".format(TREENAME, line))


def start(tty=None):
    """
    run with $ python -c 'from rpi.main import start; start()'
    tty is for testing (with socat, for example, tty="/dev/pts/XYZ")
    """
    # listen to arduino
                                # "/dev/pts/{}".format(28)
    if tty is None:
        tty = find_tty()

    SerialPort(ArduinoReceiver(), tty, reactor, 115200)

    # configure arduino for writing
    global arduino
    arduino = Serial(tty, 115200)

    from rpi.peers import subscriber
    subscriber.subscribe("")  # CONFIGURE ME
    subscriber.gotMessage = handleOtherTreeMessage

    reactor.run()
