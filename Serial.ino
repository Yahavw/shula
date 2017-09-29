//
//void sendMsg(struct TreeMsg treeMsg) {
//  Serial.println(String(treeMsg.intro) + "\t" + String(treeMsg.R) + "\t" + String(treeMsg.G) + "\t" + String(treeMsg.B));
//  Serial.flush();
//}
//
//void sendEndMsg() {
//  Serial.println("-2 0 0 0");
//  Serial.flush();   
//}
//
//void sendStartMsg() {
//  Serial.println("-1 0 0 0");
//  Serial.flush();
//}
//
//void sendPlayMsg() {
//  Serial.println("-3 0 0 0");
//  Serial.flush();
//}
//
//void sendStartOtherMsg() {
//  Serial.println("-4 0 0 0");
//  Serial.flush();
//}
//
//struct TreeMsg readMsg() {
//  struct TreeMsg treeMsg;
//  String introMsg = Serial.readStringUntil(' ');
//
//  // If message start with 'start' or ' 'end' - return -1
//  if (treeMsg.intro > 0) {
//    treeMsg.intro = introMsg.toInt();
//    treeMsg.R = Serial.readStringUntil(' ').toInt();
//    treeMsg.G = Serial.readStringUntil(' ').toInt();
//    treeMsg.B = Serial.readStringUntil('\n').toInt();
//  } else if (introMsg == "-2") {
//    shouldPlayOther = false;
//    treeMsg.intro = -1;
//    Serial.readStringUntil('\n');
//  } else if (introMsg == "-1") {
//    treeMsg.intro = -1;
//    shouldPlayOther = true;
//    Serial.readStringUntil('\n');
//
//  } else if (introMsg == "-3") {
//    treeMsg.intro = -3;
//    Serial.readStringUntil('\n');
//
//  } else if (introMsg == "-4") {
//    treeMsg.intro = -4;
//    Serial.readStringUntil('\n');
//
//  } 
//
//  return treeMsg;
//}
//
//boolean checkConnection() {
//  return Serial.available();
//}
