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
#define MS_BETWEEN_LETTER_FRAMES 100
#define MS_BETWEEN_WIPE_FRAMES 100
#define NUM_LETTERS 2

void setupLEDs();
void colourFill(CRGB colour);
void colourFill(CHSV colour);
void oneByOne(CRGB colour, int delay_ms);
void clearAll();
void multiColourFade();
void spiral(CRGB colour);
//bool matrixFilledIn(struct matrix disp);
//bool cellFilledIn(struct LED cell);
int RC2Linear(int row, int col);
void displayMatrix(struct matrix disp);
void waterEffect(struct rotationValues rotations, CRGB colour);
void basicWipe(CRGB colour);
int rainbow(int offset);
void sinRainbow();
void sparkles(bool finishAnimation);
void fire(bool finishAnimation);
void elsocLogo();
void EAnimation();
void LAnimation();
void SAnimation();
void OAnimation();
void CAnimation();
void elsocFullAnimation();
void letterScroll(int* letter, CRGB colour, int delay_ms);
void wordScroll(char* str, CRGB colour, int delay_ms);

#endif
