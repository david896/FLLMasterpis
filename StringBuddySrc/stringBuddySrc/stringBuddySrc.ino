#include <TFT_eSPI.h>
#include "bitmap.h"
#include "ledControl.h"



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

int menuPos[3] = {0, 1, 1}; // first element is not being used
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

void writeInTheMiddle(const char* text) {
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  
  // Print the message in the center of the screen
  // Calculate the center coordinates
  int centerX = tft.width() / 2;
  int centerY = tft.height() / 2;
  
  // Print the message at the center coordinates
  tft.setCursor(centerX - (strlen(text) * 6), centerY - 8); // Adjust 6 according to your font
  tft.print(text);
}

void mainMenuImage(int counter) {
  Serial.print(menuPos[pos]);
  if(pos == 1){
    tft.fillScreen(TFT_BLACK);
    tft.pushImage(0, 0, 240, 240, imageDataBase[0][counter]);
  } else{
    tft.fillScreen(TFT_BLACK);
    writeInTheMiddle(menuOptions[menuPos[1]][menuPos[2]]);
  }
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
      //short pressx
      if (pos == 1) {    
        Serial.println("In sec Menu");    //in main menu
        pos++;                //enter secondary menu
      } else if (pos == 2) {  //already in secondary menu
        runSelectedAction(menuPos[1], menuPos[2]); //interact with secondary menu
      }
    }
    clickTime = millis();
    isClicked = false;
    isLongClick = false;
  }
}

void runSelectedAction(int counter1, int counter2) {
}

void setup() {
  Serial.begin(115200);

  ledInit();

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
    if (menuPos[pos] - 1 == 0) {
      menuPos[pos] = 5;
    } else {
      menuPos[pos]--;
    }
    mainMenuImage(menuPos[pos]);
    encoderPos = 0;
  }

  delay(10);
}
