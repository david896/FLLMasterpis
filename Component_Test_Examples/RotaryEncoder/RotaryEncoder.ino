const int encoderPinA = 2;
const int encoderPinB = 3;
volatile int counter = 0;
volatile int lastState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateCounter, CHANGE);
}

void loop() {
  // Afiseaza valoarea contorului la fiecare schimbare
  Serial.println(counter);
  delay(100);
}

void updateCounter() {
  int currentStateA = digitalRead(encoderPinA);
  int currentStateB = digitalRead(encoderPinB);
  
  if (currentStateA != lastState && currentStateA == currentStateB) {
    counter++;
  } else if (currentStateA != lastState && currentStateA != currentStateB) {
    counter--;
  }

  lastState = currentStateA;
}
