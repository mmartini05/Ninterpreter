// V+ from USB-C goes to 5V on board
// V- from USB-C goes to GND (any)

// 5V (Yellow) line for GCC is unused currently
// 3.3 (Blue) line for GCC is from the onboard 3.3V pin
// GND (Green/White) line for GCC goes to GND (any)

int dPlus = 1; // D3
int dMin = 2; // D4
int gcData = 23; // A0
uint16_t usbData;

void setup() { // Initalization
  pinMode(dPlus, INPUT);
  pinMode(dMin, INPUT);
  pinMode(gcData, OUTPUT);
}

void loop() { // Loops continuously
  byte high = digitalRead(dPlus);
  byte low = digitalRead(dMin);
  printf("%b\n\r", differential(high, low)); // Testing to see if I can read a byte from USB-C Data+/Data- (and parse)
}

byte differential(byte high, byte low){ // This function takes the Data+ and Data- bytes from the USB-C and combines into a single Data byte for the GCC
  byte diff;
  int i = 0;
  while(i < (sizeof(high) - 1)){
    hBit = high[i];
    lBit = low[i];
    if(hBit > lBit){
      diff[i] = 1;
    }else{
      diff[i] = 0;
    }
    i++
  }
  return diff;
}
