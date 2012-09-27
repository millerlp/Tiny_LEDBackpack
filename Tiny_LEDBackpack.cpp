/*************************************************** 
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks 
  ----> http://www.adafruit.com/products/
  ----> http://www.adafruit.com/products/

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
  
  Modified to use TinyWireM library 2012-09-26 Luke Miller
  For using the LED Backpack with the ATtiny 85 or 84 processors. This
  requires a different I2C library, TinyWireM, to communicate with
  the LED Backpack. 
  TinyWireM library obtained from http://www.scenelight.nl/?wpfb_dl=22
  
  
 ****************************************************/

#include "TinyWireM.h"
#include "Tiny_LEDBackpack.h"
//#include "Adafruit_GFX.h"

static const uint8_t numbertable[] = { 
	0x3F, /* 0 */
	0x06, /* 1 */
	0x5B, /* 2 */
	0x4F, /* 3 */
	0x66, /* 4 */
	0x6D, /* 5 */
	0x7D, /* 6 */  // 125
	0x07, /* 7 */ // 7
	0x7F, /* 8 */ //  127
	0x6F, /* 9 */
	0x77, /* a */
	0x7C, /* b */
	0x39, /* C */
	0x5E, /* d */
	0x79, /* E */
	0x71, /* F */
};

void Tiny_LEDBackpack::setBrightness(uint8_t b) {
  if (b > 15) b = 15;
  TinyWireM.beginTransmission(i2c_addr);
  TinyWireM.send(0xE0 | b);
  TinyWireM.endTransmission();  
}

void Tiny_LEDBackpack::blinkRate(uint8_t b) {
  TinyWireM.beginTransmission(i2c_addr);
  if (b > 3) b = 0; // turn off if not sure
  
  TinyWireM.send(HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1)); 
  TinyWireM.endTransmission();
}

Tiny_LEDBackpack::Tiny_LEDBackpack(void) {
}

void Tiny_LEDBackpack::begin(uint8_t _addr = 0x70) {
  i2c_addr = _addr;

  TinyWireM.begin();
  TinyWireM.beginTransmission(i2c_addr);
  TinyWireM.send(0x21);  // turn on oscillator
  TinyWireM.endTransmission();
  blinkRate(HT16K33_BLINK_OFF);
  
  setBrightness(15); // max brightness
}

void Tiny_LEDBackpack::writeDisplay(void) {
  TinyWireM.beginTransmission(i2c_addr);
  TinyWireM.send((uint8_t)0x00); // start at address 0x00
  for (uint8_t i = 0; i < 5; i++) {
	  TinyWireM.send(displaybuffer[i]);
	  TinyWireM.send(0x00);   
  }
  TinyWireM.endTransmission();  
}

void Tiny_LEDBackpack::clear(void) {
	TinyWireM.beginTransmission(i2c_addr);
	TinyWireM.send(0x00); // starting address
	for(int i = 0; i < 5; i++){
		displaybuffer[i] = 0;
		TinyWireM.send(displaybuffer[i]);
		TinyWireM.send(0x00);
	}
	TinyWireM.endTransmission();
}

Tiny_7segment::Tiny_7segment(void) {
  position = 0;
}

void Tiny_7segment::print(unsigned long n, int base)
{
  if (base == 0) write(n); // if a byte (base 0) is being sent
  else printNumber(n, base);
}

void Tiny_7segment::print(char c, int base)
{
  print((long) c, base);
}

void Tiny_7segment::print(unsigned char b, int base)
{
  print((unsigned long) b, base);
}

void Tiny_7segment::print(int n, int base)
{
  print((long) n, base);
}

void Tiny_7segment::print(unsigned int n, int base)
{
  print((unsigned long) n, base);
}

void  Tiny_7segment::println(void) {
  position = 0;
}

void  Tiny_7segment::println(char c, int base)
{
  print(c, base);
  println();
}

void  Tiny_7segment::println(unsigned char b, int base)
{
  print(b, base);
  println();
}

void  Tiny_7segment::println(int n, int base)
{
  print(n, base);
  println();
}

void  Tiny_7segment::println(unsigned int n, int base)
{
  print(n, base);
  println();
}

void  Tiny_7segment::println(long n, int base)
{
  print(n, base);
  println();
}

void  Tiny_7segment::println(unsigned long n, int base)
{
  print(n, base);
  println();
}

void  Tiny_7segment::println(double n, int digits)
{
  print(n, digits);
  println();
}

void  Tiny_7segment::print(double n, int digits)
{
  printFloat(n, digits);
}


size_t Tiny_7segment::write(uint8_t c) {

  if (c == '\n') position = 0;
  if (c == '\r') position = 0;

  if ((c >= '0') && (c <= '9'))
    writeDigitNum(position, c-'0');

  position++;
  if (position == 2) position++;
}

void Tiny_7segment::writeDigitRaw(uint8_t d, uint8_t bitmask) {
  if (d > 4) return;
  displaybuffer[d] = bitmask;
}

void Tiny_7segment::drawColon(boolean state) {
  if (state)
    displaybuffer[2] = 0xFF;
  else
    displaybuffer[2] = 0;
}

void Tiny_7segment::writeDigitNum(uint8_t d, uint8_t num, boolean dot) {
  if (d > 4) return;

  writeDigitRaw(d, numbertable[num] | (dot << 7));
}

void Tiny_7segment::print(long n, int base)
{
  printNumber(n, base);
}

void Tiny_7segment::printNumber(long n, uint8_t base)
{
    printFloat(n, 0, base);
}

void Tiny_7segment::printFloat(double n, uint8_t fracDigits, uint8_t base) 
{ 
  uint8_t numericDigits = 4;   // available digits on display
  boolean isNegative = false;  // true if the number is negative
  
  // is the number negative?
  if(n < 0) {
    isNegative = true;  // need to draw sign later
    --numericDigits;    // the sign will take up one digit
    n *= -1;            // pretend the number is positive
  }
  
  // calculate the factor required to shift all fractional digits
  // into the integer part of the number
  double toIntFactor = 1.0;
  for(int i = 0; i < fracDigits; ++i) toIntFactor *= base;
  
  // create integer containing digits to display by applying
  // shifting factor and rounding adjustment
  uint32_t displayNumber = n * toIntFactor + 0.5;
  
  // calculate upper bound on displayNumber given
  // available digits on display
  uint32_t tooBig = 1;
  for(int i = 0; i < numericDigits; ++i) tooBig *= base;
  
  // if displayNumber is too large, try fewer fractional digits
  while(displayNumber >= tooBig) {
    --fracDigits;
    toIntFactor /= base;
    displayNumber = n * toIntFactor + 0.5;
  }
  
  // did toIntFactor shift the decimal off the display?
  if (toIntFactor < 1) {
    printError();
  } else {
    // otherwise, display the number
    int8_t displayPos = 4;
    
    for(uint8_t i = 0; displayNumber; ++i) {
      boolean displayDecimal = (fracDigits != 0 && i == fracDigits);
      writeDigitNum(displayPos--, displayNumber % base, displayDecimal);
      if(displayPos == 2) writeDigitRaw(displayPos--, 0x00);
      displayNumber /= base;
    }
  
    // display negative sign if negative
    if(isNegative) writeDigitRaw(displayPos--, 0x40);
  
    // clear remaining display positions
    while(displayPos >= 0) writeDigitRaw(displayPos--, 0x00);
  }
}

void Tiny_7segment::printError(void) {
  for(uint8_t i = 0; i < SEVENSEG_DIGITS; ++i) {
    writeDigitRaw(i, (i == 2 ? 0x00 : 0x40));
  }
}
