#include "toggle.h"


void Toggle::check() {
  int level = digitalRead(pin);
  if (level != last_level) {
    last_level = level;
    if (level == LOW) {
      callback();
    }
  }
}

Toggle::Toggle(int pin, toggle_cb callback) {
  this->callback = callback;
  this->pin = pin;
  pinMode(pin, INPUT_PULLUP);
  check();
}
