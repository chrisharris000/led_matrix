#define SIZE 10

struct LED {
  int R;
  int G;
  int B;
};

struct matrix {
  LED M[SIZE][SIZE];
  float rotation;
};
