#include "basicAnimations.h"
#include "letters.h"

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
  FastLED.clear();
  FastLED.show();
  
  for (int i=0; i<NUM_LEDS; i++) {
    leds[i] = colour;
  }
  
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
    CHSV dispColour(h+i,200, 200);
    colourFill(dispColour);
    delay(50);
  }
}

void spiral(CRGB colour) {
  /*
  int rowCoords[NUM_LEDS];
  int colCoords[NUM_LEDS];
  int i = 0;
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
      rowCoords[i] = row;
      colCoords[i] = col;
      i++;
    }
    top++;

    if (top > bottom) break;

    // right column
    for (int row = top; row <= bottom; row++) {
      int col = right;
      rowCoords[i] = row;
      colCoords[i] = col;
      i++;
    }
    right--;

    if (left > right) break;

    // bottom row
    for (int col = right; col >= left; col--) {
      int row = bottom;
      rowCoords[i] = row;
      colCoords[i] = col;
      i++;
    }
    bottom--;

    if (top > bottom) break;

    // left column
    for (int row = bottom; row >= top; row--) {
      int col = left;
      rowCoords[i] = row;
      colCoords[i] = col;
      i++;
    }
    left++;
  }
  */
  // to generate hardcoded arrays try the above
  int rowCoords[NUM_LEDS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7, 8, 8, 8, 8, 8, 8, 8, 8, 7, 6, 5, 4, 3, 2, 2, 2, 2, 2, 2, 2, 3, 4, 5, 6, 7, 7, 7, 7, 7, 7, 6, 5, 4, 3, 3, 3, 3, 3, 4, 5, 6, 6, 6, 6, 5, 4, 4, 4, 5, 5};
  int colCoords[NUM_LEDS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 8, 8, 8, 8, 8, 8, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7, 7, 7, 7, 7, 7, 6, 5, 4, 3, 2, 2, 2, 2, 2, 3, 4, 5, 6, 6, 6, 6, 5, 4, 3, 3, 3, 4, 5, 5, 4};
  // outside to inside
  for (int i = 0; i<NUM_LEDS; i++) {
    int l = RC2Linear(rowCoords[i], colCoords[i]);
    leds[l] = colour;
    FastLED.show();
    delay(50);
  }
  // inside to outside
  for (int i = NUM_LEDS-1; i>=0; i--) {
    int l = RC2Linear(rowCoords[i], colCoords[i]);
    leds[l] = CRGB::Black;
    FastLED.show();
    delay(50);
  }
}

/*bool matrixFilledIn(struct matrix disp) {
  for (int i=0; i<NUM_LEDS; i++) {
    int r = floor(i / MATRIX_LENGTH);
    int c = i % MATRIX_LENGTH;
    if (!cellFilledIn(disp.M[r][c])) {
      return false;
    }
  }
  return true;
}*/

/*bool cellFilledIn(struct LED cell) {
  return cell.R && cell.G && cell.B;
}*/

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

void waterEffect(struct rotationValues rotations, CRGB colour) {
  struct matrix disp;
  disp.rotation = rotations.rotation;

  struct LED off = {0, 0, 0};
  for (int r=0; r<MATRIX_LENGTH; r++) {
      for (int c=0; c<MATRIX_LENGTH; c++) {
        disp.M[r][c] = off;
      }
  }

  float particles = 120;
  float wallLength = 340; // side length of actual 10x10 matrix in mm
  float LEDSpacing = 33.3; // distance in mm between each LED (i.e. 30 LEDs/m = 1 LED/33.3mm
  float particleArea = particles * wallLength; // determines approximate area in mm^2 that will be covered with water
   // coordinate system is with top left corner as (0, 0)
   // postive x axis is toward the right hand edge
   // positive y axis is toward the bottom edge
  struct point p1, p2;
  int corner = findBottomCorner(disp.rotation); // this is the corner/edge that the 'water' will pool in
  struct LED LEDdisp = {colour.r, colour.g, colour.b};

  // handle flat edge cases
  if (corner >= TOP_EDGE) {
    // for flat edge cases, the water is stagnant forming a rectangle/square
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

    float m = (p2.y - p1.y) / (p2.x - p1.x);

    for (int r=0; r<MATRIX_LENGTH; r++) {
      for (int c=0; c<MATRIX_LENGTH; c++) {
        float realX, realY;
        realX = c*LEDSpacing;
        realY = r*LEDSpacing;

        if (corner != TOP_EDGE) {
          // inequality checks whether a given cell (r,c), when projected into the real world coordinates (realY, realX)
          // is located below the line formed between the 2 points calculated before
          // special case is the top edge because... (didn't have time to figure this out)
          if (realY > m*(realX-p1.x)+p1.y) {
            int l = RC2Linear(r, c);
            leds[l] = colour;
          }
        }
        else {
          if (realY < m*(realX-p1.x)+p1.y) {
            int l = RC2Linear(r, c);
            leds[l] = colour;
          }
        }
      }
    }
  } // closing if corner >= TOP_EDGE

  // handle corner cases
  
  else {
    // calculate side lengths
    float quad1_rotation = 90 - ((int)(90*(corner+2) - disp.rotation) % 360); // calculate rotation in the range of 0-90 (independent of what the overall rotation is)
    // the area covered by the water will form a triangle with some rotation (quad1_rotation) and side lengths b and h
    // We know that the area of the triangle (in the real world) will be A = 0.5 * b * h
    // We also know that tan(theta) = opp / adj
    // Combining these 2 facts we get the 2 values below
    float b = sqrt(2*particleArea / tan(deg2rad(quad1_rotation)));
    float h = (2 * particleArea) / b;

    if (corner == TOP_LEFT) {
      p1 = {h, 0}; // originally top left coords
      p2 = {0, b}; // originally top left coords
    }

    if (corner == TOP_RIGHT) {
      p1 = {wallLength, h}; // originally top right coords
      p2 = {wallLength - b, 0}; // originally top right coords
    }

    if (corner == BOTTOM_RIGHT) {
      p1 = {wallLength - h, wallLength}; // originally bottom left coords
      p2 = {wallLength, wallLength - b}; // originally bottom left coords 
    }

    if (corner == BOTTOM_LEFT) {
      p1 = {0, wallLength - h}; // originally bottom right coords
      p2 = {b, wallLength}; // originally bottom right coords
    }

    float m = (p2.y - p1.y) / (p2.x - p1.x);
    for (int r=0; r<MATRIX_LENGTH; r++) {
      for (int c=0; c<MATRIX_LENGTH; c++) {
        float realX, realY;
        realX = c*LEDSpacing;
        realY = r*LEDSpacing;

        // similar to flat edge scenario, except BOTTOM_RIGHT and BOTTOM_LEFT are edge cases
        // Again, didn't have time to figure it out
        if (corner == BOTTOM_RIGHT || corner == BOTTOM_LEFT) {
          if (realY > m*(realX-p1.x)+p1.y) {
            int l = RC2Linear(r, c);
            leds[l] = colour;
          }
        }
        else {
          if (realY < m*(realX-p1.x)+p1.y) {
            int l = RC2Linear(r, c);
            leds[l] = colour;
          }
        }
      }
    }
  } // closing else
  
  FastLED.show();
  delay(100); // vary delay, couldn't really avoid flickering
  clearAll();
}

