#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX của HC-05

void setup() {
  pinMode(9, OUTPUT);             // Chân 9 dùng để đặt HC-05 vào chế độ AT
  digitalWrite(9, HIGH);          // Đặt HIGH để bật chế độ AT mode
  Serial.begin(9600);             // Kết nối với Serial Monitor
  Serial.println("Enter AT commands:");
  BTSerial.begin(38400);          // Tốc độ mặc định của HC-05 trong chế độ AT
}

void loop() {
  // Đọc từ HC-05 và gửi lên Serial Monitorat
  if (BTSerial.available()) {
    Serial.write(BTSerial.read());
  }

  // Đọc từ Serial Monitor và gửi tới HC-05
  if (Serial.available()) {
    BTSerial.write(Serial.read());
  }
}