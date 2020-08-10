/*
  HD44780 16 x 2 LCD - displaying the progress Bar
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/bookish-enigma/blob/master/LICENSE
*/

#include <LiquidCrystal.h>

const byte percent20 [] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
};

const byte percent40 [] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
};

const byte percent60 [] = {
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
};

const byte percent80 [] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
};

const byte percent100 [] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};


// initialize the library by associating any needed LCD interface pin
// with the Arduino pin number it is connected to
LiquidCrystal lcd(2, 3, 8, 9, 10, 11);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Static message
  lcd.print ("Loading: ");
  // create special characters
  lcd.createChar (0, percent20);
  lcd.createChar (1, percent40);
  lcd.createChar (2, percent60);
  lcd.createChar (3, percent80);
  lcd.createChar (4, percent100);
}

void loop() {
  
  for (int i = 0; i < 5; i++) {
    lcd.setCursor (8, 0); //move cursor
    lcd.write (i);
    delay (750);
  }
}
