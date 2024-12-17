#include <DHT.h>
#include <Servo.h>

#define DHT11Pin 4
#define DHTType DHT11

DHT HT(DHT11Pin, DHTType);
Servo myServo;

float humi;
float temp;

void setup(){
  HT.begin();
  myServo.attach(6);
  Serial.begin(9600);
}

void loop(){
  humi = HT.readHumidity();
  temp = HT.readTemperature();
  Serial.print("Humidity: ");
  Serial.println(humi);
  Serial.print("Temperature: ");
  Serial.println(temp);
  if(humi > 90 && temp > 29){
    myServo.write(180);
    delay(2000);
    myServo.write(0);
  }
  else{
    myServo.write(90);
    delay(2000);
    myServo.write(0);
  }
  delay(500);
  
}
