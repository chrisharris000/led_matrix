#include "basicAnimations.h"

CRGB leds[NUM_LEDS];

void setupLEDs() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
};

void redFill() {
  for (int i=0; i<NUM_LEDS; i++) {
    leds[i] = CRGB(128, 0, 0);
  }
  FastLED.show();
};

void waterEffect(DFRobot_LIS2DH12 *LIS) {
  struct matrix disp;
  // calculate rotation
  struct rotationValues *rotations;
  getRotation(LIS, rotations);
  disp.rotation = rotations->rotation;
}
