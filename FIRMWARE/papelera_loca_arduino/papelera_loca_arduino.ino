// Junio 2017
// Manu García
//CIFP SANTA CATALINA - Aranda de Duero


#include <SoftwareSerial.h>
#include <Servo.h>
#include <NewPing.h>
NewPing sonar(3,12,200);
Servo servo;
SoftwareSerial BTSerial(10, 11); // TX | RX
char val;
int mode=1;
int cambio=1;
int a;
long tinicio=0;
void setup()
{
servo.attach(A0);
pinMode(2,INPUT_PULLUP);
servo.write(3);
BTSerial.begin(9600);
Serial.begin(9600);
pinMode(4,OUTPUT);//I
pinMode(5,OUTPUT);//I
pinMode(6,OUTPUT);//IPWM
pinMode(7,OUTPUT);//D
pinMode(8,OUTPUT);//D
pinMode(9,OUTPUT);//DPWM
}
void loop()
{ 
tinicio=millis();
while(digitalRead(2)==0)
{
 if(millis()>(tinicio+2000))
 {
  digitalWrite(A1,0);
  digitalWrite(A2,0);
  digitalWrite(A3,1);
  if(cambio==1)
  {
  mode++;
  if(mode==2)mode=0;
  cambio=0;
  }
 }
}
if(mode==0)
{
 digitalWrite(A2,0);
 digitalWrite(A3,0);
  digitalWrite(A1,1);
if(BTSerial.available())
val=BTSerial.read();
switch(val)
{
 case 's':
 //paro
 analogWrite(6,0);
 analogWrite(9,0);
 break;
 case 'l':
 //izquierda
  analogWrite(9,255);
  analogWrite(6,0);
  pinMode(7,0);
  pinMode(8,1);
 break;
 case 'r':
 //derecha
  analogWrite(6,255);
  analogWrite(9,0);
  pinMode(4,0);
  pinMode(5,1);
 break;
 case 'd':
 //atras
 analogWrite(6,235);
  analogWrite(9,255);
  pinMode(4,1);
  pinMode(5,0);
  pinMode(7,1);
  pinMode(8,0);
 break;
 case 'u':
 //adelante
  analogWrite(6,235);
  analogWrite(9,255);
  pinMode(4,0);
  pinMode(5,1);
  pinMode(7,0);
  pinMode(8,1);
 break;
 case 'x':
 //michael jackson
  analogWrite(6,255);
  analogWrite(9,255);
  pinMode(4,0);
  pinMode(5,1);
  pinMode(7,1);
  pinMode(8,0);
 break;
 case 'O':
 servo.write(80);
 break;
 case 'o':
 servo.write(3);
 break;
}
}
if(mode==1)
{
  digitalWrite(A3,0);
  digitalWrite(A2,1);
  digitalWrite(A1,0);
  a=sonar.ping_cm();
   if((a<15)&&(a!=0))
   {
    Serial.println(a);
    servo.write(80);
    delay(2000);
    servo.write(3);
    delay(500);
    a=93;
   }
}
cambio=1;
}
