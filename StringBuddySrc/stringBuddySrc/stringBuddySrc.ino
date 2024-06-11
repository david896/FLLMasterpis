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

bool singingsog;

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
  if (menuPositions[0] == 2) {

    tft.setTextSize(10);
    tft.setTextColor(TFT_CYAN);
  
    int centerX = tft.width() / 2;
    int centerY = tft.height() / 2;
    int bottomY = tft.height();

    tft.setCursor(centerX - (strlen(text) * 15), centerY - 20);  
    tft.print(text);
    tft.setTextSize(4);
    tft.setCursor(centerX - (strlen("Scale") * 12), bottomY - 50);  
    tft.print("Scale");
  }
  if (menuPositions[0] == 4) {

    tft.setTextSize(4);
    tft.setTextColor(TFT_PURPLE);
  
    int centerX = tft.width() / 2;
    int centerY = tft.height() / 2;
    int bottomY = tft.height();

    tft.setCursor(centerX - (strlen(text) * 12), centerY - 10);  
    tft.print(text);

    
  }
  if (menuPositions[0] == 1) {

    tft.setTextSize(10);
    tft.setTextColor(TFT_YELLOW);
  
    int centerX = tft.width() / 2;
    int centerY = tft.height() / 2;
    int bottomY = tft.height();

    tft.setCursor(centerX - (strlen(text) * 15), centerY - 20);  
    tft.print(text);
    tft.setTextSize(4);
    tft.setCursor(centerX - (strlen("Chord") * 12), bottomY - 50);  
    tft.print("Chord");
  }
  
  if (menuPositions[0] == 0) {
    tft.setTextColor(TFT_PINK);

    tft.setTextSize(2);

  
    int centerX = tft.width() / 2;
    int centerY = tft.height() / 2;

  
    tft.setCursor(centerX - (strlen(text) * 6), centerY - 8);  
    tft.print(text);
  }
  if (menuPositions[0] == 3) {
    tft.setTextColor(TFT_GREEN);

    tft.setTextSize(6);

  
    int centerX = tft.width() / 2;
    int centerY = tft.height() / 2;

  
    tft.setCursor(centerX - (strlen(text) * 18), centerY - 8);  
    tft.print(text);
  }
  
  
  
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

void songCountdown(){
  
  for (int i=3; i>0; i--) {
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(4);
    tft.setTextColor(TFT_PINK);
  
    int centerX = tft.width() / 2;
    int centerY = tft.height() / 2;
    
    CRGB color = CRGB(255, 150, 0);
    leds1[0] = color;
    leds1[1] = color;
    leds2[0] = color;
    leds2[1] = color;
    leds3[0] = color;
    leds3[1] = color;
    leds4[0] = color;
    leds4[1] = color;
    leds5[0] = color;
    leds5[1] = color;
    leds6[0] = color;
    leds6[1] = color;
    FastLED.show(); 
    tone(5, 1000);
    tft.setCursor(centerX - 12, centerY - 10);  
    tft.print(i);
    delay(50);
    noTone(5);
    delay(950);

    clearStrummingLeds();
    buzzerOn = false;

    
  }
  noTone(5);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_PINK);

    tft.setTextSize(3);

  
    int centerX = tft.width() / 2;
    int centerY = tft.height() / 2;

  
    tft.setCursor(centerX - (strlen("Now Playing:") * 9), centerY - 8);  
    tft.print("Now Playing:");
}

void detectHold() {
  if (digitalRead(encoderButton) == LOW) {
    
    isClicked = true;
    if (millis() - clickTime >= longPressDuration && !isLongClick) {  //long press

      isLongClick = true;
      if (pos > 0) pos--;
      mainMenuImage(menuPositions[pos]);
      singingsog = false;
      stopStrumming(); 
      clearLeds();

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
  if (menuPositions[0] == 2 && menuPositions[1] == 0) {
    Ascale();
  }
  if (menuPositions[0] == 0 && menuPositions[1] == 1) {
    songCountdown();
    debounce = millis();
    singingsog = true;
  }
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
  if (menuPositions[0] == 1 && menuPositions[1] == 2) {
    Bchord();
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
  if (singingsog) {
    KnockingOnHeavensDoor();
  }

  buzzerActivator();

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


      } else {
        menuPositions[pos]--;


      }
      mainMenuImage(menuPositions[pos]);
      encoderPos = 0;
    } else if (encoderPos > 1) {
      int length = optionsLengths[menuPositions[0]];
      if (menuPositions[pos] + 1 > length - 1) {
        menuPositions[pos] = 0;


      } else {
        menuPositions[pos]++;

 
      }
      mainMenuImage(menuPositions[pos]);
      encoderPos = 0;
    }
  }
  delay(10);
  
}
