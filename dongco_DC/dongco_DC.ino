int buttonright = 2;
int buttonleft = 3;
int moto1 = 9;
int moto2 = 10;
int enable = 5;
int motoState = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(moto1, OUTPUT);
  pinMode(moto2, OUTPUT);
  pinMode(enable, OUTPUT);
  Serial.begin(9600);
  pinMode(buttonright, INPUT_PULLUP);
  pinMode(buttonleft, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(buttonright), turnRight, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonleft), turnLeft, FALLING);

}

void loop() {
  // put your main code here, to run repeatedly:
  int speed = 100;
  switch(motoState){
    case 0:
      digitalWrite(moto1, HIGH);
      digitalWrite(moto2, LOW);
      analogWrite(enable, speed);
      Serial.println("Thuan chieu kim dong ho");
      break;
    case 1:
      digitalWrite(moto1, LOW);
      digitalWrite(moto2, HIGH);
      analogWrite(enable, speed);
      Serial.println("nguoc chieu dong ho");
      break;
  }

  delay(100);

}

void turnRight()
{
  motoState = 0;
}

void turnLeft()
{
  motoState = 1;
}
