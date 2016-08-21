
void sendMsg(struct TreeMsg treeMsg) {
  Serial.println(String(treeMsg.intro) + "\t" + String(treeMsg.R) + "\t" + String(treeMsg.G) + "\t" + String(treeMsg.B));
  Serial.flush();
}

void sendEndMsg() {
  Serial.println("end ");
}

void sendStartMsg() {
  Serial.println("start ");
}

struct TreeMsg readMsg() {
  struct TreeMsg treeMsg;
  String introMsg = Serial.readStringUntil(' ');

  // If message start with 'start' or ' 'end' - return -1
  if (introMsg == "end") {
    shouldPlayOther = false;
    treeMsg.intro = -1;
  } else if (introMsg == "start") {
    treeMsg.intro = -1;
    Serial.readStringUntil('\n');
  } else {
    treeMsg.intro = introMsg.toInt();
    treeMsg.R = Serial.readStringUntil(' ').toInt();
    treeMsg.G = Serial.readStringUntil(' ').toInt();
    treeMsg.B = Serial.readStringUntil('\n').toInt();
  }

  return treeMsg;
}

boolean checkConnection() {
  return Serial.available();
}

