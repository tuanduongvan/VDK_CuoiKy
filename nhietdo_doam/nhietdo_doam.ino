#include<DHT.h>
// 3 chân: 1VCC, 1GND, 1dhtpin(D)
const int dhtpin = 3;
const int DHTTYPE = DHT11;

DHT dht(dhtpin, DHTTYPE);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("Nhiet do: ");
  Serial.println(t); 
  Serial.print("Do am: ");
  Serial.println(h); 

  Serial.println();
  delay(1000);

}
