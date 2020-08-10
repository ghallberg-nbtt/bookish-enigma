/*
  Light Chaser
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/bookish-enigma/blob/master/LICENSE
*/

const int SERIAL_DATA = 10; //Serial data
const int LATCH = 9; //Shift register latch
const int CLOCK = 8; //Shift register clock
//set up sequence
const int sequence[] = {1, 2, 4, 8, 16, 32, 64, 128, 64, 32, 16, 8, 4, 2};

void setup() {
  // put your setup code here, to run once:
  pinMode (SERIAL_DATA, OUTPUT);
  pinMode (LATCH, OUTPUT);
  pinMode (CLOCK, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 14; i++) {
    digitalWrite (LATCH, LOW); //allow data in
    shiftOut (SERIAL_DATA, CLOCK, MSBFIRST, sequence[i]); //load shift regsiter
    digitalWrite (LATCH, HIGH); //trigger outputs
    delay (100);
  }
}
