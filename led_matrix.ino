#include "matrix.h"
#include "accelerometer.h"
#include "basicAnimations.h"

// instantiate accelerometer
DFRobot_LIS2DH12 *LIS;

void setup() {
  Serial.begin(115200);
  Serial.println("Start of program");
  //setupAccelerometer(LIS);
  //Serial.println("Accelerometer setup");
  setupLEDs();
  Serial.println("LEDs setup");
}

void loop() {
  //spiral(CRGB::Red);
  //exit(0);
  //colourFill(CRGB::Red);
  clearAll();
}
