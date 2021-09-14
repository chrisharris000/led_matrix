#include "matrix.h"
#include "accelerometer.h"
#include "basicAnimations.h"

// instantiate accelerometer
DFRobot_LIS2DH12 *LIS;

void setup() {
  Serial.begin(115200);
  Serial.println("Start of program");
  //setupAccelerometer(LIS);
  setupLEDs();
  Serial.println("LEDs setup");
}

void loop() {
  multiColourFade();  
}
