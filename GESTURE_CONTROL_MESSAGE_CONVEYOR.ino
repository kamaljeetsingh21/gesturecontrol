#include "Wire.h"       
#include "I2Cdev.h"     
#include "MPU6050.h"    
#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
int buzzer = 11;
int gesture=5;
MPU6050 mpu;

int16_t ax, ay, az;
int16_t gx, gy, gz;

struct MyData {
  byte X;
  byte Y;
};

MyData data;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  lcd.begin(16, 2);
  pinMode(buzzer, OUTPUT);
  
  lcd.clear();
  lcd.print("scanning");
  Serial.println("welcome");
}

void loop()
{
  
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -17000, 17000, 0, 255 ); // X axis data
  data.Y = map(ay, -17000, 17000, 0, 255);  // Y axis data
 

  
   if (data.Y < 80) {//gesture : down 
    if (gesture!=1){
      
    gesture = 1;
     lcd.clear();
     Serial.println("RESTROOM");
    lcd.print("RESTROOM");
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer,LOW);
    delay(500);
    }}
  if (data.Y > 145) {//gesture : up
    if (gesture!=2){
      gesture = 2;
     lcd.clear();
     Serial.println("NEED MEDICINE");
  lcd.print("MEDICINE");
  digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer,LOW);
  delay(500);
    }}
 if (data.X > 155) {//gesture : left
  if (gesture!=3){
    gesture = 3;
   lcd.clear();
  lcd.print("NEED WATER");
  Serial.println("NEED WATER");
  digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer,LOW);
  delay(500);
    }}
 if (data.X < 80) {//gesture : right
  if (gesture!=4){
    gesture = 4;
   lcd.clear();
   Serial.println("Emergency");
  lcd.print("Emergency");
  digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer,LOW);
  delay(500);
    }}
 if (data.X > 100 && data.X < 170 && data.Y > 80 && data.Y < 130) { //gesture : little bit down
  if (gesture!=5){
    gesture = 5;
 
   lcd.clear();
   Serial.println(" ");
    lcd.print(" ");
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer,LOW);
    delay(500);
    }}
  
}
