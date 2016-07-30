import time
import pygame

import serial

# Init pygame for playing the audio
pygame.mixer.init()
sound1 = pygame.mixer.Sound("Here01-C1.wav")
sound2 = pygame.mixer.Sound("Here02-D1.wav")
# sound3 = pygame.mixer.Sound("Here01-C1.wav")
pygame.init()
# sound.play()
port = "COM4"
ard = serial.Serial(port, 9600, timeout=5)

time.sleep(2)  # wait for Arduino
while (True):

    msg = ard.read(ard.inWaiting())  # read all characters in buffer
    if msg == "1":
        print ("play1: " + msg)
        sound1.play()
        # time.sleep(1)  # wait for Arduino
        sendValue = '0';
        ard.write(sendValue);
    if msg == "2":
        print ("play2: " + msg)
        sound2.play()
        # time.sleep(1)  # wait for Arduino
        sendValue = '0';
        ard.write(sendValue);
    # else: time.sleep(0.1)
    # print ("running")
else:
    print ("Exiting")
exit()
