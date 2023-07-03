# InterruptedButton
Yet another Button Library this time for ESP32 Arduino IDE with GPIO Interrupt and Timer Interrupt for debounce  


This library is using the interrupt functionality of ESP32s GPIOs.  
The debounce functionality is using the ESP32s HardwareTimer 2 , so there is no stupid polling or millis() timekeeping.  

Have a look at the example file.  

The Callback functionality is not a must use! The nice part of it is, you can use delay() in it how much you like because it's not running in the actual ISR.  

The only Catch is, that you have to call the run() function in order to update the Callbacks.  
Good thing though: the run() functions return true if the button was pressed and false if not.  
