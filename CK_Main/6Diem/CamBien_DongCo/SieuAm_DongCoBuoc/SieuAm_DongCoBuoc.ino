#include <Stepper.h>

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 3, 5, 4, 6);

const int trigPin = 9;
const int echoPin = 7;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myStepper.setSpeed(15);
  Serial.begin(9600);
}

void loop() {
  unsigned long duration; // biến đo thời gian
  int distance;           // biến lưu khoảng cách

  digitalWrite(trigPin, LOW); // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // phát xung từ chân trig
  delayMicroseconds(10); // xung có độ dài 10 microSeconds
  digitalWrite(trigPin, LOW); // tắt chân trig
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print(distance);
  Serial.println("cm"); 
   if(distance < 5){
     myStepper.step(stepsPerRevolution);
     delay(2000);
  }
  else {
    myStepper.step(-stepsPerRevolution);
     delay(2000);
  }
  
}
