#include <IRremote.h> // IR library
IRsend irsend; // Initiate IR library
const int ledPin =  9; // the number of the LED pin
int buttonPushCounter1; // counts the button pushes

// Button code 
const int button_one = 10; // Button set to pin 5
unsigned long time_button_one = 0; // the last time the output pin was toggled
unsigned long debounce_one = 200; // the debounce time, increase if the output flickers
int reading_button_one; // the current reading from the input pin
int previous_button_one = HIGH; // the previous reading from the input pin

boolean boot = true;

void setup(){
  Serial.begin(9600); // Start serial
  pinMode(button_one, INPUT_PULLUP); // Set the button as input
  pinMode(ledPin, OUTPUT); // Set the IR LED as output
}

void loop() {

  reading_button_one = digitalRead(button_one); // Read button pin for a press
  if (reading_button_one == HIGH && previous_button_one == LOW && millis() - time_button_one > debounce_one) 
  {
  
    digitalWrite(ledPin, HIGH); // Turn LED on
    buttonPushCounter1++;
    boot = true;
      
    if (buttonPushCounter1 == 6) 
    {
      buttonPushCounter1 = 1;
    }
  }
  
  previous_button_one = reading_button_one;

  if (buttonPushCounter1 == 1 && boot == true) {
    Serial.println("BBC 1 HD"); 
    irsend.sendRC6(0xC00C01, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C01, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C05, 24); // Send to IR LED
    boot = false;
    digitalWrite(ledPin, LOW); // Turn LED off
  }
  
  if (buttonPushCounter1 == 2 && boot == true) {
    Serial.println("BBC 2 HD"); 
    irsend.sendRC6(0xC00C01, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C00, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C02, 24); // Send to IR LED
    boot = false;
    digitalWrite(ledPin, LOW); // Turn LED off
  }

  if (buttonPushCounter1 == 3 && boot == true) {
    Serial.println("ITV HD"); 
    irsend.sendRC6(0xC00C01, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C07, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C08, 24); // Send to IR LED
    boot = false;
    digitalWrite(ledPin, LOW); // Turn LED off
  }

  if (buttonPushCounter1 == 4 && boot == true) {
    Serial.println("Channel 4 HD"); 
    irsend.sendRC6(0xC00C02, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C02, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C07, 24); // Send to IR LED
    boot = false;
    digitalWrite(ledPin, LOW); // Turn LED off
  }

  if (buttonPushCounter1 == 5 && boot == true) {
    Serial.println("Channel 5 HD"); 
    irsend.sendRC6(0xC00C01, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C00, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C05, 24); // Send to IR LED
    boot = false;
    digitalWrite(ledPin, LOW); // Turn LED off
  }
}
