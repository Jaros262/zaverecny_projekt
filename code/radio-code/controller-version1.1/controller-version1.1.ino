//MASTER-JOYSTICK

//KNIHOVNY
#include <ezButton.h>             //knihovna pro ovladani prepinacu
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


//second fourth of buttons
#define B8 2
#define B7 3
#define B6 4
#define B5 5
//first fourth of buttons
#define B4 6
#define B3 7
#define B2 8
#define B1 9
//radio
#define CSN_GPIO    1
#define CE_GPIO     2
//switch that will controll switching modes of controlling
//#define SW1 12

//ezButton toggleSwitch(10);        //Switch for toggling modes
RF24 radio(CE_GPIO, CSN_GPIO);
//SoftwareSerial mySerial(2, 3);    // RX, TX - nastaveni pinu modulu hc-05 (bluetooth)

const byte Address[6] = "00001";
unsigned char Tx_command = 0;

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
  Serial.begin(9600);
  for (byte i=4; i<=12;i++) {           //setting all the pins to output
    pinMode(i,OUTPUT);
  }
  
  radio.begin();
  radio.openWritingPipe(Address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  radio.write(&Tx_command, sizeof(Tx_command));
  //toggleSwitch.setDebounceTime(50);     //set debounce time to 50 milliseconds
}

void loop() {
  // put your main code here, to run repeatedly:
  //toggleSwitch.loop(); // MUST call the loop() function first
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
  x1 = analogRead(A7);      //Joystick X axis 1
  y1 = analogRead(A6);      //Joystick Y axis 1
  //val1 = analogRead(A0);    //Joystick button 1
  x2 = analogRead(A5);      //Joystick X axis 2
  y2 = analogRead(A4);      //Joystick Y axis 2
  //val2 = analogRead(A3);    //Joystick button 2
  //-----------------------------------------------------
  //Inicializace switche---------------------------------
  //swState = toggleSwitch.getState();
  //-----------------------------------------------------
  //MODE 1 SW HIGH-----------------------------------------
  //while(swState==HIGH){     //prvni poloha spinace, urcujici aktualni mod ovladani
    //Ovladani motoru--------------------------------------
    if(y1<=100){
      Tx_command = 0;      //zasila do tanku pokyn k pohybu
    } else if (y1>=900){
        Tx_command = 1;     //zasila do tanku pokyn k pohybu
    }else if (x1<=100){
        Tx_command = 2;    //zasila do tanku pokyn k pohybu
    }else if (x1>=900){
        Tx_command = 3;   //zasila do tanku pokyn k pohybu
    }
    //-----------------------------------------------------
    //Ovladani serva---------------------------------------
    if(x2<100){
      Tx_command = 8;       //zasila do tanku pokyn k pohybu serva doleva
    }
    if(x2>900){
      Tx_command = 9;      //zasila do tanku pokyn k pohybu serva doprava
    }
    //-----------------------------------------------------
    radio.write(&Tx_command, 1);
    delay(150);
  //}
  //-------------------------------------------------------
  //while(swState==LOW){      //druha poloha spinace, urcujici aktualni mod ovladani
    //Ovladani motoru--------------------------------------
    /*if(y1<=100){
      Tx_command = 4;     //zasila do tanku pokyn k pohybu
    }
    if(y2<=100){
      Tx_command = 5;     //zasila do tanku pokyn k pohybu
    }
    if(y1>=900){
      Tx_command = 6;     //zasila do tanku pokyn k pohybu
    }
    if(y2>=900){
      Tx_command = 7;     //zasila do tanku pokyn k pohybu
    }
    //-----------------------------------------------------
    //Ovladani serva---------------------------------------
    if(B1 == HIGH){
      Tx_command = 8;      //zasila do tanku pokyn k pohybu serva doleva
    }
    if(B2 == HIGH){
      Tx_command = 9;    //zasila do tanku pokyn k pohybu serva doprava
    }
    //-----------------------------------------------------
    radio.write(&Tx_command, 1);
    delay(150);*/
  //}
  //-------------------------------------------------------
}