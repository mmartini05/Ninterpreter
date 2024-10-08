# Intro
The Ninterpreter is a project designed to convert the Nintendo Switch Pro Controller's USB-C connection to a Gamecube female port on the Wii. Other controllers (PS4/PS5, Xbox, etc.) may be added in future versions.<br>
The goal of this is to be able to use a Nintendo Switch Pro Controller as if it were a Gamecube controller. The important thing is I don't want to resort to software or any Wii homebrew - I simply want to
make an adapter so the Wii thinks the SPC is a GCC.<br>
I created this because of a dilemma I had faced: The Wii's Classic Controller Pro has digital triggers, but I prefer the button layout of the GCC.  The Gamecube controller is nice, but I dislike the analog triggers.  I could short the springs in my GCC, but that's above my paygrade. The Switch Pro Controller is absolutely perfect in every way (perfect layout, digital triggers), and feels amazing. But I cannot plug it into the Wii's USB-A port without Wii homebrew. I could develop software (I believe there is homebrew that lets you use alternative controllers) but I want this to be something that anyone can plug in and instantly use, no setup necessary. There is also a USB-C to GC adapter, but it requires the user to swap their controller's board with a custom one - the goal of the Ninterpreter is to allow the Switch Pro Controller to be recognized as a Gamecube Controller, without any form of Wii software or hardware replacements.<br><br>
# Links
Christopher Wang has a very insightful API for interacting with a GCC here (https://os.mbed.com/users/christopherjwang/code/gamecube_controller/) (https://github.com/christopherjwang/gamecube_controller_mbed).
Another important GCC protocol documentation is found here (https://simplecontrollers.com/blogs/resources/gamecube-protocol).<br><br>
# Parts (BOM Soon)
Teensy 4.1 (https://a.co/d/1gAxpMp)
<br>
WiiGamecube Extension Cable (https://a.co/d/5ErQUo0)
<br>
USB-C Breakout Board from Adafruit (https://www.adafruit.com/product/4090)
<br>
30 AWG Solid Core Wire (100 ft) (https://a.co/d/9TfQNIi)
<br>
2.54mm 1x8 Dual Side Pinheaders (20 pc) (https://a.co/d/eHWcvdy)
