#include "matrix.h"
#include "accelerometer.h"
#include "basicAnimations.h"
//#include "letters.h"
#include <Wire.h>

// instantiate accelerometer
DFRobot_LIS2DH12 LIS;
int offset = 0; // used for rainbow effect
struct rotationValues *rotations;
int nColours = 7;
CRGB colours[] = {CRGB::Red, CRGB::Blue, CRGB::Green, CRGB::Fuchsia, CRGB::Cyan, CRGB::DeepPink, CRGB::Gold};
CRGB randomColour;
unsigned long startTime;
unsigned long endTime;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Start of program");
  
  while(!Serial);
  delay(100);
  while(LIS.init(LIS2DH12_RANGE_2GA) == -1){  //Equipment connection exception or I2C address error
    Serial.println("No I2C devices found");
    delay(1000);
  }
  Serial.println("Accelerometer setup");
  
  setupLEDs();
  Serial.println("LEDs setup");
  delay(10000);
  Serial.println("Beginning of effects");
}

void loop() {
  // cycle animations
  randomColour = CRGB::Fuchsia;
  oneByOne(randomColour, 100);

  multiColourFade();

  randomColour = CRGB::Cyan;
  spiral(randomColour);

  startTime = millis();
  endTime = millis();
  while ((endTime - startTime) <= 10000) {
    offset = rainbow(offset);
    endTime = millis();
  }

  startTime = millis();
  endTime = millis();
  while ((endTime - startTime) <= 10000) {
    sinRainbow();
    endTime = millis();
  }

  startTime = millis();
  endTime = millis();
  while ((endTime - startTime) <= 10000) {
    sparkles(false);
    endTime = millis();
  }

  //randomColour = colours[random(nColours)];
  //wordScroll("POOP", randomColour, 100);
  // cycle animations
  randomColour = CRGB::Green;
  oneByOne(randomColour, 100);

  multiColourFade();

  randomColour = CRGB::Blue;
  spiral(randomColour);

  startTime = millis();
  endTime = millis();
  while ((endTime - startTime) <= 10000) {
    offset = rainbow(offset);
    endTime = millis();
  }

  startTime = millis();
  endTime = millis();
  while ((endTime - startTime) <= 10000) {
    sinRainbow();
    endTime = millis();
  }

  startTime = millis();
  endTime = millis();
  while ((endTime - startTime) <= 10000) {
    sparkles(false);
    endTime = millis();
  }
}
