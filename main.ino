#include <USBHost_t36.h>

// V+ from USB-C goes to 5V on board
// V- from USB-C goes to GND (any)

// 5V (Yellow) line for GCC is unused currently
// 3.3 (Blue) line for GCC is from the onboard 3.3V pin
// GND (Green/White) line for GCC goes to GND (any)

USBHost SPC; // Sets up SPC as the USB Host
USBHIDParser hid(SPC); // HID input decoded with USBHIDParser
JoystickController joysticks[1] = {JoystickController(SPC)}; // 1 joystick being used (testing)

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
  uint32_t buttons = joysticks[0].getButtons();
  Serial.printf("Joystick(0): buttons = %x", buttons);
  Serial.println();
  delay(200);
}
