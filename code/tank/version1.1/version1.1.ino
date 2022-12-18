#include <Servo.h> //Libary for servo controll

//pins setup
#define ENA 11
#define IN1 10
#define IN2 9
#define IN3 8
#define IN4 7
#define ENB 6
//jeden digital pin pro servo

int value = 100; //vychozi pozice pro servo

Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created

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
}

void servoLeft(){
  myservo.write(value);
  value = value-5;
}

void servoRight(){
  myservo.write(value);
  value = value+5;
}

void setup() { // put your setup code here, to run once:
  for (byte i=6; i<=11;i++) {
    pinMode(i,OUTPUT);
  }
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  }
  
  myservo.attach(9); //Nastaveni pinu serva na knihovnu <Servo.h>
  Serial.begin(38400); // Default communication rate of the Bluetooth module
}

void loop() {
  //Ovladani serva---------------------------------------
  if(joystickXVal<100&&(((joystickXVal+520)/10)>1)){
   servoLeft();
  }
  if(joystickXVal>900&&(((joystickXVal+520)/10)<199)){
   servoRight();
  }
  //-----------------------------------------------------

  //Ovladani motoru--------------------------------------
  if(y<=100){
    Serial.print("Joy Value in y is");
    Serial.println(y);
    vpred();
  } else if (y>=900){
      Serial.print("Joy Value in y is");
      Serial.println(y);
      vzad();
  }else if (x<=100){
      vlevo();
  }else if (x>=900){
      vpravo();
  }else if (x<=600 && x>=400 && y<=600 && y>=400){
      stat();
  }
  //-----------------------------------------------------

}
