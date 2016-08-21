
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
    strip.setPixelColor(treeMsg.intro, treeMsg.R, treeMsg.G, treeMsg.B);
  }
}

