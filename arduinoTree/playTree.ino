
void playThisTree() {
  long start = millis();
  measureCapcitive();

  if (DEBUG) {
    debug_loop(start);
  }

  delay(10);                             // arbitrary delay to limit data to serial port

  for (int i = 0; i < LEDS_NUMBER; i++) {
    if (capacitiveArray[i] > THRESHOLD) {
      changeColor(i, ledsStatusArray[i]);
      TreeMsg treeMsg = {i, ledsStatusArray[i][0], ledsStatusArray[i][1], ledsStatusArray[i][2]};
      sendMsg(treeMsg);
    }
  }
  strip.show();
}

void playOtherTree() {
  TreeMsg treeMsg = readMsg();
  if (treeMsg.intro != -1) {
    ledsStatusArray[treeMsg.intro][0] = treeMsg.R;
    ledsStatusArray[treeMsg.intro][1] = treeMsg.G;
    ledsStatusArray[treeMsg.intro][2] = treeMsg.B;
    strip.setPixelColor(treeMsg.intro, treeMsg.R, treeMsg.G, treeMsg.B);
  }

}

void playFinalMsg() {
  for (int i = 0; i < LEDS_NUMBER; i++) {
    TreeMsg treeMsg = {i, 255, 0, 0};
    // 254 1 0
    if (255 >= ledsStatusArray[i][0]  && ledsStatusArray[i][0] > 127 && ledsStatusArray[i][2] == 0) {
      treeMsg = {i, 254, 1, 0};
    }
    // 127 128 0
    else if (127 >= ledsStatusArray[i][0]  && ledsStatusArray[i][0] > 0 && ledsStatusArray[i][2] == 0) {
      treeMsg = {i, 127, 128, 0};
    }
    // 0 254 1
    else if (255 >= ledsStatusArray[i][1]  && ledsStatusArray[i][1] > 127 && ledsStatusArray[i][0] == 0) {
      treeMsg = {i, 0, 254, 1};
    }
    // 0 127 128
    else if (127 >= ledsStatusArray[i][1]  && ledsStatusArray[i][1] > 0 && ledsStatusArray[i][0] == 0) {
      treeMsg = {i, 0, 127, 128};
    }
    // 1 0 254
    else if (255 >= ledsStatusArray[i][2]  && ledsStatusArray[i][2] > 127 && ledsStatusArray[i][1] == 0) {
      treeMsg = {i, 1, 0, 254};
    }
    // 128 0 127
    else if (127 >= ledsStatusArray[i][2]  && ledsStatusArray[i][2] > 0 && ledsStatusArray[i][1] == 0) {
      treeMsg = {i, 128, 0, 127};
    }

    strip.setPixelColor(i, ledsStatusArray[i][0], ledsStatusArray[i][1], ledsStatusArray[i][2]);
    for (int j = 0; j < LEDS_NUMBER; j++) {
      if (j != i) {
        strip.setPixelColor(j, 0, 0, 0);
      }

    }
    sendMsg(treeMsg);
    delay(400);
    strip.show();
    delay(200);
    }
    delay(600);
    for (int i = 0; i < LEDS_NUMBER; i++) {
    strip.setPixelColor(i, ledsStatusArray[i][0], ledsStatusArray[i][1], ledsStatusArray[i][2]);
    }
    strip.show();
  }

  void startOther() {
    for (int i = 0; i < LEDS_NUMBER; i++) {
      strip.setPixelColor(i, 0, 0, 255);
    }
    strip.show();
  }

