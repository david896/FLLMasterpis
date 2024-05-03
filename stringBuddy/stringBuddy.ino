#include <TFT_eSPI.h>
#include "bitmap.h"

#define encoderPinA 34
#define encoderPinB 33

/*DISPLAY PINS
GND - GND
VCC - VCC
SCL - 18
SDA - 23
RES - 19
DC - 14
BLK - 3.3V
*/

TFT_eSPI tft = TFT_eSPI();

volatile int counter = 0;
volatile int lastState = LOW;
int menuCounter = 0;
String currentDir ="";

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

void mainMenuImage(int counter){
  switch(counter) {
    case 1:
      tft.fillScreen(TFT_BLACK);
      tft.pushImage(0, 0, 240, 240, Songs);
      break;
    case 2:
      tft.fillScreen(TFT_BLACK);
      tft.pushImage(0, 0, 240, 240, Chords);
      break;
    case 3:
      tft.fillScreen(TFT_BLACK);
      tft.pushImage(0, 0, 240, 240, Scales);
      break;
    case 4:
      tft.fillScreen(TFT_BLACK);
      tft.pushImage(0, 0, 240, 240, Games);
      break;
    case 5:
      tft.fillScreen(TFT_BLACK);
      tft.pushImage(0, 0, 240, 240, Settings);
      break;
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);

  Serial.print("TFT Test");

  tft.begin();
  tft.setSwapBytes(true);

  tft.fillScreen(TFT_BLACK);
  tft.pushImage(0, 0, 240, 240, Songs);

  menuCounter = 1;
  mainMenuImage(menuCounter);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateCounter, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), updateCounter, CHANGE);
}


void loop() {
  
  if (counter < 0) {
    Serial.println(counter);
    menuCounter++;
    mainMenuImage(menuCounter);
    counter = 0;
  } else if (counter > 0) {
    Serial.println(counter);
    menuCounter--;
    mainMenuImage(menuCounter);
    counter = 0;
  }

  delay(10);
}


