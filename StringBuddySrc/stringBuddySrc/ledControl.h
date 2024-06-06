#include <FastLED.h>

#define LED_PIN1 27
#define NUM_LEDS1 25

#define LED_PIN2 25
#define NUM_LEDS2 25

#define LED_PIN3 32
#define NUM_LEDS3 25

#define LED_PIN4 12
#define NUM_LEDS4 25

#define LED_PIN5 4
#define NUM_LEDS5 25

#define LED_PIN6 0
#define NUM_LEDS6 25

#define LED_TYPE WS2812
#define COLOR_ORDER GRB

#define TOTAL_MENUS 5

CRGB leds1[NUM_LEDS1];
CRGB leds2[NUM_LEDS2];
CRGB leds3[NUM_LEDS3];
CRGB leds4[NUM_LEDS4];
CRGB leds5[NUM_LEDS5];
CRGB leds6[NUM_LEDS6];

void ledInit() {
  FastLED.addLeds<LED_TYPE, LED_PIN1, COLOR_ORDER>(leds1, NUM_LEDS1).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN2, COLOR_ORDER>(leds2, NUM_LEDS2).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN3, COLOR_ORDER>(leds3, NUM_LEDS3).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN4, COLOR_ORDER>(leds4, NUM_LEDS4).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN5, COLOR_ORDER>(leds5, NUM_LEDS5).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN6, COLOR_ORDER>(leds6, NUM_LEDS6).setCorrection(TypicalLEDStrip);

  FastLED.clear();
  FastLED.setBrightness(255);

  FastLED.show();
}

void clearLeds() {
  FastLED.clear();
}

void turnOnLedsForFret(CRGB leds[], int fret, CRGB color) {
  if (fret <= 3) {
    leds[fret + 3] = color;
  } else if (fret == 4) {
    leds[7] = color;
    leds[8] = color;
  } else if (fret == 5) {
    leds[9] = color;
  } else if (fret == 6) {
    leds[10] = color;
    leds[11] = color;
  } else if (fret == 7) {
    leds[12] = color;
  } else {
    leds[22 - (12 - fret) * 2] = color;
    leds[21 - (12 - fret) * 2] = color;
  }
}

void turnOnFret(int string, int fret, int finger) {
  if (fret > 12)
    return;

  CRGB fingerColor = CRGB(0, 0, 0);

  if (finger == 1) {
    fingerColor = CRGB(255, 162, 0);  //finger1 color
  } else if (finger == 2) {
    fingerColor = CRGB(0, 255, 0);  //finger2 color
  } else if (finger == 3) {
    fingerColor = CRGB(222, 1, 245);  //finger3 color
  } else if (finger == 4) {
    fingerColor = CRGB(255, 0, 0);  //finger4 color
  }

  switch (string) {
    case 1:
      turnOnLedsForFret(leds1, fret, fingerColor);
      break;
    case 2:
      turnOnLedsForFret(leds2, fret, fingerColor);
      break;
    case 3:
      turnOnLedsForFret(leds3, fret, fingerColor);
      break;
    case 4:
      turnOnLedsForFret(leds4, fret, fingerColor);
      break;
    case 5:
      turnOnLedsForFret(leds5, fret, fingerColor);
      break;
    case 6:
      turnOnLedsForFret(leds6, fret, fingerColor);
      break;
  }

  FastLED.show();
}

bool strumming = false;
int strumIndex = 0;
unsigned long strumDuration;
unsigned long lastStrumLed;
bool strumUp;
bool loopStrumming;
int globalCount = 0;
int globalCount2 = 3;

void clearStrummingLeds() {
  CRGB color = CRGB(0, 0, 0);
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
}

void stopStrumming() {
  strumming = false; 

}



void turnOnLedsForStrum(int string) {
  CRGB color = CRGB(255, 255, 0);  //strum color
  if (string == 1) {
    leds1[0] = color;
    leds1[1] = color;
  } else if (string == 2) {
    leds2[0] = color;
    leds2[1] = color;
  } else if (string == 3) {
    leds3[0] = color;
    leds3[1] = color;
  } else if (string == 4) {
    leds4[0] = color;
    leds4[1] = color;
  } else if (string == 5) {
    leds5[0] = color;
    leds5[1] = color;
  } else if (string == 6) {
    leds6[0] = color;
    leds6[1] = color;
  }

  FastLED.show();
}

 void strum(int strumDuration1, bool up, bool loop, int count, int stringCount = 6) {// stringCount ----- how many strings are being played per strum
  globalCount2 = count * stringCount;
  if (up) {
    strumUp = true;
    strumIndex = 0;
  } else{
    strumUp = false;
    strumIndex = 7;
  }
  loopStrumming = loop;
  strumming = true;
  strumDuration = strumDuration1;
}

void strumLoop() {
  if (strumming) {
    if (strumUp) {
      if (millis() - lastStrumLed > (strumDuration / 6)) {
        globalCount++;
        clearStrummingLeds();
        turnOnLedsForStrum(++strumIndex);
        if (strumIndex == 6) {
          if (loopStrumming) {
            strumUp = false;
          } else {
            strumIndex = 0;
          }
        }
        lastStrumLed = millis();
      }
    } else {
      if (millis() - lastStrumLed > (strumDuration / 6)) {
        globalCount++;
        clearStrummingLeds();
        turnOnLedsForStrum(--strumIndex);
        if (strumIndex == 1) {
          if (loopStrumming) {
            strumUp = true;
          } else {
            strumIndex = 7;
          }
        }
        lastStrumLed = millis();
      }
    }
  } else {
    clearStrummingLeds();
    Serial.print("clearing leds");
  }

  if(globalCount == globalCount2){
    globalCount = 0;
    clearStrummingLeds();
    strumming = false;
   
  }
}





void Cchord() {
  clearLeds();
  turnOnFret(2,12,1);
  turnOnFret(4,11,2);
  turnOnFret(5,10,3);
}

void Dchord() {
  clearLeds();
  turnOnFret(1,11,2);
  turnOnFret(2,10,3);
  turnOnFret(3,11,1);
}

void Achord() {
  clearLeds();
  turnOnFret(2,11,3);
  turnOnFret(3,11,2);
  turnOnFret(4,11,1);
}

void Gchord() {
  clearLeds();
  turnOnFret(1,10,3);
  turnOnFret(5,11,2);
  turnOnFret(6,10,1);
}

void Echord() {
  clearLeds();
  turnOnFret(4,11,2);
  turnOnFret(5,11,1);
}

void Fchord() {
  clearLeds();
  turnOnFret(2,12,1);
  turnOnFret(3,11,2);
  turnOnFret(4,10,3);
  turnOnFret(5,10,4);
}
