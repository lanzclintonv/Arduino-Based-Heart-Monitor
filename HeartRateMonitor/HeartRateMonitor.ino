#include "DHT.h"

#define DHTPIN 2 

#define DHTTYPE DHT11


int Pulse = A0;
int tempPin = A1;

float h;
float t;
float temp;
int BMP;
int val;
float mv;
unsigned long HeartRate;
String data;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
   t = dht.readTemperature();
   h = dht.readHumidity();
   lm35();
   hrate();

   data = String(t) + "," + String(h) + "," + String(temp) + "," + String(HeartRate);
   Serial.println(data);
}

void lm35(){
  val = analogRead(tempPin);
  mv = (val/1024.0)*5000;
  temp = mv/10;
}

void hrate(){
  while (digitalRead(Pulse) == HIGH);
  while (digitalRead(Pulse) == LOW);
  int T1 = millis();
  while (digitalRead(Pulse) == HIGH);
  while (digitalRead(Pulse) == LOW);
  int T2 = millis();
  int Time = T2-T1;
  HeartRate = 60000L;
  HeartRate = HeartRate/Time;
}