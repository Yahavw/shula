
// Change 1 rgb led color according to it's status.
void changeColor(int led, unsigned int ledStatus[LEDS_NUMBER]) {
  if (ledStatus[RED] == 254) {
    ledStatus[RED] -= 2;
    ledStatus[GREEN] += 2;
  } else if (ledStatus[GREEN] == 254) {
    ledStatus[GREEN] -= 2;
    ledStatus[BLUE] += 2;
  } else if (ledStatus[BLUE] == 254) {
    ledStatus[BLUE] -= 2;
    ledStatus[RED] += 2;
  } else if (ledStatus[BLUE] == 0) {
    ledStatus[RED] -= 2;
    ledStatus[GREEN] += 2;
  } else if (ledStatus[RED] == 0) {
    ledStatus[GREEN] -= 2;
    ledStatus[BLUE] += 2;
  } else if (ledStatus[GREEN] == 0) {
    ledStatus[BLUE] -= 2;
    ledStatus[RED] += 2;
  }
  strip.setPixelColor(led, ledStatus[RED], ledStatus[GREEN], ledStatus[BLUE]);
}

void initLedsStatus() {
  for (int i = 0; i < LEDS_NUMBER; i++) {
    ledsStatusArray[i][0] = 254;
    ledsStatusArray[i][1] = 0;
    ledsStatusArray[i][2] = 0;
  }
  strip.show();
}


