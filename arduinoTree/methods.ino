

void playOther() {
  struct TreeMsg treeMsg;
  treeMsg = readMsg();

  if ( treeMsg.data == 0) {
    turnOffOther(treeMsg.sensor);
  } else if (treeMsg.data == 1) {
    turnOnOther(treeMsg.sensor);
  }
}

void turnOffOther(int sensor) {
  otherSensorStatusArray[sensor] = false;
}

void turnOnOther(int sensor) {
  otherSensorStatusArray[sensor] = true;
}

// This ardunio sensor send on ping
void turnOnthis(int sensor) {
  if (not DEBUG  && not thisSensorStatusArray[sensor]) {
    sendMsg(String(sensor), "1");
  }
  thisSensorStatusArray[sensor] = true;
}

// This ardunio sensor send off ping
void trunOffThis(int sensor) {
  if (not DEBUG  && thisSensorStatusArray[sensor]) {
    sendMsg(String(sensor), "0");
  }
  thisSensorStatusArray[sensor] = false;
}



void measureCapcitive() {
  for (int i = 0 ; i < LEDS_NUMBER; i++) {
    capacitiveArray[i] = cs_12[i].capacitiveSensor(30);
  }
}

