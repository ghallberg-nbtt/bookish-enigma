/*
  HD44780 16 x 2 LCD - displaying standard text
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/bookish-enigma/blob/master/LICENSE
*/

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the Arduino pin number it is connected to
LiquidCrystal lcd(2, 3, 8, 9, 10, 11);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

}

void loop() {
  // Print a message to the LCD.
  lcd.print("hello, world!");
  delay (2000);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcd.print("hello, world!");
  delay (2000);
  lcd.clear(); // clear display
  // Shifting text around the screen
  for (int i = 0; i < 4; i++) {
    lcd.setCursor(i, 0);  // Move cursor to first row and third column
    lcd.print("12345?<>!");
    delay (2000);
    lcd.clear();
  }
  lcd.clear(); // Blank screen for 2 seconds
  delay(2000);
  // Show that cursor auto increments after each character is printed
  lcd.setCursor(0, 0);
  for (int i = 0; i < 16; i++) {
    lcd.print("*");
    delay (250);
  }
  lcd.clear();
}
