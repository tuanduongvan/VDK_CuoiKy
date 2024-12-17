#include <DHT.h>
#include <Stepper.h>

#define DHT11Pin 4
#define DHTType DHT11
DHT HT(DHT11Pin, DHTType);

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 2, 4, 3, 5);

float humi;
float temp;

void setup() {
  HT.begin();
  myStepper,setSpeed(15);
  Serial.begin(9600);
}

void loop() {
  humi = HT.readHumidity();
  temp = HT.readTemperature();
  Serial.print("Humidity: ");
  Serial.println(humi);
  Serial.print("Temperature: ");
  Serial.println(temp);
  if(humi > 90 && temp > 29){
    myStepper.step(stepsPerRevolution);
    delay(2000);
  }
}
