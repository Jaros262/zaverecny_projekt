#include <Wire.h>
#include <Adafruit_SSD1306_STM32.h>

#define Reset 4

Adafruit_SSD1306 display(Reset);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(1);
  display.print("Hudy zije");
  display.setTextSize(2);
  display.setCursor(4,50);
  display.print(millis()/1000);
  display.display();
  delay(1000);
}
