#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiManager.h>
#include <SoftwareSerial.h>
#include "UwU.h"

WiFiManager wifim;
SoftwareSerial com(13,15);
String send;

unsigned long sendDataPrevMillis = 0;
bool nyala = false;
int durasi = 0;
int ke = 0;
int kesebelumnya = 0;
float tnh = 0;
String data;
float kelembapantnh;

void setup(){
Serial.begin(9600);
com.begin(9600);

wifim.autoConnect("TheBramBang");
}

void loop(){
  while (com.available() > 0) {
    delay(10);
    char c = com.read();
    data += c;
  }

}

String update() {
  WiFiClientSecure client;
  client.setInsecure();  // Ignore SSL certificate validation
  HTTPClient https;
  String response;
  //bool response=false;

  Serial.printf("[Firebase] UPDATE with data : %s\n", send.c_str());
  if (https.begin(client, DATABASE_URL1)) {  // HTTPS
    https.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpCode = https.PUT(send);
    if (httpCode > 0) {
      response = https.getString();
      //response=true;
      Serial.printf("[Firebase] UPDATE response code: %d\n", httpCode);
      //Serial.println(response); // debug
    } else {
      Serial.printf("[Firebase] UPDATE error: %s\n", https.errorToString(httpCode).c_str());
    }
    https.end();
  } else {
    Serial.printf("[Firebase] Unable to connect\n");
  }
  return response;
}

void siram(){
   DynamicJsonDocument doc(1024);
    deserializeJson(doc, update());
  
    if(bool(doc["nyala"])){
      com.println(String(doc["delay"]));
    }
    WiFiClientSecure client;
    client.setInsecure();  // Ignore SSL certificate validation
    HTTPClient https;
    Serial.printf("[Firebase] UPDATE with data : %s\n", send.c_str());
    if (https.begin(client, DATABASE_URL2)) {  // HTTPS
    https.addHeader("Content-Type", "application/x-www-form-urlencoded");
    delay(doc["delay"]);
    int httpCode = https.PUT("false");
    if (httpCode > 0) {
      Serial.printf("[Firebase] response code: %d\n", httpCode);
    }
    else {
      Serial.printf("[Firebase] error: %s\n", https.errorToString(httpCode).c_str());
    }
    https.end();
  } else {
    Serial.printf("[Firebase] Unable to connect\n");
    }
}