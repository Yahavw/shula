void measureCapcitive() {
  for (int i = 0 ; i < LEDS_NUMBER; i++) {
    capacitiveArray[i] = cs_12[i].capacitiveSensor(30);
  }
}

void initCapacivite(unsigned long timeout_millis) {
  for (int i = 0 ; i < LEDS_NUMBER; i++) {
    cs_12[i].set_CS_Timeout_Millis(timeout_millis);
  }
}

