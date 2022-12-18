#define IN1 15
#define IN2 14
#define LED1 7
#define LED2 8

int x1;
int x2;
int y1;
int y2;


void vpred(){
  //digitalWrite(LED2, HIGH);
  Serial.print("vpred");
}

void vzad(){
  //digitalWrite(LED1, HIGH);
  Serial.print("vzad");
}

void setup() {
for (byte i=8; i<=15;i++) {
pinMode(i,OUTPUT);
Serial.begin(9600);
}
}

void loop() {
x1 = analogRead(A0);
y1 = analogRead(A1);
x2 = analogRead(A2);
y2 = analogRead(A3);
if (y1<=100){
  vpred();
}
if (y1>=900){
  vzad();
}
}
