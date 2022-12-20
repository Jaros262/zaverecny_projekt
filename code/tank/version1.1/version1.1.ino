//SLAVE-REMOTE CAR (TANK)

//KNIHOVNY
#include <Servo.h>            //Libary for servo controll
#include <SoftwareSerial.h>   //knihovna pro bluetooth

//pins setup
#define ENA 11    //digital pin pro rychlost motoru A
#define IN1 10    //prvni digital pin pro motor A
#define IN2 9     //druhy digital pin pro motor A
#define IN3 8     //druhy digital pin pro motor B
#define IN4 7     //prvni digital pin pro motor B
#define ENB 6     //digital pin pro rychlost motoru B
#define SER 5     //digital pin pro servo

int value = 100;  //vychozi pozice pro servo
int state = 0;    //promena ktera bude pouzivana na prijimani informaci z druheho arduina
int speedA;       //promena uchovavajici rychlost motoru A
int speedB;       //promena uchovavajici rychlost motoru B

Servo myservo;                      // create servo object to control a servo
                                    // a maximum of eight servo objects can be created
SoftwareSerial mySerial(3, 4);      // RX, TX - nastaveni pinu modulu hc-05 (bluetooth)

//Stara verze ovladani motorů
/*
void vpred(){
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
}
void vzad(){
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
}
void vlevo(){
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
}
void vpravo(){
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
}
void stat(){
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
}*/

//Funkce pro ovladani motoru A a B
void vpredMotorA(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void vzadMotorA(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void statMotorA(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void vpredMotorB(){
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, LOW);
}

void vzadMotorB(){
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, HIGH);
}

void statMotorB(){
  digitalWrite(IN4, LOW);
  digitalWrite(IN3, LOW);
}
//--------------------------------

//Funkce pro ovladani serva doleva a doprava
void servoLeft(){
  myservo.write(value);   //udavani pozici servu
  value = value-5;        //ubirani pozice serva
}

void servoRight(){
  myservo.write(value);   //udavani pozici servu
  value = value+5;        //pridavani pozice serva
}
//------------------------------------------

void setup() {                      // put your setup code here, to run once:
  for (byte i=5; i<=11;i++) {       //seting up all digital pins to output
    pinMode(i,OUTPUT);
  }
  Serial.begin(38400);              // Default communication rate of the Bluetooth module
  myservo.attach(5);                //Nastaveni pinu serva na knihovnu <Servo.h>
}

void loop() {
  if(Serial.available() > 0){       // Checks whether data is comming from the serial port
    state = Serial.read();          // Reads the data from the serial port
  }
  //SPEED SETUP
  analogWrite(ENA,speedA);          //speed of motor A
  analogWrite(ENB,speedB);          //speed of motor B
  //MODE 1 SW==HIGH
    //Ovladani serva---------------------------------------
    if(/*state joystickX<100&&(((state joystickX+520)/10)>1*/state == 'left'){
      servoLeft();            //vyvolani funkce pohybu serva doleva
      Serial.write(value);    //sending curent position of servo to controller

    }
    if(/*state joystickX>900&&(((state joystickX+520)/10)<199*/state == 'right'){
      servoRight();           //vyvolani funkce pohybu serva doprava
      Serial.write(value);    //sending curent position of servo to controller
    }
    //-----------------------------------------------------

    //Ovladani motoru--------------------------------------
    if(state == 'vpred'){
      while(speedA<=245&&speedB<=245){    //funkce pridavajici rychlost dokud nedojde do maximalni hodnoty
        speedA = speedA + 10;             //adding speed to motor
        speedB = speedB + 10;             //adding speed to motor
      }
      vpredMotorA();                       //vyvolani funkcí k pohybu motoru
      vpredMotorB();
      
    } else if (state == 'vzad'){
        while(speedA<=245&&speedB<=245){  //funkce pridavajici rychlost dokud nedojde do maximalni hodnoty
          speedA = speedA + 10;           //adding speed to motor
          speedB = speedB + 10;           //adding speed to motor
        }
        vzadMotorA();                      //vyvolani funkcí k pohybu motoru
        vzadMotorB();
        
    }else if (state == 'vlevo'){
        while(speedA<=245&&speedB<=245){  //funkce pridavajici rychlost dokud nedojde do maximalni hodnoty
          speedA = speedA + 10;           //adding speed to motor
          speedB = speedB + 10;           //adding speed to motor
        }
        vzadMotorA();                      //vyvolani funkcí k pohybu motoru
        vpredMotorB();
        
    }else if (state == 'vpravo'){
        while(speedA<=245&&speedB<=245){  //funkce pridavajici rychlost dokud nedojde do maximalni hodnoty
          speedA = speedA + 10;           //adding speed to motor
          speedB = speedB + 10;           //adding speed to motor
        }
        vpredMotorA();                     //vyvolani funkcí k pohybu motoru
        vzadMotorB();
        
    }else if (state == 'stat'){
      while(speedA>=20&&speedB>=20){      //funkce ubírající rychlost dokud nedojde do minimální hodnoty
        speedA = speedA - 20;             //reducing speed of motor
        speedB = speedB - 20;             //reducing speed of motor
      }
        
        statMotorA();                      //vyvolani funkcí k pohybu motoru
        statMotorB();
        
    }
    //-----------------------------------------------------
  //_____________________________________________________

  //MODE 2 SW==LOW  
    //Ovladani serva---------------------------------------
    if(state == 'left'){
      servoLeft();          //vyvolani funkce pohybu serva doleva
      Serial.write(value);  //sending curent position of servo to controller
    }
    if(state == 'right'){
      servoRight();         //vyvolani funkce pohybu serva doprava
      Serial.write(value);  //sending curent position of servo to controller
    }
    //-----------------------------------------------------

    //Ovladani motoru--------------------------------------
    if(state == 'A1'){
      while(speedA<=245){       //funkce pridavajici rychlost dokud nedojde do maximalni hodnoty
        speedA = speedA + 10;   //adding speed to motor
      }
      vpredMotorA();
    } else if (state == 'A2'){
        while(speedA<=245){     //funkce pridavajici rychlost dokud nedojde do maximalni hodnoty
          speedA = speedA + 10; //adding speed to motor
        }
        vzadMotorA();
    }
    else if (state == 'A0'){
        while(speedA>=20){      //funkce pridavajici rychlost dokud nedojde do maximalni hodnoty
          speedA = speedA - 20; //adding speed to motor
        }
        statMotorA();            //vyvolani funkce k pohybu motoru
    }
    if(state == 'B1'){
      while(speedB<=245){       //funkce pridavajici rychlost dokud nedojde do maximalni hodnoty
        speedB = speedB + 10;   //adding speed to motor
      }
      vpredMotorB();             //vyvolani funkce k pohybu motoru
    } else if (state == 'B2'){
        while(speedB<=245){     //funkce pridavajici rychlost dokud nedojde do maximalni hodnoty
          speedB = speedB + 10; //adding speed to motor
        }
        vzadMotorB();           //vyvolani funkce k pohybu motoru
    }
    else if (state == 'B0'){
        while(speedB>=20){      //funkce ubírající rychlost dokud nedojde do minimální hodnoty
          speedB = speedB - 20; //reducing speed of motor
        }
        statMotorB();            //vyvolani funkce k pohybu motoru
    }
    //-----------------------------------------------------
  //_____________________________________________________
}