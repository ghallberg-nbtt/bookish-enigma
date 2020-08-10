/*
  Shift Register LED Patterns
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/bookish-enigma/blob/master/LICENSE
*/

const int SERIAL_DATA = 10; //Serial data
const int LATCH = 9; //Shift register latch
const int CLOCK = 8; //Shift register clock
const int SEQUENCE1 = B10101010; //Light sequence 1
const int SEQUENCE2 = B01010101; //Light sequence 2

void setup() {
  // put your setup code here, to run once:
  pinMode (SERIAL_DATA, OUTPUT);
  pinMode (LATCH, OUTPUT);
  pinMode (CLOCK, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite (LATCH, LOW); //allow data in
  shiftOut (SERIAL_DATA, CLOCK, MSBFIRST, SEQUENCE1); //load shift register
  digitalWrite (LATCH, HIGH); //trigger outputs
  delay (500);
  digitalWrite (LATCH, LOW); //allow data in
  shiftOut (SERIAL_DATA, CLOCK, MSBFIRST, SEQUENCE2); //load shift register
  digitalWrite (LATCH, HIGH); //trigger outputs
  delay (500);
}
