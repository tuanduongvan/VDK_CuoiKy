// Kết nối động cơ A
int enableA = 3;
int input1 = 5;
int input2 = 4;

const int trigPin = 6; // chân trig của HC-SR04
const int echoPin = 7; // chân echo của HC-SR04
float tmprVal = 0;
float sinVal;
int toneVal;

void setup(){
  pinMode(enableA, OUTPUT);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  
  pinMode(trigPin, OUTPUT); // chân trig sẽ phát tín hiệu
  pinMode(echoPin, INPUT); // chân echo sẽ nhận tín hiệu
  Serial.begin(9600);
}
void loop(){
  unsigned long duration; // biến đo thời gian
  int distance;           // biến lưu khoảng cách

  digitalWrite(trigPin, LOW); // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // phát xung từ chân trig
  delayMicroseconds(10); // xung có độ dài 10 microSeconds
  digitalWrite(trigPin, LOW); // tắt chân trig
  duration = pulseIn(echoPin, HIGH);

 
  // Tính khoảng cách đến vật.
  distance = duration * 0.034 / 2;
    
  Serial.print(distance);
  Serial.println("cm"); 
   if(distance < 5){
    Serial.println("dong co quay nghich");
    // Điều khiển tốc độ động cơ
    analogWrite(enableA, 175);

    // Động cơ chạy thuận 5s
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    delay(3000);
    
    // Tắt 1 giây
    analogWrite(enableA, 0);
    delay(3000);
  }
  else{

    Serial.println("dong co quay thuan");
    // Điều khiển tốc độ động cơ
    analogWrite(enableA, 175);

    // Động cơ chạy nghịch 5s
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    delay(3000);

    // Tắt 1 giây
    analogWrite(enableA, 0);
    delay(3000);
  } 
    
}
