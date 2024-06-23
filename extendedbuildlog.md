5/18/24
Started yesterday (5/17/24) night - I faced my GCC/CCP dilemma since playing Mogi Lounge and the mods told me that using a SPC on the Wii, if I could find a way to do so, is perfectly allowed. And so, that is what I am doing.
Last night I found an API for interacting with the GCC (https://os.mbed.com/users/christopherjwang/code/gamecube_controller/), but I didn't do a very deep dive. The first problem I have with the SPC: it's bluetooth, but it charges and connects via USB-C.
I need to find out if the USB-C is used explicitly for charging, or if it also transmits data through that cable. Hopefully it does.
Update - https://handheldlegend.com/products/retro-c-gamecube-cable-usb-c-to-gamecube-cable?variant=40434041356422 bought one of these - it is a USB-C to GC cable. It ONLY works for things like the PhobGCC (a replacement motherboard), NOT a native SPC. I am going to cut the cable just to look at wiring and the likes.

https://www.bitbuilt.net/forums/index.php?threads/ninterpreter-buildlog.6355/
This link is to my buildlog - this text document will be my extended buildlog and thoughts, whereas the BitBuilt link is a more proper buildlog

Ordered a ‎1528-5180-ND‎ (#‎5180) from DigiKey, a simple USB-C breakout. I will solder some extending wires to make it easier to put into a breadboard.‎

Night of 5/18/24 (it's 1:30am 5/19) - I settled on the Arduino Nano Every. I began to write the main.ino (just the basic structure). Got a lot of work ahead of me.

5/19/24
Wrote a lot more code so far. Added declarations for buttons on SPC/GCC.
FIRST GOAL: Be able to get input from Data+/Data- lines on SPC's USB-C: HOPEFULLY my differential function works and can actually combine it into a single byte.
NEXT GOAL: Translate hexadecimal into actual input: be able to read values of all buttons (similar to the aforementioned GCC API and the demo video on that website)
NEXT GOAL: Be able to translate that into GCC output
NEXT GOAL: Design PCB to replace breadboard. Once that works, design case, cable, etc.

5/22/24
USB-C to GC cable from Hand Held Legend came through. I wanted to see if it would invalide my project - it does say that the cable only works for things like b0xx, and it only works on a modded SPC, which makes sense as it actually caused my Wii to shut off (shorted the Wii somehow) lol - the nInterpreter is good to continue work! Arduino Nano Every and my USB-C breakout arrived today, so time for some testing...

5/28/24
Spent the weekend having to buy new cable (solid core 30 awg) since my 22 awg stranded was being a pain. Turns out the SPC connection is male, so I need a female breakout board. Also changed name from "nInterpreter" to "Ninterpreter"
Had to buy a female breakout board here: https://a.co/d/0UALeOm - the original one I found was only available in India

5/29/24
Fears are true - GPIO pins are NOT fast enough to read USB-C signals, luckily the every has a host shield, so I just need a USB-C to Micro adapter and I'll have to go from there!

5/30/24
Got hex to output clearly, but obviously right now it's not really sending anything useful. Screenshot below
![Got a nice chunk of 40 bytes each](https://github.com/mmartini05/Ninterpreter/blob/main/Images/5.30.24.png)
Gonna redo the soldering and charge the SPC - I DOUBT this will make any difference

6/2/24
Hex output is bogus, nothing useful. Luckily I have a spare Raspberry Pi Pico, which does have a USB host. The nice thing is, even though I don't have pinheaders for it, I don't really need it, since the only outputs on the RPi are for UART (GCC)!
Teensy 4.1 is exactly what I need! RPi doesn't have USB host actually, but not only does the Teensy 4.1 have USB host/shield capabilities, it can act as a controller. That would be great, but I really just need to interpret and repackage the SPC data. Teensy 4.1 would've solved all my problems earlier! No breakout board necessary!

6/5/24
Teensy 4.1 is amazing. I just solder the breakout board to exclusive "USB Host" pads on the board. I just have to use the USBHost_t36 library. I do need new soldering iron tips, as the replacement ones I have been using are poor quality. I bought these Japan import tips and I am excited for those! I want to be able to display the inputs from the SPC, which I think I can do soon. Repackaging it is a different story, though.

6/7/24
Big update! I have code working based on the USBHost_t36 header! It just works for the ABXY buttons for now, and I need to figure out how to make the buttons separate - right now, the button value is just a total number of all the buttons.
Update: ALL buttons' values are displayed! The SPC sends a long string of binary data - bit 0 is Y, bit 6 is R, bit 13 is camera, bit 19 is Dpad left, so on and so forth.![Works perfect!](https://github.com/mmartini05/Ninterpreter/blob/main/Images/6.7.24.png) I just need to get the LJOY/RJOY X/Y values and I'm done! (Other than rumble...)

6/8/24
Conversion is done! Just need to figure out how to send data through UART ![Amazing. And it sets the midpoint of the GCC joysticks!](https://github.com/mmartini05/Ninterpreter/blob/main/Images/6.8.24.png) (For SPC, joystick X/Y values range from -2048 to 2047, with 0 in the middle, while for GCC, joystick X/Y values range from 0 to 255, where 128 is the middle)

6/9/24
Keep forgetting to write in here (technically it's 6/10) - the GCC is supposed to send 8 bytes of data. I have created those 8 bytes based on the inputs from the SPC. SPC inputs are decoded and parsed, converted to GCC inputs, and that data is used to create 8 bytes to send. I have to do more research on how to send (probably Serial.write()? - UART doesn't seem possible since data is bidirectional. Update 1 am on 6/10 - Serial1 (Pin 1 is Tx) will be used to send data. I realized that instead of combining all 8 bytes and sending 8 bytes over, it may just be easier (and with my limited experience, easier to understand) to just send each byte as the byte is made. It might be faster too, since the code is literally "byte0 = (number that = 0, 0, 0, START, Y, X, B, A); Serial1.write(byte0)" so on and so forth!

6/10/24
Documented SPC data findings on this repo. Wii seems to turn off to prevent damage as soon as I plug in the GC plug. Not sure why

6/23/24
Had surgery so I was out for a bit - Wii turned off due to wrong wiring. I am going to start PCB design!
