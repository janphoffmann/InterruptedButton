//include the library
#include "myButton.h"

//define some Pins if you like
int FirstPin = 32;
int SecondPin = 33;

//Button Definitions, no Arguments needed.
myButton FirstButton;
myButton SecondButton;

//callback function
void doSth(void* arg, myButton* Button){
  Serial.printf("This is Pin %d",Button->_PinNo);
}

//Callback Function
void doSthElse(void* arg, myButton* Button){
  Serial.printf("This is Pin %d",Button->_PinNo);
}

void setup() {

  //Begin Functions
  //Sytax: myButton::begin(int Pin, int PinMode, uint64_t DebounceTime [default = 0.5s])
  FirstButton.begin(FirstPin, INPUT_PULLUP);
  //attatch Callback function
  FirstButton.onButtonPress(doSth);

  SecondButton.begin(SecondPin,INPUT_PULLUP, 100000);
  SecondButton.onButtonPress(doSthElse);

  Serial.begin(115200);
}

void loop() {
  //Run() functions for every Button needed, so you can do as much delay() in the above callback functions as you like ;)
  FirstButton.run();
  SecondButton.run();
}