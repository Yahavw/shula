
#include <Adafruit_NeoPixel.h>
#include <CapacitiveSensor.h>

#define PIN A0

#define THRESHOLD 350
#define LEDS_NUMBER 7

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

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS_NUMBER + 1, PIN, NEO_GRB + NEO_KHZ800);
CapacitiveSensor   cs_12[] = {CapacitiveSensor(12, 2), CapacitiveSensor(12, 3), CapacitiveSensor(12, 4)
                              , CapacitiveSensor(12, 5), CapacitiveSensor(12, 6), CapacitiveSensor(12, 7), CapacitiveSensor(12, 8)
                             };    // 10M resistor between pins 12, pin 2 is sensor pin, add a wire and or foil if desired

boolean DEBUG = false;

boolean shouldPlayOther = false;

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
  playFinalMsg();
  unsigned long sendTime = millis();
  while (millis() - sendTime < PERIOD_TIME) {
    playThisTree();
  }
  playFinalMsg();
  sendEndMsg();
  delay(1000);
}





