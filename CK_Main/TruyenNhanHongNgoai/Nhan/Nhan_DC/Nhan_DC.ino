#include <IRremote.h>
#define PIN_RECV 2
#define MAX_SPEED 255  //từ 0-255
#define MIN_SPEED 0 

IRrecv receiver(PIN_RECV);
decode_results output;

// Kết nối động cơ A
int IN1 = 5;
int IN2 = 4;

void Lui(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);  
  digitalWrite(IN1, LOW);                      
  analogWrite(IN2, speed);
}
void Dung() {// Hàm dừng motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
void Tien(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED); //đảm báo giá trị nằm trong một khoảng từ 0 - MAX_SPEED 
  analogWrite(IN1, speed); 
  digitalWrite(IN2, LOW);
}
void NhanhDan(){
  for (int i = 0 ; i <= 255 ; i++){
    analogWrite(IN1 , i);
    digitalWrite(IN2 , LOW);
    delay(50);
  }
}
void ChamDan(){
  for (int i = 255; i >= 0 ; i--){
    analogWrite(IN1 , i);
    digitalWrite(IN2 , LOW);
    delay(50);
  }
}

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  Serial.begin(9600);
  IrReceiver.begin(PIN_RECV, ENABLE_LED_FEEDBACK);
}

void loop() {
  //  Serial.println("Received something...");
  //  Serial.println();
  //  Serial.println(IrReceiver.decode());
  if (IrReceiver.decode()) {
    uint32_t val = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(val);
    if (val == 1) {
      Serial.println("decode");
      // Động cơ chạy thuận 5s
      Tien(255);
      delay(1000);
    } else if (val == 0) {
      Serial.println("decoode2");
      Lui(255);
      delay(1000);
    }
    IrReceiver.resume();
  }
}
