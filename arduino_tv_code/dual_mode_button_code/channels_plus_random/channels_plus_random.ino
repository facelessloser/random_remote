#define buttonPin 10 // analog input pin to use as a digital input
#define ledPin1 9 // digital output pin for LED 1 indicator

#define debounce 20 // ms debounce period to prevent flickering when pressing or releasing the button
#define holdTime 1000 // ms hold period: how long to wait for press+hold event

// Button variables
int buttonVal = 0; // value read from button
int buttonLast = 0; // buffered value of the button's previous state
long btnDnTime; // time the button was pressed down
long btnUpTime; // time the button was released
boolean ignoreUp = false; // whether to ignore the button release because the click+hold was triggered
boolean menuMode = false; // whether menu mode has been activated or not

//=================================================
#include <IRremote.h> // IR library
IRsend irsend; // Initiate IR library
const int ledPin =  9; // the number of the LED pin

long unsigned int randomList[3]; // Random number array
long unsigned int irList[] = {0xC00C00,0xC00C01,0xC00C02,0xC00C03,0xC00C04,0xC00C05,0xC00C06,0xC00C07,0xC00C08,0xC00C09}; // IR channel list
long unsigned int channelListFirst[] = {0,1,2,3,5,6}; // First random number pick array
long unsigned int channelListSecondIfThree[] = {5,6,7,8,9}; // Second random number pick if the first number is 3

int buttonPushCounter1 = 0; // counts the button pushes
boolean runOnce = true;
//=================================================


void setup()
{

 // Set button input pin
 pinMode(buttonPin, INPUT);
 digitalWrite(buttonPin, HIGH );

 // Set LED output pins
 pinMode(ledPin1, OUTPUT);
 digitalWrite(ledPin1, LOW);
 Serial.begin(9600);

  randomSeed(analogRead(0));
}


//=================================================
// Events to trigger by click and press+hold

void event1()
{
  digitalWrite(ledPin1, HIGH);
  Serial.println("button 1");

  buttonPushCounter1++;
  runOnce = true;
  
  if (buttonPushCounter1 == 5) 
  {
    buttonPushCounter1 = 0;
  }
}

void event2()
{
  digitalWrite(ledPin1, HIGH);
  Serial.println("button 2");

  randomList[0] = channelListFirst[random(1,5)]; // Use random number to pick number from channel array then add to random array


  if (randomList[0] == 3)
  {
    randomList[1] = channelListSecondIfThree[random(0, 4)]; // Use random number to pick number from channel array then add to random array
  }
  else
  {
    randomList[1] = random(0, 9); // Add random number to random array
  }

    randomList[2] = random(0, 9); // Add random number to random array

//    Serial.println("-------------"); // Print to serial
    int i;
    for (i = 0; i < 3; i = i + 1){ // For loop to loop thought random array
    Serial.println(randomList[i]); // Print to serial
    irsend.sendRC6(irList[randomList[i]], 24); // Send to IR LED
    delay(200); // Dirty delay
    }
    digitalWrite(ledPin1, LOW);

  
}

//=================================================

void loop()
{

  // Read the state of the button
  buttonVal = digitalRead(buttonPin);
  delay(10);

  // Test for button pressed and store the down time
  if (buttonVal == LOW && buttonLast == HIGH && (millis() - btnUpTime) > debounce)
  {
    btnDnTime = millis();
  }

  // Test for button release and store the up time
  if (buttonVal == HIGH && buttonLast == LOW && (millis() - btnDnTime) > debounce)
  {
    digitalWrite(ledPin1, LOW);//
    if (ignoreUp == false && menuMode == false) 
      event1();
    else ignoreUp = false;
      btnUpTime = millis();
  }

  // Test for button held down for longer than the hold time
  if (buttonVal == LOW && menuMode == false && (millis() - btnDnTime) > long(holdTime))
  {
    Serial.println("Menu Mode");
    ignoreUp = true;
    btnDnTime = millis();
    menuMode = true;
    digitalWrite(ledPin1, HIGH);
    delay(300);
    digitalWrite(ledPin1, LOW);
    delay(300);
    digitalWrite(ledPin1, HIGH);
  }
    if (buttonVal == HIGH && buttonLast == LOW && (millis() - btnDnTime) > debounce)
  {
    if (ignoreUp == false && menuMode == true) 
      event2();
    else ignoreUp = false;
      btnUpTime = millis();
//      digitalWrite(ledPin1, LOW);//
  }
  if (buttonVal == LOW && menuMode == true && (millis() - btnDnTime) > long(holdTime))
  {
    Serial.println("Normal Mode");
    ignoreUp = true;
    btnDnTime = millis();
    menuMode = false;
    digitalWrite(ledPin1, HIGH);//
  }


  buttonLast = buttonVal;

  if (buttonPushCounter1 == 0 && runOnce == true) {
    Serial.println("BBC 1 HD"); 
    irsend.sendRC6(0xC00C01, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C01, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C05, 24); // Send to IR LED
    runOnce = false;
    digitalWrite(ledPin1, LOW);
  }
  
  if (buttonPushCounter1 == 1 && runOnce == true) {
    Serial.println("BBC 2 HD"); 
    irsend.sendRC6(0xC00C01, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C04, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C01, 24); // Send to IR LED
    runOnce = false;
    digitalWrite(ledPin1, LOW);
  }

  if (buttonPushCounter1 == 2 && runOnce == true) {
    Serial.println("ITV HD"); 
    irsend.sendRC6(0xC00C01, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C07, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C08, 24); // Send to IR LED
    runOnce = false;
    digitalWrite(ledPin1, LOW);
  }

  if (buttonPushCounter1 == 3 && runOnce == true) {
    Serial.println("Channel 4 HD"); 
    irsend.sendRC6(0xC00C02, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C02, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C07, 24); // Send to IR LED
    runOnce = false;
    digitalWrite(ledPin1, LOW);
  }

  if (buttonPushCounter1 == 4 && runOnce == true) {
    Serial.println("Channel 5 HD"); 
    irsend.sendRC6(0xC00C01, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C07, 24); // Send to IR LED
    delay(200);
    irsend.sendRC6(0xC00C01, 24); // Send to IR LED
    runOnce = false;
    digitalWrite(ledPin1, LOW);
  }
}
