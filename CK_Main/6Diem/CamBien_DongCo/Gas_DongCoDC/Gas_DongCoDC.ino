int enableA = 3;
int input1 = 5;
int input2 = 4;

int GasPin = 0;
int val;

void setup() {
  pinMode(enableA, OUTPUT);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(GasPin);
  Serial.println(val, DEC);
  if(val > 850){
    // Điều khiển tốc độ động cơ
    analogWrite(enableA, 175);

    // Động cơ chạy thuận 5s
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    delay(5000);
    
    // Tắt 1 giây
    analogWrite(enableA, 0);
    delay(3000);
  }
  else{
    // Điều khiển tốc độ động cơ
    analogWrite(enableA, 175);

    // Động cơ chạy nghịch 5s
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    delay(5000);

    // Tắt 1 giây
    analogWrite(enableA, 0);
    delay(3000);
  }
}
