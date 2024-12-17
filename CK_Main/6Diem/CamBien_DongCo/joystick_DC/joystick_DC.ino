int JoyStick_X = 0;
  int JoyStick_Y = 1;
// Kết nối động cơ A
int enableA = 3;
int input1 = 5;
int input2 = 4;

  void setup() {
  pinMode(enableA, OUTPUT);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
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
      Serial.println("quay ngược chiều");
      analogWrite(enableA, 175);

      // Động cơ chạy thuận 5s
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      delay(1000);
    }
    else if (x < 300 || y < 300) {
      Serial.println("quay chiều thuận");
      analogWrite(enableA, 175);

      // Động cơ chạy thuận 5s
      digitalWrite(input2, HIGH);
      digitalWrite(input1, LOW);
      delay(1000);
    }
    else if (x < 600 && y > 600)
    {
      Serial.println("quay ngược chiều");
      analogWrite(enableA, 175);

      // Động cơ chạy thuận 5s
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
      delay(1000);
    }
    else {
      Serial.println("dừng quay");
      analogWrite(enableA, 175);

      // Động cơ chạy thuận 5s
      digitalWrite(input1, LOW);
      digitalWrite(input2, LOW);
      delay(100);
    }
    delay(100);
  }