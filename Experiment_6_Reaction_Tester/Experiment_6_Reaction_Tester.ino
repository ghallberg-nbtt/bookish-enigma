/*
  Reaction Tester
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
                        B11100110,  // = 9
                        B00000010   // = -
                      };
const int SERIAL_DATA = 10; //Serial data
const int LATCH = 9; //Shift register latch
const int CLOCK = 8; //Shift register clock
const int DIGIT1 = 2; //First digit
const int DIGIT2 = 3; //Second digit
const int DIGIT3 = 4; //Third digit
const int DIGIT4 = 5; //Fourth digit
const int REACTION_LED = 11; //Reaction LED
const int SWITCH = 6; //Reaction switch
const int OUTPUT_ENABLE = 7; // enable and disable shift register output

//Variables
int number; //Number to be displayed
int disgitSelection; //Digit selection
int waitTime; //Time to display the digit
long startTime; //Time at start of loop
long stopTime; //Time at end of loop
int ledOffTimer; //Random time to turn off LED
int switchState = LOW; //Switch on or off
boolean tooSoon; //Button press too soon
long loopStartTime; //Timer for start of loop
long loopStopTime; //Timer for end of loop

void setup() {
  pinMode (SERIAL_DATA, OUTPUT);
  pinMode (LATCH, OUTPUT);
  pinMode (CLOCK, OUTPUT);
  pinMode (DIGIT1, OUTPUT);
  pinMode (DIGIT2, OUTPUT);
  pinMode (DIGIT3, OUTPUT);
  pinMode (DIGIT4, OUTPUT);
  pinMode (OUTPUT_ENABLE, OUTPUT);
  pinMode (REACTION_LED, OUTPUT);
  pinMode (SWITCH, INPUT_PULLUP);
  digitalWrite(DIGIT1, LOW); //Set transistor off
  digitalWrite(DIGIT2, LOW); //Set transistor off
  digitalWrite(DIGIT3, LOW); //Set transistor off
  digitalWrite(DIGIT4, LOW); //Set transistor off
  Serial.begin(9600);
}

void loop() {
  startTime = millis(); //Reset timers
  stopTime = millis() - startTime;
  tooSoon = false; //reset flag
  turnOffDisplay ();
  digitalWrite (REACTION_LED, HIGH); //Turn on reaction LED
  ledOffTimer = random (2000, 4000); //set timer random 2 to 4 seconds
  Serial.print ("led off timer: ");
  Serial.println(ledOffTimer);
  delay (ledOffTimer); //Wait for that period
  switchState = digitalRead(SWITCH); // check to see if switch is already pressed
  digitalWrite (REACTION_LED, LOW); //Turn off reaction LED
  if (switchState == HIGH) {
    //not cheating - look for reaction time
    startTime = millis(); //Start reaction timer
    while ((switchState == HIGH) && (stopTime < 10000)) { //Wait until button press or time out
      switchState = digitalRead (SWITCH);
      stopTime = millis() - startTime; //elapsed time
    }
  } else {
    Serial.println ("button pressed too soon");
    tooSoon = true; //Set flag
  }
  Serial.print ("reaction time: ");
  Serial.println(stopTime);
  if ((!tooSoon) && (stopTime < 10000)) {
    //Display results
    //Convert reaction time to digits
    unsigned firstDigit = (stopTime / 1000) % 10;
    unsigned secondDigit = (stopTime / 100) % 10;
    unsigned thirdDigit = (stopTime / 10) % 10;
    unsigned fourthDigit = stopTime % 10;
    loopStartTime = millis();
    loopStopTime = millis();
    while (loopStopTime <= (loopStartTime + 3000)) {
      sevenSegWrite (firstDigit, B1, DIGIT1); //Write first digit with decimal point
      sevenSegWrite (secondDigit, B0, DIGIT2); //Write second digit
      sevenSegWrite (thirdDigit, B0, DIGIT3); //Write third digit
      sevenSegWrite (fourthDigit, B0, DIGIT4); //Write fourth digit
      loopStopTime = millis(); //Update timer
    }
  } else {
    //display ----
    loopStartTime = millis();
    loopStopTime = millis();
    while (loopStopTime <= (loopStartTime + 3000)) {
      sevenSegWrite (10, B0, DIGIT1); //Write -
      sevenSegWrite (10, B0, DIGIT2); //Write -
      sevenSegWrite (10, B0, DIGIT3); //Write -
      sevenSegWrite (10, B0, DIGIT4); //Write -
      loopStopTime = millis(); //Update timer}
    }
  }
}


void turnOffDisplay() {
  digitalWrite(DIGIT1, LOW); //Set transistor off
  digitalWrite(DIGIT2, LOW); //Set transistor off
  digitalWrite(DIGIT3, LOW); //Set transistor off
  digitalWrite(DIGIT4, LOW); //Set transistor off
}


// function to display a number
void sevenSegWrite(int digit, int decimalPoint, int digitSelect) {
  digitalWrite (OUTPUT_ENABLE, HIGH); //disable output
  digitalWrite(digitSelect, HIGH);
  digitalWrite(LATCH, LOW); //allow data in
  shiftOut(SERIAL_DATA, CLOCK, LSBFIRST, (DIGITS[digit] + decimalPoint)); //load shift register
  digitalWrite(LATCH, HIGH); //trigger outputs
  digitalWrite (OUTPUT_ENABLE, LOW); //turn on outputs
  delay (3);
  digitalWrite(digitSelect, LOW);
}
