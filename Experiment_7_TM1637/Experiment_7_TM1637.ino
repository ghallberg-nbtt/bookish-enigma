/*
  TM1637
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/bookish-enigma/blob/master/LICENSE
*/
#include <TM1637Display.h> //Include TM1637 library functions

const int DIO = 2; //data in
const int CLK = 3; //clock
TM1637Display display(CLK, DIO);

const uint8_t SEG_DONE[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};

void setup() {
  pinMode (DIO, OUTPUT);
  pinMode (CLK, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  display.setBrightness(0x0f);
  /*Sequence 1
    This sequence shows how individual segments can turned on and off
    The library defines constants to encode each segment as follows
    #define SEG_A   0b00000001
    #define SEG_B   0b00000010
    #define SEG_C   0b00000100
    #define SEG_D   0b00001000
    #define SEG_E   0b00010000
    #define SEG_F   0b00100000
    #define SEG_G   0b01000000
    #define SEG_DP  0b10000000
  */
  Serial.println ("Sequence 1");
  //Define which segments are on for each digit
  uint8_t allOn[] = { 0xff, 0xff, 0xff, 0xff }; //All segments on
  uint8_t allOff[] = { 0x00, 0x00, 0x00, 0x00 }; //All segments off
  uint8_t segA[] = { SEG_A, SEG_A, SEG_A, SEG_A }; //Segment A on
  uint8_t segB[] = { SEG_B, SEG_B, SEG_B, SEG_B }; //Segment B on
  uint8_t segC[] = { SEG_C, SEG_C, SEG_C, SEG_C }; //Segment C on
  uint8_t segD[] = { SEG_D, SEG_D, SEG_D, SEG_D }; //Segment D on
  uint8_t segE[] = { SEG_E, SEG_E, SEG_E, SEG_E }; //Segment E on
  uint8_t segF[] = { SEG_F, SEG_F, SEG_F, SEG_F }; //Segment F on
  uint8_t segG[] = { SEG_G, SEG_G, SEG_G, SEG_G }; //Segment A on
  for (int i = 0; i < 2; i++) {
    //Run sequence  1and repeat twice
    display.setSegments(allOn);
    delay (200);
    display.setSegments(segA);
    delay (200);
    display.setSegments(segB);
    delay (200);
    display.setSegments(segC);
    delay (200);
    display.setSegments(segD);
    delay (200);
    display.setSegments(segE);
    delay (200);
    display.setSegments(segF);
    delay (200);
    display.setSegments(segG);
    delay (200);
    display.setSegments(allOff);
    delay (300);
  }
  /*Sequence 2
    This sequence shows how you can encode a digit
    in decimal form and pass that to any one of the displays
  */
  Serial.println ("Sequence 2");
  //display 0123
  uint8_t data[4]; //declare array
  data[0] = display.encodeDigit(0);
  data[1] = display.encodeDigit(1);
  data[2] = display.encodeDigit(2);
  data[3] = display.encodeDigit(3);
  display.setSegments(data);
  delay (2000);
  //display 5678
  // Selectively set different digits
  data[0] = display.encodeDigit(5);
  data[1] = display.encodeDigit(6);
  data[2] = display.encodeDigit(7);
  data[3] = display.encodeDigit(8);
  display.setSegments(data);
  delay (2000);
  /*Sequence 3
    This sequence displays a number presented as up to
    4 digits with or without leading zeros.
    False disables leading zeros
  */
  Serial.println ("Sequence 3");
  display.showNumberDec(0, false); // Expect: ___0
  delay(2000);
  display.showNumberDec(0, true);  // Expect: 0000
  delay(2000);
  display.showNumberDec(99, false); // Expect: __99
  delay(2000);
  display.showNumberDec(99, true);  // Expect: 0099
  delay(2000);
  display.clear();
  // Show 14, no leading zeros, length 2 digits, position 1
  // left most digit is position 0 and right most position 3
  display.showNumberDec(14, false, 2, 1); // Expect: _14_
  delay(2000);
  display.showNumberDec(-1, false);  // Expect: __-1
  delay(2000);
  display.showNumberDec(-999);       // Expect: -999
  delay(2000);
  /*Sequence 4
    This sequence displays hexadecimal numbers
  */
  Serial.println ("Sequence 4");
  display.showNumberHexEx(0xf1af);        // Expect: f1Af
  delay(2000);
  display.showNumberHexEx(0x2c);          // Expect: __2C
  delay(2000);
  display.showNumberHexEx(0xd1, 0, true); // Expect: 00d1
  delay(2000);
  /*Sequence 5
    Turn on the display colon. Function usage
    showNumberDecEx (<number>, <code to turn on colon>, <leading zeros>)
  */
  Serial.println ("Sequence 5");
  display.showNumberDecEx(8888, B01000000, true);
  delay (2000);
  for (int i = 0; i < 5; i++) {
    display.showNumberDecEx(1256, B01000000, true);
    delay (500);
    display.showNumberDecEx(1256, B0, true);
    delay (500);
  }
  /*Sequence 6
    Set brightness
  */

  for (int i = 0; i < 7; i++) {
    display.setBrightness(i);
    display.showNumberDec(8888);
    delay(500);
  }
  for (int i = 6; i >= 0; i--) {
    display.setBrightness(i);
    display.showNumberDec(8888);
    delay(500);
  }
  /*Sequence 7
    Custom characters
    dislay done
  */
  display.setBrightness(0x0f);
  display.setSegments(SEG_DONE);
  delay (5000);
}
