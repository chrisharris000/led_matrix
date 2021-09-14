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
  struct matrix disp;
  int r = 0;
  int c = 0;
  char dir = 'E';
  int cells = 0;
  struct LED off = {0, 0, 0};

  for (int r=0; r<MATRIX_LENGTH; r++) {
    for (int c=0; c<MATRIX_LENGTH; c++) {
      disp.M[r][c] = off;
    }
  }
  
  while (cells < NUM_LEDS) {
    if (dir == 'E') {
      if (c != MATRIX_LENGTH && !cellFilledIn(disp.M[r][c+1])) {
        c++;
      }
      else {
        Serial.print("(");
        Serial.print(r);
        Serial.print(", ");
        Serial.print(") - cellFilledIn? ");
        Serial.print(cellFilledIn(disp.M[r][c+1]));
        Serial.print(" - dir = ");
        Serial.println(dir);
        dir = 'S';
        r++;
      }
    }

    else if (dir == 'S') {
      if (r != MATRIX_LENGTH && !cellFilledIn(disp.M[r+1][c])) {
        r++;
      }
      else {
        Serial.print("(");
        Serial.print(r);
        Serial.print(", ");
        Serial.print(") - cellFilledIn? ");
        Serial.print(cellFilledIn(disp.M[r][c+1]));
        Serial.print(" - dir = ");
        Serial.println(dir);
        dir = 'W';
        c--;
      }
    }

    else if (dir == 'W') {
      if (c != 0 && !cellFilledIn(disp.M[r][c-1])) {
        c--;
      }
      else {
        Serial.print("(");
        Serial.print(r);
        Serial.print(", ");
        Serial.print(") - cellFilledIn? ");
        Serial.print(cellFilledIn(disp.M[r][c+1]));
        Serial.print(" - dir = ");
        Serial.println(dir);
        dir = 'S';
        r--;
      }
    }

    else if (dir == 'N') {
      if (r != 0 && !cellFilledIn(disp.M[r-1][c])) {
        r--;
      }
      else {
        Serial.print("(");
        Serial.print(r);
        Serial.print(", ");
        Serial.print(") - cellFilledIn? ");
        Serial.print(cellFilledIn(disp.M[r][c+1]));
        Serial.print(" - dir = ");
        Serial.println(dir);
        dir = 'E';
        c++;
      }
    }

    struct LED cell = {colour.r, colour.g, colour.b};
    disp.M[r][c] = cell;
    displayMatrix(disp);
    delay(100);
    cells++;
    Serial.print(r);
    Serial.print(", ");
    Serial.println(c);
  }
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
