#include "DHT.h"                              // DHT Sensor
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "jtfcQ-3atei9TbXHPTrw6q1dqjeBO0uo";
char ssid[] = "Benders Scotland";
char pass[] = "$ingapore14";

DHT dhtA(5, DHT22);                           // DHT instance named dhtA, D1 and sensor type

BlynkTimer timer;

void setup() {
  Blynk.begin(auth, ssid, pass);              // Connecting to blynk
  dhtA.begin();                               // Starting the DHT-22
  timer.setInterval(1000L,climateRoutine); 
}

void loop() {
  Blynk.run();
  timer.run();
}

void climateRoutine() {
    byte h1 = dhtA.readHumidity();            // f1 and h1 are celsius and humidity readings
    // byte t1 = dhtA.readTemperature(true);  // for temperature in farenheits
    byte t1 = dhtA.readTemperature();         // from DHT/A
    byte t2 = 1.8*t1+32;     
    Blynk.virtualWrite(V0, t1);               //  Set Virtual Pin 0 frequency to PUSH in Blynk app
    Blynk.virtualWrite(V1, h1);               //  Set Virtual Pin 1 frequency to PUSH in Blynk app
    Blynk.virtualWrite(V2, t2);               //  Set Virtual Pin 1 frequency to PUSH in Blynk app
}
