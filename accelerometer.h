#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Wire.h>
#include <Arduino.h>
#include <DFRobot_LIS2DH12.h>
#include <math.h>

struct rotationValues {
  int16_t bit_x;
  int16_t bit_y;
  float rotation;
};

struct rawXYZ {
  int x;
  int y;
  int z;
};

struct rawXYZ readAccelerometer(DFRobot_LIS2DH12 LIS);
struct rotationValues getRotation(DFRobot_LIS2DH12 LIS);
float roundToNearest(float n, int resolution);
float rad2deg(float n);

#endif
