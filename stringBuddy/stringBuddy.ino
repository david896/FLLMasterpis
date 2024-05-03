#include <TFT_eSPI.h>
#include "bitmap.h"

#define CLK 34
#define DT 35

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

int counter = 0;
int currentStateCLK;
int lastStateCLK;
int menuCounter = 0;
String currentDir ="";

void setup() {
    pinMode(CLK, INPUT);
    pinMode(DT, INPUT);

    Serial.begin(115200);
    delay(1000); // Add a delay after initializing serial

    Serial.print("TFT Test");

    lastStateCLK = digitalRead(CLK);

    tft.begin();
    tft.setSwapBytes(true);

    tft.fillScreen(TFT_BLACK);
    tft.pushImage(0, 0, 240, 240, Songs);

    menuCounter = 1;
    mainMenuImage(menuCounter);

    attachInterrupt(digitalPinToInterrupt(CLK), updateEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(DT), updateEncoder, CHANGE);
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

void loop() {
  
  if (counter < 0) {
    menuCounter++;
    mainMenuImage(menuCounter);
  } else if (counter > 0) {
    menuCounter++;
    mainMenuImage(menuCounter);
  }

  counter = 0;

  delay(100);
}

void updateEncoder() {
  currentStateCLK = digitalRead(CLK);

  if (currentStateCLK != lastStateCLK) {
    if (currentStateCLK == 1) {
        if (digitalRead(DT) != currentStateCLK) {
          counter--;
          currentDir ="CCW";
        } else {
          counter++;
          currentDir ="CW";
        }

        Serial.print("Direction: ");
        Serial.print(currentDir);
        Serial.print(" | Counter: ");
        Serial.println(counter);
      }
    }
    
  lastStateCLK = currentStateCLK;
}
  


