/*
  Single Digit 7-Segment LED Display
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/bookish-enigma/blob/master/LICENSE
*/

// define the LED digit patterns, from 0 - 9 and DP off
// 1 = LED on, 0 = LED off, in this order:
// 74HC595 pin     QA,QB,QC,QD,QE,QF,QG,QH
const byte DIGITS[] = { B11111100,  // = 0
                        B01100000,  // = 1
                        B11011010,  // = 2
                        B11110010,  // = 3
                        B01100110,  // = 4
                        B10110110,  // = 5
                        B10111110,  // = 6
                        B11100000,  // = 7
                        B11111110,  // = 8
                        B11100110   // = 9
                      };
const int SERIAL_DATA = 10; //Serial data
const int LATCH = 9; //Shift register latch
const int CLOCK = 8; //Shift register clock

int dp = 0; //set decimal point 0=off 1=on

void setup() {
  pinMode (SERIAL_DATA, OUTPUT);
  pinMode (LATCH, OUTPUT);
  pinMode (CLOCK, OUTPUT);

}

void loop() {
  // count from 0 to 9
  dp = 0; //decimal point off
  for (int i = 0; i < 10; i++) {
    delay(1000);  //Wait 1 second
    sevenSegWrite(i, dp);
  }
  // wait 3 seconds
  dp = 1; //decimal point on
  delay(3000);
  // count from 9 to 0
  for (int i = 9; i >= 0; i--) {
    delay(1000);  //Wait 1 second
    sevenSegWrite(i, dp);
  }
  delay(3000);
}

// function to display a number
void sevenSegWrite(int digit, int decimalPoint) {
  digitalWrite(LATCH, LOW); //allow data in
  shiftOut(SERIAL_DATA, CLOCK, LSBFIRST, (DIGITS[digit] + decimalPoint)); //load shift register
  digitalWrite(LATCH, HIGH); //trigger outputs
}
