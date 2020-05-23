#include "DHT.h"                              // DHT Sensor
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define trigPin 10
#define echoPin 11

char auth[] = "yAOlH42DMWGx3wFkBne2JY9tUEpw1GCb";
char ssid[] = "Benders Scotland";
char pass[] = "$ingapore14";
int messent =1;

DHT dhtA(5, DHT22);                           // DHT instance named dhtA, D1 and sensor type

BlynkTimer timer;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Blynk.begin(auth, ssid, pass);              // Connecting to blynk
  dhtA.begin();                               // Starting the DHT-22
  timer.setInterval(1000L,climateRoutine); 
}

void loop() {
  Blynk.run();
  timer.run();
}

void climateRoutine() {
  float h1 = dhtA.readHumidity();            // f1 and h1 are celsius and humidity readings
  float t1 = dhtA.readTemperature();         // from DHT/A
  float t2 = 1.8*t1+32;     
  Blynk.virtualWrite(V0, t1);   
  Blynk.virtualWrite(V1, h1);  
  Blynk.virtualWrite(V2, t2);  

  float duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;
  Blynk.virtualWrite(V3, distance);  
  if(distance > 17 && messent ==1){
  Blynk.notify("Pellets Running Low");
  messent=0;
  }
  else{
  messent=1;
  }  
}
