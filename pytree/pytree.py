import pygame
import serial
import zmq

# Init pygame for playing the audio
pygame.mixer.init()


def init_sounds():
    return {'here': {0: pygame.mixer.Sound('Here01-C1.wav'),
                     1: pygame.mixer.Sound('Here02-D1.wav'),
                     2: pygame.mixer.Sound('Here03-E1.wav'),
                     3: pygame.mixer.Sound('Here04-F1.wav'),
                     4: pygame.mixer.Sound('Here05-G1.wav'),
                     5: pygame.mixer.Sound('Here06-A1.wav'),
                     6: pygame.mixer.Sound('Here07-B1.wav'),
                     7: pygame.mixer.Sound('Here08-C2.wav')},
            'there': {0: pygame.mixer.Sound('There01-C1.wav'),
                      1: pygame.mixer.Sound('There02-D1.wav'),
                      2: pygame.mixer.Sound('There03-E1.wav'),
                      3: pygame.mixer.Sound('There04-F1.wav'),
                      4: pygame.mixer.Sound('There05-G1.wav'),
                      5: pygame.mixer.Sound('There06-A1.wav'),
                      6: pygame.mixer.Sound('There07-B1.wav'),
                      7: pygame.mixer.Sound('There08-C2.wav')}}

def play(n, sounds):
    sounds[n].play()

pygame.init()

sounds = init_sounds()

ard = serial.Serial("COM7", 115200, timeout = 0)

# subscriber
ip = "192.168.2.101"
port = 1212
context = zmq.Context()
sub_socket = context.socket(zmq.SUB)
sub_socket.connect("tcp://{}:{}".format(ip, port))
sub_socket.setsockopt(zmq.SUBSCRIBE, 'elfdans')

while True:

    # Read and play massage from arduino
    try:
        inp = ard.readline().strip().split(" ")

        if len(inp) >= 2:
            print(inp)
            sensor = int(inp[0])
            value = int(inp[1])

            if value == 1:
                play(sensor, sounds['here'])

    except Exception as e:
        print(str(e))

    # Receive massage from other, play sound and send to arduino
    try:
        other_msg =  sub_socket.recv(flags=zmq.NOBLOCK)  # non blocking
        print other_msg
        tree_name, sensor_no, value = other_msg.strip().split(" ")
        if int(value) > 0:
            play(int(sensor_no), sounds['there'])
            ard.write(str(sensor_no) + " 1")
        elif int(value) == 0:
            ard.write(str(sensor_no) + " 0")
    except zmq.Again:
       pass                                  # no message
else:
   print ("Exiting")
exit()