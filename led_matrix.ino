#include "matrix.h"
#include "accelerometer.h"
#include "basicAnimations.h"

// instantiate accelerometer
DFRobot_LIS2DH12 *LIS;

void setup() {
  setupAccelerometer(LIS);
  setupLEDs();
}

void loop() {
  colourFill(CRGB::Red);  
}
