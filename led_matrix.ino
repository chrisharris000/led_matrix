#include "matrix.h"
#include "accelerometer.h"
#include "basicAnimations.h"

// instantiate accelerometer
DFRobot_LIS2DH12 *LIS;
int offset = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Start of program");
  //setupAccelerometer(LIS);
  //Serial.println("Accelerometer setup");
  setupLEDs();
  Serial.println("LEDs setup");
  delay(10000);
  Serial.println("Beginning of effects");
}

void loop() {
  spiral(CRGB::Red);
}
