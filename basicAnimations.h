#ifndef BASICANIMATIONS_H
#define BASICANIMATIONS_H

#define FASTLED_INTERNAL
#include <FastLED.h>
#include "matrix.h"
#include "accelerometer.h"

#define LED_PIN 5
#define MATRIX_LENGTH 10
#define NUM_LEDS MATRIX_LENGTH*MATRIX_LENGTH


void setupLEDs();
void redFill();
void waterEffect(DFRobot_LIS2DH12 *LIS);

#endif
