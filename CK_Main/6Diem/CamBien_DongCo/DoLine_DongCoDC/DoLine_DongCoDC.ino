#define LINE 2
int enableA = 3;
int input1 = 5;
int input2 = 4;
int val = 0;

void setup(){
  pinMode(enableA, OUTPUT);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  Serial.begin(9600);
}
void loop(){
 val = digitalRead(LINE);
  Serial.println(val);
   if(val == 0){ 
    analogWrite(enableA, 70);

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
    analogWrite(enableA, 75);

    // Động cơ chạy nghịch 5s
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
    delay(5000);

    // Tắt 1 giây
    analogWrite(enableA, 0);
    delay(3000);
  } 
  
    
}
