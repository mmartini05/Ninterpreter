typedef uint8_t byte; // I believe Arduino (#include <Arduino.h>) does this already - not sure though

// V+ from USB-C goes to 5V on board
// V- from USB-C goes to GND (any)

// 5V (Yellow) line for GCC is unused currently
// 3.3 (Blue) line for GCC is from the onboard 3.3V pin
// GND (Green/White) line for GCC goes to GND (any)

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
  pinMode(1, INPUT); // Data+ is connected to Pin 1 / Port D3
  pinMode(2, INPUT); // Data- is connected to Pin 2 / Port D4
  pinMode(31, OUTPUT); // Gamecube Data is connected to Pin 31 / Port PD1 - this is TX (UART)
}

void loop() { // Loops continuously
  byte high = digitalRead(1); // Reads 1 byte from Data+
  byte low = digitalRead(2); // Reads 1 byte from Data-
  Serial.print(differential(high, low), HEX); // Testing to see if I can read a byte from USB-C Data+/Data- (and parse)
}

byte differential(byte high, byte low) { // This function takes the Data+ and Data- bytes from the USB-C and combines into a single Data byte for the GCC
  byte diff = 0; // Initializes diff (differential byte) to zero
  bool hBit;
  bool lBit;

  for (int i = 0; i < 8; i++) { // Loop through all 8 bits of the byte
    hBit = (high >> i) & 0x01; // Extract the ith bit of high
    lBit = (low >> i) & 0x01;  // Extract the ith bit of low
    
    if (hBit > lBit) {
      diff |= (1 << i); // Set the ith bit of diff to 1
    }
  }

  return diff;
}
