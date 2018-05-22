#include "RTClib.h"

#include <Servo.h>
#include <NewPing.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal  lcd(12, 11, 5, 4, 3, 2); 
NewPing sonar(10,9);
RTC_DS3231 rtc;
Servo myservo;
byte porc=0;
int a=1;
boolean b=0;
byte d,m,h,mi,s,serv;
int y;

 
void setup () {
 delay(3000); 
 Serial.begin(9600);
 pinMode(13,INPUT_PULLUP);
 lcd.begin(16,2);
 myservo.attach(6);
  if (! rtc.begin()) {
 Serial.println("No hay un módulo RTC");
 while (1);
 }
}
 
void loop () {
 DateTime now = rtc.now();
 myservo.write(180);
 while(a==1){//Estado inicial
  if(analogRead(0)<300){
    a++;
    delay(500);
  }
  if(sonar.ping_cm()<30){
    myservo.write(105);
    delay(4000);
    myservo.write(180);
    delay(200);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute());
  lcd.setCursor(0,1);
  lcd.print(now.day());
  lcd.print("/");
  lcd.print(now.month());
  lcd.print("/");
  lcd.print(now.year());
  delay(200);
  Serial.println(sonar.ping_cm());

 }   
 while(a==2){//1ºFecha, Hora, Tª
  if(analogRead(0)<300){
    a++;
    delay(500);
  }
  if(analogRead(1)>700){
    a=1;
    delay(500);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Papeleitor 3000");
  lcd.setCursor(0,1);
  lcd.print("Ajuste Fecha/Hora");
  delay(200);
 
 
  Serial.println(a);
 }
 while(a==3){//2ºEstablecer fecha y hora
  if(analogRead(0)<300){
    a++;
    delay(500);
  }
  if(analogRead(1)>700){
    a=5;
    delay(500);
  }
  if(analogRead(0)>700){
    a--;
    delay(500);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ajuste Fecha/Hora");
  lcd.setCursor(0,1);
  lcd.print("Control Servo");
  delay(200);
   Serial.println(a);
 }

 while(a==4){//4ºManejar el servo

  if(analogRead(1)>700){
    a=10;
    delay(500);
  }
  if(analogRead(0)>700){
    a--;
    delay(500);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Control Servo");
  delay(200);
 }
 //                     Ajuste fecha
 while(a==5){//dia
  if(b==0){
   d=now.day();
   m=now.month();
   y=now.year();
   h=now.hour();
   mi=now.minute();
   s=now.second();
   b++;
  }
  if(analogRead(0)<300){
    d--;
    delay(800);
  }
  if(analogRead(0)>700){
    d++;
    delay(800);
  }
  if(d>31)d=31;
  if(analogRead(1)<300){
    a=3;
    delay(500);
  }
  if(analogRead(1)>700){
    a=6;
    delay(500);
  }
  if(digitalRead(13)==0){
    rtc.adjust(DateTime(y,m,d,h,m));
    a=3;
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">");
  lcd.print(d);
  lcd.print("/");
  lcd.print(m);
  lcd.print("/");
  lcd.print(y);
  lcd.setCursor(0,1);
  lcd.print(h);
  lcd.print(":");
  lcd.print(mi);
  delay(200);
  
 }
 while(a==6){//mes
  if(analogRead(0)<300){
    m--;
    delay(800);
  }
  if(analogRead(0)>700){
    m++;
    delay(800);
  }
  if(m>12)m=12;
  if(analogRead(1)<300){
    a=5;
    delay(500);
  }
  if(analogRead(1)>700){
    a=7;
    delay(500);
  }
  if(digitalRead(13)==0){
    rtc.adjust(DateTime(y,m,d,h,m));
    a=3;
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(d);
  lcd.print("/");
  lcd.print(">");
  lcd.print(m);
  lcd.print("/");
  lcd.print(y);
  lcd.setCursor(0,1);
  lcd.print(h);
  lcd.print(":");
  lcd.print(mi);
  delay(200);  
 }
 
 while(a==7){//año
  if(analogRead(0)<300){
    y--;
    delay(800);
  }
  if(analogRead(0)>700){
    y++;
    delay(800);
  }
  
   if(analogRead(1)>700){
    a=8;
    delay(500);
   }
   if(analogRead(1)<300){
    a=6;
    delay(500);
   }
   if(digitalRead(13)==0){
    rtc.adjust(DateTime(y,m,d,h,m));
    a=3;
   }
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print(d);
   lcd.print("/");
   lcd.print(m);
   lcd.print("/");
   lcd.print(">");
   lcd.print(y);
   lcd.setCursor(0,1);
   lcd.print(h);
   lcd.print(":");
   lcd.print(mi);
   delay(200);
       
 }
 while(a==8){//hora
  if(analogRead(0)<300){
    h--;
    delay(800);
  }
  if(analogRead(0)>700){
    h++;
    delay(800);
  }
  if(h>24)h=24;
  if(analogRead(1)>700){
    a=9;
    delay(500);
   }
  if(analogRead(1)<300){
    a=7;
    delay(500);
  }
  if(digitalRead(13)==0){
    rtc.adjust(DateTime(y,m,d,h,m));
    a=3;
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(d);
  lcd.print("/");
  lcd.print(m);
  lcd.print("/");
  lcd.print(y);
  lcd.setCursor(0,1);
  lcd.print(">");
  lcd.print(h);
  lcd.print(":");
  lcd.print(mi);
  delay(200);   
 }
 while(a==9){//minutos
  if(analogRead(0)<300){
    mi--;
    delay(800);
  }
  if(analogRead(0)>700){
    mi++;
    delay(800);
  }
  if(mi>60)mi=60;
  if(analogRead(1)<300){
    a=8;
    delay(500);
  }

  if(digitalRead(13)==0){
    rtc.adjust(DateTime(y,m,d,h,m));
    a=3;
  } 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(d);
  lcd.print("/");
  lcd.print(m);
  lcd.print("/");
  lcd.print(y);
  lcd.setCursor(0,1);
  lcd.print(h);
  lcd.print(":");
  lcd.print(">");
  lcd.print(mi);
  delay(200);   
 }
 while(a==10){//control servo
  if(analogRead(0)<300){
   porc--;
   delay(50);
  }
  if(analogRead(0)>700){
   porc++;
   delay(50);
  }
  if(analogRead(1)<300){
    a=4;
    delay(500);
  }
  if(porc==255)porc=0;
  if(porc==101)porc=100;
  
  serv=map(porc,0,100,180,105);
  lcd.clear();
  lcd.print(porc);
  lcd.print("%");
  delay(100);
  myservo.write(serv);
  
     
 }
 
 
}
