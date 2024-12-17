#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX
int echoPin = 3;
int trigPin = 4;
long duration;
int distance;
int previousState = 0; // Lưu trạng thái trước đó (0 = không gửi lệnh, 1 = gửi "90", 2 = gửi "180")

void setup() {
  Serial.begin(9600);       // Serial monitor
  BTSerial.begin(38400);     // Khởi động giao tiếp Bluetooth
  Serial.println("Master ready!");
  pinMode(echoPin , INPUT);
  pinMode(trigPin , OUTPUT);
}

void loop() {
  // Đo khoảng cách từ cảm biến siêu âm
  digitalWrite(trigPin , LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin , HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin , LOW);
  duration = pulseIn(echoPin , HIGH);
  distance  = duration * 0.034 / 2; // Tính khoảng cách
  Serial.println(distance);

  // Gửi lệnh "90" hoặc "180" chỉ khi có thay đổi trạng thái
  if (distance <= 20 && previousState != 1) {
    BTSerial.write('a');
    Serial.println("Sent: a");
    previousState = 1; // Cập nhật trạng thái
  } 
  else if (distance > 20 && previousState != 2) {
    BTSerial.write('b');
    Serial.println("Sent: b");
    previousState = 2; // Cập nhật trạng thái
  }

  delay(200); // Tăng delay để giảm tần suất gửi lệnh
}


