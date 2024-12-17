#include <Stepper.h>

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 3, 5, 4, 6);

int GasPin = 0;
int val;

void setup() {
  myStepper.setSpeed(10);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(GasPin);
  Serial.println(val, DEC);
  if(val > 550){
    myStepper.step(stepsPerRevolution);
    delay(2000);
  }
  else{
    myStepper.step(-stepsPerRevolution);
    delay(2000);
  }
}
