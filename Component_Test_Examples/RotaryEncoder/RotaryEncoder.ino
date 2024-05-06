
const int encoderPinA = 34;
const int encoderPinB = 33;
volatile int counter = 0;
volatile int lastState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateCounter, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), updateCounter, CHANGE);

}

void loop() {
  // Afiseaza valoarea contorului la fiecare schimbare
  Serial.println(counter);
  delay(100);
}


