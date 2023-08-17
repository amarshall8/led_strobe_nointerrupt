#define FAN_INPUT 2
#define FAN_INPUT_MASK (1 << 2) // PD2
#define FAN_SPEED 10

bool tachPhase = false;
bool prevTachState = false;
bool interrupt_happened = false;
float spin_state1 = 0;
bool end_reached = false;
uint16_t delayTime = 250;

void setup() {
  // Serial.begin(115200);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  //pinMode(FAN_SPEED, OUTPUT);
  pinMode(FAN_INPUT, INPUT_PULLUP);
}

// set up Timer1 to count increments of time OR use micros/millis
// measure time between this rising edge & previous one - this is angular period (or 1/2 of it)
// you can then add predelays (i think) which are proportional to the period
void loop() {
  bool tachState = !!(PIND & FAN_INPUT_MASK);
  // rising edge
  if (tachState && !prevTachState) {
    if (tachPhase) {
      PORTD |= 0b11000000;  //Pin 9 = HIGH
      delayMicroseconds(delayTime);
      PORTD &= ~(0b11000000);  // Pin 9 = LOW
    }

    tachPhase = !tachPhase;
  }
  prevTachState = tachState;
}
