#include <IRremote.h>
IRsend irsend;
const int ledPin =  8;      // the number of the LED pin

// Button one 
const int button_one = 12; // Button set to pin 5
unsigned long time_button_one = 0; // the last time the output pin was toggled
unsigned long debounce_one = 200; // the debounce time, increase if the output flickers
int reading_button_one; // the current reading from the input pin
int previous_button_one = HIGH; // the previous reading from the input pin

int ledState = LOW;         // the current state of the output pin

long randNumber;
long first;
long second;
long third;
long unsigned int randomList[3];
long unsigned int irList[] = {0xC00C00,0xC00C01,0xC00C02,0xC00C03,0xC00C04,0xC00C05,0xC00C06,0xC00C07,0xC00C08,0xC00C09}; 

void setup(){
  Serial.begin(9600);
  Serial.println("-------------");
  pinMode(button_one, INPUT_PULLUP); // Set the button as input
//  digitalWrite(button_one, HIGH); // initiate the internal pull up resistor
  pinMode(ledPin, OUTPUT);
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
}

void loop() {
  // print a random number from 0 to 299
//  randNumber = random(300);
//  Serial.println(randNumber);  

  // print a random number from 10 to 19
//  randNumber = random(101, 279);
//  Serial.println(randNumber);
//  first=randNumber/100;
//  second=randNumber%100/10;
//  third=randNumber%10;
//  Serial.println(first);
//  Serial.println(second);
//  Serial.println(third);
//  randomList[0] = first;
//  randomList[1] = second;
//  randomList[2] = third;
//  int i;
//  for (i = 0; i < 3; i = i + 1){
//    Serial.println(randomList[i]);
//    delay(500);
//    }
//
//  delay(500);
  reading_button_one = digitalRead(button_one);

  if (reading_button_one == HIGH && previous_button_one == LOW && millis() - time_button_one > debounce_one) 
  { 
    time_button_one = millis(); 
//    digitalWrite(ledPin, HIGH);
    ledState = !ledState;
    randNumber = random(101, 279);
    Serial.println(randNumber);
    first=randNumber/100;
    second=randNumber%100/10;
    third=randNumber%10;
    randomList[0] = first;
    randomList[1] = second;
    randomList[2] = third;
    int i;
    for (i = 0; i < 3; i = i + 1){
      Serial.println(randomList[i]);
      irsend.sendRC6(irList[randomList[i]], 24);
      delay(500);
    }
//    irsend.sendRC6(0xC00C06, 24);
  }
  previous_button_one = reading_button_one;

  digitalWrite(ledPin, ledState);
}

