#include <Stepper.h>
#define LINE 2

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 3, 5, 4, 6);

int val = 0;

void setup() {
  myStepper.setSpeed(10);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(LINE);
  Serial.println(val);
  if(val == 0){
    myStepper.step(stepsPerRevolution);
    delay(2000);
  }
  else{
    myStepper.step(-stepsPerRevolution);
    delay(2000);
  }
}
