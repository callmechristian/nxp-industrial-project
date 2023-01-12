//simple button masher esp32 ttgo
#include <TFT_eSPI.h> 
// for the user file in setting up the TFT_eSPI library
// #include <User_Setups/Setup25_TTGO_T_Display.h>
// v 2.4.50


#define BUTTON1PIN 35
#define BUTTON2PIN 0

TFT_eSPI tft = TFT_eSPI();

void IRAM_ATTR toggleButton1() {
  Serial.println("Button 1 Pressed!");
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(&Orbitron_Light_24);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("Display 1", 0, 0, 4);
}

void IRAM_ATTR toggleButton2() {
  Serial.println("Button 2 Pressed!");
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(&Orbitron_Light_24);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("Display 2", 0, 0, 4);
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON1PIN, INPUT);
  pinMode(BUTTON2PIN, INPUT);
  attachInterrupt(BUTTON1PIN, toggleButton1, FALLING);
  attachInterrupt(BUTTON2PIN, toggleButton2, FALLING);

  tft.init();
  tft.begin();
  tft.setRotation(3);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10);
  //tft.fillScreen(TFT_GREEN);
  //tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setCursor(0, 30);
  tft.setFreeFont(&Orbitron_Light_24);
}