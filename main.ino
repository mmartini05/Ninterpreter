// V+ from USB-C goes to 5V on board
// V- from USB-C goes to GND (any)

// 5V (Yellow) line for GCC is unused currently
// 3.3 (Blue) line for GCC is from the onboard 3.3V pin
// GND (Green/White) line for GCC goes to GND (any)

int dPlus = 1; // D3
int dMin = 2; // D4
int gcData = 23; // A0
uint16_t usbData;

void setup() {
  // put your setup code here, to run once:
  pinMode(dPlus, INPUT);
  pinMode(dMin, INPUT);
  pinMode(gcData, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  byte high = digitalRead(dPlus);
  byte low = digitalRead(dMin);
  usbData = (high >> 8) + low;
}