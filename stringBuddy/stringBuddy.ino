#include <TFT_eSPI.h>
#include "bitmap.h"

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

#define UP_BUTTON 5
#define ENTER_BUTTON 16
#define DOWN_BUTTON 33

int counter = 1, menuCounter = 0;

void setup() {   
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(ENTER_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);

  Serial.begin(115200);
  Serial.print("TFT Test");

  tft.begin();
  tft.setSwapBytes(true);

  tft.fillScreen(TFT_BLACK);
  tft.pushImage(0, 0, 240, 240, Songs);
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
  


