#ifndef MATRIX_H
#define MATRIX_H

#define MATRIX_LENGTH 10
#define TOP_LEFT 0
#define TOP_RIGHT 1
#define BOTTOM_RIGHT 2
#define BOTTOM_LEFT 3
#define TOP_EDGE 4
#define RIGHT_EDGE 5
#define BOTTOM_EDGE 6
#define LEFT_EDGE 7

struct LED {
  int R;
  int G;
  int B;
};

struct matrix {
  LED M[MATRIX_LENGTH][MATRIX_LENGTH];
  float rotation;
};

struct point {
  float x;
  float y;
};

int findBottomCorner(float rotation);
float deg2rad(float theta);

#endif
