

void sendMsg(String sensor, String data) {
  Serial.println(sensor + " " + data);
  Serial.flush();
}

struct TreeMsg readMsg() {
  struct TreeMsg treeMsg; // = {0, 0};
  int sensor = Serial.readStringUntil(' ').toInt();
  int data = Serial.readStringUntil('\n').toInt();
  treeMsg.sensor = sensor;
  treeMsg.data = data;
  Serial.println(treeMsg.sensor);
  return treeMsg;
}

