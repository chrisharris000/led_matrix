#include "matrix.h"
#include "accelerometer.h"
#include "basicAnimations.h"
#include <Wire.h>

// instantiate accelerometer
DFRobot_LIS2DH12 LIS;
int offset = 0; // used for rainbow effect
struct rotationValues *rotations;

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
  struct rotationValues rotations = getRotation(LIS);
  waterEffect(rotations, CRGB::Red);
}
