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

int menuPositions[2] = { 0, 0 };
int pos = 0;

const unsigned long longPressDuration = 1000;
unsigned long clickTime;
bool isClicked;
bool isLongClick;

int encoderPos = 0;

volatile int lastState = LOW;
volatile int lastStateButton = LOW;

void updateCounter() {
  int currentStateA = digitalRead(encoderPinA);
  int currentStateB = digitalRead(encoderPinB);

  if (currentStateA != lastState && currentStateA == currentStateB) {  // clockwise
    encoderPos--;
  } else if (currentStateA != lastState && currentStateA != currentStateB) {  // anticlockwise
    encoderPos++;
  }
  lastState = currentStateA;
}

void writeInTheMiddle(const char* text) {
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(3);

  // Print the message in the center of the screen
  // Calculate the center coordinates
  int centerX = tft.width() / 2;
  int centerY = tft.height() / 2;

  // Print the message at the center coordinates
  tft.setCursor(centerX - (strlen(text) * 6), centerY - 8);  // Adjust 6 according to your font
  tft.print(text);
}

void mainMenuImage(int counter) {
  if (pos == 0) {
    tft.fillScreen(TFT_BLACK);
    tft.pushImage(0, 0, 240, 240, imageDataBase[counter]);
  } else if (pos == 1) {
    tft.fillScreen(TFT_BLACK);
    writeInTheMiddle(menuOptions[menuPositions[0]][menuPositions[1]]);
  }
}

void detectHold() {
  if (digitalRead(encoderButton) == LOW) {
    clearLeds();
    isClicked = true;
    if (millis() - clickTime >= longPressDuration && !isLongClick) {  //long press

      isLongClick = true;
      if (pos > 0) pos--;
      mainMenuImage(menuPositions[pos]);

      stopStrumming(); 
      
    }
  }
  if (digitalRead(encoderButton) == HIGH) {
    if (isClicked && !isLongClick) {  //short press
      if (pos == 0) {
        pos++;
        mainMenuImage(menuPositions[pos]);
        menuPositions[1] = 0;
      } else if (pos > 0) {
        submenuAction();
      }
    }
    clickTime = millis();
    isClicked = false;
    isLongClick = false;
  }
}

void submenuAction() {
  Serial.print(menuPositions[1]);
  if (menuPositions[0] == 1 && menuPositions[1] == 3) {
    Cchord();
  }
  if (menuPositions[0] == 1 && menuPositions[1] == 5) {
    Dchord();
  }
  if (menuPositions[0] == 1 && menuPositions[1] == 0) {
    Achord();
  }
  if (menuPositions[0] == 1 && menuPositions[1] == 10) {
    Gchord();
  }
  if (menuPositions[0] == 1 && menuPositions[1] == 7) {
    Echord();
  }
  if (menuPositions[0] == 1 && menuPositions[1] == 8) {
    Fchord();
  }
}

void setup() {
  Serial.begin(115200);

  ledInit();

  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderButton, INPUT_PULLUP);

  tft.begin();
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateCounter, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), updateCounter, CHANGE);

  mainMenuImage(menuPositions[pos]);


  
}

void loop() {
  strumLoop();

  detectHold();

  if (pos == 0)
  {
    clearLeds();
    if (encoderPos < -1) {
      int length = sizeof(imageDataBase) / sizeof(imageDataBase[0]);
      if (menuPositions[pos] - 1 < 0) {
        menuPositions[pos] = length - 1;
      } else {
        menuPositions[pos]--;
      }
      mainMenuImage(menuPositions[pos]);
      encoderPos = 0;
    } else if (encoderPos > 1) {
      int length = sizeof(imageDataBase) / sizeof(imageDataBase[0]);
      if (menuPositions[pos] + 1 > length - 1) {
        menuPositions[pos] = 0;
      } else {
        menuPositions[pos]++;
      }
      mainMenuImage(menuPositions[pos]);
      encoderPos = 0;
    }
  }
  else if (pos == 1)
  {
    if (encoderPos < -1) {
      int length = optionsLengths[menuPositions[0]];
      if (menuPositions[pos] - 1 < 0) {
        menuPositions[pos] = length - 1;
        clearLeds();

      } else {
        menuPositions[pos]--;
        clearLeds();

      }
      mainMenuImage(menuPositions[pos]);
      encoderPos = 0;
    } else if (encoderPos > 1) {
      int length = optionsLengths[menuPositions[0]];
      if (menuPositions[pos] + 1 > length - 1) {
        menuPositions[pos] = 0;
        clearLeds();

      } else {
        menuPositions[pos]++;
        clearLeds();
 
      }
      mainMenuImage(menuPositions[pos]);
      encoderPos = 0;
    }
  }
  delay(10);
  
}
