// Methods that should run in debug mode only

void debug_loop(long start) {
  Serial.print(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");

  Serial.print(capacitiveArray[0]);                    // tab character for debug windown spacing
  Serial.print("\t");
  Serial.print(capacitiveArray[1]);                    // tab character for debug windown spacing
  Serial.print("\t");
  Serial.print(capacitiveArray[2]);                    // tab character for debug windown spacing
  Serial.print("\t");
  Serial.print(capacitiveArray[3]);                    // tab character for debug windown spacing
  Serial.print("\t");
  Serial.print(capacitiveArray[4]);                    // tab character for debug windown spacing
  Serial.print("\t");
  Serial.println(capacitiveArray[5]);                    // tab character for debug windown spacing
}

