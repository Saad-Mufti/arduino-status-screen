//  This sketch uses font files created from the Noto family of fonts:
//  https://www.google.com/get/noto/
#include "NotoSansBold15.h"
#include "NotoSansBold36.h"

#include "cat.h"

// The font names are arrays references, thus must NOT be in quotes ""
#define AA_FONT_SMALL NotoSansBold15
#define AA_FONT_LARGE NotoSansBold36

// Screen res = 240(w) x 135(h)
#include <SPI.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include "NetworkCreds.h"

TFT_eSPI tft = TFT_eSPI();
int wpm = 0;
String wpm_msg = "WPM: ";

void setup() {
  Serial.begin(250000);
  tft.begin();
  // Change to 1 if device is plugged in on left side,
  // or 3 if on right side
  tft.setRotation(1);

  
  // Can connect to a router, and other devices can connect to this device
  // Use WIFI_AP for only acting as a wifi network,
  // or WIFI_STA for only connecting to a router
  WiFi.mode(WIFI_AP_STA);
  

  WiFi.begin(ssid, pass);
  WiFi.softAP("Hacking device", "Pwn3d");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
}

void loop() {
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_BLACK, TFT_WHITE); // Set the font colour AND the background colour for anti-aliasing
  
  tft.loadFont(AA_FONT_SMALL);    // Must load the font first
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.pushImage(70, 30, catWidth, catHeight, cat_bitmap);

  if(Serial.available() > 0) {
    wpm = Serial.readString().toInt();
  }
  tft.setCursor(110, 110);
  tft.print(wpm_msg);
  tft.print(wpm);

  tft.setCursor(0, 0);
  if(WiFi.status() == WL_CONNECTED) {
    tft.println(WiFi.localIP());
    tft.print("RSSI: ");
    tft.println(WiFi.RSSI());
  }
  else {
    tft.print("Not connected");
  }
  delay(500);
  
  tft.unloadFont();
}
