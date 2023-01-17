//SLAVE-REMOTE CAR (TANK)

//KNIHOVNY
#include <Servo.h>            //Libary for servo controll
//#include <SoftwareSerial.h>   //knihovna pro bluetooth
#include <SPI.h>              //radio
#include <nRF24L01.h>         //radio
#include <RF24.h>             //radio

//pins setup
#define ENA 2    //digital pin pro rychlost motoru A
#define IN1 10    //prvni digital pin pro motor A
#define IN2 9     //druhy digital pin pro motor A
#define IN3 8     //druhy digital pin pro motor B
#define IN4 7     //prvni digital pin pro motor B
#define ENB 6     //digital pin pro rychlost motoru B
#define SER 5     //digital pin pro servo
#define CSN_GPIO 4//digital pin for radio
#define CE_GPIO  3//digital pin for radio
//MOSI 11
//MISO 12
//SCK 13
//3V3 3V3

int value = 100;  //vychozi pozice pro servo
//int state = 0;    //promena ktera bude pouzivana na prijimani informaci z druheho arduina
int speedA;       //promena uchovavajici rychlost motoru A
int speedB;       //promena uchovavajici rychlost motoru B

Servo myservo;                      // create servo object to control a servo
                                    // a maximum of eight servo objects can be created
//SoftwareSerial mySerial(3, 4);      // RX, TX - nastaveni pinu modulu hc-05 (bluetooth)

// Hardware configuration
RF24 radio(CE_GPIO, CSN_GPIO);                           // Set up nRF24L01 radio on SPI bus plus pins 7 & 8

const byte Address[6] = "00001";
unsigned char Received_Command = '0';

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
  Serial.begin(9600);
  for (byte i=5; i<=11;i++) {       //seting up all digital pins to output
    pinMode(i,OUTPUT);
  }
  //radio setup--------------------------
  radio.begin();
  radio.openReadingPipe(0, Address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Serial.println("START");
  //-------------------------------------
  myservo.attach(5);                //Nastaveni pinu serva na knihovnu <Servo.h>
}

void loop() {
  if (radio.available())    // If the NRF240L01 module received data
  {  
    delay(10);
    radio.read(&Received_Command, 1);
    Serial.print(Received_Command);
  }
  //SPEED SETUP
  analogWrite(ENA,speedA);          //speed of motor A
  analogWrite(ENB,speedB);          //speed of motor B
  //MODE 1 SW==HIGH
    //Ovladani serva---------------------------------------
    if(Received_Command == 8){
      servoLeft();            //vyvolani funkce pohybu serva doleva

    }
    if(Received_Command == 9){
      servoRight();           //vyvolani funkce pohybu serva doprava
    }
    //-----------------------------------------------------

    //Ovladani motoru--------------------------------------
    if(Received_Command == 0){
      while(speedA<=245&&speedB<=245){    //funkce pridavajici rychlost dokud nedojde do maximalni hodnoty
        speedA = speedA + 10;             //adding speed to motor
        speedB = speedB + 10;             //adding speed to motor
      }
      vpredMotorA();                       //vyvolani funkcí k pohybu motoru
      vpredMotorB();
      
    } else if (Received_Command == 1){
        while(speedA<=245&&speedB<=245){  //funkce pridavajici rychlost dokud nedojde do maximalni hodnoty
          speedA = speedA + 10;           //adding speed to motor
          speedB = speedB + 10;           //adding speed to motor
        }
        vzadMotorA();                      //vyvolani funkcí k pohybu motoru
        vzadMotorB();
        
    }else if (Received_Command == 2){
        while(speedA<=245&&speedB<=245){  //funkce pridavajici rychlost dokud nedojde do maximalni hodnoty
          speedA = speedA + 10;           //adding speed to motor
          speedB = speedB + 10;           //adding speed to motor
        }
        vzadMotorA();                      //vyvolani funkcí k pohybu motoru
        vpredMotorB();
        
    }else if (Received_Command == 3){
        while(speedA<=245&&speedB<=245){  //funkce pridavajici rychlost dokud nedojde do maximalni hodnoty
          speedA = speedA + 10;           //adding speed to motor
          speedB = speedB + 10;           //adding speed to motor
        }
        vpredMotorA();                     //vyvolani funkcí k pohybu motoru
        vzadMotorB();
        
    }else {
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
    //Ovladani motoru--------------------------------------
    if(Received_Command == 4){
      while(speedA<=245){       //funkce pridavajici rychlost dokud nedojde do maximalni hodnoty
        speedA = speedA + 10;   //adding speed to motor
      }
      vpredMotorA();
    } else if (Received_Command == 5){
        while(speedA<=245){     //funkce pridavajici rychlost dokud nedojde do maximalni hodnoty
          speedA = speedA + 10; //adding speed to motor
        }
        vzadMotorA();
    }
    else {
        while(speedA>=20){      //funkce pridavajici rychlost dokud nedojde do maximalni hodnoty
          speedA = speedA - 20; //adding speed to motor
        }
        statMotorA();            //vyvolani funkce k pohybu motoru
    }
    if(Received_Command == 6){
      while(speedB<=245){       //funkce pridavajici rychlost dokud nedojde do maximalni hodnoty
        speedB = speedB + 10;   //adding speed to motor
      }
      vpredMotorB();             //vyvolani funkce k pohybu motoru
    } else if (Received_Command == 7){
        while(speedB<=245){     //funkce pridavajici rychlost dokud nedojde do maximalni hodnoty
          speedB = speedB + 10; //adding speed to motor
        }
        vzadMotorB();           //vyvolani funkce k pohybu motoru
    }
    else {
        while(speedB>=20){      //funkce ubírající rychlost dokud nedojde do minimální hodnoty
          speedB = speedB - 20; //reducing speed of motor
        }
        statMotorB();            //vyvolani funkce k pohybu motoru
    }
    //-----------------------------------------------------
  //_____________________________________________________
}