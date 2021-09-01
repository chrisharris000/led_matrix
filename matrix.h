#ifndef MATRIX_H
#define MATRIX_H

#define MATRIX_LENGTH 10

struct LED {
  int R;
  int G;
  int B;
};

struct matrix {
  LED M[MATRIX_LENGTH][MATRIX_LENGTH];
  float rotation;
};

#endif
