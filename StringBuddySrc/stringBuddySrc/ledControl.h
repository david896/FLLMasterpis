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


