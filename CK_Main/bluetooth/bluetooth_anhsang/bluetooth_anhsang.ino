#include <SoftwareSerial.h>

const int LIGHT_SENSOR_PIN = A0; // Chân analog dùng để đọc giá trị từ cảm biến ánh sáng
SoftwareSerial BTSerial(10, 11); // RX, TX cho Bluetooth

void setup() {
  Serial.begin(9600); // Giao tiếp với Serial Monitor
  BTSerial.begin(38400); // Baud rate cho Bluetooth
}

void loop() {
  // Đọc giá trị từ cảm biến ánh sáng
  int lightValue = analogRead(LIGHT_SENSOR_PIN);

  // In ra Serial Monitor
  Serial.print("Light value: ");
  Serial.println(lightValue);

  // Gửi tín hiệu qua Bluetooth
  if (lightValue > 900) { // Ngưỡng ánh sáng, tùy chỉnh theo thực tế
    BTSerial.print("1"); // Ánh sáng mạnh
  } else {
    BTSerial.print("0"); // Ánh sáng yếu
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
