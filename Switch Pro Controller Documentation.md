# Setup
This is documentation on the Nintendo Switch Pro Controller's data sent over USB-C (Wired Mode). This is specifically for using the Teensy 4.1's USB Host mode.<br><br>
To first connect your Switch Pro Controller to the Teensy, you must have a USB-C Female Breakout Board. This allows you to solder wire directly to the Teensy's USB Host pads. I reccomend 30 AWG solid core wire. If you can get a simple breakout board that just includes V+, Data-, Data+, and GND, that is best.<br><br>
Once connected, include the USBHost_t36 library (#include <USBHost_t36.h>). The library itself is a GitHub repository, and reading through the header file and joystick example is very useful. To setup the SPC, you must first name the USBHost class (USBHost "SPC"), and then in the next line you must name the USBHIDParser class in order to parse the data sent via USB-C (USBHIDParser "HID"("SPC")). The third line is for the joysticks, as you must name the JoystickController class (JoystickController "joysticks" = JoystickController("SPC")). Note that the names in quotation marks are up to you. The way I have it setup is as follows:<br><br>
#include <USBHost_t36.h><br>
USBHost SPC;<br>
USBHIDParser HID(SPC);<br>
JoystickController joysticks = JoystickController(SPC);<br><br>
In your setup function (void setup), you must include (name of USBHost).begin() - so mine looks like SPC.begin();<br><br>
# Buttons
The buttons are accessed with (name of JoystickController).getButtons(). Mine looks like joysticks.getButtons(). This is 3 bytes of button data. The bytes are as follows:<br><br>
| Byte # | Data                                           |
| :----: | :--------------------------------------------: |
| 0      | Y, X, B, A, 0, 0, R, ZR                        |
| 1      | -, +, Rin, Lin, Home, Camera (Screenshot), 0, 0|
| 2      | DP_D, DP_U, DP_R, DP_L, 0, 0, L, ZL            |
<br><br>
Notes: Rin/Lin is the action of pressing down on a joystick (Lin = pressing Left in, Rin = pressing Right in)<br> DP_D/U/R/L is the D-Pad (D = Down, U = Up, R = Right, L = Left)<br><br>
# Joysticks
The joysticks are accessed with (name of JoystickController).getAxis(n), where n is:<br><br>
| n   | Joystick        |
| :-: | :-------------: |
| 0   | Left Joystick X |
| 1   | Left Joystick Y |
| 2   | Right Joystick X|
| 3   | Right Joystick Y|
<br><br>
Each joystick value is a 12 bit signed integer ranging from -2048 to 2047, where 0 is the middle.
