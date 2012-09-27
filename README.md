This library is designed to allow the use of Adafruit 4-digit 7-segment LED backpacks
with ATtiny85 and ATtiny84 processors (and likely other ATtiny models as well). 
It is adapted from the Adafruit_LEDBackpack library available at
http://github.com/adafruit/Adafruit-LED-Backpack-Library
The Adafruit 7-segment LED Backpacks are available here:
http://www.adafruit.com/category/37_103


To use this library, you also need the TinyWireM library, available here:
http://www.scenelight.nl/?wpfb_dl=22 (ATtiny84 and ATtiny85 support)

or here:

http://arduino.cc/playground/uploads/Code/TinyWireM.zip (ATtiny85 support only)

See this page:

http://arduino.cc/playground/Code/USIi2c

for an introduction to what the TinyWireM library does.

Install the TinyWireM library in your arduino-1.0.1/libraries/ directory.

Download the contents of this repository and install them in a directory 
called Tiny_LEDBackpack in your arduino-1.0.1/libraries/ directory.
Then restart the Arduino IDE. The Tiny_LEDBackpack
library includes an example sketch SevenSegTest_tiny that illustrates the use
of the library. 

Note that you will need an external programmer to upload sketches to the ATtiny
chips, and you will need to down load the ATtiny core files for the Arduino software.
To accomplish this, visit
http://hlt.media.mit.edu/?p=1695

