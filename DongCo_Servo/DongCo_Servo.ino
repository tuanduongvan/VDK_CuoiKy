#include <Servo.h>
#include <math.h>
Servo myservo;
int r = 0;//góc quay
int pinServo = 9;
void setup() {
  // put your setup code here, to run once:
  myservo.attach(pinServo);
  Serial.begin(9600);
  myservo.write(r);
}

void loop() {
  // put your main code here, to run repeatedly:
  myservo.write(150);
  delay(800);
  myservo.write(0);
  delay(500);
}
