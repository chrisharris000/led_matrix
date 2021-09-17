#include "accelerometer.h"

#define PLANE_AXIS_1 String("x")
#define PLANE_AXIS_2 String("y")
#define ROTATION_RESOLUTION 10

void setupAccelerometer(DFRobot_LIS2DH12 *LIS) {
  Wire.begin();
  Serial.begin(115200);
  while(!Serial);
  delay(100);

  // Set measurement range
  // Ga: LIS2DH12_RANGE_2GA
  // Ga: LIS2DH12_RANGE_4GA
  // Ga: LIS2DH12_RANGE_8GA
  // Ga: LIS2DH12_RANGE_16GA
  while((*LIS).init(LIS2DH12_RANGE_16GA) == -1){  //Equipment connection exception or I2C address error
    Serial.println("No I2C devices found");
    delay(1000);
  }
};

void readAccelerometer(DFRobot_LIS2DH12 *LIS, int16_t *x, int16_t *y, int16_t *z) {
  delay(100);
  (*LIS).readXYZ(*x, *y, *z);
  (*LIS).mgScale(*x, *y, *z);
}

void getRotation(DFRobot_LIS2DH12 *LIS, struct rotationValues *rotations) {
  int16_t *x;
  int16_t *y;
  int16_t *z;
  readAccelerometer(LIS, x, y, z);

  if (PLANE_AXIS_1 == String("x")) {
    (*rotations).bit_x = *x;
  }

  if (PLANE_AXIS_1 == String("y")) {
    (*rotations).bit_x = *y;
  }

  if (PLANE_AXIS_1 == String("z")) {
    (*rotations).bit_x = *z;
  }

  if (PLANE_AXIS_2 == String("x")) {
    (*rotations).bit_y = *x;
  }

  if (PLANE_AXIS_2 == String("y")) {
    (*rotations).bit_y = *y;
  }

  if (PLANE_AXIS_2 == String("z")) {
    (*rotations).bit_y = *z;
  }

  (*rotations).rotation = roundToNearest(atan2((*rotations).bit_y, (*rotations).bit_x), ROTATION_RESOLUTION);
}

float roundToNearest(float n, int resolution) {
    int base = n / resolution;
    return ((base+1)*resolution - n <= n - base*resolution) ? (base+1)*resolution : base*resolution;
}
