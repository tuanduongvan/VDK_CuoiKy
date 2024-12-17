int enableA = 3;
int input1 = 5;
int input2 = 4;
const int InfraredPin = 2;

void setup() {
  pinMode(InfraredPin, INPUT);
  pinMode(enableA, OUTPUT);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(InfraredPin) == HIGH){
    // Điều khiển tốc độ động cơ
    analogWrite(enableA, 175);

    // Động cơ chạy thuận 5s
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    delay(5000);
    Serial.println("YES");
    
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
    Serial.println("NO");
    
    // Tắt 1 giây
    analogWrite(enableA, 0);
    delay(3000);
  }
}
