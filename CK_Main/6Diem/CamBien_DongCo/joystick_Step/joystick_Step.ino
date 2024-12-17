#include <Stepper.h>

  int JoyStick_X = 0;
  int JoyStick_Y = 1;

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  myStepper.setSpeed(15);
  Serial.begin(9600);
}

  void loop() {
    int x, y;
    x = analogRead(JoyStick_X);
    y = analogRead(JoyStick_Y);
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.println();
    if (x > 600 && y < 600)
    {
    Serial.println("quay chiều thuận");
    myStepper.step(stepsPerRevolution);
    delay(2000);
    }
    else if (x < 300 || y < 300) {
    Serial.println("quay ngược");
    myStepper.step(-stepsPerRevolution);
    delay(2000);
    }
    else if (x < 600 && y > 600)
    {
    Serial.println("quay chiều thuận");
    myStepper.step(stepsPerRevolution);
    delay(2000);
    }
    else {
    Serial.println("dừng lại");
    myStepper.step(0);
    delay(2000);
    }
    delay(100);
  }