#include "toggle.h"
#include <Encoder.h>

RGBEncoder *rgb;
Toggle *toggle;


void new_color() {
  Serial.println("Button Press LOW");
  rgb->next();
}


void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
  int pins[3] = {
    10, 11, 13
  };
  rgb = new RGBEncoder(pins, 0, 1);
  toggle = new Toggle(6, new_color);
}


RGBEncoder::RGBEncoder(int rgb_pins[3], int enc_pin_a, int enc_pin_b) {
  encoder = new Encoder(enc_pin_a, enc_pin_b);
  for (int i = 0; i < 3; i++) {
    pinMode(rgb_pins[i], OUTPUT);

    LED color = {rgb_pins[i], 0};
    RGB[i] = color;
  }
  current_led = &RGB[0];
  current_led_idx = 0;

}

void RGBEncoder::write(LED *led) {
  Serial.println("R, G, B");
  Serial.println(RGB[0].last_position);
  Serial.println(RGB[1].last_position);
  Serial.println(RGB[2].last_position);
  analogWrite(led->pin, led->last_position % 255);
}

void RGBEncoder::next() {
  if (current_led_idx == 2) {
    current_led_idx = 0;
  } 
  else {
    current_led_idx++;
  }
  current_led = &RGB[current_led_idx];
  encoder->write(current_led->last_position);
  this->write(current_led);
}

void RGBEncoder::check() {
  long new_position = encoder->read();
  if (new_position != current_led->last_position) {
    current_led->last_position = new_position;
    this->write(current_led);
  }
}

void loop() {
  rgb->check();
  toggle->check();
  delay(100);
}






