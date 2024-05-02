

void setup() {
  Serial.begin(9600);
  
  
}

void loop() {
  // Afiseaza valoarea contorului la fiecare schimbare
  Serial.println(counter);
  delay(100);
}


