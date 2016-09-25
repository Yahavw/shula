
#include <Adafruit_NeoPixel.h>
#include <CapacitiveSensor.h>

#define PLAYER "C"

#define PIN A0

//#define THRESHOLD 350
#define LEDS_NUMBER 8

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

int capPotenPin = A1;    // select the input pin for the potentiometer
int speedPotenPin = A2;

int threshold = 10;       // variable to store the value coming from the potentiometer
int speedVal = 10;

int periodTime = 20000;
int timeOut = 30000;

boolean DEBUG = true;

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
  threshold = analogRead(capPotenPin * 5);    // read the value from the sensor
  speedVal = analogRead(speedPotenPin);    // read the value from the sensor
  periodTime = speedVal * 50;
  timeOut = periodTime + 5000;

 
  if (PLAYER == "A") {

    // Start sending
    while (true) {
      sendStartMsg();
      delay(50);
      TreeMsg treeMsg = readMsg();
      if (treeMsg.intro == -2) {
        break;
      }
    }
    unsigned long sendTime = millis();
    while (millis() - sendTime < PERIOD_TIME) {
      playThisTree();
    }
    sendEndMsg();

    // Play together
    sendPlayMsg();
    delay(100);
    while (true) {
      TreeMsg treeMsg = readMsg();
      if (treeMsg.intro == -3) {
        break;
      }
      delay(30);
    }

    playFinalMsg();

    sendStartOtherMsg();
    while (true) {
      TreeMsg treeMsg = readMsg();
      if (treeMsg.intro == -1) {
        break;
      }
      delay(30);
    }
    unsigned long receiveTime = millis();
    while (shouldPlayOther && (millis() - receiveTime) < TIMEOUT) {
      while (Serial.available() > 0) {
        playOtherTree();
      }
      playStandby();
    }

    // Play together
    sendPlayMsg();
    delay(100);
    while (true) {
      TreeMsg treeMsg = readMsg();
      if (treeMsg.intro == -3) {
        break;
      }
      delay(30);
    }

    playFinalMsg();

  } else if (PLAYER == "B") { // player B
    TreeMsg treeMsg = readMsg();
    if (treeMsg.intro == -1) {
      sendEndMsg();
      delay(50);
      unsigned long receiveTime = millis();
      while (shouldPlayOther && (millis() - receiveTime) < TIMEOUT) {
        while (Serial.available() > 0) {
          playOtherTree();
        }
        playStandby();
      }
    } else if (treeMsg.intro == -3) {
      sendPlayMsg();
      playFinalMsg();
    } else if (treeMsg.intro == -4) {
      sendStartMsg();
      unsigned long sendTime = millis();
      while (millis() - sendTime < PERIOD_TIME) {
        playThisTree();
      }
      sendEndMsg();
    }

    delay(10);

  } else {
    // Check if other sent a massege, if true listen to other until finishing or timeout.
    if (Serial.available() > 0) {
      while (Serial.available()) {
        TreeMsg treeMsg = readMsg();
        if (treeMsg.intro == -1) {
          break;
        }
      }
      unsigned long receiveTime = millis();
      //    startOther();
      while (shouldPlayOther && (millis() - receiveTime) < TIMEOUT) {
        while (Serial.available() > 0) {
          playOtherTree();
        }
        playStandby();
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
    delay(200);
  }
}





