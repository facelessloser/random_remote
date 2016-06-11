#include <IRremote.h> // IR library
IRsend irsend; // Initiate IR library
const int ledPin =  8; // the number of the LED pin

// Button code 
const int button_one = 12; // Button set to pin 5
unsigned long time_button_one = 0; // the last time the output pin was toggled
unsigned long debounce_one = 200; // the debounce time, increase if the output flickers
int reading_button_one; // the current reading from the input pin
int previous_button_one = HIGH; // the previous reading from the input pin

long unsigned int randomList[3]; // Random number array
long unsigned int irList[] = {0xC00C00,0xC00C01,0xC00C02,0xC00C03,0xC00C04,0xC00C05,0xC00C06,0xC00C07,0xC00C08,0xC00C09}; // IR channel list
long unsigned int channelListFirst[] = {0,1,2,3,5,6}; // First random number pick array
long unsigned int channelListSecondIfThree[] = {5,6,7,8,9}; // Second random number pick if the first number is 3

void setup(){
  Serial.begin(9600); // Start serial
  pinMode(button_one, INPUT_PULLUP); // Set the button as input
  pinMode(ledPin, OUTPUT); // Set the IR LED as output
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
}

void loop() {

  reading_button_one = digitalRead(button_one); // Read button pin for a press
  if (reading_button_one == HIGH && previous_button_one == LOW && millis() - time_button_one > debounce_one) 
  { 
    time_button_one = millis(); 
    Serial.println("-------------"); // Print to serial
    digitalWrite(ledPin, HIGH); // Turn LED on

    randomList[0] = channelListFirst[random(1,5)]; // Use random number to pick number from channel array then add to random array

//    Serial.print("First "); // Print to serial
//    Serial.println(randomList[0]); // Print to serial

    if (randomList[0] == 3)
    {
//      Serial.println("if"); // Print to serial
      randomList[1] = channelListSecondIfThree[random(0, 4)]; // Use random number to pick number from channel array then add to random array
//      Serial.print("Second "); // Print to serial
//      Serial.println(randomList[1]); // Print to serial
    }
    else
    {
//      Serial.println("else"); // Print to serial
      randomList[1] = random(0, 9); // Add random number to random array
//      Serial.print("Second "); // Print to serial
//      Serial.println(randomList[1]); // Print to serial
    }

    randomList[2] = random(0, 9); // Add random number to random array
//    Serial.print("Third "); // Print to serial
//    Serial.println(randomList[2]); // Print to serial

    Serial.println("-------------"); // Print to serial
    int i;
    for (i = 0; i < 3; i = i + 1){ // For loop to loop thought random array
      Serial.println(randomList[i]); // Print to serial
      irsend.sendRC6(irList[randomList[i]], 24); // Send to IR LED
      delay(500); // Dirty delay
    }
  }
  previous_button_one = reading_button_one;

  digitalWrite(ledPin, LOW); // Turn LED off
}

