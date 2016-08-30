void measureCapcitive() {
  for (int i = 0 ; i < LEDS_NUMBER; i++) {
    capacitiveArray[i] = cs_12[i].capacitiveSensor(30);
  }
}
