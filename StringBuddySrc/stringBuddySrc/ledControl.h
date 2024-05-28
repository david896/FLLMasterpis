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

#define finger1 CRGB(255, 162, 0);
#define finger2 CRGB(0, 255, 0);
#define finger3 CRGB(222, 1, 245);
#define finger4 CRGB(255, 0, 0);

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

void turnOnFret(CRGB leds[], int fret, CRGB color) {
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

void turnOnLed(int string, int fret, CRGB fingerColor) {
  if (fret > 12)
    return;

  switch (string) {
    case 1:
      turnOnFret(leds1, fret, fingerColor);
      break;
    case 2:
      turnOnFret(leds2, fret, fingerColor);
      break;
    case 3:
      turnOnFret(leds3, fret, fingerColor);
      break;
    case 4:
      turnOnFret(leds4, fret, fingerColor);
      break;
    case 5:
      turnOnFret(leds5, fret, fingerColor);
      break;
    case 6:
      turnOnFret(leds6, fret, fingerColor);
      break;
  }

  FastLED.show();
}

void strumming(int durataF) {
  int durataMain = durataF;
  if (durataF > 400) {
    durataF = 400;
  }
  tone(33, 1000);
  unsigned long Time = millis();
  verifyTone(Time);
  durataF /= 6;
  leds6[0] = S7;
  leds6[1] = S7;
  FastLED.show();
  delay(durataF);
  verifyTone(Time);
  leds6[0] = off;
  leds6[1] = off;
  leds5[0] = S7;
  leds5[1] = S7;
  FastLED.show();
  delay(durataF);
  verifyTone(Time);
  leds5[0] = off;
  leds5[1] = off;
  leds4[0] = S7;
  leds4[1] = S7;
  FastLED.show();
  delay(durataF);
  verifyTone(Time);
  leds4[0] = off;
  leds4[1] = off;
  leds3[0] = S7;
  leds3[1] = S7;
  FastLED.show();
  delay(durataF);
  verifyTone(Time);
  leds3[0] = off;
  leds3[1] = off;
  leds2[0] = S7;
  leds2[1] = S7;
  FastLED.show();
  delay(durataF);
  verifyTone(Time);
  leds2[0] = off;
  leds2[1] = off;
  leds1[0] = S7;
  leds1[1] = S7;
  FastLED.show();
  delay(durataF);
  verifyTone(Time);
  leds1[0] = off;
  leds1[1] = off;
  FastLED.show();
  noTone(33);
  if ((millis() - Time) < durataMain) {
    delay(millis() - Time);
  }
}
void reverseStrumming(int durataF) {
  int durataMain = durataF;
  if (durataF > 400) {
    durataF = 400;
  }
  tone(33, 650);
  unsigned long Time = millis();
  verifyTone(Time);
  durataF /= 6;
  leds1[0] = S7;
  leds1[1] = S7;
  FastLED.show();
  delay(durataF);
  verifyTone(Time);
  leds1[0] = off;
  leds1[1] = off;
  leds2[0] = S7;
  leds2[1] = S7;
  FastLED.show();
  delay(durataF);
  verifyTone(Time);
  leds2[0] = off;
  leds2[1] = off;
  leds3[0] = S7;
  leds3[1] = S7;
  FastLED.show();
  delay(durataF);
  verifyTone(Time);
  leds3[0] = off;
  leds3[1] = off;
  leds4[0] = S7;
  leds4[1] = S7;
  FastLED.show();
  delay(durataF);
  verifyTone(Time);
  leds4[0] = off;
  leds4[1] = off;
  leds5[0] = S7;
  leds5[1] = S7;
  FastLED.show();
  delay(durataF);
  verifyTone(Time);
  leds5[0] = off;
  leds5[1] = off;
  leds6[0] = S7;
  leds6[1] = S7;
  FastLED.show();
  delay(durataF);
  verifyTone(Time);
  leds6[0] = off;
  leds6[1] = off;
  FastLED.show();
  noTone(33);
  if ((millis() - Time) < durataMain) {
    delay(millis() - Time);
  }
}


void Amajor(int durata, int direction) {
  int x = 20;
  leds2[x] = dgt3;
  leds3[x] = dgt1;
  leds4[x] = dgt2;
  if (direction == 0) strumming(durata * speed);
  else if (direction == 1) reverseStrumming(durata * speed);
  else {
    leds1[0] = S7;
    leds1[1] = S7;
    leds2[0] = S7;
    leds2[1] = S7;
    leds3[0] = S7;
    leds3[1] = S7;
    leds4[0] = S7;
    leds4[1] = S7;
    leds5[0] = S7;
    leds5[1] = S7;
  }
  FastLED.show();
  FastLED.clear();
}

void Aminor(int durata, int direction) {

  int x = 20;
  leds2[x + 2] = dgt1;
  leds2[x + 1] = dgt1;
  leds3[x] = dgt3;
  leds3[x - 1] = dgt3;
  leds4[x] = dgt2;
  leds4[x - 1] = dgt2;
  if (direction == 0) strumming(durata * speed);
  else if (direction == 1) reverseStrumming(durata * speed);
  else if (direction == 2) {
    leds1[0] = S7;
    leds1[1] = S7;
    leds2[0] = S7;
    leds2[1] = S7;
    leds3[0] = S7;
    leds3[1] = S7;
    leds4[0] = S7;
    leds4[1] = S7;
    leds5[0] = S7;
    leds5[1] = S7;
  }
  FastLED.show();
  FastLED.clear();
}

void B7(int durata, int direction) {
  int x;
  leds2[x] = S2;
  leds3[x + 1] = S3;
  leds4[x] = S4;
  leds6[x] = S6;
  FastLED.show();
  if (direction == 0) strumming(durata * speed);
  else reverseStrumming(durata * speed);
  FastLED.clear();
}

void Cmajor(int durata, int direction) {
  int x = 20;
  leds2[x + 1] = dgt1;
  leds2[x + 2] = dgt1;
  leds4[x] = dgt2;
  leds4[x - 1] = dgt2;
  leds5[x - 2] = dgt3;
  leds5[x - 3] = dgt3;
  if (direction == 0) strumming(durata * speed);
  else if (direction == 1) reverseStrumming(durata * speed);
  else if (direction == 2) {
    leds1[0] = S7;
    leds1[1] = S7;
    leds2[0] = S7;
    leds2[1] = S7;
    leds3[0] = S7;
    leds3[1] = S7;
    leds4[0] = S7;
    leds4[1] = S7;
    leds5[0] = S7;
    leds5[1] = S7;
  }
  FastLED.show();

  FastLED.clear();
}

void Dmajor(int durata, int direction) {
  int x = 20;
  leds1[x] = dgt2;
  leds1[x - 1] = dgt2;
  leds2[x - 2] = dgt3;
  leds2[x - 3] = dgt3;
  leds3[x] = dgt1;
  leds3[x - 1] = dgt1;
  if (direction == 0) strumming(durata * speed);
  else if (direction == 1) reverseStrumming(durata * speed);
  else if (direction == 2) {
    leds1[0] = S7;
    leds1[1] = S7;
    leds2[0] = S7;
    leds2[1] = S7;
    leds3[0] = S7;
    leds3[1] = S7;
    leds4[0] = S7;
    leds4[1] = S7;
  }
  FastLED.show();
  FastLED.clear();
}
void Gmajor(int durata, int direction) {
  int x = 18;
  leds1[x] = dgt4;
  leds1[x - 1] = dgt4;
  leds2[x] = dgt3;
  leds2[x - 1] = dgt3;
  leds5[x + 2] = dgt1;
  leds5[x + 1] = dgt1;
  leds6[x] = dgt2;
  leds6[x - 1] = dgt2;
  if (direction == 0) strumming(durata * speed);
  else if (direction == 1) reverseStrumming(durata * speed);
  else if (direction == 2) {
    leds1[0] = S7;
    leds1[1] = S7;
    leds2[0] = S7;
    leds2[1] = S7;
    leds3[0] = S7;
    leds3[1] = S7;
    leds4[0] = S7;
    leds4[1] = S7;
    leds5[0] = S7;
    leds5[1] = S7;
    leds6[0] = S7;
    leds6[1] = S7;
  }
  FastLED.show();
  FastLED.clear();
}

void KnockingOnHavensDoor() {
  for (int i = 0; i < 2; i++) {
    Gmajor(1210, 0);
    Gmajor(600, 0);
    Gmajor(230, 0);
    Gmajor(230, 1);
    Dmajor(1210, 0);
    Dmajor(600, 0);
    Dmajor(230, 0);
    Dmajor(230, 1);
    Aminor(1210, 0);
    Aminor(600, 0);
    Aminor(230, 0);
    Aminor(230, 1);
    Aminor(1210, 0);
    Aminor(600, 0);
    Aminor(230, 0);
    Aminor(230, 1);
  }
}

void functionArray[][TOTAL_MENUS+1] ={
  NULL,
  NULL, NULL, KnockingOnHavensDoor, NULL, NULL,
  NULL, Amajor, Aminor, Cmajor, Dmajor, Gmajor,
  NULL, 
  NULL, 
  NULL,
}