void basicWipe(CRGB colour) {
  //struct matrix disp;
  struct LED colourDisp = {colour.r, colour.g, colour.b};
  struct LED off = {0, 0, 0};
  int rCoordsToDisp[10];
  int cCoordsToDisp[10];
  clearAll();
  for (int r = MATRIX_LENGTH-1; r>=0; r--) {
    for (int c = 0; c<MATRIX_LENGTH; c++) {
      //disp.M[r][c] = off;
    }
  }

  // left to right
  for (int c = 0; c<MATRIX_LENGTH; c++) {
    for (int r = 0; r<MATRIX_LENGTH; r++) {
      //disp.M[r][c] = colourDisp;
      rCoordsToDisp[r] = r;
      cCoordsToDisp[r] = c;
    }
    //displayMatrix(disp);
    for (int i=0; i<10; i++) {
      int l = RC2Linear(rCoordsToDisp[i], cCoordsToDisp[i]);
      leds[l] = colour;
    }
    FastLED.show();
    delay(MS_BETWEEN_WIPE_FRAMES);
    FastLED.clear();
    FastLED.show();
    for (int r = MATRIX_LENGTH-1; r>=0; r--) {
      for (int c = 0; c<MATRIX_LENGTH; c++) {
        //disp.M[r][c] = off;
      }
    }
  }

  FastLED.clear();
  FastLED.show();
  delay(3*MS_BETWEEN_WIPE_FRAMES);

  // right to left
  for (int c = MATRIX_LENGTH-1; c>=0; c--) {
    for (int r = 0; r<MATRIX_LENGTH; r++) {
      //disp.M[r][c] = colourDisp;
      rCoordsToDisp[r] = r;
      cCoordsToDisp[r] = c;
    }
    for (int i=0; i<10; i++) {
      int l = RC2Linear(rCoordsToDisp[i], cCoordsToDisp[i]);
      leds[l] = colour;
    }
    FastLED.show();
    //displayMatrix(disp);
    delay(MS_BETWEEN_WIPE_FRAMES);
    FastLED.clear();
    FastLED.show();
    for (int r = MATRIX_LENGTH-1; r>=0; r--) {
      for (int c = 0; c<MATRIX_LENGTH; c++) {
        //disp.M[r][c] = off;
      }
    }
  }

  FastLED.clear();
  FastLED.show();
  delay(3*MS_BETWEEN_WIPE_FRAMES);

  // top to bottom
  for (int r = 0; r<MATRIX_LENGTH; r++) {
    for (int c = 0; c<MATRIX_LENGTH; c++) {
      //disp.M[r][c] = colourDisp;
      rCoordsToDisp[r] = r;
      cCoordsToDisp[r] = c;
    }

    //displayMatrix(disp);
    for (int i=0; i<10; i++) {
      int l = RC2Linear(rCoordsToDisp[i], cCoordsToDisp[i]);
      leds[l] = colour;
    }
    FastLED.show();
    delay(MS_BETWEEN_WIPE_FRAMES);
    FastLED.clear();
    FastLED.show();
    for (int r = MATRIX_LENGTH-1; r>=0; r--) {
      for (int c = 0; c<MATRIX_LENGTH; c++) {
        //disp.M[r][c] = off;
      }
    }
  }

  FastLED.clear();
  FastLED.show();
  delay(3*MS_BETWEEN_WIPE_FRAMES);

  // bottom to top
  for (int r = MATRIX_LENGTH-1; r>=0; r--) {
    for (int c = 0; c<MATRIX_LENGTH; c++) {
      //disp.M[r][c] = colourDisp;
      rCoordsToDisp[r] = r;
      cCoordsToDisp[r] = c;
    }

    //displayMatrix(disp);
    for (int i=0; i<10; i++) {
      int l = RC2Linear(rCoordsToDisp[i], cCoordsToDisp[i]);
      leds[l] = colour;
    }
    FastLED.show();
    delay(MS_BETWEEN_WIPE_FRAMES);
    FastLED.clear();
    FastLED.show();
    for (int r = MATRIX_LENGTH-1; r>=0; r--) {
      for (int c = 0; c<MATRIX_LENGTH; c++) {
        //disp.M[r][c] = off;
      }
    }
  }
  FastLED.clear();
  FastLED.show();
  delay(3*MS_BETWEEN_WIPE_FRAMES);
}

int rainbow(int offset) {
  // credit - https://editor.soulmatelights.com/tutorial
  offset++;
  for (int x = 0; x < MATRIX_LENGTH; x++) {
    for (int y = 0; y < MATRIX_LENGTH; y++) {
      // XY tells us the index of a given X/Y coordinate
      int index = RC2Linear(x, y);

      // Let's take the X and Y values, and add them together to get the hue
      int hue = x * 10 + y * 10;

      // add the offset so it changes every frame
      hue += offset;
      leds[index] = CHSV(hue, 255, 255);
    }
  }
  FastLED.show();
  return offset;
}

void sinRainbow() {
  // credit - https://editor.soulmatelights.com/tutorial
  int offset = beatsin8(12, 0, 255);

  for (int x = 0; x < MATRIX_LENGTH; x++) {
    for (int y = 0; y < MATRIX_LENGTH; y++) {
      int index = RC2Linear(x, y);
      int hue = y * 10 + x * 10;
      leds[index] = CHSV(hue + offset, 255, 255);
    }
  }
  FastLED.show();
}

void sparkles(bool finishAnimation) {
  // credit - https://editor.soulmatelights.com/tutorial
  // 6 beats per minute, between 1 and 10
  int numberOfSparkles = beatsin16(6, 10, 20);
  int hue = 50;
  while (!finishAnimation) {
    EVERY_N_MILLISECONDS(100) {
      for (int i = 0; i < numberOfSparkles; i++) {
        int pos = random16(NUM_LEDS);
  
        if (!leds[pos]) {
          leds[pos] = CHSV(hue + (pos / 10), 255, 255);
        }
      }
      FastLED.show();
    }
  
    EVERY_N_MILLISECONDS(150) {
      hue -= 1;
    }
  
    fade_raw(leds, NUM_LEDS, 4);
  }
}

// used for fire effect
int scalexy = 60; // scale of fire
int _speed = 20; //speed of effect 

DEFINE_GRADIENT_PALETTE(firepal) { // define fire palette
  0,  0,  0,  0, //black
  32,  255,  0,  0, // red
  190,  255,  255,  0, //yellow
  255,  255,  255,  255 // white
};
void fire(bool finishAnimation) {
  // credit - https://editor.soulmatelights.com/gallery/234-fire
  while (!finishAnimation) {
    CRGBPalette16 myPal = firepal;
  
   uint16_t a = millis();
    for (int i = 0; i < MATRIX_LENGTH; i++) {
      for (int j = 0; j < MATRIX_LENGTH; j++) {
        leds[RC2Linear((MATRIX_LENGTH - 1) - i, (MATRIX_LENGTH - 1) - j)] = ColorFromPalette(myPal, qsub8(inoise8(i * scalexy, j * scalexy + a, a / _speed), abs8(j - (MATRIX_LENGTH - 1)) * 255 / (MATRIX_LENGTH - 1)), BRIGHTNESS);
        
      }
    }
    FastLED.show();
  }
}

void elsocFullAnimation() {
  elsocLogo();
  delay(2000);
  EAnimation();
  LAnimation();
  SAnimation();
  OAnimation();
  CAnimation();
}

