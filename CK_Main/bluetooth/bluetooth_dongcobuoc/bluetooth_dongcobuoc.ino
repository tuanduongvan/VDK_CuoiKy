#include <SoftwareSerial.h>
#include <Stepper.h>

// Số bước cho mỗi vòng quay của động cơ bước 28BYJ-48
const int stepsPerRevolution = 2048;

// Khai báo đối tượng Stepper, chân điều khiển là 2, 4, 3, 5
Stepper myStepper(stepsPerRevolution, 3, 5, 4, 6);

// Khai báo đối tượng SoftwareSerial để giao tiếp Bluetooth
SoftwareSerial BTSerial(10, 11); // RX, TX

void setup() {
  pinMode(9, OUTPUT); // Chân 9 dùng để đặt HC-05 vào chế độ AT

  pinMode(13, OUTPUT); // Cấu hình pin 13 làm OUTPUT (LED điều khiển)
  myStepper.setSpeed(10); // Đặt tốc độ quay cho động cơ bước

  Serial.begin(9600); // Giao tiếp với Serial Monitor
  BTSerial.begin(38400); // Baud rate cho Bluetooth
}

void loop() {
  if (BTSerial.available()) {
    // Đọc giá trị mới nhất từ buffer
    char t;
    while (BTSerial.available()) {
      t = BTSerial.read(); // Lấy giá trị cuối cùng
    }

    // In giá trị nhận được từ master
    Serial.print("Received from master: ");
    Serial.println(t);

    if (t == '0') {
      digitalWrite(13, HIGH); // Bật LED
      Serial.println("LED ON, Motor rotating CW...");

      // Quay theo góc 90 độ theo chiều kim đồng hồ
      int stepsToMove = (180.0 / 360.0) * stepsPerRevolution; // Quay 90 độ
      myStepper.step(stepsToMove);
      delay(200);

    } else if (t == '1') {
      digitalWrite(13, LOW); // Tắt LED
      Serial.println("LED OFF, Motor rotating CCW...");

      // Quay theo góc 90 độ ngược chiều kim đồng hồ
      int stepsToMove = (180.0 / 360.0) * stepsPerRevolution; // Quay 90 độ
      myStepper.step(-stepsToMove);
      delay(200);
    }
    Serial.flush(); // Đảm bảo in ra ngay lập tức
  }
}
