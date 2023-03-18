/*
  The SSD1306 OLED Display Controller
  Copyright 2023 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/bookish-enigma/blob/master/LICENSE
*/

#include <Wire.h>
#include <Adafruit_SSD1306.h>

const int SWITCH = 3;
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;
const int OLED_RESET = -1;      //uses Arduino reset button
int mode = 0;                   // controlled by the switch to change mode of display
boolean previousButton = HIGH;  // Variable containing the previous button state
boolean currentButton = HIGH;   // Variable containing the current button state

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  pinMode(SWITCH, INPUT_PULLUP);
  // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;)
      ;  // Don't proceed, loop forever
  }
  //clear display buffer
  display.clearDisplay();
  display.display();  //write empty buffer to display
}

void loop() {
  //read the switch to get display mode
  currentButton = digitalRead(SWITCH);  // Read the switch state

  if (previousButton != currentButton)  // If switch pressed
  {
    delay(5);                             // Wait 5ms
    currentButton = digitalRead(SWITCH);  // Read switch again
  }

  if (previousButton == HIGH && currentButton == LOW)  // Detect a button press
  {
    //Display code follows here
    if (mode == 0) {
      //display text smallest size
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 30);
      display.println("OLED Display!");
      display.display();
      display.clearDisplay();
    } else if (mode == 1) {
      //invert text
      display.setTextColor(BLACK, WHITE);
      display.setCursor(0, 30);
      display.println("OLED Display!");
      display.display();
      display.clearDisplay();
    } else if (mode == 2) {
      //larger text
      display.setTextColor(WHITE);
      display.setCursor(0, 26);
      display.setTextSize(2);
      display.println("OLED Display!");
      display.display();
      display.clearDisplay();
    } else if (mode == 3) {
      //display decimal numbers
      display.setTextSize(1);
      display.setCursor(0, 30);
      display.println(12345);
      int x = 100;
      display.println(x);
      display.display();
      display.clearDisplay();
    } else if (mode == 4) {
      //defining base for numbers
      display.setCursor(0, 30);
      display.print("0x");
      display.print(0xFF, HEX);
      display.print("(HEX) = ");
      display.print(0xFF, DEC);
      display.println("(DEC)");
      display.display();
      display.clearDisplay();
    } else if (mode == 5) {
      //printing ASCII Characters
      display.setCursor(0, 26);
      display.setTextSize(2);
      display.write(3);
      display.display();
      display.clearDisplay();
    } else if (mode == 6) {
      //scrolling
      display.setCursor(0, 0);
      display.setTextSize(1);
      display.println("Full");
      display.println("screen");
      display.println("scrolling");
      display.display();
      display.startscrollright(0x00, 0x07);
      delay(2000);
      display.stopscroll();
      delay(1000);
      display.startscrollleft(0x00, 0x07);
      delay(2000);
      display.stopscroll();
      delay(1000);
      display.startscrolldiagright(0x00, 0x07);
      delay(2000);
      display.startscrolldiagleft(0x00, 0x07);
      delay(2000);
      display.stopscroll();
      display.clearDisplay();
    } else if (mode == 7) {
      display.setCursor(0, 0);
      display.setTextSize(1);
      display.println("Part");
      display.println("screen");
      display.println("scrolling");
      display.display();
      display.startscrollright(0x00, 0x00);
      display.clearDisplay();
      delay(10000);
      display.stopscroll();
    } else if (mode == 8) {
      // Draw random pixel
      int x;
      int y;
      for (int i = 0; i < 50; i++) {
        x = random(display.width());
        y = random(display.height());
        display.drawPixel(x, y, WHITE);
        display.display();
        delay(100);
      }
      display.clearDisplay();
    } else if (mode == 9) {
      // Draw lines
      for (int i = 0; i < display.width(); i += 4) {
        display.drawLine(0, 0, i, display.height() - 1, WHITE);
        display.display();
        delay(1);
      }
      for (int i = 0; i < display.height(); i += 4) {
        display.drawLine(0, 0, display.width() - 1, i, WHITE);
        display.display();
        delay(1);
      }
      display.clearDisplay();
    } else if (mode == 10) {
      // Draw a rectangle
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("Rectangle");
      display.drawRect(0, 15, 90, 40, WHITE);
      display.display();
      display.clearDisplay();
    } else if (mode == 11) {
      // Draw filled rectangle
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("Filled Rectangle");
      display.fillRect(0, 15, 90, 40, WHITE);
      display.display();
      display.clearDisplay();
    } else if (mode == 12) {
      // Draw round rectangle
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("Round Rectangle");
      display.drawRoundRect(0, 15, 90, 40, 8, WHITE);
      display.display();
      display.clearDisplay();
    } else if (mode == 13) {
      // Draw filled round rectangle
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("Filled Round Rect");
      display.fillRoundRect(0, 15, 90, 40, 8, WHITE);
      display.display();
      display.clearDisplay();
    } else if (mode == 14) {
      // Draw circle
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("Circle");
      display.drawCircle(40, 35, 20, WHITE);
      display.display();
      display.clearDisplay();
    } else if (mode == 15) {
      // Draw filled circle
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("Filled Circle");
      display.fillCircle(40, 35, 20, WHITE);
      display.display();
      display.clearDisplay();
    } else if (mode == 16) {
      // Draw triangle
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("Triangle");
      display.drawTriangle(40, 15, 10, 60, 70, 60, WHITE);
      display.display();
      display.clearDisplay();
    } else {
      // Draw filled triangle
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("Filled Triangle");
      display.fillTriangle(40, 15, 10, 60, 70, 60, WHITE);
      display.display();
      display.clearDisplay();
    }

    mode++;
    //cycle mode if needed
    if (mode == 18) {
      mode = 0;
    }
  }
  previousButton = currentButton;  // Reset button value
}