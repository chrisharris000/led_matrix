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
void spiral(CRGB colour);
bool matrixFilledIn(struct matrix disp);
bool cellFilledIn(struct LED cell);
int RC2Linear(int row, int col);
void displayMatrix(struct matrix disp);
void waterEffect(DFRobot_LIS2DH12 *LIS);

#endif
