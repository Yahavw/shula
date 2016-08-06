import os
import pygame

from rpi.config import SOUNDS_DIR


def init_sounds(dirname=SOUNDS_DIR):
    # set volume to 100%
    os.system("amixer set 'PCM' 100%")
    # initialize the pygame mixer
    pygame.mixer.init()

    return {'here': {0: pygame.mixer.Sound(os.path.join(dirname, 'Here01-C1.wav')),
                     1: pygame.mixer.Sound(os.path.join(dirname, 'Here02-D1.wav')),
                     2: pygame.mixer.Sound(os.path.join(dirname, 'Here03-E1.wav')),
                     3: pygame.mixer.Sound(os.path.join(dirname, 'Here04-F1.wav')),
                     4: pygame.mixer.Sound(os.path.join(dirname, 'Here05-G1.wav')),
                     5: pygame.mixer.Sound(os.path.join(dirname, 'Here06-A1.wav')),
                     6: pygame.mixer.Sound(os.path.join(dirname, 'Here07-B1.wav')),
                     7: pygame.mixer.Sound(os.path.join(dirname, 'Here08-C2.wav'))},
            'there': {0: pygame.mixer.Sound(os.path.join(dirname, 'There01-C1.wav')),
                      1: pygame.mixer.Sound(os.path.join(dirname, 'There02-D1.wav')),
                      2: pygame.mixer.Sound(os.path.join(dirname, 'There03-E1.wav')),
                      3: pygame.mixer.Sound(os.path.join(dirname, 'There04-F1.wav')),
                      4: pygame.mixer.Sound(os.path.join(dirname, 'There05-G1.wav')),
                      5: pygame.mixer.Sound(os.path.join(dirname, 'There06-A1.wav')),
                      6: pygame.mixer.Sound(os.path.join(dirname, 'There07-B1.wav')),
                      7: pygame.mixer.Sound(os.path.join(dirname, 'There08-C2.wav'))}}


sounds = init_sounds()


def _play(n, sounds):
    sounds[n].play()


def play_remote_sound(idx):
    print("playing remote sound {}".format(idx))
    _play(idx, sounds["there"])


def play_local_sound(idx):
    print("playing local sound {}".format(idx))
    _play(idx, sounds["here"])
