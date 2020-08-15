/*
  MAX7219 using the LedControl Library
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/bookish-enigma/blob/master/LICENSE
*/
#include "LedControl.h"

/*
  Now we need to identify the pins
  Pin 2 is connected to the DIN
  Pin 3 is connected to CS (LOAD)
  Pin 4 is connected to the CLK
  We have only a single MAX7219 so last parameter is 1
  No need to set the pins to output. The library does that
*/
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
  //Sequence 1 - addressing an individual LED
  //turn all on in turn
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, row, col, true);
      delay (100);
    }
  }
  //turn all off in turn
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, row, col, false);
      delay (100);
    }
  }
  //one on at a time
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, row, col, true);
      delay (100);
      lc.setLed(0, row, col, false);
    }
  }
  lc.clearDisplay(0);

  //Sequence 2 - Addressing rows and columns
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, B10110000);
    delay (100);
    lc.setRow(0, row, B00000000);
  }
  lc.clearDisplay(0);
  for (int col = 0; col < 8; col++) {
    lc.setColumn(0, col, B10110010);
    delay (100);
    lc.setColumn(0, col, B00000000);
  }
  lc.clearDisplay(0);
}
