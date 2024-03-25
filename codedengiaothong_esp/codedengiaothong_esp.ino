/*********
  Rui Santos
  Complete instructions at https://RandomNerdTutorials.com/esp8266-web-server-gauges/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/
#include <Wire.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "LittleFS.h"
#include <Arduino_JSON.h>
#include<SoftwareSerial.h> //Included SoftwareSerial Library
#include "DHT.h"            
const int DHTPIN = 14;      
const int DHTTYPE = DHT11;  
DHT dht(DHTPIN, DHTTYPE);
//SoftwareSerial s(3, 1);
// Replace with your network credentials
const char* ssid = "Florentino";
const char* password = "anhem76maidinh";
char c,d,e;
int nhietdo = 0;
int doam = 0;
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Create an Event Source on /events
AsyncEventSource events("/events");

// Json Variable to Hold Sensor Readings
JSONVar readings;
JSONVar reading2s;
// Timer variables
unsigned long lastTime = 0;  
unsigned long timerDelay = 30000;
// Initialize LittleFS
void initFS() {
  if (!LittleFS.begin()) {
    Serial.println("An error has occurred while mounting LittleFS");
  }
//  Serial.println("LittleFS mounted successfully");
}

// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println(WiFi.localIP());
}
void trangthaiuno(char a){
 Wire.beginTransmission(8); /* begin with device address 8 */
 Wire.write(a);  /* sends hello slave string */
 Wire.endTransmission();    /* stop transmitting */
 
 Wire.requestFrom(8, 1); /* request & read data of size 13 from slave */
 while(Wire.available()){
    c = Wire.read();
  Serial.print(c);
 }
 Serial.println();
}
void chophepuno(char a){
 Wire.beginTransmission(8); /* begin with device address 8 */
 Wire.write(a);  /* sends hello slave string */
 Wire.endTransmission();    /* stop transmitting */
 
 Wire.requestFrom(8, 1); /* request & read data of size 13 from slave */
 while(Wire.available()){
    d = Wire.read();
  Serial.print(d);
 }
 Serial.println();
}

void dongbouno(){
 Wire.beginTransmission(8); /* begin with device address 8 */
 Wire.write('5');  /* sends hello slave string */
 Wire.endTransmission();    /* stop transmitting */
 
 Wire.requestFrom(8, 1); /* request & read data of size 13 from slave */
 while(Wire.available()){
    e = Wire.read();
  Serial.print(e);
 }
 Serial.println();
}
String gettrangthai(){
  readings["trangthai"] = String(c);
  String jsonString = JSON.stringify(readings);
  return jsonString;}

String getchophepdieukhien(){
  readings["chophep"] = String(d);
  String jsonString = JSON.stringify(readings);
  return jsonString;}
String getdongbouno(){
  readings["dongbo"] = String(e);
  String jsonString = JSON.stringify(readings);
  return jsonString;}
String getdht11(){ 
  reading2s["nhietdo"] = String(nhietdo);
  reading2s["doam"] = String(doam);
  String jsonString2 = JSON.stringify(reading2s);
  return jsonString2;}
void setup() {
  Serial.begin(9600);
//  s.begin(9600);
  initWiFi();
  initFS();
  Wire.begin(D1, D2);
  dht.begin(); 

  // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html");
  });

  server.serveStatic("/", LittleFS, "/");

  server.on("/trangthai1",HTTP_GET, [](AsyncWebServerRequest *request){
//    s.write(1);
    Serial.println("Chuyển sang trạng thái 1");
    trangthaiuno('1');
    String json = gettrangthai();
    Serial.println(json);
    request->send(200, "application/json", json);
    json = String();
    });

  server.on("/trangthai2",HTTP_GET, [](AsyncWebServerRequest *request){
//    s.write(2);
    Serial.println("Chuyển sang trạng thái 2");
    trangthaiuno('2');
    String json = gettrangthai();
    Serial.println(json);
    request->send(200, "application/json", json);
    json = String();
    });
  server.on("/trangthai3",HTTP_GET, [](AsyncWebServerRequest *request){
//    s.write(3);
    Serial.println("Chuyển sang trạng thái 3");
    trangthaiuno('3');
    String json = gettrangthai();
    Serial.println(json);
    request->send(200, "application/json", json);
    json = String();
    });
    server.on("/dht11",HTTP_GET, [](AsyncWebServerRequest *request){
//    s.write(3);
    Serial.println("Đọc giá trị cảm biến DHT11");
    String json = getdht11();
    Serial.println(json);
    request->send(200, "application/json", json);
    json = String();
    });

    server.on("/chophep",HTTP_GET, [](AsyncWebServerRequest *request){
//    s.write(3);
    chophepuno('4');
    Serial.println("Kiểm tra trạng thái cho phép điều khiển không");
    String json = getchophepdieukhien();
    Serial.println(json);
    request->send(200, "application/json", json);
    json = String();
    });
    server.on("/dongbo",HTTP_GET, [](AsyncWebServerRequest *request){
//    s.write(3);
    dongbouno();
    Serial.println("Kiểm tra trạng thái cho phép điều khiển không");
    String json = getdongbouno();
    Serial.println(json);
    request->send(200, "application/json", json);
    json = String();
    });
    
  server.addHandler(&events);
  // Start server
  server.begin();
}

void loop() {
  delay(500);
  nhietdo = dht.readTemperature();
  doam = dht.readHumidity();
}
