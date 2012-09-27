/* SevenSegTest_tiny
  This is a demonstration of using the Adafruit 4-digit 
  7-segment LED backpack with an ATtiny uC. 
  It requires the TinyWireM library for I2C communication
  and the Tiny_LEDBackpack library for the various display
  functions.  
  
   NOTE: Tested successfully on ATtiny85, using 4700ohm pull-up
   resistors on SCL and SDA lines. Tested using 1MHz internal clock.
   ATtiny85 physical pin7 --> SCL pin on LED Backpack
   ATtiny85 physical pin5 --> SDA pin on LED Backpack
   
   NOTE: Tested successfully on ATtiny84, using 4700ohm pull-up
   resistors on SCL and SDA lines. Tested using 1MHz internal clock
   ATtiny84 physical pin9 --> SCL pin on LED Backpack
   ATtiny84 physical pin7 --> SDA pin on LED Backpack
   
   Tested with and without AVRISP mkII hooked up, works fine both
   ways.
  
  This demo also uses a regular LED attached to 
  ATtiny84 physical pin 2 (Arduino pin 10) to show 
  that the sketch is running. 
*/
#include <TinyWireM.h>
#include <Tiny_LEDBackpack.h>


Tiny_7segment sevenseg = Tiny_7segment();
int led = 10; // indicator LED for ATtiny84. Connect with 100-470ohm resistor


#define i2c_addr 0x70 // stock address for Adafruit 7-segment LED backpack

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led,HIGH);
  delay(1500);
  digitalWrite(led,LOW);
  delay(300); 
  sevenseg.begin(i2c_addr); // initialize HT16K33 controller
//  sevenseg.blinkRate(2); // set blink rate (0,1,2 or 3)
  sevenseg.clear(); // clear all digits on display
  delay(1000);
}

