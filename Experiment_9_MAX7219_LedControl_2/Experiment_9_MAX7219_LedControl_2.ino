/*
  MAX7219 using the LedControl Library - displaying text
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/bookish-enigma/blob/master/LICENSE
*/
#include "LedControl.h"

const byte A[] = {B00011000,
                  B00100100,
                  B01000010,
                  B01000010,
                  B01111110,
                  B01000010,
                  B01000010,
                  B01000010
                 };

const byte R[] = {B01111100,
                  B01000010,
                  B01000010,
                  B01000010,
                  B01111100,
                  B01000010,
                  B01000010,
                  B01000010
                 };

const byte D[] = {B01111000,
                  B01000100,
                  B01000010,
                  B01000010,
                  B01000010,
                  B01000010,
                  B01000100,
                  B01111000
                 };

const byte U[] = {B01000010,
                  B01000010,
                  B01000010,
                  B01000010,
                  B01000010,
                  B01000010,
                  B01000010,
                  B00111100
                 };

const byte I[] = {B00111000,
                  B00010000,
                  B00010000,
                  B00010000,
                  B00010000,
                  B00010000,
                  B00010000,
                  B00111000
                 };

const byte N[] = {B01000010,
                  B01000010,
                  B01100010,
                  B01010010,
                  B01001010,
                  B01000110,
                  B01000010,
                  B01000010
                 };

const byte O[] = {B00111100,
                  B01000010,
                  B01000010,
                  B01000010,
                  B01000010,
                  B01000010,
                  B01000010,
                  B00111100
                 };

LedControl lc = LedControl(2, 4, 3, 1);

void setup() {
  /*
    The MAX72XX is in power - saving mode on startup,
      we have to do a wakeup call.
      display 1 has an index of 0
  */
  lc.shutdown(0, false);
  //Set the brightness to a medium value
  lc.setIntensity(0, 8);
  //and clear the display
  lc.clearDisplay(0);
}

void loop() {
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, A[i]);
  }
  delay (750);
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, R[i]);
  }
  delay (750);
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, D[i]);
  }
  delay (750);
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, U[i]);
  }
  delay (750);
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, I[i]);
  }
  delay (750);
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, N[i]);
  }     
  delay (750);
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, O[i]);
  }
  delay (750);
}
