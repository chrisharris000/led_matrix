#include "matrix.h"
#include "math.h"

int findBottomCorner(float rotation) {
  // 0 = top left
  // 1 = top right
  // 2 = bottom right
  // 3 = bottom left
  // 4 = top edge
  // 5 = right edge
  // 6 = bottom edge
  // 7 = left edge
  if (rotation == 0 || rotation == 360) return BOTTOM_EDGE;
  if (rotation == 90) return LEFT_EDGE;
  if (rotation == 180) return TOP_EDGE;
  if (rotation == 270) return RIGHT_EDGE;

  if (0 < rotation && rotation < 90) {
    return BOTTOM_LEFT;
  }

  if (90 < rotation && rotation < 180) {
    return TOP_LEFT;
  }

  if (180 < rotation && rotation < 270) {
    return TOP_RIGHT;
  }

  if (270 < rotation && rotation < 360) {
    return BOTTOM_RIGHT;
  }
  return BOTTOM_EDGE;
}

float deg2rad(float theta) {
  return theta * M_PI / 180;
}