void elsocLogo() {
  // used software in this video to make logo and letter animations - https://www.youtube.com/watch?v=o6_UYb6I4x4
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(255, 255, 255);
  leds[6] = CRGB(255, 255, 0);
  leds[7] = CRGB(255, 255, 0);
  leds[8] = CRGB(255, 255, 0);
  leds[9] = CRGB(255, 255, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(255, 255, 255);
  leds[16] = CRGB(255, 255, 0);
  leds[17] = CRGB(255, 255, 0);
  leds[18] = CRGB(255, 255, 0);
  leds[19] = CRGB(255, 255, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[22] = CRGB(0, 0, 0);
  leds[23] = CRGB(0, 0, 0);
  leds[24] = CRGB(0, 0, 0);
  leds[25] = CRGB(255, 255, 255);
  leds[26] = CRGB(255, 255, 0);
  leds[27] = CRGB(255, 255, 0);
  leds[28] = CRGB(255, 255, 0);
  leds[29] = CRGB(255, 255, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(0, 0, 0);
  leds[33] = CRGB(0, 0, 0);
  leds[34] = CRGB(0, 0, 0);
  leds[35] = CRGB(255, 255, 255);
  leds[36] = CRGB(255, 255, 0);
  leds[37] = CRGB(255, 255, 0);
  leds[38] = CRGB(255, 255, 0);
  leds[39] = CRGB(255, 255, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[42] = CRGB(0, 0, 0);
  leds[43] = CRGB(255, 255, 255);
  leds[44] = CRGB(255, 255, 255);
  leds[45] = CRGB(255, 255, 255);
  leds[46] = CRGB(255, 255, 255);
  leds[47] = CRGB(255, 255, 255);
  leds[48] = CRGB(255, 255, 255);
  leds[49] = CRGB(255, 255, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(255, 255, 255);
  leds[52] = CRGB(0, 0, 0);
  leds[53] = CRGB(255, 255, 255);
  leds[54] = CRGB(0, 0, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[56] = CRGB(255, 255, 255);
  leds[57] = CRGB(255, 255, 0);
  leds[58] = CRGB(255, 255, 0);
  leds[59] = CRGB(255, 255, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[61] = CRGB(255, 255, 255);
  leds[62] = CRGB(255, 255, 255);
  leds[63] = CRGB(0, 0, 0);
  leds[64] = CRGB(0, 0, 0);
  leds[65] = CRGB(0, 0, 0);
  leds[66] = CRGB(0, 0, 0);
  leds[67] = CRGB(255, 255, 255);
  leds[68] = CRGB(255, 255, 0);
  leds[69] = CRGB(255, 255, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(255, 255, 255);
  leds[72] = CRGB(255, 255, 255);
  leds[73] = CRGB(255, 255, 255);
  leds[74] = CRGB(0, 0, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[76] = CRGB(0, 0, 0);
  leds[77] = CRGB(0, 0, 0);
  leds[78] = CRGB(255, 255, 255);
  leds[79] = CRGB(255, 255, 0);
  leds[80] = CRGB(255, 255, 255);
  leds[81] = CRGB(0, 0, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[84] = CRGB(0, 0, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[86] = CRGB(0, 0, 0);
  leds[87] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  leds[89] = CRGB(255, 255, 255);
  leds[90] = CRGB(0, 0, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[92] = CRGB(0, 0, 0);
  leds[93] = CRGB(0, 0, 0);
  leds[94] = CRGB(0, 0, 0);
  leds[95] = CRGB(0, 0, 0);
  leds[96] = CRGB(0, 0, 0);
  leds[97] = CRGB(0, 0, 0);
  leds[98] = CRGB(0, 0, 0);
  leds[99] = CRGB(255, 255, 255);
  FastLED.show();
}

void EAnimation() {
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  leds[6] = CRGB(0, 0, 0);
  leds[7] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[22] = CRGB(0, 0, 0);
  leds[23] = CRGB(0, 0, 0);
  leds[24] = CRGB(0, 0, 0);
  leds[25] = CRGB(0, 0, 0);
  leds[26] = CRGB(0, 0, 0);
  leds[27] = CRGB(0, 0, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(0, 0, 0);
  leds[33] = CRGB(0, 0, 0);
  leds[34] = CRGB(0, 0, 0);
  leds[35] = CRGB(0, 0, 0);
  leds[36] = CRGB(0, 0, 0);
  leds[37] = CRGB(0, 0, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[42] = CRGB(0, 0, 0);
  leds[43] = CRGB(0, 0, 0);
  leds[44] = CRGB(0, 0, 0);
  leds[45] = CRGB(0, 0, 0);
  leds[46] = CRGB(0, 0, 0);
  leds[47] = CRGB(0, 0, 0);
  leds[48] = CRGB(0, 0, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[52] = CRGB(0, 0, 0);
  leds[53] = CRGB(0, 0, 0);
  leds[54] = CRGB(0, 0, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[56] = CRGB(0, 0, 0);
  leds[57] = CRGB(0, 0, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[62] = CRGB(0, 0, 0);
  leds[63] = CRGB(0, 0, 0);
  leds[64] = CRGB(0, 0, 0);
  leds[65] = CRGB(0, 0, 0);
  leds[66] = CRGB(0, 0, 0);
  leds[67] = CRGB(0, 0, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(0, 0, 0);
  leds[73] = CRGB(0, 0, 0);
  leds[74] = CRGB(0, 0, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[76] = CRGB(0, 0, 0);
  leds[77] = CRGB(0, 0, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[81] = CRGB(0, 0, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[84] = CRGB(0, 0, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[86] = CRGB(0, 0, 0);
  leds[87] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[90] = CRGB(255, 255, 0);
  leds[91] = CRGB(255, 255, 0);
  leds[92] = CRGB(255, 255, 0);
  leds[93] = CRGB(255, 255, 0);
  leds[94] = CRGB(255, 255, 0);
  leds[95] = CRGB(255, 255, 0);
  leds[96] = CRGB(255, 255, 0);
  leds[97] = CRGB(255, 255, 0);
  leds[98] = CRGB(255, 255, 0);
  leds[99] = CRGB(255, 255, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[70] = CRGB(255, 255, 0);
  leds[71] = CRGB(255, 255, 0);
  leds[72] = CRGB(255, 255, 0);
  leds[73] = CRGB(255, 255, 0);
  leds[74] = CRGB(255, 255, 0);
  leds[75] = CRGB(255, 255, 0);
  leds[76] = CRGB(255, 255, 0);
  leds[77] = CRGB(255, 255, 0);
  leds[78] = CRGB(255, 255, 0);
  leds[79] = CRGB(255, 255, 0);
  leds[80] = CRGB(255, 255, 0);
  leds[85] = CRGB(255, 255, 0);
  leds[89] = CRGB(255, 255, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[92] = CRGB(0, 0, 0);
  leds[93] = CRGB(0, 0, 0);
  leds[94] = CRGB(0, 0, 0);
  leds[96] = CRGB(0, 0, 0);
  leds[97] = CRGB(0, 0, 0);
  leds[98] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[50] = CRGB(255, 255, 0);
  leds[51] = CRGB(255, 255, 0);
  leds[52] = CRGB(255, 255, 0);
  leds[53] = CRGB(255, 255, 0);
  leds[54] = CRGB(255, 255, 0);
  leds[55] = CRGB(255, 255, 0);
  leds[56] = CRGB(255, 255, 0);
  leds[57] = CRGB(255, 255, 0);
  leds[58] = CRGB(255, 255, 0);
  leds[59] = CRGB(255, 255, 0);
  leds[60] = CRGB(255, 255, 0);
  leds[65] = CRGB(255, 255, 0);
  leds[69] = CRGB(255, 255, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(0, 0, 0);
  leds[73] = CRGB(0, 0, 0);
  leds[74] = CRGB(0, 0, 0);
  leds[76] = CRGB(0, 0, 0);
  leds[77] = CRGB(0, 0, 0);
  leds[78] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[30] = CRGB(255, 255, 0);
  leds[31] = CRGB(255, 255, 0);
  leds[32] = CRGB(255, 255, 0);
  leds[33] = CRGB(255, 255, 0);
  leds[34] = CRGB(255, 255, 0);
  leds[35] = CRGB(255, 255, 0);
  leds[36] = CRGB(255, 255, 0);
  leds[37] = CRGB(255, 255, 0);
  leds[38] = CRGB(255, 255, 0);
  leds[39] = CRGB(255, 255, 0);
  leds[40] = CRGB(255, 255, 0);
  leds[45] = CRGB(255, 255, 0);
  leds[49] = CRGB(255, 255, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[52] = CRGB(0, 0, 0);
  leds[53] = CRGB(0, 0, 0);
  leds[54] = CRGB(0, 0, 0);
  leds[56] = CRGB(0, 0, 0);
  leds[57] = CRGB(0, 0, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[90] = CRGB(0, 0, 0);
  leds[95] = CRGB(0, 0, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[10] = CRGB(255, 255, 0);
  leds[11] = CRGB(255, 255, 0);
  leds[12] = CRGB(255, 255, 0);
  leds[13] = CRGB(255, 255, 0);
  leds[14] = CRGB(255, 255, 0);
  leds[15] = CRGB(255, 255, 0);
  leds[16] = CRGB(255, 255, 0);
  leds[17] = CRGB(255, 255, 0);
  leds[18] = CRGB(255, 255, 0);
  leds[19] = CRGB(255, 255, 0);
  leds[20] = CRGB(255, 255, 0);
  leds[25] = CRGB(255, 255, 0);
  leds[29] = CRGB(255, 255, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(0, 0, 0);
  leds[33] = CRGB(0, 0, 0);
  leds[34] = CRGB(0, 0, 0);
  leds[36] = CRGB(0, 0, 0);
  leds[37] = CRGB(0, 0, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[65] = CRGB(0, 0, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[0] = CRGB(255, 255, 0);
  leds[5] = CRGB(255, 255, 0);
  leds[9] = CRGB(255, 255, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[45] = CRGB(0, 0, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[59] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[20] = CRGB(0, 0, 0);
  leds[25] = CRGB(0, 0, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[35] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[0] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[19] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
}

void LAnimation() {
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  leds[6] = CRGB(0, 0, 0);
  leds[7] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[22] = CRGB(0, 0, 0);
  leds[23] = CRGB(0, 0, 0);
  leds[24] = CRGB(0, 0, 0);
  leds[25] = CRGB(0, 0, 0);
  leds[26] = CRGB(0, 0, 0);
  leds[27] = CRGB(0, 0, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(0, 0, 0);
  leds[33] = CRGB(0, 0, 0);
  leds[34] = CRGB(0, 0, 0);
  leds[35] = CRGB(0, 0, 0);
  leds[36] = CRGB(0, 0, 0);
  leds[37] = CRGB(0, 0, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[42] = CRGB(0, 0, 0);
  leds[43] = CRGB(0, 0, 0);
  leds[44] = CRGB(0, 0, 0);
  leds[45] = CRGB(0, 0, 0);
  leds[46] = CRGB(0, 0, 0);
  leds[47] = CRGB(0, 0, 0);
  leds[48] = CRGB(0, 0, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[52] = CRGB(0, 0, 0);
  leds[53] = CRGB(0, 0, 0);
  leds[54] = CRGB(0, 0, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[56] = CRGB(0, 0, 0);
  leds[57] = CRGB(0, 0, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[62] = CRGB(0, 0, 0);
  leds[63] = CRGB(0, 0, 0);
  leds[64] = CRGB(0, 0, 0);
  leds[65] = CRGB(0, 0, 0);
  leds[66] = CRGB(0, 0, 0);
  leds[67] = CRGB(0, 0, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(0, 0, 0);
  leds[73] = CRGB(0, 0, 0);
  leds[74] = CRGB(0, 0, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[76] = CRGB(0, 0, 0);
  leds[77] = CRGB(0, 0, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[81] = CRGB(0, 0, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[84] = CRGB(0, 0, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[86] = CRGB(0, 0, 0);
  leds[87] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[90] = CRGB(255, 255, 0);
  leds[91] = CRGB(255, 255, 0);
  leds[92] = CRGB(255, 255, 0);
  leds[93] = CRGB(255, 255, 0);
  leds[94] = CRGB(255, 255, 0);
  leds[95] = CRGB(255, 255, 0);
  leds[96] = CRGB(255, 255, 0);
  leds[97] = CRGB(255, 255, 0);
  leds[98] = CRGB(255, 255, 0);
  leds[99] = CRGB(255, 255, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[70] = CRGB(255, 255, 0);
  leds[71] = CRGB(255, 255, 0);
  leds[72] = CRGB(255, 255, 0);
  leds[73] = CRGB(255, 255, 0);
  leds[74] = CRGB(255, 255, 0);
  leds[75] = CRGB(255, 255, 0);
  leds[76] = CRGB(255, 255, 0);
  leds[77] = CRGB(255, 255, 0);
  leds[78] = CRGB(255, 255, 0);
  leds[79] = CRGB(255, 255, 0);
  leds[80] = CRGB(255, 255, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[92] = CRGB(0, 0, 0);
  leds[93] = CRGB(0, 0, 0);
  leds[94] = CRGB(0, 0, 0);
  leds[95] = CRGB(0, 0, 0);
  leds[96] = CRGB(0, 0, 0);
  leds[97] = CRGB(0, 0, 0);
  leds[98] = CRGB(0, 0, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[50] = CRGB(255, 255, 0);
  leds[51] = CRGB(255, 255, 0);
  leds[52] = CRGB(255, 255, 0);
  leds[53] = CRGB(255, 255, 0);
  leds[54] = CRGB(255, 255, 0);
  leds[55] = CRGB(255, 255, 0);
  leds[56] = CRGB(255, 255, 0);
  leds[57] = CRGB(255, 255, 0);
  leds[58] = CRGB(255, 255, 0);
  leds[59] = CRGB(255, 255, 0);
  leds[60] = CRGB(255, 255, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(0, 0, 0);
  leds[73] = CRGB(0, 0, 0);
  leds[74] = CRGB(0, 0, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[76] = CRGB(0, 0, 0);
  leds[77] = CRGB(0, 0, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[30] = CRGB(255, 255, 0);
  leds[31] = CRGB(255, 255, 0);
  leds[32] = CRGB(255, 255, 0);
  leds[33] = CRGB(255, 255, 0);
  leds[34] = CRGB(255, 255, 0);
  leds[35] = CRGB(255, 255, 0);
  leds[36] = CRGB(255, 255, 0);
  leds[37] = CRGB(255, 255, 0);
  leds[38] = CRGB(255, 255, 0);
  leds[39] = CRGB(255, 255, 0);
  leds[40] = CRGB(255, 255, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[52] = CRGB(0, 0, 0);
  leds[53] = CRGB(0, 0, 0);
  leds[54] = CRGB(0, 0, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[56] = CRGB(0, 0, 0);
  leds[57] = CRGB(0, 0, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[90] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[10] = CRGB(255, 255, 0);
  leds[11] = CRGB(255, 255, 0);
  leds[12] = CRGB(255, 255, 0);
  leds[13] = CRGB(255, 255, 0);
  leds[14] = CRGB(255, 255, 0);
  leds[15] = CRGB(255, 255, 0);
  leds[16] = CRGB(255, 255, 0);
  leds[17] = CRGB(255, 255, 0);
  leds[18] = CRGB(255, 255, 0);
  leds[19] = CRGB(255, 255, 0);
  leds[20] = CRGB(255, 255, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(0, 0, 0);
  leds[33] = CRGB(0, 0, 0);
  leds[34] = CRGB(0, 0, 0);
  leds[35] = CRGB(0, 0, 0);
  leds[36] = CRGB(0, 0, 0);
  leds[37] = CRGB(0, 0, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[0] = CRGB(255, 255, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[20] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[0] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
}

void SAnimation() {
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  leds[6] = CRGB(0, 0, 0);
  leds[7] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[22] = CRGB(0, 0, 0);
  leds[23] = CRGB(0, 0, 0);
  leds[24] = CRGB(0, 0, 0);
  leds[25] = CRGB(0, 0, 0);
  leds[26] = CRGB(0, 0, 0);
  leds[27] = CRGB(0, 0, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(0, 0, 0);
  leds[33] = CRGB(0, 0, 0);
  leds[34] = CRGB(0, 0, 0);
  leds[35] = CRGB(0, 0, 0);
  leds[36] = CRGB(0, 0, 0);
  leds[37] = CRGB(0, 0, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[42] = CRGB(0, 0, 0);
  leds[43] = CRGB(0, 0, 0);
  leds[44] = CRGB(0, 0, 0);
  leds[45] = CRGB(0, 0, 0);
  leds[46] = CRGB(0, 0, 0);
  leds[47] = CRGB(0, 0, 0);
  leds[48] = CRGB(0, 0, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[52] = CRGB(0, 0, 0);
  leds[53] = CRGB(0, 0, 0);
  leds[54] = CRGB(0, 0, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[56] = CRGB(0, 0, 0);
  leds[57] = CRGB(0, 0, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[62] = CRGB(0, 0, 0);
  leds[63] = CRGB(0, 0, 0);
  leds[64] = CRGB(0, 0, 0);
  leds[65] = CRGB(0, 0, 0);
  leds[66] = CRGB(0, 0, 0);
  leds[67] = CRGB(0, 0, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(0, 0, 0);
  leds[73] = CRGB(0, 0, 0);
  leds[74] = CRGB(0, 0, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[76] = CRGB(0, 0, 0);
  leds[77] = CRGB(0, 0, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[81] = CRGB(0, 0, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[84] = CRGB(0, 0, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[86] = CRGB(0, 0, 0);
  leds[87] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[90] = CRGB(0, 0, 0);
  leds[91] = CRGB(255, 255, 0);
  leds[92] = CRGB(255, 255, 0);
  leds[93] = CRGB(0, 0, 0);
  leds[94] = CRGB(0, 0, 0);
  leds[95] = CRGB(255, 255, 0);
  leds[96] = CRGB(255, 255, 0);
  leds[97] = CRGB(255, 255, 0);
  leds[98] = CRGB(255, 255, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[71] = CRGB(255, 255, 0);
  leds[72] = CRGB(255, 255, 0);
  leds[75] = CRGB(255, 255, 0);
  leds[76] = CRGB(255, 255, 0);
  leds[77] = CRGB(255, 255, 0);
  leds[78] = CRGB(255, 255, 0);
  leds[80] = CRGB(255, 255, 0);
  leds[81] = CRGB(255, 255, 0);
  leds[84] = CRGB(255, 255, 0);
  leds[85] = CRGB(255, 255, 0);
  leds[88] = CRGB(255, 255, 0);
  leds[89] = CRGB(255, 255, 0);
  leds[90] = CRGB(255, 255, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[92] = CRGB(0, 0, 0);
  leds[94] = CRGB(255, 255, 0);
  leds[95] = CRGB(0, 0, 0);
  leds[96] = CRGB(0, 0, 0);
  leds[97] = CRGB(0, 0, 0);
  leds[98] = CRGB(0, 0, 0);
  leds[99] = CRGB(255, 255, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[51] = CRGB(255, 255, 0);
  leds[52] = CRGB(255, 255, 0);
  leds[55] = CRGB(255, 255, 0);
  leds[56] = CRGB(255, 255, 0);
  leds[57] = CRGB(255, 255, 0);
  leds[58] = CRGB(255, 255, 0);
  leds[60] = CRGB(255, 255, 0);
  leds[61] = CRGB(255, 255, 0);
  leds[64] = CRGB(255, 255, 0);
  leds[65] = CRGB(255, 255, 0);
  leds[68] = CRGB(255, 255, 0);
  leds[69] = CRGB(255, 255, 0);
  leds[70] = CRGB(255, 255, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(0, 0, 0);
  leds[74] = CRGB(255, 255, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[76] = CRGB(0, 0, 0);
  leds[77] = CRGB(0, 0, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[79] = CRGB(255, 255, 0);
  leds[81] = CRGB(0, 0, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  leds[91] = CRGB(255, 255, 0);
  leds[93] = CRGB(255, 255, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[31] = CRGB(255, 255, 0);
  leds[32] = CRGB(255, 255, 0);
  leds[35] = CRGB(255, 255, 0);
  leds[36] = CRGB(255, 255, 0);
  leds[37] = CRGB(255, 255, 0);
  leds[38] = CRGB(255, 255, 0);
  leds[40] = CRGB(255, 255, 0);
  leds[41] = CRGB(255, 255, 0);
  leds[44] = CRGB(255, 255, 0);
  leds[45] = CRGB(255, 255, 0);
  leds[48] = CRGB(255, 255, 0);
  leds[49] = CRGB(255, 255, 0);
  leds[50] = CRGB(255, 255, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[52] = CRGB(0, 0, 0);
  leds[54] = CRGB(255, 255, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[56] = CRGB(0, 0, 0);
  leds[57] = CRGB(0, 0, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[59] = CRGB(255, 255, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[65] = CRGB(0, 0, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[71] = CRGB(255, 255, 0);
  leds[73] = CRGB(255, 255, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[81] = CRGB(255, 255, 0);
  leds[82] = CRGB(255, 255, 0);
  leds[83] = CRGB(255, 255, 0);
  leds[84] = CRGB(0, 0, 0);
  leds[88] = CRGB(255, 255, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[90] = CRGB(0, 0, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[93] = CRGB(0, 0, 0);
  leds[94] = CRGB(0, 0, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[11] = CRGB(255, 255, 0);
  leds[12] = CRGB(255, 255, 0);
  leds[15] = CRGB(255, 255, 0);
  leds[16] = CRGB(255, 255, 0);
  leds[17] = CRGB(255, 255, 0);
  leds[18] = CRGB(255, 255, 0);
  leds[20] = CRGB(255, 255, 0);
  leds[21] = CRGB(255, 255, 0);
  leds[24] = CRGB(255, 255, 0);
  leds[25] = CRGB(255, 255, 0);
  leds[28] = CRGB(255, 255, 0);
  leds[29] = CRGB(255, 255, 0);
  leds[30] = CRGB(255, 255, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(0, 0, 0);
  leds[34] = CRGB(255, 255, 0);
  leds[35] = CRGB(0, 0, 0);
  leds[36] = CRGB(0, 0, 0);
  leds[37] = CRGB(0, 0, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[39] = CRGB(255, 255, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[45] = CRGB(0, 0, 0);
  leds[48] = CRGB(0, 0, 0);
  leds[51] = CRGB(255, 255, 0);
  leds[53] = CRGB(255, 255, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[61] = CRGB(255, 255, 0);
  leds[62] = CRGB(255, 255, 0);
  leds[63] = CRGB(255, 255, 0);
  leds[64] = CRGB(0, 0, 0);
  leds[68] = CRGB(255, 255, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[73] = CRGB(0, 0, 0);
  leds[74] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[81] = CRGB(0, 0, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[0] = CRGB(255, 255, 0);
  leds[1] = CRGB(255, 255, 0);
  leds[4] = CRGB(255, 255, 0);
  leds[5] = CRGB(255, 255, 0);
  leds[8] = CRGB(255, 255, 0);
  leds[9] = CRGB(255, 255, 0);
  leds[10] = CRGB(255, 255, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[14] = CRGB(255, 255, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  leds[19] = CRGB(255, 255, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[25] = CRGB(0, 0, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[31] = CRGB(255, 255, 0);
  leds[33] = CRGB(255, 255, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[41] = CRGB(255, 255, 0);
  leds[42] = CRGB(255, 255, 0);
  leds[43] = CRGB(255, 255, 0);
  leds[44] = CRGB(0, 0, 0);
  leds[48] = CRGB(255, 255, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[53] = CRGB(0, 0, 0);
  leds[54] = CRGB(0, 0, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[62] = CRGB(0, 0, 0);
  leds[63] = CRGB(0, 0, 0);
  leds[68] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[1] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[13] = CRGB(255, 255, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(255, 255, 0);
  leds[22] = CRGB(255, 255, 0);
  leds[23] = CRGB(255, 255, 0);
  leds[24] = CRGB(0, 0, 0);
  leds[28] = CRGB(255, 255, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[33] = CRGB(0, 0, 0);
  leds[34] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[42] = CRGB(0, 0, 0);
  leds[43] = CRGB(0, 0, 0);
  leds[48] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(255, 255, 0);
  leds[2] = CRGB(255, 255, 0);
  leds[3] = CRGB(255, 255, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[8] = CRGB(255, 255, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[22] = CRGB(0, 0, 0);
  leds[23] = CRGB(0, 0, 0);
  leds[28] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
}

void OAnimation() {
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  leds[6] = CRGB(0, 0, 0);
  leds[7] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[22] = CRGB(0, 0, 0);
  leds[23] = CRGB(0, 0, 0);
  leds[24] = CRGB(0, 0, 0);
  leds[25] = CRGB(0, 0, 0);
  leds[26] = CRGB(0, 0, 0);
  leds[27] = CRGB(0, 0, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(0, 0, 0);
  leds[33] = CRGB(0, 0, 0);
  leds[34] = CRGB(0, 0, 0);
  leds[35] = CRGB(0, 0, 0);
  leds[36] = CRGB(0, 0, 0);
  leds[37] = CRGB(0, 0, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[42] = CRGB(0, 0, 0);
  leds[43] = CRGB(0, 0, 0);
  leds[44] = CRGB(0, 0, 0);
  leds[45] = CRGB(0, 0, 0);
  leds[46] = CRGB(0, 0, 0);
  leds[47] = CRGB(0, 0, 0);
  leds[48] = CRGB(0, 0, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[52] = CRGB(0, 0, 0);
  leds[53] = CRGB(0, 0, 0);
  leds[54] = CRGB(0, 0, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[56] = CRGB(0, 0, 0);
  leds[57] = CRGB(0, 0, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[62] = CRGB(0, 0, 0);
  leds[63] = CRGB(0, 0, 0);
  leds[64] = CRGB(0, 0, 0);
  leds[65] = CRGB(0, 0, 0);
  leds[66] = CRGB(0, 0, 0);
  leds[67] = CRGB(0, 0, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(0, 0, 0);
  leds[73] = CRGB(0, 0, 0);
  leds[74] = CRGB(0, 0, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[76] = CRGB(0, 0, 0);
  leds[77] = CRGB(0, 0, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[81] = CRGB(0, 0, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[84] = CRGB(0, 0, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[86] = CRGB(0, 0, 0);
  leds[87] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[90] = CRGB(0, 0, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[92] = CRGB(255, 255, 0);
  leds[93] = CRGB(255, 255, 0);
  leds[94] = CRGB(255, 255, 0);
  leds[95] = CRGB(255, 255, 0);
  leds[96] = CRGB(255, 255, 0);
  leds[97] = CRGB(255, 255, 0);
  leds[98] = CRGB(0, 0, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[72] = CRGB(255, 255, 0);
  leds[73] = CRGB(255, 255, 0);
  leds[74] = CRGB(255, 255, 0);
  leds[75] = CRGB(255, 255, 0);
  leds[76] = CRGB(255, 255, 0);
  leds[77] = CRGB(255, 255, 0);
  leds[81] = CRGB(255, 255, 0);
  leds[88] = CRGB(255, 255, 0);
  leds[90] = CRGB(255, 255, 0);
  leds[92] = CRGB(0, 0, 0);
  leds[93] = CRGB(0, 0, 0);
  leds[94] = CRGB(0, 0, 0);
  leds[95] = CRGB(0, 0, 0);
  leds[96] = CRGB(0, 0, 0);
  leds[97] = CRGB(0, 0, 0);
  leds[99] = CRGB(255, 255, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[52] = CRGB(255, 255, 0);
  leds[53] = CRGB(255, 255, 0);
  leds[54] = CRGB(255, 255, 0);
  leds[55] = CRGB(255, 255, 0);
  leds[56] = CRGB(255, 255, 0);
  leds[57] = CRGB(255, 255, 0);
  leds[61] = CRGB(255, 255, 0);
  leds[68] = CRGB(255, 255, 0);
  leds[70] = CRGB(255, 255, 0);
  leds[72] = CRGB(0, 0, 0);
  leds[73] = CRGB(0, 0, 0);
  leds[74] = CRGB(0, 0, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[76] = CRGB(0, 0, 0);
  leds[77] = CRGB(0, 0, 0);
  leds[79] = CRGB(255, 255, 0);
  leds[80] = CRGB(255, 255, 0);
  leds[81] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  leds[89] = CRGB(255, 255, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[32] = CRGB(255, 255, 0);
  leds[33] = CRGB(255, 255, 0);
  leds[34] = CRGB(255, 255, 0);
  leds[35] = CRGB(255, 255, 0);
  leds[36] = CRGB(255, 255, 0);
  leds[37] = CRGB(255, 255, 0);
  leds[41] = CRGB(255, 255, 0);
  leds[48] = CRGB(255, 255, 0);
  leds[50] = CRGB(255, 255, 0);
  leds[52] = CRGB(0, 0, 0);
  leds[53] = CRGB(0, 0, 0);
  leds[54] = CRGB(0, 0, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[56] = CRGB(0, 0, 0);
  leds[57] = CRGB(0, 0, 0);
  leds[59] = CRGB(255, 255, 0);
  leds[60] = CRGB(255, 255, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[69] = CRGB(255, 255, 0);
  leds[90] = CRGB(0, 0, 0);
  leds[91] = CRGB(255, 255, 0);
  leds[98] = CRGB(255, 255, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[12] = CRGB(255, 255, 0);
  leds[13] = CRGB(255, 255, 0);
  leds[14] = CRGB(255, 255, 0);
  leds[15] = CRGB(255, 255, 0);
  leds[16] = CRGB(255, 255, 0);
  leds[17] = CRGB(255, 255, 0);
  leds[21] = CRGB(255, 255, 0);
  leds[28] = CRGB(255, 255, 0);
  leds[30] = CRGB(255, 255, 0);
  leds[32] = CRGB(0, 0, 0);
  leds[33] = CRGB(0, 0, 0);
  leds[34] = CRGB(0, 0, 0);
  leds[35] = CRGB(0, 0, 0);
  leds[36] = CRGB(0, 0, 0);
  leds[37] = CRGB(0, 0, 0);
  leds[39] = CRGB(255, 255, 0);
  leds[40] = CRGB(255, 255, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[48] = CRGB(0, 0, 0);
  leds[49] = CRGB(255, 255, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(255, 255, 0);
  leds[78] = CRGB(255, 255, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[82] = CRGB(255, 255, 0);
  leds[83] = CRGB(255, 255, 0);
  leds[84] = CRGB(255, 255, 0);
  leds[85] = CRGB(255, 255, 0);
  leds[86] = CRGB(255, 255, 0);
  leds[87] = CRGB(255, 255, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[98] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[1] = CRGB(255, 255, 0);
  leds[8] = CRGB(255, 255, 0);
  leds[10] = CRGB(255, 255, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[19] = CRGB(255, 255, 0);
  leds[20] = CRGB(255, 255, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[29] = CRGB(255, 255, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(255, 255, 0);
  leds[58] = CRGB(255, 255, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[62] = CRGB(255, 255, 0);
  leds[63] = CRGB(255, 255, 0);
  leds[64] = CRGB(255, 255, 0);
  leds[65] = CRGB(255, 255, 0);
  leds[66] = CRGB(255, 255, 0);
  leds[67] = CRGB(255, 255, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[84] = CRGB(0, 0, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[86] = CRGB(0, 0, 0);
  leds[87] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[0] = CRGB(255, 255, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[9] = CRGB(255, 255, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(255, 255, 0);
  leds[38] = CRGB(255, 255, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[42] = CRGB(255, 255, 0);
  leds[43] = CRGB(255, 255, 0);
  leds[44] = CRGB(255, 255, 0);
  leds[45] = CRGB(255, 255, 0);
  leds[46] = CRGB(255, 255, 0);
  leds[47] = CRGB(255, 255, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[62] = CRGB(0, 0, 0);
  leds[63] = CRGB(0, 0, 0);
  leds[64] = CRGB(0, 0, 0);
  leds[65] = CRGB(0, 0, 0);
  leds[66] = CRGB(0, 0, 0);
  leds[67] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(255, 255, 0);
  leds[18] = CRGB(255, 255, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[22] = CRGB(255, 255, 0);
  leds[23] = CRGB(255, 255, 0);
  leds[24] = CRGB(255, 255, 0);
  leds[25] = CRGB(255, 255, 0);
  leds[26] = CRGB(255, 255, 0);
  leds[27] = CRGB(255, 255, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[42] = CRGB(0, 0, 0);
  leds[43] = CRGB(0, 0, 0);
  leds[44] = CRGB(0, 0, 0);
  leds[45] = CRGB(0, 0, 0);
  leds[46] = CRGB(0, 0, 0);
  leds[47] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[0] = CRGB(0, 0, 0);
  leds[2] = CRGB(255, 255, 0);
  leds[3] = CRGB(255, 255, 0);
  leds[4] = CRGB(255, 255, 0);
  leds[5] = CRGB(255, 255, 0);
  leds[6] = CRGB(255, 255, 0);
  leds[7] = CRGB(255, 255, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  leds[22] = CRGB(0, 0, 0);
  leds[23] = CRGB(0, 0, 0);
  leds[24] = CRGB(0, 0, 0);
  leds[25] = CRGB(0, 0, 0);
  leds[26] = CRGB(0, 0, 0);
  leds[27] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
}

void CAnimation() {
  leds[0] = CRGB(0, 0, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[2] = CRGB(0, 0, 0);
  leds[3] = CRGB(0, 0, 0);
  leds[4] = CRGB(0, 0, 0);
  leds[5] = CRGB(0, 0, 0);
  leds[6] = CRGB(0, 0, 0);
  leds[7] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[22] = CRGB(0, 0, 0);
  leds[23] = CRGB(0, 0, 0);
  leds[24] = CRGB(0, 0, 0);
  leds[25] = CRGB(0, 0, 0);
  leds[26] = CRGB(0, 0, 0);
  leds[27] = CRGB(0, 0, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[32] = CRGB(0, 0, 0);
  leds[33] = CRGB(0, 0, 0);
  leds[34] = CRGB(0, 0, 0);
  leds[35] = CRGB(0, 0, 0);
  leds[36] = CRGB(0, 0, 0);
  leds[37] = CRGB(0, 0, 0);
  leds[38] = CRGB(0, 0, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[42] = CRGB(0, 0, 0);
  leds[43] = CRGB(0, 0, 0);
  leds[44] = CRGB(0, 0, 0);
  leds[45] = CRGB(0, 0, 0);
  leds[46] = CRGB(0, 0, 0);
  leds[47] = CRGB(0, 0, 0);
  leds[48] = CRGB(0, 0, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[52] = CRGB(0, 0, 0);
  leds[53] = CRGB(0, 0, 0);
  leds[54] = CRGB(0, 0, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[56] = CRGB(0, 0, 0);
  leds[57] = CRGB(0, 0, 0);
  leds[58] = CRGB(0, 0, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[62] = CRGB(0, 0, 0);
  leds[63] = CRGB(0, 0, 0);
  leds[64] = CRGB(0, 0, 0);
  leds[65] = CRGB(0, 0, 0);
  leds[66] = CRGB(0, 0, 0);
  leds[67] = CRGB(0, 0, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[72] = CRGB(0, 0, 0);
  leds[73] = CRGB(0, 0, 0);
  leds[74] = CRGB(0, 0, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[76] = CRGB(0, 0, 0);
  leds[77] = CRGB(0, 0, 0);
  leds[78] = CRGB(0, 0, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[81] = CRGB(0, 0, 0);
  leds[82] = CRGB(0, 0, 0);
  leds[83] = CRGB(0, 0, 0);
  leds[84] = CRGB(0, 0, 0);
  leds[85] = CRGB(0, 0, 0);
  leds[86] = CRGB(0, 0, 0);
  leds[87] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[90] = CRGB(0, 0, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[92] = CRGB(255, 255, 0);
  leds[93] = CRGB(255, 255, 0);
  leds[94] = CRGB(255, 255, 0);
  leds[95] = CRGB(255, 255, 0);
  leds[96] = CRGB(255, 255, 0);
  leds[97] = CRGB(255, 255, 0);
  leds[98] = CRGB(0, 0, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[72] = CRGB(255, 255, 0);
  leds[73] = CRGB(255, 255, 0);
  leds[74] = CRGB(255, 255, 0);
  leds[75] = CRGB(255, 255, 0);
  leds[76] = CRGB(255, 255, 0);
  leds[77] = CRGB(255, 255, 0);
  leds[81] = CRGB(255, 255, 0);
  leds[88] = CRGB(255, 255, 0);
  leds[90] = CRGB(255, 255, 0);
  leds[92] = CRGB(0, 0, 0);
  leds[93] = CRGB(0, 0, 0);
  leds[94] = CRGB(0, 0, 0);
  leds[95] = CRGB(0, 0, 0);
  leds[96] = CRGB(0, 0, 0);
  leds[97] = CRGB(0, 0, 0);
  leds[99] = CRGB(255, 255, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[52] = CRGB(255, 255, 0);
  leds[53] = CRGB(255, 255, 0);
  leds[54] = CRGB(255, 255, 0);
  leds[55] = CRGB(255, 255, 0);
  leds[56] = CRGB(255, 255, 0);
  leds[57] = CRGB(255, 255, 0);
  leds[61] = CRGB(255, 255, 0);
  leds[68] = CRGB(255, 255, 0);
  leds[70] = CRGB(255, 255, 0);
  leds[72] = CRGB(0, 0, 0);
  leds[73] = CRGB(0, 0, 0);
  leds[74] = CRGB(0, 0, 0);
  leds[75] = CRGB(0, 0, 0);
  leds[76] = CRGB(0, 0, 0);
  leds[77] = CRGB(0, 0, 0);
  leds[79] = CRGB(255, 255, 0);
  leds[80] = CRGB(255, 255, 0);
  leds[81] = CRGB(0, 0, 0);
  leds[88] = CRGB(0, 0, 0);
  leds[89] = CRGB(255, 255, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[32] = CRGB(255, 255, 0);
  leds[33] = CRGB(255, 255, 0);
  leds[34] = CRGB(255, 255, 0);
  leds[35] = CRGB(255, 255, 0);
  leds[36] = CRGB(255, 255, 0);
  leds[37] = CRGB(255, 255, 0);
  leds[41] = CRGB(255, 255, 0);
  leds[48] = CRGB(255, 255, 0);
  leds[50] = CRGB(255, 255, 0);
  leds[52] = CRGB(0, 0, 0);
  leds[53] = CRGB(0, 0, 0);
  leds[54] = CRGB(0, 0, 0);
  leds[55] = CRGB(0, 0, 0);
  leds[56] = CRGB(0, 0, 0);
  leds[57] = CRGB(0, 0, 0);
  leds[59] = CRGB(255, 255, 0);
  leds[60] = CRGB(255, 255, 0);
  leds[61] = CRGB(0, 0, 0);
  leds[68] = CRGB(0, 0, 0);
  leds[69] = CRGB(255, 255, 0);
  leds[90] = CRGB(0, 0, 0);
  leds[91] = CRGB(255, 255, 0);
  leds[98] = CRGB(255, 255, 0);
  leds[99] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[12] = CRGB(255, 255, 0);
  leds[13] = CRGB(255, 255, 0);
  leds[14] = CRGB(255, 255, 0);
  leds[15] = CRGB(255, 255, 0);
  leds[16] = CRGB(255, 255, 0);
  leds[17] = CRGB(255, 255, 0);
  leds[21] = CRGB(255, 255, 0);
  leds[28] = CRGB(255, 255, 0);
  leds[30] = CRGB(255, 255, 0);
  leds[32] = CRGB(0, 0, 0);
  leds[33] = CRGB(0, 0, 0);
  leds[34] = CRGB(0, 0, 0);
  leds[35] = CRGB(0, 0, 0);
  leds[36] = CRGB(0, 0, 0);
  leds[37] = CRGB(0, 0, 0);
  leds[39] = CRGB(255, 255, 0);
  leds[40] = CRGB(255, 255, 0);
  leds[41] = CRGB(0, 0, 0);
  leds[48] = CRGB(0, 0, 0);
  leds[49] = CRGB(255, 255, 0);
  leds[70] = CRGB(0, 0, 0);
  leds[71] = CRGB(255, 255, 0);
  leds[78] = CRGB(255, 255, 0);
  leds[79] = CRGB(0, 0, 0);
  leds[80] = CRGB(0, 0, 0);
  leds[89] = CRGB(0, 0, 0);
  leds[91] = CRGB(0, 0, 0);
  leds[98] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[1] = CRGB(255, 255, 0);
  leds[8] = CRGB(255, 255, 0);
  leds[10] = CRGB(255, 255, 0);
  leds[12] = CRGB(0, 0, 0);
  leds[13] = CRGB(0, 0, 0);
  leds[14] = CRGB(0, 0, 0);
  leds[15] = CRGB(0, 0, 0);
  leds[16] = CRGB(0, 0, 0);
  leds[17] = CRGB(0, 0, 0);
  leds[19] = CRGB(255, 255, 0);
  leds[20] = CRGB(255, 255, 0);
  leds[21] = CRGB(0, 0, 0);
  leds[28] = CRGB(0, 0, 0);
  leds[29] = CRGB(255, 255, 0);
  leds[50] = CRGB(0, 0, 0);
  leds[51] = CRGB(255, 255, 0);
  leds[58] = CRGB(255, 255, 0);
  leds[59] = CRGB(0, 0, 0);
  leds[60] = CRGB(0, 0, 0);
  leds[69] = CRGB(0, 0, 0);
  leds[71] = CRGB(0, 0, 0);
  leds[78] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[0] = CRGB(255, 255, 0);
  leds[1] = CRGB(0, 0, 0);
  leds[8] = CRGB(0, 0, 0);
  leds[9] = CRGB(255, 255, 0);
  leds[30] = CRGB(0, 0, 0);
  leds[31] = CRGB(255, 255, 0);
  leds[38] = CRGB(255, 255, 0);
  leds[39] = CRGB(0, 0, 0);
  leds[40] = CRGB(0, 0, 0);
  leds[49] = CRGB(0, 0, 0);
  leds[51] = CRGB(0, 0, 0);
  leds[58] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[10] = CRGB(0, 0, 0);
  leds[11] = CRGB(255, 255, 0);
  leds[18] = CRGB(255, 255, 0);
  leds[19] = CRGB(0, 0, 0);
  leds[20] = CRGB(0, 0, 0);
  leds[29] = CRGB(0, 0, 0);
  leds[31] = CRGB(0, 0, 0);
  leds[38] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
  leds[0] = CRGB(0, 0, 0);
  leds[9] = CRGB(0, 0, 0);
  leds[11] = CRGB(0, 0, 0);
  leds[18] = CRGB(0, 0, 0);
  FastLED.show();
  delay(MS_BETWEEN_LETTER_FRAMES);
}

void letterScroll(int* letter, CRGB colour, int delay_ms) {
  int shift = 9;

  while (shift > -9) {
    int RCoordsDisp[NUM_LEDS];
    int CCoordsDisp[NUM_LEDS];
    int nCoords = 0;
     for (int r = 0; r < MATRIX_LENGTH; r++) {
       for (int c = 0; c < MATRIX_LENGTH; c++) {
         int index = RC2Linear(r, c);
         if (*(letter+index) && (c + shift) < MATRIX_LENGTH && (c + shift) >= 0) {
           RCoordsDisp[nCoords] = r;
           CCoordsDisp[nCoords] = c + shift;
           nCoords++;
         }
       }
    }
  
    for (int j = 0; j < nCoords; j++) {
       int l = RC2Linear(RCoordsDisp[j], CCoordsDisp[j]);
       if (l >= 0 && l < NUM_LEDS) {
         leds[l] = colour;
       }
     }
     FastLED.show();
     delay(delay_ms);
     clearAll();
     shift--;
  }
}

void wordScroll(char* str, CRGB colour, int delay_ms) {
  for (int i = 0; i < strlen(str); i++) {
    char letter = str[i];
    int letterIdx = 0;
    
    for (int j = 0; j < NUM_LETTERS; j++) {
      if (letters[j] == letter) {
        letterIdx = j;
      }
    }
    
    int* letterArr = (int *)letterBytes[letterIdx];
    letterScroll(letterArr, colour, delay_ms);
  }
}
