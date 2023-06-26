#ifndef MYBUTTON
#define MYBUTTON

#ifdef ESP32
#include <Arduino.h>
#include <FunctionalInterrupt.h>
#include <functional>
#else
#error Platform not supported
#endif

class myButton;

typedef std::function<void(void*, myButton*)> ButtonHandler;

class myButton {
private:
  volatile bool _handleTask;
  int _PinNo;
  int _mode;
  int _isrMode;
  static int ButtonCounter;
  static myButton* Buttons[32];
  static hw_timer_t* My_timer;
  ButtonHandler _ButtonCallback = NULL;
  void* _ButtonCallback_arg = NULL;
  static void beginTimer();
  void IRAM_ATTR ButtonIsr();
  static void ARDUINO_ISR_ATTR TimerIsr();
public:
  volatile bool _pressed;
  myButton();
  void begin(int PinNo, int Pinmode);
  void onButtonPress(ButtonHandler callbackFunc, void* arg = 0);
  bool run();
};

#endif