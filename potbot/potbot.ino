//#include <DHT.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd (0x27, 16, 2);
/* next fitur
#define DHTPIN 2
#define DHTVER DHT11
DHT udara(DHTPIN,DHTVER);
*/
SoftwareSerial com(13,15);

void setup() {
  // put your setup code here, to run once: 
  com.begin(9600);
  lcd.begin();
  lcd.backlight();
  pinMode(12, OUTPUT);
  lcd.setCursor(0,0);
  lcd.print("Awalan Menyala");
  lcd.setCursor(3,1);
  digitalWrite(12, HIGH);
  lcd.print("Selesai");
  delay(2000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:

  lcd.setCursor(0,0);
  lcd.print("Info Kelembapan");
  lcd.setCursor(0,1);
  lcd.print("Tanah " + String(kelembapantnh(),0));

  if(kelembapantnh() >= 630){
    digitalWrite(12, LOW);
    com.print(Sring(kelembapantnh()) + "," + "1");
    lcd.setCursor(0,0);
    lcd.print("Tanah Kering    ");
    lcd.setCursor(0,1);
    lcd.print("Menyiram ");
    delay(60000);
    lcd.clear();
    digitalWrite(12, HIGH);
    com.print(Sring(kelembapantnh()) + "," + "0");
  } 
   while (com.available() > 0) {
    delay(10);
    char c = com.read();
    data += c;
  }
   delay(5000);
  /*
  lcd.setCursor(0,0);
  lcd.print("Info Kelembapan");
  lcd.setCursor(0,1);
  lcd.print("Udara " + String(kelembapanudr(),0));
  delay(5000);
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Info Suhu udara");
  lcd.setCursor(0,1);
  lcd.print(String(kelembapanudr(),0));
  delay(5000);
  lcd.clear();
  */
}

float kelembapantnh(){
  float sensortnh = analogRead(A0);
  return sensortnh;
}
/*
float kelembapanudr(){
  float sensorudr = udara.readHumidity();
  return sensorudr;
}
float suhuudara(){
  float sensorudr = udara.readTemperature();
  return sensorudr;
}
*/

void kirim(){
  com.print(kelembapantnh());
  com.print(",");
  com.begin("n")
}
String splitteks(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;
 
  for(int i=0; i<=maxIndex &amp;&amp; found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  } 
 
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}