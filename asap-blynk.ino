//library blynk
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//library DHT 11
#include "DHT.h"

#define DHTPIN D6
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//inisialisasi kipas
#define kipas D7

//inisialisasi mq2
const int asap = A0;
int sensorValue = 0;

//token blynk
char auth[] = "83A8iRjjw8z39p-qLjuqZMmgQBOUt3Wj";

//konfigurasi ssid
char ssid[] = "rosandi";
char pass[] = "12345678";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(kipas, OUTPUT);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(A0);
  Serial.println(sensorValue, DEC);
  int suhu = dht.readTemperature();
  Blynk.virtualWrite(V6, suhu);
  Blynk.virtualWrite(V7, sensorValue);
  Serial.println(suhu);

  if(sensorValue > 500 || suhu > 34)
  {
    Serial.println("KIPAS MENYALA");
    digitalWrite(kipas, LOW);
  }
  else
  {
    Serial.println("KIPAS MATI");
    digitalWrite(kipas, HIGH);
  }

  delay(1000);
}
