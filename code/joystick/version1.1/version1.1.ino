//MASTER-JOYSTICK

//KNIHOVNY
#include <ezButton.h>             //knihovna pro ovladani prepinacu
#include <SoftwareSerial.h>       //knihovna pro bluetooth
#include <Adafruit_SSD1306.h>     //knihovna k displeji
#include <Adafruit_GFX.h>         //knihovna k displeji
#include <Wire.h>                 //knihovna k displeji


//second fourth of buttons
#define B8 4
#define B7 5
#define B6 6
#define B5 7
//first fourth of buttons
#define B4 8
#define B3 9
#define B2 10
#define B1 11
//switch that will controll switching modes of controlling
//#define SW1 12

ezButton toggleSwitch(12);        //Switch for toggling modes
SoftwareSerial mySerial(2, 3);    // RX, TX - nastaveni pinu modulu hc-05 (bluetooth)

int x1;           //Joystick X axis 1 inicialization
int y1;           //Joystick Y axis 1 inicialization
int val1;         //Joystick button 1 inicialization
int x2;           //Joystick X axis 2 inicialization
int y2;           //Joystick Y axis 2 inicialization
int val2;         //Joystick button 2 inicialization
int state = 0;    //promena ktera bude pouzivana na prijimani informaci z druheho arduina
int swState;      //promena ktera bude pouzivana na ukladani statusu spinace


void setup() {
  // put your setup code here, to run once:
  for (byte i=4; i<=12;i++) {           //setting all the pins to output
    pinMode(i,OUTPUT);
  }
  Serial.begin(38400);                  //Basic bluetooth communication
  toggleSwitch.setDebounceTime(50);     //set debounce time to 50 milliseconds
}

void loop() {
  // put your main code here, to run repeatedly:
  toggleSwitch.loop(); // MUST call the loop() function first
  //Bluetooth inicializace-------------------------------
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
  }
  //-----------------------------------------------------
  //Joystick X axis 1 inicialization
int val1;         //Joystick button 1 inicialization
int x2;           //Joystick X axis 2 inicialization
int y2;           //Joystick Y axis 2 inicialization
int val2;         //Joystick button 2 inicialization
  //Inicializace analog pinů-----------------------------
  x1 = analogRead(A1);      //Joystick X axis 1
  y1 = analogRead(A2);      //Joystick Y axis 1
  val1 = analogRead(A0);    //Joystick button 1
  x2 = analogRead(A4);      //Joystick X axis 2
  y2 = analogRead(A5);      //Joystick Y axis 2
  val2 = analogRead(A3);    //Joystick button 2
  //-----------------------------------------------------
  //Inicializace switche---------------------------------
  swState = toggleSwitch.getState();
  //-----------------------------------------------------
  //MODE 1 SW HIGH-----------------------------------------
  while(swState==HIGH){     //prvni poloha spinace, urcujici aktualni mod ovladani
    //Ovladani motoru--------------------------------------
    if(y1<=100){
      Serial.write('vpred');      //zasila do tanku pokyn k pohybu
    } else if (y1>=900){
        Serial.write('vzad');     //zasila do tanku pokyn k pohybu
    }else if (x1<=100){
        Serial.write('vlevo');    //zasila do tanku pokyn k pohybu
    }else if (x1>=900){
        Serial.write('vpravo');   //zasila do tanku pokyn k pohybu
    }else if (x1<=600 && x1>=400 && y1<=600 && y1>=400){
        Serial.write('stat');     //zasila do tanku pokyn k zastaveni
    }
    //-----------------------------------------------------
    //Ovladani serva---------------------------------------
    if(/*state joystickX*/x2<100&&(state>1)){
      Serial.write('left');       //zasila do tanku pokyn k pohybu serva doleva
    }
    if(/*state joystickX*/x2>900&&(state<179)){
      Serial.write('right');      //zasila do tanku pokyn k pohybu serva doprava
    }
    //-----------------------------------------------------
  }
  //-------------------------------------------------------
  while(swState==LOW){      //druha poloha spinace, urcujici aktualni mod ovladani
    //Ovladani motoru--------------------------------------
    if(y1<=100){
      Serial.write('A1');     //zasila do tanku pokyn k pohybu
    }
    if(y2<=100){
      Serial.write('B1');     //zasila do tanku pokyn k pohybu
    }
    if(y1>=900){
      Serial.write('A2');     //zasila do tanku pokyn k pohybu
    }
    if(y2>=900){
      Serial.write('B2');     //zasila do tanku pokyn k pohybu
    }
    if(y1<=600 && y1>=400){
      Serial.write('A0');     //zasila do tanku pokyn k zastaveni
    }
    if(y2<=600 && y2>=400){
      Serial.write('B0');     //zasila do tanku pokyn k zastaveni
    }
    //-----------------------------------------------------
    //Ovladani serva---------------------------------------
    if(B1 == HIGH &&(state>1)){
      Serial.write('left');     //zasila do tanku pokyn k pohybu serva doleva
    }
    if(B2 == HIGH &&(state<179)){
      Serial.write('right');    //zasila do tanku pokyn k pohybu serva doprava
    }
    //-----------------------------------------------------
  }
  //-------------------------------------------------------
}