#include <Encoder.h>
typedef void (*toggle_cb)();


class Toggle {
  int pin;
  int last_level;
  toggle_cb callback;
public:
  Toggle(int pin, toggle_cb);
  void check();
};


struct LED {
  int pin;
  long last_position;
};

class RGBEncoder {
  LED RGB[3];
  LED *current_led;
  int current_led_idx;
    Encoder *encoder;
  
  void write(LED *led);
public:
  RGBEncoder(int rgb[3], int enc_pin_a, int enc_pin_b);
  void check();
  void next();
};
