#include <SoftwareSerial.h>       //knihovna pro bluetooth

#define B 5

SoftwareSerial mySerial(9, 10);    // RX, TX - nastaveni pinu modulu hc-05 (bluetooth)

int state;

void setup() {
  pinMode(5,OUTPUT);
  Serial.begin(38400);                  //Basic bluetooth communication
}

void loop() {
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
  }
  int buttonState= digitalRead(B);
  Serial.write(buttonState);

  //-------------------------------------------------------
}