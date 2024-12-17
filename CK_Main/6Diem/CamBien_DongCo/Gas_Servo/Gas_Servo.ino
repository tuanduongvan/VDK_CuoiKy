#include <Servo.h>
#define Servo_PWM 6

Servo MG995_Servo;

int GasPin = 0;
int val;

void setup() {
  MG995_Servo.attach(6);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(GasPin);
  Serial.println(val, DEC);
  if(val > 850){
    MG995_Servo.write(180);
    delay(2000);
  }
  else{
    MG995_Servo.write(0);
    delay(2000);
  }
}
