#include <SoftwareSerial.h>

const int LINE_SENSOR_PIN = 7; // Chân digital dùng để đọc giá trị từ cảm biến dò line
SoftwareSerial BTSerial(10, 11); // RX, TX cho Bluetooth

void setup() {
  pinMode(LINE_SENSOR_PIN, INPUT); // Cảm biến dò line nối với chân digital 7
  Serial.begin(9600); // Giao tiếp với Serial Monitor
  BTSerial.begin(38400); // Baud rate cho Bluetooth
}

void loop() {
  // Đọc giá trị từ cảm biến dò line
  int lineValue = digitalRead(LINE_SENSOR_PIN); 

  // In ra Serial Monitor
  Serial.print("Line value: ");
  Serial.println(lineValue);

  // Gửi tín hiệu qua Bluetooth
  if (lineValue == HIGH) { // Nếu phát hiện vạch
    BTSerial.print("1"); // Gửi "1"
  } else {
    BTSerial.print("0"); // Gửi "0"
  }

  // Chuyển dữ liệu từ Bluetooth tới Serial Monitor
  while (BTSerial.available()) {
    char data = BTSerial.read();
    Serial.write(data); 
  }

  // Chuyển dữ liệu từ Serial Monitor tới Bluetooth
  while (Serial.available()) {
    char data = Serial.read();
    BTSerial.write(data);
  }

  delay(500); // Để dễ quan sát
}
