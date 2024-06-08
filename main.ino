#include <USBHost_t36.h>

// V+ from USB-C goes to 5V on Teensy's USB Host pads
// GND from USB-C goes to 2nd GND on Teensy's USB Host pads (doesn't matter, I just had a better solder joint with 2nd pad)

// 5V (Yellow) line for GCC is unused currently
// 3.3 (Blue) line for GCC is from the onboard 3.3V pin
// GND (Green/White) line for GCC goes to GND (any)

USBHost SPC; // Sets up SPC as the USB Host
USBHIDParser HID(SPC); // HID input decoded with USBHIDParser
JoystickController joysticks[1] = {JoystickController(SPC)}; // 1 joystick being used (testing)

uint32_t buttons_prev = 0;

// SPC Controls

bool spc_A;
bool spc_B;
bool spc_X;
bool spc_Y;

bool spc_DP_U;
bool spc_DP_D;
bool spc_DP_L;
bool spc_DP_R;

bool spc_PLUS; // Will prob = GCC Start?
bool spc_MINUS; // Prob won't be used
bool spc_HOME; // Prob won't be used (or maybe = GCC Start)
bool spc_SS; // Screenshot button - will not be used (impossible?)

int spc_LJOY_X;
int spc_LJOY_Y;
bool spc_LJOY_IN; // Pressing left joystick into controller

int spc_RJOY_X;
int spc_RJOY_Y;
bool spc_RJOY_IN; // Pressing right joystick into controller

bool spc_L;
bool spc_R;
bool spc_ZL;
bool spc_ZR;

// GCC Controls

bool gcc_A;
bool gcc_B;
bool gcc_X;
bool gcc_Y;

bool gcc_DP_U;
bool gcc_DP_D;
bool gcc_DP_L;
bool gcc_DP_R;

bool gcc_START; // Not sure what to do with this - maybe = SPC plus?

int gcc_JOY_X;
int gcc_JOY_Y;

int gcc_C_X;
int gcc_C_Y;

bool gcc_Z;
int gcc_LTRIG; // L/R triggers maybe should be bool? regardless, SPC L/R trig = bool, so GCC L/R trig = bool
int gcc_RTRIG;

void setup() { // Initalization
  Serial.begin(9600);
  while(!Serial); // Waits for serial monitor to open
  Serial.println("Begin");
  SPC.begin();
}

void loop() { // Loops continuously
  uint32_t buttons = joysticks[0].getButtons(); // Bits are: Y (0), X (1), B (2), A (3), R (6), ZR (7), - (8), + (9), Rin (10), Lin (11), Home (12), Camera (13), Dpad Down (16), Dpad Up (17), Dpad Right (18), Dpad Left (19), L (22), ZL (23)
  // Joystick values are 12 bit signed integer ranging from -2048 to 2047
  spc_LJOY_X = joysticks[0].getAxis(0);
  spc_LJOY_Y = joysticks[0].getAxis(1);
  spc_RJOY_X = joysticks[0].getAxis(2);
  spc_RJOY_Y = joysticks[0].getAxis(3);
  Serial.printf("LJOY X: %d -- LJOY Y: %d\nRJOY X: %d -- RJOY Y_ %d", spc_LJOY_X, spc_LJOY_Y, spc_RJOY_X, spc_RJOY_Y);
  Serial.println();
  if (buttons != buttons_prev) {
    spc_Y = buttons & 1;
    spc_X = (buttons >> 1) & 1;
    spc_B = (buttons >> 2) & 1;
    spc_A = (buttons >> 3) & 1;
    spc_R = (buttons >> 6) & 1;
    spc_ZR = (buttons >> 7) & 1;
    spc_MINUS = (buttons >> 8) & 1;
    spc_PLUS = (buttons >> 9) & 1;
    spc_RJOY_IN = (buttons >> 10) & 1;
    spc_LJOY_IN = (buttons >> 11) & 1;
    spc_HOME = (buttons >> 12) & 1;
    spc_SS = (buttons >> 13) & 1;
    spc_DP_D = (buttons >> 16) & 1;
    spc_DP_U = (buttons >> 17) & 1;
    spc_DP_R = (buttons >> 18) & 1;
    spc_DP_L = (buttons >> 19) & 1;
    spc_L = (buttons >> 22) & 1;
    spc_ZL = (buttons >> 23) & 1;    
    Serial.printf("A: %d -- B: %d -- X: %d -- Y: %d\nDPAD UP: %d -- DPAD DOWN: %d, DPAD LEFT: %d, DPAD RIGHT: %d\nPLUS: %d, MINUS: %d HOME: %d CAMERA: %d\nLin: %d Rin: %d\nL: %d R: %d ZL: %d ZR: %d\n\n\n", spc_A, spc_B, spc_X, spc_Y, spc_DP_U, spc_DP_D, spc_DP_L, spc_DP_R, spc_PLUS, spc_MINUS, spc_HOME, spc_SS, spc_LJOY_IN, spc_RJOY_IN, spc_L, spc_R, spc_ZL, spc_ZR);
    buttons_prev = buttons;
  }
  delay(200);
}
