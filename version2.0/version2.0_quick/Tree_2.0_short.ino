
#include <Adafruit_NeoPixel.h>
#include <CapacitiveSensor.h>

#define PIN A0
#define LEDS_NUMBER 8
// Send/Receive period time
boolean DEBUG = false;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS_NUMBER , PIN, NEO_GRB + NEO_KHZ800);
CapacitiveSensor   cs_12[] = {CapacitiveSensor(12, 2), CapacitiveSensor(12, 3), CapacitiveSensor(12, 4)
                              , CapacitiveSensor(12, 5), CapacitiveSensor(12, 6), CapacitiveSensor(12, 7), CapacitiveSensor(12, 8), CapacitiveSensor(12, 9)
                             };    // 10M resistor between pins 12, pin 2 is sensor pin, add a wire and or foil if desired

int threshold = 3000;       // variable to store the value coming from the potentiometer
long capacitiveArray[LEDS_NUMBER];
int message[LEDS_NUMBER];
int times[LEDS_NUMBER];
int mintimes = 2;
int maxtimes = 10; //stabilizing counter - number of needed active counts to send a message to other pi and other arduino
//float ramp1 = 1/((maxtimes-mintimes)*4);
//float ramp2 = 1/maxtimes-mintimes;
float ramp1=0.05;
float ramp2=0.1;
int colors[LEDS_NUMBER][2];
int G[LEDS_NUMBER];
int R[LEDS_NUMBER];
int B[LEDS_NUMBER];

void setup() {
    // put your setup code here, to run once:
  Serial.begin(115200) ;
  initCapacivite(100);
  strip.begin();
  strip.setBrightness(255);
  strip.show(); // Initialize all pixels to 'off'
  G[0] = 255; R[0] = 000; B[0] = 000;
  G[1] = 000; R[1] = 255; B[1] = 000;
  G[2] = 000; R[2] = 000; B[2] = 255;
  G[3] = 255; R[3] = 255; B[3] = 000;
  G[4] = 255; R[4] = 000; B[4] = 255;
  G[5] = 255; R[5] = 255; B[5] = 120;
  G[6] = 120; R[6] = 255; B[6] = 255;
  G[7] = 255; R[7] = 120; B[7] = 255;
}

void loop() {
    long start = millis();
    if (DEBUG) {
    debug_loop(start);
    }
    measureCapcitive();
    for (int i = 0; i < LEDS_NUMBER  ; i++) {
      if (capacitiveArray[i] > threshold or capacitiveArray[i] ==-2) {
        strip.setPixelColor(i, G[i], R[i], B[i]);
            Serial.print(1);
            Serial.print("\t");
      }
      else{
         strip.setPixelColor(i, 0, 0, 0);
        Serial.print(0);
        Serial.print("\t");
      }      
    }
    strip.show();
    Serial.print('\n');
    
//  while(Serial.available()){
//    for (int i = 0; i < LEDS_NUMBER  ; i++){
//      message[i] = Serial.readStringUntil('  ').toInt();
//      //Serial.print(message[i]);
//     }
//  }
//    //Serial.print('\n');
//    for (int i = 0; i < LEDS_NUMBER  ; i++) {       
//      if (message[i] == 1){
//       strip.setPixelColor(i, 255, 255, 255); 
//       //Serial.print(3);      
//      }
//      else{
//        //strip.setPixelColor(i, 0, 0, 0);
//        //Serial.print(2); 
//      }
//    }
    //Serial.print('\n');
  strip.show();
  //delay(10);
  


}





