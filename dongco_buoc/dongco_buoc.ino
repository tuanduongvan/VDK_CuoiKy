#include <Stepper.h>
//số bước / 1 vòng quay của động cơ
const int StepsPerRevolution = 2048;

Stepper mystepper = Stepper(StepsPerRevolution, 3, 5, 4, 6);//muốn đổi chiều thì đổi vị trí 8,10


void setup() {
  // put your setup code here, to run once:
  mystepper.setSpeed(10);//tốc độ quay

}

void loop() {
  // put your main code here, to run repeatedly:

  mystepper.step(StepsPerRevolution);//quay ngược chiều kim đồng hồ
  delay(1000);
  mystepper.step(-2*StepsPerRevolution);//  quay cùng chiều kim đồng hồ
  delay(1000);

}
