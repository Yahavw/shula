
// Change 1 rgb led color according to it's status.
void changeColor(int led, unsigned int ledStatus[6]) {
        if (ledStatus[RED] == 255) {
            ledStatus[RED]--;
            ledStatus[GREEN]++;
        } else if (ledStatus[GREEN] == 255) {
            ledStatus[GREEN]--;
            ledStatus[BLUE]++;
        } else if (ledStatus[BLUE] == 255) {
            ledStatus[BLUE]--;
            ledStatus[RED]++;
        } else if (ledStatus[BLUE] == 0) {
            ledStatus[RED]--;
            ledStatus[GREEN]++;
        } else if (ledStatus[RED] == 0) {
            ledStatus[GREEN]--;
            ledStatus[BLUE]++;
        } else if (ledStatus[GREEN] == 0) {
            ledStatus[BLUE]--;
            ledStatus[RED]++;
        }
        strip.setPixelColor(led, ledStatus[RED], ledStatus[GREEN], ledStatus[BLUE]);
}

void initLedsStatus() {
  for (int i = 0; i < LEDS_NUMBER; i++) {
    ledsStatusArray[i][0] = 255;
    ledsStatusArray[i][1] = 0;
    ledsStatusArray[i][2] = 0;
    ledsStatusArray[i][3] = 0;
    ledsStatusArray[i][4] = 0;
    ledsStatusArray[i][5] = 1;
  }
  strip.show();
}


// Not in use right now
void setLeds() {
  for (int i = 0; i < 3; i++) {
    if (not thisSensorStatusArray[i] && not otherSensorStatusArray[i]) {
      strip.setPixelColor(ledsPinArray[i], 255, 255, 0);
    } else if (not thisSensorStatusArray[i] && otherSensorStatusArray[i]) {
      strip.setPixelColor(ledsPinArray[i], 255, 0, 0);
    } else if ( thisSensorStatusArray[i] && not otherSensorStatusArray[i]) {
      strip.setPixelColor(ledsPinArray[i], 0, 0, 255);
    } else {
      strip.setPixelColor(ledsPinArray[i], 0, 255, 0);
    }
  }
  strip.show();
}
