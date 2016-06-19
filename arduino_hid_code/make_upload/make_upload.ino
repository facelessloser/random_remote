// Button cod 
const int button_one = 10; // Button set to pin 5
unsigned long time_button_one = 0; // the last time the output pin was toggled
unsigned long debounce_one = 200; // the debounce time, increase if the output flickers
int reading_button_one; // the current reading from the input pin
int previous_button_one = HIGH; // the previous reading from the input pin

#include "Keyboard.h"

const int buttonPin = 10; // input pin for pushbutton
int previousButtonState = HIGH; // for checking the state of a pushButton
int counter = 0; // button push counter

void setup() {
  // make the pushButton pin an input:
  pinMode(buttonPin, INPUT_PULLUP);
  // initialize control over the keyboard:
  Keyboard.begin();
}

void loop() {
  reading_button_one = digitalRead(button_one); // Read button pin for a press
  if (reading_button_one == HIGH && previous_button_one == LOW && millis() - time_button_one > debounce_one) 
  { 
    time_button_one = millis(); 
    // type out a message
    Keyboard.println("make upload"); // Sends to the computer as keyboard
    Keyboard.write(KEY_RETURN); // Sends to the computer as keyboard
  }
  previous_button_one = reading_button_one;
  // save the current button state for comparison next time:
}
