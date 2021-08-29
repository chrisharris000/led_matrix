#include "matrix.h"
#include "accelerometer.h"

// instantiate matrix representation
matrix disp;

// instantiate accelerometer
DFRobot_LIS2DH12 *LIS;

void setup() {
  setupAccelerometer(LIS);
}

void loop() {
  // calculate rotation
  struct rotationValues *rotations;
  getRotation(LIS, rotations);
  disp.rotation = rotations->rotation;

}
