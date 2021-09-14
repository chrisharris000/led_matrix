#ifndef BASICANIMATIONS_H
#define BASICANIMATIONS_H

#define FASTLED_INTERNAL
#include <FastLED.h>
#include "matrix.h"
#include "accelerometer.h"

#define LED_PIN 5
#define MATRIX_LENGTH 10
#define NUM_LEDS MATRIX_LENGTH*MATRIX_LENGTH
#define BRIGHTNESS 100


void setupLEDs();
void colourFill(CRGB colour);
void colourFill(CHSV colour);
void oneByOne(CRGB colour, int delay_ms);
void clearAll();
void multiColourFade();
void waterEffect(DFRobot_LIS2DH12 *LIS);

#endif
