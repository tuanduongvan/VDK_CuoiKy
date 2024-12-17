#include <Servo.h> 
#define Servo_PWM 6 

Servo MG995_Servo; 
const int trigPin = 5; // chân trig của HC-SR04
const int echoPin = 3; // chân echo của HC-SR04
float tmprVal = 0;
float sinVal;
int toneVal;
void setup(){
  pinMode(trigPin, OUTPUT); // chân trig sẽ phát tín hiệu
  pinMode(echoPin, INPUT); // chân echo sẽ nhận tín hiệu
  MG995_Servo.attach(6);
  Serial.begin(9600);
}
void loop(){
  unsigned long duration; // biến đo thời gian
  int distance;           // biến lưu khoảng cách

  digitalWrite(trigPin, LOW); // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // phát xung từ chân trig
  delayMicroseconds(10); // xung có độ dài 10 microSeconds
  digitalWrite(trigPin, LOW); // tắt chân trig
  duration = pulseIn(echoPin, HIGH);

 
  // Tính khoảng cách đến vật.
  distance = duration * 0.034 / 2;
    
  Serial.print(distance);
  Serial.println("cm"); 
   if(distance < 5){
    MG995_Servo.write(180); 
    delay(2000);
  }
  else{
    
    MG995_Servo.write(0);
    delay(2000);
  } 
    
}
