#include <Adafruit_NeoPixel.h>
#include <CapacitiveSensor.h>

#define PIN 13

#define LED1 0
#define LED2 1
#define LED3 4

#define THRESHOLD 500
#define LEDS_NUMBER 6

// define led status in array
#define RED 0
#define GREEN 1
#define BLUE 2
#define INDEX 3
#define DEC_COLOR 4
#define INC_COLOR 5

struct TreeMsg {
  int sensor;
  int data;
} ;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);
CapacitiveSensor   cs_12[] = {CapacitiveSensor(12, 2), CapacitiveSensor(12, 3), CapacitiveSensor(12, 4)
                              , CapacitiveSensor(12, 5), CapacitiveSensor(12, 6), CapacitiveSensor(12, 7)
                             };    // 10M resistor between pins 12, pin 2 is sensor pin, add a wire and or foil if desired

boolean DEBUG = false;

// TODO - Handle this for communication
boolean thisSensorStatusArray[3] = {false, false, false};
boolean otherSensorStatusArray[3] = {false, false, false};

// TODO - not in use right now
unsigned int ledsPinArray[3] = {LED1, LED2, LED3};

// Hold the each led status
unsigned int ledsStatusArray[LEDS_NUMBER][6];

long capacitiveArray[LEDS_NUMBER];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200) ;
  strip.begin();
  strip.setBrightness(64);
  initLedsStatus();
  strip.show(); // Initialize all pixels to 'off'

  //cs_1_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
}

void loop() {
  long start = millis();
  measureCapcitive();

  if (DEBUG) {
    debug_loop(start);
  }
  
  delay(10);                             // arbitrary delay to limit data to serial port

  for (int i = 0; i < LEDS_NUMBER; i++) {
    if (capacitiveArray[i] > THRESHOLD) {
//      turnOnthis(i);
      changeColor(i, ledsStatusArray[i]);
      sendMsg(String(i), String(ledsStatusArray[i][0]) + String(ledsStatusArray[i][1]) + String(ledsStatusArray[i][2]));  
    }
//    else {
//      trunOffThis(0);
//    }
  }

//  if (not DEBUG && Serial.available()) {
//    playOther();
//  }
  strip.show();

}




