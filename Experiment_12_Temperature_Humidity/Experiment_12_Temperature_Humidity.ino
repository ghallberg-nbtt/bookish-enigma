/*
  HD44780 16 x 2 LCD - temperature and humidity
  Copyright 2020 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/bookish-enigma/blob/master/LICENSE
*/

#include <LiquidCrystal.h>

/*
 This Sketch was written with SimpleDHT version 1.0.11
 The code may need to be modified if other verions are used
*/
#include <SimpleDHT.h>

const byte degree [] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000,
};

const byte hot [] = {
  B00000,
  B00100,
  B10101,
  B01110,
  B11111,
  B01110,
  B10101,
  B00100,
};

// assign I/O pins
const int SWITCH = 5;
const int LED = 7;

// variables that will change value
boolean previousButton = HIGH; // Variable containing the previous button state
boolean currentButton = HIGH; // Variable containing the current button state
boolean celsiusSelected = HIGH;  // Flag if Celsius or Fahrenheit selected

// initialize the library by associating any needed LCD interface pin
// with the Arduino pin number it is connected to
LiquidCrystal lcd(2, 3, 8, 9, 10, 11);

// for DHT11,
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 6
int pinDHT11 = 6;
SimpleDHT11 dht11(pinDHT11);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // create special characters
  lcd.createChar (0, degree);
  lcd.createChar (1, hot);
  // set I/O pins
  pinMode (SWITCH, INPUT_PULLUP);
  pinMode (LED, OUTPUT);
  // display static text
  lcd.setCursor (0, 0);
  lcd.print ("Temperature:" );
  lcd.setCursor(0, 1);
  lcd.print("Humidity:" );
}

void loop() {
  // first read switch
  // is Celsius or Fahrenheit selected?
  currentButton = digitalRead(SWITCH); // Read the switch state for C or F
  if (previousButton != currentButton)  // If switch pressed
  {
    delay(5);  // Wait 5ms to debounce
    currentButton = digitalRead(SWITCH);  // Read switch again
  }

  if (previousButton == HIGH && currentButton == LOW)  // Detect a button press
  {
    celsiusSelected = !celsiusSelected;  // Toggle C/F state
  }
  previousButton = currentButton;  // Reset button value

  // now read temperature and humidity
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    lcd.clear();
    lcd.setCursor (0, 0);
    lcd.print("DHT11 read fail");
    lcd.setCursor (0, 1);
    lcd.print ("err="); lcd.print(err); delay(1000);
    return;
  }

  // display the results
  int tempC = temperature;
  if (celsiusSelected) {
    lcd.setCursor (12, 0);
    lcd.print((int)temperature); lcd.write((byte)0); lcd.print("C");
    lcd.setCursor (9, 1);
    lcd.print((int)humidity); lcd.print("%");
  } else {
    // convert to Fahrenheit
    temperature = ((temperature / 5) * 9) + 32;
    lcd.setCursor (12, 0);
    lcd.print((int)temperature); lcd.write((byte)0); lcd.print("F");
    lcd.setCursor (9, 1);
    lcd.print((int)humidity); lcd.print("%");
  }

  // set alarm if greater than 25C
  if ((int)tempC > 25) {
    digitalWrite (LED, HIGH);
    lcd.setCursor (15, 1);
    lcd.write(1); // display hot alarm
  } else {
    digitalWrite (LED, LOW);
    lcd.setCursor (15, 1);
    lcd.print(" "); // turn off hot alarm
  }
  delay (1500);
}
