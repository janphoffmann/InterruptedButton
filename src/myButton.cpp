#include "myButton.h"

hw_timer_t* myButton::My_timer = NULL;
myButton* myButton::Buttons[32] = {};
int myButton::ButtonCounter = 0;

void myButton::begin(int PinNo, int Pinmode, uint64_t debounceTime) {
  if (ButtonCounter == 0) {
    My_timer = timerBegin(2, 80, true);
    timerAttachInterrupt(My_timer, &TimerIsr, true);
    timerAlarmWrite(My_timer, debounceTime, false);  // .5s
  }
  Buttons[ButtonCounter] = this;
  ButtonCounter++;
  _PinNo = PinNo;
  _mode = Pinmode;
  pinMode(_PinNo, _mode);
  if (_mode == INPUT_PULLUP) _isrMode = FALLING;
  else _isrMode = RISING;
  attachInterrupt(_PinNo, std::bind(&myButton::ButtonIsr, this), _isrMode);
}

void myButton::onButtonPress(ButtonHandler callbackFunc, void* arg) {
  _ButtonCallback = callbackFunc;
  _ButtonCallback_arg = arg;
}

myButton::myButton() {
  _pressed = false;
  _handleTask = false;
}

bool myButton::run() {
  if (_handleTask) {
    if (_ButtonCallback != NULL) _ButtonCallback(_ButtonCallback_arg, this);
    _handleTask = false;
    return true;
  } else return false;
}

void myButton::ButtonIsr() {
  if (!_pressed) {
    _pressed = true;
    _handleTask = true;
    timerRestart(My_timer);
    timerAlarmEnable(My_timer);
  }
}

void myButton::TimerIsr() {
  for (int i = 0; i < ButtonCounter; i++) {
    if (Buttons[i]->_pressed) {
      Buttons[i]->_pressed = false;
    }
  }
  // attachInterrupt(Buttons[i]->_PinNo, std::bind(&myButton::ButtonIsr, Buttons[i]), Buttons[i]->_isrMode);
}
