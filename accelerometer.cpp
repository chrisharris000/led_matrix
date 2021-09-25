#include "accelerometer.h"

#define PLANE_AXIS_1 String("x")
#define PLANE_AXIS_2 String("y")
#define ROTATION_RESOLUTION 10

struct rawXYZ readAccelerometer(DFRobot_LIS2DH12 LIS) {
  int x, y, z;
  delay(100);
  (LIS).readXYZ(x, y, z);
  (LIS).mgScale(x, y, z);
  struct rawXYZ retVal = {x, y, z};
  return retVal;
}

struct rotationValues getRotation(DFRobot_LIS2DH12 LIS) {
  struct rawXYZ rawValues = readAccelerometer(LIS);
  struct rotationValues rotations;
  /*Serial.print("x=");
  Serial.println(rawValues.x);
  Serial.print("y=");
  Serial.println(rawValues.y);
  Serial.print("z=");
  Serial.println(rawValues.z);*/
  /*Serial.println("--------------");*/

  if (PLANE_AXIS_1 == String("x")) {
    (rotations).bit_x = rawValues.x;
  }

  if (PLANE_AXIS_1 == String("y")) {
    (rotations).bit_x = rawValues.y;
  }

  if (PLANE_AXIS_1 == String("z")) {
    (rotations).bit_x = rawValues.z;
  }

  if (PLANE_AXIS_2 == String("x")) {
    (rotations).bit_y = rawValues.x;
  }

  if (PLANE_AXIS_2 == String("y")) {
    (rotations).bit_y = rawValues.y;
  }

  if (PLANE_AXIS_2 == String("z")) {
    (rotations).bit_y = rawValues.z;
  }

  float theta = rad2deg(atan2((rotations).bit_y, (rotations).bit_x));
  // correct for different axes
  theta -= 90;
  if (theta < 0) {
    theta += 360;
  }
  (rotations).rotation = roundToNearest(theta, ROTATION_RESOLUTION);
  Serial.print("theta = ");
  Serial.println(theta);
  Serial.print("rotation = ");
  Serial.println(rotations.rotation);
  Serial.println("---------------");
  return rotations;
}

float roundToNearest(float n, int resolution) {
    int base = n / resolution;
    return ((base+1)*resolution - n <= n - base*resolution) ? (base+1)*resolution : base*resolution;
}

float rad2deg(float n) {
  return n * 180 / M_PI;
}
