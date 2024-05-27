#include <ezButton.h>
#include <FastLED.h>
#include <BluetoothSerial.h>

#define S1 CRGB(255, 0, 0);
#define S2 CRGB(0, 0, 255);
#define S3 CRGB(0, 255, 0);
#define S4 CRGB(178, 0, 46);
#define S5 CRGB(35, 124, 0);
#define S6 CRGB(100, 20, 255);
#define S7 CRGB(242, 92, 5);

#define dgt1 CRGB(255, 162, 0);
#define dgt2 CRGB(0, 255, 0);
#define dgt3 CRGB(222, 1, 245);
#define dgt4 CRGB(255, 0, 0);

#define LED_PIN1 17   // GPIO pin connected to the LED strip
#define NUM_LEDS1 25  // Number of LEDs in the LED strip

#define LED_PIN2 26   // GPIO pin connected to the LED strip
#define NUM_LEDS2 25  // Number of LEDs in the LED strip

#define LED_PIN3 27   // GPIO pin connected to the LED strip
#define NUM_LEDS3 25  // Number of LEDs in the LED strip

#define LED_PIN4 32  // GPIO pin connected to the LED strip
#define NUM_LEDS4 25

#define LED_PIN5 12  // GPIO pin connected to the LED strip
#define NUM_LEDS5 25

#define LED_PIN6 19
#define NUM_LEDS6 25

#define LED_TYPE WS2812
#define COLOR_ORDER GRB

#define BUTTON_PIN 34
#define BUTTON_POWER 23

CRGB leds1[NUM_LEDS1];
CRGB leds2[NUM_LEDS2];
CRGB leds3[NUM_LEDS3];
CRGB leds4[NUM_LEDS4];
CRGB leds5[NUM_LEDS5];
CRGB leds6[NUM_LEDS6];

#define off CRGB(0, 0, 0);
const int maxSongsLoaded = 10;

extern String songs[maxSongsLoaded]{};

float speed;

String selectedFileName = "";

BluetoothSerial SerialBT;

void rainbow() {
  // Fill the LED array with a rainbow pattern
  fill_rainbow(leds1, NUM_LEDS1, 0, 7);
  fill_rainbow(leds2, NUM_LEDS2, 0, 7);
  fill_rainbow(leds3, NUM_LEDS3, 0, 7);
  fill_rainbow(leds4, NUM_LEDS4, 0, 7);
  fill_rainbow(leds5, NUM_LEDS5, 0, 7);
  fill_rainbow(leds6, NUM_LEDS6, 0, 7);
  // Show the LEDs
  FastLED.show();
  // Delay for a short time to display the patter
}

void colorWipe(CRGB color) {
  // Fill the LED array with the specified color
  fill_solid(leds1, NUM_LEDS1, color);
  fill_solid(leds2, NUM_LEDS2, color);
  fill_solid(leds3, NUM_LEDS3, color);
  fill_solid(leds4, NUM_LEDS4, color);
  fill_solid(leds5, NUM_LEDS5, color);
  fill_solid(leds6, NUM_LEDS6, color);
  // Show the LEDs
  FastLED.show();
  // Delay for a short time to display the pattern
  delay(1000);
}

/*void theaterChase(CRGB color) {
  // Run a theater chase pattern with the specified color
  theaterChase(leds1, NUM_LEDS1, color, 50);
  theaterChase(leds2, NUM_LEDS2, color, 50);
  theaterChase(leds3, NUM_LEDS3, color, 50);
  theaterChase(leds4, NUM_LEDS4, color, 50);
  theaterChase(leds5, NUM_LEDS5, color, 50);
  theaterChase(leds6, NUM_LEDS6, color, 50);
}

void theaterChaseRainbow() {
  // Run a theater chase pattern with a rainbow effect
  theaterChaseRainbow(leds1, NUM_LEDS1, 50);
  theaterChaseRainbow(leds2, NUM_LEDS2, 50);
  theaterChaseRainbow(leds3, NUM_LEDS3, 50);
  theaterChaseRainbow(leds4, NUM_LEDS4, 50);
  theaterChaseRainbow(leds5, NUM_LEDS5, 50);
  theaterChaseRainbow(leds6, NUM_LEDS6, 50);
}*/

