void playOther() {
  int sensor = Serial.readStringUntil(' ').toInt();
  int mode = Serial.readStringUntil('\n').toInt();

  Serial.println("mode: " + String(mode));
  if ( mode == 0) {
    turnOffOther(sensor);
  } else if (mode == 1) {
    turnOnOther(sensor);
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
    Serial.println (String(sensor) + " 1");
    Serial.flush();
  }
  thisSensorStatusArray[sensor] = true;
}

// This ardunio sensor send off ping
void trunOffThis(int sensor) {
  if (not DEBUG  && thisSensorStatusArray[sensor]) {
    Serial.println(String(sensor) + " 0");
    Serial.flush();
  }
  thisSensorStatusArray[sensor] = false;
}
