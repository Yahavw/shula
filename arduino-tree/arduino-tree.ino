//#include <Wire.h> // Must include Wire library for I2C
#include <Adafruit_NeoPixel.h>
#include <CapacitiveSensor.h>

#define PIN 13

#define LED1 4
#define LED2 9
#define LED3 14

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
CapacitiveSensor   cs_4_2 = CapacitiveSensor(4, 2);       // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_4_6 = CapacitiveSensor(4, 6);       // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_4_8 = CapacitiveSensor(4, 8);       // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

boolean DEBUG = false;

boolean thisSensorStatusArray[3] = {false, false, false};
boolean otherSensorStatusArray[3] = {false, false, false};

int ledsPinArray[3] = {LED1, LED2, LED3};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200) ;
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  //cs_1_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
}

void loop() {
  long Threshold1 = 500;
  long Threshold2 = 500;
  long Threshold3 = 500;

  long start = millis();
  long total1 =  cs_4_2.capacitiveSensor(30);
  long total2 =  cs_4_6.capacitiveSensor(30);
  long total3 =  cs_4_8.capacitiveSensor(30);

  if (DEBUG) {
    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing

    Serial.print(total1);                  // print sensor output 1
    Serial.print("\t");
    Serial.print(total2);                  // print sensor output 2
    Serial.print("\t");
    Serial.println(total3);                // print sensor output 3
  }
  delay(10);                             // arbitrary delay to limit data to serial port

  if (total1 > Threshold1) {
    turnOnthis(0);
  }
  else {
    trunOffThis(0);
  }

  if (total2 > Threshold2) {
    turnOnthis(1);
  }
  else {
    trunOffThis(1);
  }

  if (total3 > Threshold3) {
    turnOnthis(2);
  }
  else {
    trunOffThis(2);
  }

  if (not DEBUG && Serial.available()) {
    playOther();
  }

  setLeds();
}

void setLeds() {
  for (int i = 0; i < 3; i++) {
    if (not thisSensorStatusArray[i] && not otherSensorStatusArray[i]) {
      strip.setPixelColor(ledsPinArray[i], 255, 255, 0);
    } else if (not thisSensorStatusArray[i] && otherSensorStatusArray[i]) {
      strip.setPixelColor(ledsPinArray[i], 255, 0, 0);
    } else if ( thisSensorStatusArray[i] && not otherSensorStatusArray[i]) {
      strip.setPixelColor(ledsPinArray[i], 0, 0, 255);
    } else {
      strip.setPixelColor(ledsPinArray[i], 0, 255, 0);
    }
  }
  strip.show();
}


