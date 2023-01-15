#include <SoftwareSerial.h>


SoftwareSerial Bluetooth(3, 4);

void setup() {
  Serial.begin(38400);
  Serial.println("HC-05 Commands");
  Bluetooth.begin(38400);
}

void loop() {
  if(Bluetooth.available())
    Serial.write(Bluetooth.read());
  
  if(Serial.available())
    Bluetooth.write(Serial.read());

}
