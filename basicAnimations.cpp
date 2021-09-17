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

void waterEffect(DFRobot_LIS2DH12 *LIS, CRGB colour) {
  struct matrix disp;
  // calculate rotation
  struct rotationValues *rotations;
  getRotation(LIS, rotations);
  disp.rotation = rotations->rotation;

  float particles = 120;
  float wallLength = 340;
  float LEDSpacing = 33.3;
  float particleArea = particles * wallLength;
  struct point p1, p2;
  int corner = findBottomCorner(disp.rotation);
  struct LED LEDdisp = {colour.r, colour.g, colour.b};

  // handle flat edge cases
  if (corner >= TOP_EDGE) {
    if (corner == TOP_EDGE) {
      p1 = {wallLength, particles};
      p2 = {0, particles};
    }

    if (corner == RIGHT_EDGE) {
      p1 = {wallLength-particles, wallLength};
      p2 = {wallLength-particles, 0};
    }

    if (corner == BOTTOM_EDGE) {
      p1 = {0, wallLength-particles};
      p2 = {wallLength, wallLength-particles};
    }

    if (corner == LEFT_EDGE) {
      p1 = {particles, 0};
      p2 = {particles, wallLength};
    }
    //std::cout << p1.x << ", " << p1.y << " - " << p2.x << ", " << p2.y << std::endl;
    float m = (p2.y - p1.y) / (p2.x - p1.x);
    for (int r=0; r<MATRIX_LENGTH; r++) {
      for (int c=0; c<MATRIX_LENGTH; c++) {
        float realX, realY;
        realX = c*LEDSpacing;
        realY = r*LEDSpacing;

        if (corner != TOP_EDGE) {
          if (realY > m*(realX-p1.x)+p1.y) {
            disp.M[r][c] = LEDdisp;
          }
        }
        else {
          if (realY < m*(realX-p1.x)+p1.y) {
            disp.M[r][c] = LEDdisp;
          }
        }
      }
    }
  } // closing if corner >= TOP_EDGE

  // handle corner cases
  else {
    // calculate side lengths
    float quad1_rotation = 90*(corner+2) - disp.rotation;
    float b = sqrt(2*particleArea / tan(deg2rad(quad1_rotation)));
    float h = (2 * particleArea) / b;
    //std::cout << "corner = " << corner << std::endl;
    //std::cout << "rotation = " << rotation << std::endl;
    //std::cout << "quad1_rotation = " << quad1_rotation << std::endl;
    //std::cout << "(b, h) = (" << b << ", " << h << ")" << std::endl;

    if (corner == TOP_LEFT) {
      p1 = {h, 0};
      p2 = {0, b};
    }

    if (corner == TOP_RIGHT) {
      p1 = {wallLength, h};
      p2 = {wallLength - b, 0};
    }

    if (corner == BOTTOM_LEFT) {
      p1 = {wallLength - h, wallLength};
      p2 = {wallLength, wallLength - b};
    }

    if (corner == BOTTOM_RIGHT) {
      p1 = {0, wallLength - h};
      p2 = {b, wallLength};
    }

    //std::cout << p1.x << ", " << p1.y << " - " << p2.x << ", " << p2.y << std::endl;
    float m = (p2.y - p1.y) / (p2.x - p1.x);
    for (int r=0; r<MATRIX_LENGTH; r++) {
      for (int c=0; c<MATRIX_LENGTH; c++) {
        float realX, realY;
        realX = c*LEDSpacing;
        realY = r*LEDSpacing;

        if (corner == BOTTOM_RIGHT || corner == BOTTOM_LEFT) {
          if (realY > m*(realX-p1.x)+p1.y) {
            disp.M[r][c] = LEDdisp;
          }
        }
        else {
          if (realY < m*(realX-p1.x)+p1.y) {
            disp.M[r][c] = LEDdisp;
          }
        }
      }
    }
  } // closing else
}
