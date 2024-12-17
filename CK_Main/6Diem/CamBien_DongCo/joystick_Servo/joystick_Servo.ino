#include <Servo.h>

  int val = 0;

  int JoyStick_X = 0;
  int JoyStick_Y = 1;

Servo myServo;

void setup() {
  myServo.attach(6);
  Serial.begin(9600);
}

  void loop() {

    myServo.write(0);
    int x, y;
    x = analogRead(JoyStick_X);
    y = analogRead(JoyStick_Y);
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.println();
    if (x > 600 && y < 600)
    {
      Serial.println("quay 135");
      myServo.write(135);
      delay(1000);
      myServo.write(0);
    }
    else if (x < 600 && y > 600)
    {
      Serial.println("quay 180");
      myServo.write(180);
      delay(1000);
      myServo.write(0);
    }
    else if (x < 600 && y < 200) {
      Serial.println("quay 90");
      myServo.write(90);
      delay(1000);
      myServo.write(0);
    }
    else if (x < 200 && y < 600) {
      Serial.println("quay 45");
      myServo.write(45);
      delay(1000);
      myServo.write(0);
    }
    else {
      myServo.write(0);
    }
    delay(2000);
  }