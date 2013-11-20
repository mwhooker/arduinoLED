/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(0, 1);
//   avoid using pins with LEDs attached

int redPin = 10, greenPin = 11, bluePin = 13;

void setup() {
  // pinMode(2, INPUT);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);

  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
}

long oldPosition  = -999;


/* cycles from 0-2^24*/
void writeRGB(unsigned int count) {
  unsigned int trimmed = count % int(pow(2, 24));
  unsigned char *colors = (unsigned char *)&trimmed;
  unsigned char r = colors[0], g = colors[1], b = colors[2];
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
  Serial.println("r, g, b");
  Serial.println(r, DEC);
  Serial.println(g, DEC);
  Serial.println(b, DEC);

}


void loop() {


  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
    writeRGB(newPosition);
  }

}





