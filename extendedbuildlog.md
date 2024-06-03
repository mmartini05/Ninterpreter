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
Teensy 4.1 is exactly what I need! RPi doesn't have USB host actually, but not only does the Teensy 4.1 have USB host/shield capabilities, it can act as a controller. That would be great, but I really just need to interpret and repackage the SPC data.
