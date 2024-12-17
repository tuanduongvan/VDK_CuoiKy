#include <Servo.h>
int val = 0;
int LIGHT = 0;

Servo myServo;

void setup() {
  myServo.attach(6);
  Serial.begin(9600);
}

void loop() {
  myServo.write(0);
  val = analogRead(LIGHT);
  Serial.println(val);
  if(val > 800){
    myServo.write(180);
    delay(1000);
    myServo.write(0);
  }
  else{
    myServo.write(90);
    delay(1000);
    myServo.write(0);
  }
  delay(2000);
}
