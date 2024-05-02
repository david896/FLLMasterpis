#include <TFT_eSPI.h>
#include "bitmap.h"

TFT_eSPI tft = TFT_eSPI();

volatile int counter = 1, menuCounter = 0;
const int encoderPinA = 2;
const int encoderPinB = 3;
volatile int lastState = LOW;

<<<<<<< Updated upstream
void setup() {   
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(ENTER_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
=======
void setup(void) { 
  Serial.begin(9600);
  
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
>>>>>>> Stashed changes

  Serial.begin(115200);
  Serial.print("TFT Test");

  tft.begin();
  tft.setSwapBytes(true);

  tft.fillScreen(TFT_BLACK);
  tft.pushImage(0, 0, 240, 240, Songs);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateCounter, CHANGE);

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
  Serial.println(counter);
  if(menuCounter == 0){
    if(digitalRead(UP_BUTTON) == 0){
      while(1){
        if(digitalRead(UP_BUTTON) == 1){
          if(counter + 1 > 5){ 
            counter = 1;
          }
          else counter++;

          break;
        }
        delay(10);
      }
      mainMenuImage(counter);
    }
    if(digitalRead(DOWN_BUTTON) == 0){
      while(1){
        if(digitalRead(DOWN_BUTTON) == 1){
          if(counter - 1 < 1){ 
            counter = 5;
          }
          else counter--;

          break;
        }
        delay(10);
      }
      mainMenuImage(counter);
    }
    if(digitalRead(ENTER_BUTTON) == 0){
      while(1){
        if(digitalRead(ENTER_BUTTON) == 1){
          menuCounter = counter;
          break;
        }
        delay(10);
      }
      tft.fillScreen(TFT_BLACK);
    }
  }
  else if(menuCounter == 1){
    tft.setCursor(0, 0, 1);
    tft.setTextColor(TFT_MAGENTA,TFT_BLACK);
    tft.setTextSize(3);
    tft.print("Songs");
  }
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


