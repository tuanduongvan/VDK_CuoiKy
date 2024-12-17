#include <Stepper.h>

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 2, 4, 3, 5);

const int InfraredPin = 2;

void setup() {
  pinMode(InfraredPin, INPUT);
  myStepper.setSpeed(15);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(InfraredPin) == HIGH){
    myStepper.step(stepsPerRevolution);
    delay(2000);
  }
}
