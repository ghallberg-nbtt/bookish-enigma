/*
  LED Dice
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/bookish-enigma/blob/master/LICENSE
*/

/*
   LED1 = pin 2
   LED2 = pin 3
   LED3 = pin 4
   LED4 = pin 5
   LED5 = pin 6
   LED6 = pin 7
   LED7 = pin 8
*/
const int ledPin[] = {2, 3, 4, 5, 6, 7, 8}; //array to identify pin numbers
const int diceFace1[] = {LOW, LOW, LOW, HIGH, LOW, LOW, LOW}; //display 1
const int diceFace2[] = {HIGH, LOW, LOW, LOW, LOW, LOW, HIGH}; //display 2
const int diceFace3[] = {HIGH, LOW, LOW, HIGH, LOW, LOW, HIGH}; //display 3
const int diceFace4[] = {HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH}; //display 4
const int diceFace5[] = {HIGH, LOW, HIGH, HIGH, HIGH, LOW, HIGH}; //display 5
const int diceFace6[] = {HIGH, HIGH, HIGH, LOW, HIGH, HIGH, HIGH}; //display 6
const int buttonPress = 9; //button on pin 9
int buttonState = HIGH; //the state of the button
int number; //the number rolled

void setup() {
  //put your setup code here, to run once:

  //Initialize I/O pins
  for (int i = 0; i < 7; i++) {
    pinMode (ledPin[i], OUTPUT); //set pins to output
  }
  pinMode (buttonPress, INPUT_PULLUP); //set pin 9 to read button state
  Serial.begin(9600); //initialize serial monitor
}

void loop() {
  //put your main code here, to run repeatedly:

  //wait until button is pressed
  while (buttonState == HIGH) {
    buttonState = digitalRead (buttonPress); //read the button
  }
  buttonState = HIGH; //reset buton state
  //generate randon number
  number = random(1, 7); //random number between 1 and 6
  Serial.println (number); //print number to serial monitor
  if (number == 1) {
    //write 1
    for (int i = 0; i < 7; i++) {
      digitalWrite (ledPin[i], diceFace1[i]);
    }
  } else if (number == 2) {
    //write 2
    for (int i = 0; i < 7; i++) {
      digitalWrite (ledPin[i], diceFace2[i]);
    }
  } else if (number == 3) {
    //write 3
    for (int i = 0; i < 7; i++) {
      digitalWrite (ledPin[i], diceFace3[i]);
    }
  } else if (number == 4) {
    //write 4
    for (int i = 0; i < 7; i++) {
      digitalWrite (ledPin[i], diceFace4[i]);
    }
  } else if (number == 5) {
    //write 5
    for (int i = 0; i < 7; i++) {
      digitalWrite (ledPin[i], diceFace5[i]);
    }
  } else {
    //write 6
    for (int i = 0; i < 7; i++) {
      digitalWrite (ledPin[i], diceFace6[i]);
    }
  }
  // wait for 1 seconds before next button press
  delay (1000);
}
