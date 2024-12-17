#include <Servo.h>
#define Servo_PWM 6

const int InfraredPin = 2;
Servo MG995_Servo;

void setup() {
  pinMode(InfraredPin, INPUT);
  MG995_Servo.attach(6);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(InfraredPin) == HIGH){
    MG995_Servo.write(180);
    Serial.println("YES");
    delay(2000);
  }
  else{
    MG995_Servo.write(0);
    Serial.println("NO");
    delay(2000);
  }
}
