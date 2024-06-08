#include <USBHost_t36.h>

// V+ from USB-C goes to 5V on Teensy's USB Host pads
// GND from USB-C goes to 2nd GND on Teensy's USB Host pads (doesn't matter, I just had a better solder joint with 2nd pad)

// 5V (Yellow) line for GCC is unused currently
// 3.3 (Blue) line for GCC is from the onboard 3.3V pin
// GND (Green/White) line for GCC goes to GND (any)

USBHost SPC; // Sets up SPC as the USB Host
USBHIDParser HID(SPC); // HID input decoded with USBHIDParser
JoystickController joysticks = JoystickController(SPC); // Left / Right Joysticks

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
bool spc_HOME; // Not used
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

bool gcc_START;

int gcc_JOY_X;
int gcc_JOY_Y;

int gcc_C_X;
int gcc_C_Y;

bool gcc_Z;
int gcc_LTRIG;
int gcc_RTRIG;

void setup() { // Initalization
  Serial.begin(9600);
  while(!Serial); // Waits for serial monitor to open
  Serial.println("Begin");
  SPC.begin();
  printf("GCC VALUES\n\n");
  delay(100);
}

void loop() { // Loops continuously

  // This first section gets values for the SPC buttons/joysticks

  // Bits are: Y (0), X (1), B (2), A (3), R (6), ZR (7), - (8), + (9), Rin (10), Lin (11), Home (12), Camera (13), Dpad Down (16), Dpad Up (17), Dpad Right (18), Dpad Left (19), L (22), ZL (23)
  uint32_t buttons = joysticks.getButtons();
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
  
  // Joystick values are 12 bit signed integer ranging from -2048 to 2047
  spc_LJOY_X = joysticks.getAxis(0);
  spc_LJOY_Y = joysticks.getAxis(1);
  spc_RJOY_X = joysticks.getAxis(2);
  spc_RJOY_Y = joysticks.getAxis(3);

  // This second section assigns values to the GCC buttons/joysticks

  gcc_A = spc_A;
  gcc_B = spc_B;
  gcc_X = spc_X;
  gcc_Y = spc_Y;

  gcc_DP_U = spc_DP_U;
  gcc_DP_D = spc_DP_D;
  gcc_DP_L = spc_DP_L;
  gcc_DP_R = spc_DP_R;

  gcc_START = spc_PLUS;

  gcc_JOY_X = convert(spc_LJOY_X);
  gcc_JOY_Y = convert(spc_LJOY_Y);
  
  gcc_C_X = convert(spc_RJOY_X);
  gcc_C_Y = convert(spc_RJOY_Y);

  gcc_Z = spc_R;

  gcc_LTRIG = ((spc_L | spc_ZL) * 255); // LTRIG is equal to the value of L/ZL 
  gcc_RTRIG = (spc_ZR * 255);

  Serial.printf("JOY X: %d -- JOY Y: %d\nC X: %d -- C Y_ %d", gcc_JOY_X, gcc_JOY_Y, gcc_C_X, gcc_C_Y);
  Serial.println();
  Serial.printf("A: %d -- B: %d -- X: %d -- Y: %d\nDPAD UP: %d -- DPAD DOWN: %d, DPAD LEFT: %d, DPAD RIGHT: %d\nSTART: %d\nZ: %d LTRIG: %d RTRIG: %d\n\n\n", gcc_A, gcc_B, gcc_X, gcc_Y, gcc_DP_U, gcc_DP_D, gcc_DP_L, gcc_DP_R, gcc_START, gcc_Z, gcc_LTRIG, gcc_RTRIG);
  Serial.println();
  delay(200);
  // This third section constructs 8 bytes to send. Bytes are: ABXY/Start (0), DPAD/L/R/Z (1), Joystick X (2), Joystick Y (3), C Stick X (4), C Stick Y (5), LTRIG (analog) (6), RTRIG (analog) (7)
}

uint8_t convert(int joystickVal) { // This function converts the value of the Left / Right Joystick (12 bit signed integer) into an 8 bit unsigned integer for the GCC
  uint16_t adjustedVal = joystickVal + 2048;
  uint8_t newVal = (adjustedVal * 256) / 4095;
  if (newVal > 255) {
    newVal = 255;
  }
  return newVal;
}

void construct() { // This function constructs 7 bytes to send to the GC Data wire
  
}
