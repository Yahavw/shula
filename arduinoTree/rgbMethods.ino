
// Change 1 rgb led color according to it's status.
void changeColor(int led, unsigned int ledStatus[6]) {
  if (ledStatus[INDEX] >= 255) {
    ledStatus[INDEX] = 0;
    ledStatus[DEC_COLOR] = (ledStatus[DEC_COLOR] + 1) % 3;
    ledStatus[INC_COLOR] = ledStatus[DEC_COLOR] == 2 ? 0 : ledStatus[DEC_COLOR] + 1;
  }
  ledStatus[ledStatus[DEC_COLOR]] -= 1;
  ledStatus[ledStatus[INC_COLOR]] += 1;
  strip.setPixelColor(led, ledStatus[RED], ledStatus[GREEN], ledStatus[BLUE]);
  //  delay(5);
  ledStatus[INDEX] += 1;
}

void initLedsStatus() {
  for (int i = 0; i < LEDS_NUMBER; i++) {
    ledsStatusArray[i][0] = 0;
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
