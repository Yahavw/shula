#include <Adafruit_NeoPixel.h>
#include <CapacitiveSensor.h>

#define PIN 13

#define LED1 0
#define LED2 1
#define LED3 4

#define THRESHOLD 200
#define LEDS_NUMBER 6

// define led status in array
#define RED 0
#define GREEN 1
#define BLUE 2

// Send/Receive period time
#define PERIOD_TIME 20000
#define TIMEOUT 30000


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
unsigned int ledsStatusArray[LEDS_NUMBER][3];

long capacitiveArray[LEDS_NUMBER];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200) ;
  initLedsStatus();
  initCapacivite(100);
  // init led strip
  strip.begin();
  strip.setBrightness(255);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Check if other sent a massege, if true listen to other until finishing or timeout.
  if (Serial.available() > 0) {
    while (Serial.available()) {
      TreeMsg treeMsg = readMsg();
      if (treeMsg.intro == -1) {
        strip.setPixelColor(7, 255, 0, 0);
        break;
      }
    }
    strip.show();
    unsigned long receiveTime = millis();
    startOther();
    while (shouldPlayOther && (millis() - receiveTime) < TIMEOUT) {
      if (Serial.available() > 0) {
        playOtherTree();
      }
      delay(10);
    }
  }

  sendStartMsg();
  strip.setPixelColor(7, 0, 255, 0);
  playFinalMsg();
  unsigned long sendTime = millis();
  while (millis() - sendTime < PERIOD_TIME) {
    playThisTree();
  }
  playFinalMsg();
  sendEndMsg();
  delay(1000);
}





