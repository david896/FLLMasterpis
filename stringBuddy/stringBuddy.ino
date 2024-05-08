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

int menuPos[4] = {0, 1, 1, 1};
unsigned int pos = 1;

const unsigned long longPressDuration = 1000;
unsigned long clickTime;
bool isClicked;
bool isLongClick;

volatile int encoderPos = 0;

volatile int lastState = LOW;
volatile int lastStateButton = LOW;

String currentDir = "";
unsigned long lastButtonPress = 0;

void updateCounter() {
  int currentStateA = digitalRead(encoderPinA);
  int currentStateB = digitalRead(encoderPinB);

  if (currentStateA != lastState && currentStateA == currentStateB) {
    encoderPos++;
  } else if (currentStateA != lastState && currentStateA != currentStateB) {
    encoderPos--;
  }

  lastState = currentStateA;
}


void menuImage(int pos, int counter){
  if(pos == 1){
    switch (counter) {
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
}

void subMenuImage(int secondaryCounter) {
}

void detectHold() {
  if (digitalRead(encoderButton) == LOW) {
    isClicked = true;
    if (millis() - clickTime >= longPressDuration && !isLongClick) {
      //long press
      isLongClick = true;
      if (pos != 1) pos--;  //going back a menu
    }
  }
  if (digitalRead(encoderButton) == HIGH) {
    if (isClicked && !isLongClick) {
      //short press
      Serial.println("short press");
      if (pos == 1) {         //in main menu
        pos++;                //enter secondary menu
      } else if (pos == 2) {  //already in secondary menu
        //interact with secondary menu
      }
    }
    clickTime = millis();
    isClicked = false;
    isLongClick = false;
  }
}

void runSelectedAction(volatile int counter1, volatile int counter2) {
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

  mainMenuImage(1);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateCounter, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), updateCounter, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(encoderButton), switchMenuOrInteract, CHANGE); // am schimbat aici la functia switchMenu simplu in caz ca o sa o folosim pe cealalta.  --David
}

void loop() {

  detectHold();

  if (encoderPos < -1) {
    if (menuPos[pos] + 1 > 5) {
      menuPos[pos] = 1;
    } else {
      menuPos[pos]++;
    }
    mainMenuImage(menuPos[pos]);
    encoderPos = 0;
  } else if (encoderPos > 1) {
    if (menuPos[pos] - 1 < 0) {
      menuPos[pos] = 5;
    } else {
      menuPos[pos]--;
    }
    mainMenuImage(menuPos[pos]);
    encoderPos = 0;
  }
  delay(10);
}
