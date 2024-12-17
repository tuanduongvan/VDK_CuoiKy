#include <DHT.h>
#define DHT11Pin 7
#define DHTType DHT11

DHT HT(DHT11Pin, DHTType);

int enableA = 3;
int input1 = 5;
int input2 = 4;

float humi;
float temp;

void setup(){
  HT.begin();
  pinMode(enableA, OUTPUT);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
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
    // Điều khiển tốc độ động cơ
    analogWrite(enableA, 175);

    // Động cơ chạy thuận 5s
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    delay(5000);
    
    // Tắt 1 giây
    analogWrite(enableA, 0);
    delay(3000);
  }
  else{    
    // Điều khiển tốc độ động cơ
    analogWrite(enableA, 175);

    // Động cơ chạy nghịch 5s
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    delay(5000);

    // Tắt 1 giây
    analogWrite(enableA, 0);
    delay(3000);
  }
  
}
