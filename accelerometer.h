#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Wire.h>
#include <Arduino.h>
#include <DFRobot_LIS2DH12.h>

struct rotationValues {
  int16_t bit_x;
  int16_t bit_y;
  float rotation;
};

void setupAccelerometer(DFRobot_LIS2DH12 *LIS);
void readAccelerometer(DFRobot_LIS2DH12 *LIS, int16_t *x, int16_t *y, int16_t *z);
void getRotation(DFRobot_LIS2DH12 *LIS, struct rotationValues *rotations);

#endif
