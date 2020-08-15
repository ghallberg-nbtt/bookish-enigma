/*
  Four Digit 7-Segment LED Display
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
const int DIGIT1 = 2; //First digit
const int DIGIT2 = 3; //Second digit
const int DIGIT3 = 4; //Third digit
const int DIGIT4 = 5; //Fourth digit
const int OUTPUTENABLE = 7; // enable and disable shift register output

int dp = 0; //Set decimal point 0=off 1=on
int number; //Number to be displayed
int select; //Digit selection
int waitTime; //Time to display the digit
long loopStartTime;// Time at start of loop
long loopStopTime;// Time at end of loop

void setup() {
  pinMode (SERIAL_DATA, OUTPUT);
  pinMode (LATCH, OUTPUT);
  pinMode (CLOCK, OUTPUT);
  pinMode (DIGIT1, OUTPUT);
  pinMode (DIGIT2, OUTPUT);
  pinMode (DIGIT3, OUTPUT);
  pinMode (DIGIT4, OUTPUT);
  pinMode (OUTPUTENABLE, OUTPUT);
  digitalWrite(DIGIT1, LOW); //Set transistor off
  digitalWrite(DIGIT2, LOW); //Set transistor off
  digitalWrite(DIGIT3, LOW); //Set transistor off
  digitalWrite(DIGIT4, LOW); //Set transistor off
}

void loop() {
  waitTime = 1000; // 1 second delay
  number = 1; //display 1
  select = DIGIT1; //first digit
  sevenSegWrite(number, dp, select, waitTime);
  number = 2; //display 2
  select = DIGIT2; //first digit
  sevenSegWrite(number, dp, select, waitTime);
  number = 3; //display 3
  select = DIGIT3; //third digit
  sevenSegWrite(number, dp, select, waitTime);
  number = 4; //display 4
  select = DIGIT4; //fourth digit
  sevenSegWrite(number, dp, select, waitTime);
  // toggle maximum speed
  waitTime = 3; // disable wait time
  loopStartTime = millis();// set loop timers
  loopStopTime = millis();
  while (loopStopTime < (loopStartTime + 5000)) {
    // 5 second loop
    number = 1; //display 1
    select = DIGIT1; //first digit
    sevenSegWrite(number, dp, select, waitTime);
    number = 2; //display 2
    select = DIGIT2; //first digit
    sevenSegWrite(number, dp, select, waitTime);
    number = 3; //display 3
    select = DIGIT3; //third digit
    sevenSegWrite(number, dp, select, waitTime);
    number = 4; //display 4
    select = DIGIT4; //fourth digit
    sevenSegWrite(number, dp, select, waitTime);
    loopStopTime = millis(); // update timer
  }
}

// function to display a number
void sevenSegWrite(int digit, int decimalPoint, int digitSelect, int timer) {
  digitalWrite (OUTPUTENABLE, HIGH); //disable output
  digitalWrite(digitSelect, HIGH);
  digitalWrite(LATCH, LOW); //allow data in
  shiftOut(SERIAL_DATA, CLOCK, LSBFIRST, (DIGITS[digit] + decimalPoint)); //load shift register
  digitalWrite(LATCH, HIGH); //trigger outputs
  digitalWrite (OUTPUTENABLE, LOW); //turn on outputs
  delay (timer);
  digitalWrite(digitSelect, LOW);
}
