#include <Stepper.h>

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 3, 5, 4, 6);

int val = 0;
int LIGHT = 0;

void setup() {
  myStepper.setSpeed(15);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(LIGHT);
  Serial.println(val);
  if(val > 800){
    myStepper.step(stepsPerRevolution);
    delay(2000);
  }
  else{
    myStepper.step(-stepsPerRevolution);
    delay(2000);
  }
}
