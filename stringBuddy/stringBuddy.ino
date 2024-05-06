#include <TFT_eSPI.h>
#include "bitmap.h"

#define encoderPinA 34
#define encoderPinB 33
#define encoderButton 35

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

bool switchedMenu = false; // basically cand apesi butonul pe encoder valoarea variabilei acestea se schimba in opusul ei   --David 

volatile int counter = 0;
volatile int secondaryCounter = 0;
int menuCounter = 0;

volatile int lastState = LOW;
volatile int lastStateButton = LOW;

String currentDir ="";
unsigned long lastButtonPress = 0;

void updateCounter() {
  int currentStateA = digitalRead(encoderPinA);
  int currentStateB = digitalRead(encoderPinB);
  
  if (switchedMenu == false){
      if (currentStateA != lastState && currentStateA == currentStateB) {
      counter++;
    } else if (currentStateA != lastState && currentStateA != currentStateB) {
      counter--;
    } 
  }
  else {
    if (currentStateA != lastState && currentStateA == currentStateB) {
      secondaryCounter++;
    } else if (currentStateA != lastState && currentStateA != currentStateB) {
      secondaryCounter--;
    } 
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
    case 6:
      tft.fillScreen(TFT_WHITE);
      break;
  }
}

void subMenuImage(int secondaryCounter){
  
}

void switchMenuOrInteract() { // functia asta este responsabila de actiunile ce le efectueaza butonul de pe encoder. --David
  if (switchedMenu == false) {
    switchedMenu = true; // face switch la meniul secundar. --David
  }
  else {
    runSelectedAction(counter, secondaryCounter);
  }
}

void runSelectedAction(volatile int counter1,volatile int counter2){

}

void setup() {
  Serial.begin(115200);

  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderButton, INPUT_PULLUP);

  Serial.print("TFT Test");

  tft.begin();
  tft.setSwapBytes(true);

  tft.fillScreen(TFT_BLACK);
  tft.pushImage(0, 0, 240, 240, Songs);

  menuCounter = 1;
  mainMenuImage(menuCounter);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateCounter, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), updateCounter, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderButton), switchMenu, CHANGE); // am schimbat aici la functia switchMenu simplu in caz ca o sa o folosim pe cealalta.  --David
}




void loop() {  

  if(switchedMenu == false) {
    if (counter < -1) {
    Serial.println(counter);
    if(menuCounter + 1 > 5){
      menuCounter = 0;
    }
    else{
      menuCounter++;
    }
    mainMenuImage(menuCounter);
    counter = 0;
    } 
    else if (counter > 1) {
      Serial.println(counter);
      if(menuCounter - 2 < 0){
      menuCounter = 5;
      }
    }
    else{
      menuCounter--;
    }
    mainMenuImage(menuCounter);
    counter = 0;
  }

  else{

  }
  delay(10);
}
  

  





