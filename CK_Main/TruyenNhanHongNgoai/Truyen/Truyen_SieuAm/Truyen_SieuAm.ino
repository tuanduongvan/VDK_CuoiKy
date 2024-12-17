#define PIN_SEND 3
#include <IRremote.h> 

const int trigPin = 6; // chân trig của HC-SR04
const int echoPin = 5; // chân echo của HC-SR04
void setup() { 
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // chân trig sẽ phát tín hiệu
  pinMode(echoPin, INPUT); // chân echo sẽ nhận tín hiệu
  
  // Initializes IR sender 
  IrSender.begin(PIN_SEND); 
} 
  
void loop() { 
  delay(2000);
  unsigned long duration; // biến đo thời gian
  int distance;           // biến lưu khoảng cách

  digitalWrite(trigPin, LOW); // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // phát xung từ chân trig
  delayMicroseconds(10); // xung có độ dài 10 microSeconds
  digitalWrite(trigPin, LOW); // tắt chân trig
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2;   // Tính khoảng cách đến vật.
  Serial.print(distance);
  Serial.println("cm"); 

  if (distance < 10) {
    IrSender.sendNECRaw(1); 
    delay(200);
  }
  else{
    IrSender.sendNECRaw(0);
    delay(200);
  }
      
}