void colorFade() {
  // Gradually fade the LEDs through a range of colors
  for (int hue = 0; hue < 255; hue++) {
    fill_rainbow(leds1, NUM_LEDS1, hue, 7);
    fill_rainbow(leds2, NUM_LEDS2, hue, 7);
    fill_rainbow(leds3, NUM_LEDS3, hue, 7);
    fill_rainbow(leds4, NUM_LEDS4, hue, 7);
    fill_rainbow(leds5, NUM_LEDS5, hue, 7);
    fill_rainbow(leds6, NUM_LEDS6, hue, 7);
    FastLED.show();
    delay(20);
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
void verifyTone(unsigned long Time) {
  if (millis() - Time > 50) {
    noTone(33);
  }
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

void setup() {
  Serial.begin(115200);

  SerialBT.begin("String Buddy");  //Bluetooth device name
  Serial.print("The device started, now you can pair it with bluetooth!");


  String btaddress = SerialBT.getBtAddressString();
  Serial.print("ESP32 Adress: ");
  Serial.println(btaddress);

  // Initialize LED strip
  FastLED.addLeds<LED_TYPE, LED_PIN1, COLOR_ORDER>(leds1, NUM_LEDS1).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN2, COLOR_ORDER>(leds2, NUM_LEDS2).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN3, COLOR_ORDER>(leds3, NUM_LEDS3).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN4, COLOR_ORDER>(leds4, NUM_LEDS4).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN5, COLOR_ORDER>(leds5, NUM_LEDS5).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, LED_PIN6, COLOR_ORDER>(leds6, NUM_LEDS6).setCorrection(TypicalLEDStrip);

  FastLED.clear();
  FastLED.setBrightness(255);  // Set initial brightness


  FastLED.show();  // Send the updated pixel colors to the hardware
  pinMode(BUTTON_PIN, INPUT_PULLUP);

}

void clear_leds(){
  FastLED.clear(leds1);
  FastLED.clear(leds2);
  FastLED.clear(leds3);
  FastLED.clear(leds4);
  FastLED.clear(leds5);
  FastLED.clear(leds6);
}


String paired_add = "";
bool on = false;
void loop() {
  //check if button for power is pressed then prepare everything
  if(BUTTON_POWER == 0) {
    rainbow();
    delay(1500);
    clear_leds();
    on = true;
  }
  
  //if button is pressed it will stay in this while until the button is pressed again
  while(on){
    String songname = "";
    String speedconf = "";
    String loop = "";
    
    //logic if pressed to turn off
    if(BUTTON_POWER == 0) on = false;
    
    //if physical button pressed then clear registered mac address
    if(digitalRead(BUTTON_PIN) == 0){
      paired_add = "";
      rainbow();
      delay(1500);
      clear_leds();
    }

    //if not connected attempt reconnected using pre exesting mac address
    if (!SerialBT.connected() && paired_add != "") {
      SerialBT.connect(paired_add);
    }

    // IF connected to a device do:
    if (SerialBT.available()) {
      if(paired_add == "") paired_add = SerialBT.getBtAddressString();
      String receivedString = SerialBT.readStringUntil('\n');
      Serial.println("Received: " + receivedString);

      int firstDelimiterIndex = receivedString.indexOf('$');
      int secondDelimiterIndex = receivedString.indexOf('$', firstDelimiterIndex + 1);

      if (firstDelimiterIndex != -1 && secondDelimiterIndex != -1) {
        songname = receivedString.substring(0, firstDelimiterIndex);
        speedconf = receivedString.substring(firstDelimiterIndex + 1, secondDelimiterIndex);
        loop = receivedString.substring(secondDelimiterIndex + 1);

        Serial.println("Song Name: " + songname);
        Serial.println("Speed Configuration: " + speedconf);
        Serial.println("Loop: " + loop);
      }
      speedconf == "0.5" ? speed = 1.5f : (speedconf == "0.25" ? speed = 1.75f : speed = 1);

      //Songs:
      if (songname == "KnockingOnHavensDoor") KnockingOnHavensDoor();

      //Cords:
      if (songname == "C Major") Cmajor(800, 2);
      if (songname == "D Major") Dmajor(800, 2);
      if (songname == "G Major") Gmajor(800, 2);
      if (songname == "A Major") Amajor(800, 2);
      if(songname == "A Minor") Aminor(800, 2);

      //Scales:

      //Config Commads:
      if (songname == "ON") rainbow();
      if (songname == "OFF") clear_leds();
    }
  }
}