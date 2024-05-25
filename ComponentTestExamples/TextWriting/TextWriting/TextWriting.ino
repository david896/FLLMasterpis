#include <TFT_eSPI.h> // Include the TFT_eSPI library

TFT_eSPI tft; // Create an instance of the TFT_eSPI library

void setup() {
  tft.init(); // Initialize the TFT screen
  
  // Set the text color and size
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  
  // Print the message in the center of the screen
  // Calculate the center coordinates
  int centerX = tft.width() / 2;
  int centerY = tft.height() / 2;
  
  // Print the message at the center coordinates
  tft.setCursor(centerX - (strlen("Your Message") * 6), centerY - 8); // Adjust 6 according to your font
  tft.print("Your Message");
}

void loop() {
  // Your loop code here
}