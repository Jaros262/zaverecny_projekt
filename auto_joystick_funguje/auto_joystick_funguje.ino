#define ENA 11
#define IN1 10
#define IN2 9
#define IN3 8
#define IN4 7
#define ENB 6

int x;
int y;
int val;

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

void setup() {
for (byte i=6; i<=11;i++) {
pinMode(i,OUTPUT);
Serial.begin(9600);
}
digitalWrite(ENA,HIGH);
digitalWrite(ENB,HIGH);
}

void loop() {
x = analogRead(A1);
y = analogRead(A2);
val = analogRead(A0);
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
}
