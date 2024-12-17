#include <SoftwareSerial.h>

// Khai báo các chân điều khiển động cơ DC
const int IN1 = 5;
const int IN2 = 6;
const int ENA = 7;

// Khai báo đối tượng SoftwareSerial
SoftwareSerial BTSerial(10, 11); // RX, TX

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT); // Chân PWM điều khiển tốc độ

  pinMode(9, OUTPUT); // Chân 9 dùng để đặt HC-05 vào chế độ AT
  pinMode(13, OUTPUT); // LED điều khiển

  Serial.begin(9600); // Giao tiếp với Serial Monitor
  BTSerial.begin(38400); // Baud rate cho Bluetooth

  // Đặt động cơ ở trạng thái dừng ban đầu
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0); // Tắt động cơ
}

void loop() {
  // Kiểm tra tín hiệu từ Bluetooth
  while (BTSerial.available()) {
    char t = BTSerial.read();

    // Hiển thị tín hiệu nhận được
    Serial.print("Received from master: ");
    Serial.println(t);

    if (t == '0') {
      digitalWrite(13, HIGH); // Bật LED
      Serial.println("LED ON, Motor rotating CW...");

      // Quay động cơ theo chiều kim đồng hồ
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 128); // Tốc độ trung bình (có thể điều chỉnh giá trị từ 0-255)
    } 
    else if (t == '1') {
      digitalWrite(13, LOW); // Tắt LED
      Serial.println("LED OFF, Motor rotating CCW...");

      // Quay động cơ ngược chiều kim đồng hồ
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(ENA, 128); // Tốc độ trung bình (có thể điều chỉnh giá trị từ 0-255)
    } 
    else if (t == '2') {
      Serial.println("Motor stopped.");

      // Dừng động cơ
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 0);
    }
    delay(200); // Để đảm bảo động cơ hoạt động ổn định
  }

  // Chuyển dữ liệu từ Serial Monitor tới Bluetooth
  while (Serial.available()) {
    char data = Serial.read();
    BTSerial.write(data);
  }
}