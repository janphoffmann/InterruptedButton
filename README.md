# InterruptedButton
Yet another Button Library this time for ESP32 Arduino IDE with GPIO Interrupt and Timer Interrupt for debounce  


This library is using the interrupt functionality of ESP32s GPIOs.  
The debounce functionality is using the ESP32s HardwareTimer 2 , so there is no stupid polling or millis() timekeeping.  

Have a look at the example file.  

The Callback functionality is not a must use! The nice part of it is, you can use delay() in it how much you like because it's not running in the actual ISR.  

The only Catch is, that you have to call the run() function in order to update the Callbacks.  
Good thing though: the run() functions return true if the button was pressed and false if not.  


# Basic usage is like this:
```
//include the library
#include "myButton.h"

//define some Pins if you like
int FirstPin = 32;

//Button Definitions, no Arguments needed.
myButton FirstButton;

//callback function
void doSth(void* arg, myButton* Button){
  Serial.printf("This is Pin %d",Button->_PinNo);
}
// in setup() function:
void setup() {
  //Begin Functions
  //Sytax: myButton::begin(int Pin, int PinMode, uint64_t DebounceTime [default = 0.5s])
  FirstButton.begin(FirstPin, INPUT_PULLUP);
  //attatch Callback function
  FirstButton.onButtonPress(doSth);

  Serial.begin(115200);
}

// in loop function
void loop() {
  //Run() functions for every Button needed, so you can do as much delay() in the above callback functions as you like ;)
  FirstButton.run();
  // the run() functions return true, if the button was pressed and false, if not...
  if(FirstButton.run()) Serial.println("To use Callbacks , or not to use Callbacks");
}
```
