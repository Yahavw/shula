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

// Send/Receive period time
#define PERIOD_TIME 10000
#define TIMEOUT 15000


struct TreeMsg {
  int intro;
  int R;
  int G;
  int B;
} ;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);
CapacitiveSensor   cs_12[] = {CapacitiveSensor(12, 2), CapacitiveSensor(12, 3), CapacitiveSensor(12, 4)
                              , CapacitiveSensor(12, 5), CapacitiveSensor(12, 6), CapacitiveSensor(12, 7)
                             };    // 10M resistor between pins 12, pin 2 is sensor pin, add a wire and or foil if desired

boolean DEBUG = false;

// TODO - Handle this for communication
boolean thisSensorStatusArray[3] = {false, false, false};
boolean otherSensorStatusArray[3] = {false, false, false};

boolean shouldPlayOther = false;

// TODO - not in use right now
unsigned int ledsPinArray[3] = {LED1, LED2, LED3};

// Hold the each led status
unsigned int ledsStatusArray[LEDS_NUMBER][6];

long capacitiveArray[LEDS_NUMBER];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200) ;
  initLedsStatus();

  // init led strip
  strip.begin();
  strip.setBrightness(64);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Check if other sent a massege, if true listen to other until finishing or timeout.
  if (Serial.available() > 0) {
    shouldPlayOther = true;
    long receiveTime = millis();
    while (shouldPlayOther && receiveTime < TIMEOUT) {
      if (Serial.available() > 0) {
        playOtherTree();
      }
      delay(10);
    }
  }

  long sendTime = millis();
  sendStartMsg();
  while (sendTime < PERIOD_TIME) {
    playThisTree();
  }
  sendEndMsg();
  delay(300);
}





