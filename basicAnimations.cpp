#include "basicAnimations.h"

CRGB leds[NUM_LEDS];

void setupLEDs() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
};

/*
Default Colour (all prefixed by CRGB::    e.g. CRGB::Red)
https://github.com/FastLED/FastLED/wiki/Pixel-reference#predefined-colors-list

Common/Nice Colours
- Blue
- Red
- Green
- Fuchsia
- Cyan
- DeepPink
- Gold
*/

void colourFill(CRGB colour) {  
  for (int i=0; i<NUM_LEDS; i++) {
    leds[i] = colour;
  }
  FastLED.show();
};

void colourFill(CHSV colour) {  
  for (int i=0; i<NUM_LEDS; i++) {
    leds[i] = colour;
  }
  FastLED.show();
};

void oneByOne(CRGB colour, int delay_ms) {
  for (int i=0; i<NUM_LEDS; i++) {
    leds[i] = colour;
    FastLED.show();
    delay(delay_ms);
  }

  for (int i=NUM_LEDS; i>0; i--) {
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(delay_ms);
  }
};

void clearAll() {
  FastLED.clear();
  FastLED.show();
}

void multiColourFade() {
  int h = 0;
  for (int i=0; i<255; i++) {
    CHSV dispColour(h+i,175, 175);
    colourFill(dispColour);
    delay(50);
  }
}

void spiral(CRGB colour) {
  struct LED LEDColour = {colour.r, colour.g, colour.b};
  struct matrix disp;
  int top = 0;
  int bottom = MATRIX_LENGTH-1;
  int left = 0;
  int right = MATRIX_LENGTH-1;

  // spiral out to in
  while (true) {
    if (left > right) break;

    // top row
    for (int col = left; col <= right; col++) {
      int row = top;
      disp.M[row][col] = LEDColour;
      displayMatrix(disp);
      delay(50);
    }
    top++;

    if (top > bottom) break;

    // right column
    for (int row = top; row <= bottom; row++) {
      int col = right;
      disp.M[row][col] = LEDColour;
      displayMatrix(disp);
      delay(50);
    }
    right--;

    if (left > right) break;

    // bottom row
    for (int col = right; col >= left; col--) {
      int row = bottom;
      disp.M[row][col] = LEDColour;
      displayMatrix(disp);
      delay(50);
    }
    bottom--;

    if (top > bottom) break;

    // left column
    for (int row = bottom; row >= top; row--) {
      int col = left;
      disp.M[row][col] = LEDColour;
      displayMatrix(disp);
      delay(50);
    }
    left++;
  }
  clearAll();
  delay(500);
}

bool matrixFilledIn(struct matrix disp) {
  for (int i=0; i<NUM_LEDS; i++) {
    int r = floor(i / MATRIX_LENGTH);
    int c = i % MATRIX_LENGTH;
    if (!cellFilledIn(disp.M[r][c])) {
      return false;
    }
  }
  return true;
}

bool cellFilledIn(struct LED cell) {
  return cell.R && cell.G && cell.B;
}

int RC2Linear(int row, int col) {
  return row * MATRIX_LENGTH + col;
}

void displayMatrix(struct matrix disp) {
  for (int r=0; r<MATRIX_LENGTH; r++) {
    for (int c=0; c<MATRIX_LENGTH; c++) {
      int i = r*MATRIX_LENGTH + c;
      leds[i] = CRGB(disp.M[r][c].R, disp.M[r][c].G, disp.M[r][c].B);
    }
  }
  FastLED.show();
}

void waterEffect(DFRobot_LIS2DH12 *LIS) {
  struct matrix disp;
  // calculate rotation
  struct rotationValues *rotations;
  getRotation(LIS, rotations);
  disp.rotation = rotations->rotation;
}