void loop(){
  sevenseg.drawColon(true); // draw colon
  sevenseg.writeDisplay(); // push data to display
  delay(500);
  // Example of writing a multi-digit integer to the display
  sevenseg.print(4203); // print integer
  sevenseg.writeDisplay(); // push data to display
  delay(500);
  // Example of writing a multi-digit floating point number
  // to the display. The 2nd argument specifies 
  // how many digits to display after the decimal. Omit the 
  // 2nd argument for integer values. 
  sevenseg.print(12.2, 1); // print a floating point number
  sevenseg.writeDisplay(); // push data to display
  delay(500);
  sevenseg.clear(); // clear display before writing raw digit
  // The clear command doesn't need a writeDisplay call afterwards
  
  // Example of writing a single digit to a specified position on the
  // display. The 1st argument is the digit position (0,1,3,4), 2nd
  // value is the numeric value to display (0-9, a-F), and the 3rd 
  // value is whether to show the decimal point. Note that if you
  // don't clear the display ahead of time, any previously displayed 
  // values in other digits will remain visible. 
  sevenseg.writeDigitNum(3, 9, true); // position 3, value 9, show decimal)
  sevenseg.writeDisplay(); // push the data to the display
  delay(500);

  //-----------------------------------------------------------------
  // Example of a hard-coded write using the
  // TinyWireM library by itself. 
//  delay(100);
//  TinyWireM.beginTransmission(0x70); // device address
//  TinyWireM.send(0x02); // digit address (0x00, 0x02, 0x06, 0x08)
//  TinyWireM.send(0x4F); // send bitmask for number to display
//  TinyWireM.endTransmission(); // push data to display
//  TinyWireM.beginTransmission(0x70); //device address
//  TinyWireM.send(0x08); // starting address (4th digit = 0x08)
//  TinyWireM.send(0x7F); // send bitmask for number to display
//  TinyWireM.endTransmission(); // push data to display  
   //----------------------------------------------------------------
   
   //----------------------------------------------------------------
   // Hard coded example of turning on colon using TinyWireM library
//   TinyWireM.beginTransmission(0x70);
//   TinyWireM.send(0x04);  // position of colon
//   TinyWireM.send(0xFF); // send a 255 to turn on the colon
//   TinyWireM.endTransmission(); // push data to display
//   delay(500);
   //----------------------------------------------------------------
   
  //----------------------------------------------------------------- 
  // Bit mask codes. These can be used with writeDigitRaw to
  // print various letters and symbols in a digit on the
  // seven segment LED display. 
  // The first argument is the position
  // on the 4-digit display, starting at 0 (far left),
  // ending at 4 (far right), with position 2 being 
  // the colon (so you'll skip this position usually).
  // The second argument is an integer that corresponds
  // to the binary representation of the combination of
  // 7 segments making up each digit. 
  //         0
  //      ------
  //   5  |     | 1
  //      |  6  |
  //      ------ 
  //   4  |     | 2
  //      |     |
  //      ------   o7 
  //         3
  // For example, to make upper case A, you want to 
  // light up segments 0,1,2,4,5,6.
  // The binary representation would be b01110111.
  //           The bit positions are -->b76543210
  // The corresponding integer value is 119 for A. 
  // Use a binary to decimal calculator to convert.
  // Below is a list of codes for letters and symbols
//  sevenseg.writeDigitRaw(0,119); // 119 = "A"
//  sevenseg.writeDigitRaw(0,124); // 124 = "b"
//  sevenseg.writeDigitRaw(0,57); // 57 = "C"
//  sevenseg.writeDigitRaw(0,94); // 94 = "d"
//  sevenseg.writeDigitRaw(0,121); // 121 = "E"
//  sevenseg.writeDigitRaw(0,113); // 113  = "F"
//  sevenseg.writeDigitRaw(0,125); // 125 = "G"
//  sevenseg.writeDigitRaw(0,118); // 118 = "H"
//  sevenseg.writeDigitRaw(0,116); // 116 = "h"
//  sevenseg.writeDigitRaw(0,6); // 6 = "I" aka 1
//  sevenseg.writeDigitRaw(0,4); // 4 = "i"
//  sevenseg.writeDigitRaw(0,30); // 30 = "J"
//  sevenseg.writeDigitRaw(0,56); // 56 = "L"
//  sevenseg.writeDigitRaw(0,84); // 84 = "n"
//  sevenseg.writeDigitRaw(0,92); // 92 = "o"
//  sevenseg.writeDigitRaw(0,115); // 115 = "P"
//  sevenseg.writeDigitRaw(0,103); // 103 = "q" aka 9
//  sevenseg.writeDigitRaw(0,80); // 80 = "r"
//  sevenseg.writeDigitRaw(0,109); // 109 = "S" aka 5
//  sevenseg.writeDigitRaw(0,70); // 70 = "t"
//  sevenseg.writeDigitRaw(0,28); // 28 = "u"
//  sevenseg.writeDigitRaw(0,62); // 62 = "U"
//  sevenseg.writeDigitRaw(0,110); // 110 = "y"
//  sevenseg.writeDigitRaw(0,64); // 64 = "-" negative sign
//  sevenseg.writeDigitRaw(0,34); // 34 = " " " double quote
//  sevenseg.writeDigitRaw(0,32); // 32 = "'" apostrophe (upper left)
//  sevenseg.writeDigitRaw(0,2); // 2 = "'" apostrophe (upper right)  
//  sevenseg.writeDigitRaw(0,8); // 8 = "_" underscore
//  sevenseg.writeDigitRaw(0,1); // 1 = "-" overbar
//  sevenseg.writeDigitRaw(0,16); // 16 = lower left bar
//  sevenseg.writeDigitRaw(0,4); // 4 = lower right bar
//  sevenseg.writeDigitRaw(0,128); // 128 = "." decimal
//  sevenseg.writeDigitRaw(0,0); // blank
//  sevenseg.writeDigitRaw(2,255); // 255 = ":"  colon, always position 2
//  ****Always follow a writeDigitRaw command with the*****
//  sevenseg.writeDisplay(); command to push the data to the
//  display. 
  // Example of using writeDigitRaw to write numbers or characters
  // to specific digits on the display. This spells 'run'.
  sevenseg.writeDigitRaw(0,80); // specify position and code
  sevenseg.writeDigitRaw(1,28); 
  sevenseg.writeDigitRaw(3,84);
  sevenseg.writeDisplay(); // push data to display
  delay(1000);


  //---------------------------------------------------------------
  // A cute trick to make a little "processing" indicator
  // This will light each of the outer segments of a digit
  // in series, making a rotating indicator. The outer 
  // segments are conveniently set up with bit mask values
  // that are increasing multiples of 2.
  sevenseg.clear(); 
  for (int wait = 0; wait < 3; wait++) { // repeat multiple times
    for (int i = 1; i < 64; i *= 2) {
      sevenseg.writeDigitRaw(0,i);
      sevenseg.writeDisplay();
      delay(100);
    }
  }
  //-----------------------------------------------------------------
  // Another animation that lights each of the decimal points in
  // succession. 
  for (int wait = 0; wait < 3; wait++) { // repeat multiple times
    for (int i = 0; i < 5; i++) {
     if (i == 2) i++;  // This is needed to skip over position 2
     sevenseg.writeDigitRaw(i,128); // light the decimal at position i
     sevenseg.writeDisplay();
     delay(100);
     sevenseg.writeDigitRaw(i,0); // clear the decimal at position i
     sevenseg.writeDisplay();
    }
  }
  
  // Flash the external LED to indicate that the sketch is running
  // in case the 7-segment LED display isn't working.
  digitalWrite(led,HIGH);
  delay(200);
  digitalWrite(led,LOW);
  delay(200);

}
