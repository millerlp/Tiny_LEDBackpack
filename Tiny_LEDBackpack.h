/*************************************************** 
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks 
  http://www.adafruit.com/category/37_103
  http://learn.adafruit.com/adafruit-led-backpack/0-dot-56-seven-segment-backpack

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
  
  **************
  Modified to use TinyWireM library 2012-09-26 Luke Miller
  For using the Adafruit LED Backpack with the ATtiny 85 or 84 processors. This
  requires a different I2C library, TinyWireM, to communicate with
  the LED Backpack, compared to the stock Adafruit_LEDBackpack library that
  is designed to work with ATMEGA-based Arduinos like the Uno.
  
  The initial setup for getting ATtiny processors working with Arduino 1.0.1
  was based on the instructions for High-Low Tech:
  http://hlt.media.mit.edu/?p=1695
  . 
  The TinyWireM was library obtained from:
   http://www.scenelight.nl/?wpfb_dl=22
  
  Tested on ATtiny85 and ATtiny84 processors, using the modified TinyWireM
  library linked above that contains includes for both the 25/45/85 family 
  of ATtiny and 24/44/84 family of ATtiny processors. Tested under 
  Arduino IDE 1.0.1. 
  
  If you run into PCREL errors when your sketch size exceeds 4kB, use the fix
  provided by Tom Carpenter here:
  http://arduino.cc/forum/index.php/topic,116674.msg878023.html#msg878023
  
  Removed the 8x8 LED matrix code from the original Adafruit library because 
  I was unable to test it on a ATtiny. Only the 7-Segment LED displays have 
  been tested.
  
 ****************************************************/

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "TinyWireM.h"

#define HT16K33_BLINK_CMD 0x80
#define HT16K33_BLINK_DISPLAYON 0x01
#define HT16K33_BLINK_OFF 0
#define HT16K33_BLINK_2HZ  1
#define HT16K33_BLINK_1HZ  2
#define HT16K33_BLINK_HALFHZ  3

#define HT16K33_CMD_BRIGHTNESS 0x0E

#define SEVENSEG_DIGITS 5


// this is the raw HT16K33 controller
class Tiny_LEDBackpack {
 public:
  Tiny_LEDBackpack(void);
  void begin(uint8_t _addr);
  void setBrightness(uint8_t b);
  void blinkRate(uint8_t b);
  void writeDisplay(void);
  void clear(void);

//  uint16_t displaybuffer[8]; 
  uint8_t displaybuffer[8]; // changed to uint8_t
  
  void init(uint8_t a);
 private:
  uint8_t i2c_addr;
};


#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2
#define BYTE 0

class Tiny_7segment : public Tiny_LEDBackpack {
 public:
  Tiny_7segment(void);
  size_t write(uint8_t c);

  void print(char, int = BYTE);
  void print(unsigned char, int = BYTE);
  void print(int, int = DEC);
  void print(unsigned int, int = DEC);
  void print(long, int = DEC);
  void print(unsigned long, int = DEC);
  void print(double, int = 2);
  void println(char, int = BYTE);
  void println(unsigned char, int = BYTE);
  void println(int, int = DEC);
  void println(unsigned int, int = DEC);
  void println(long, int = DEC);
  void println(unsigned long, int = DEC);
  void println(double, int = 2);
  void println(void);
  
  void writeDigitRaw(uint8_t x, uint8_t bitmask);
  void writeDigitNum(uint8_t x, uint8_t num, boolean dot = false);
  void drawColon(boolean state);
  void printNumber(long, uint8_t = 2);
  void printFloat(double, uint8_t = 2, uint8_t = DEC);
  void printError(void);

 private:
  uint8_t position;
};
