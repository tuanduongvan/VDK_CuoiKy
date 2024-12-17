#include <Servo.h>
#include <SoftwareSerial.h>

Servo myservo;
SoftwareSerial BTSerial(10, 11); // Pin 10 (TX), Pin 11 (RX)

int pinServo = 6; // Chân điều khiển servo

void setup() {
  myservo.attach(pinServo);       // Gắn servo vào chân 6
  myservo.write(0);               // Đặt servo về 0 độ
  Serial.begin(9600);             // Giao tiếp với Serial Monitor
  BTSerial.begin(38400);          // Baud rate cho Bluetooth
  Serial.println("Slave is ready."); // Thông báo trạng thái
}

void loop() {
  // Kiểm tra nếu có dữ liệu từ Bluetooth
  if (BTSerial.available()) {
    char t = BTSerial.read(); // Đọc ký tự từ Bluetooth
    Serial.print("Received from master: ");
    Serial.println(t);        // Hiển thị ký tự nhận được

    // Xử lý dữ liệu nhận được
    if (t == 'a') {
      Serial.println("Moving servo to 180 degrees...");
      for (int i = 0; i <= 180; i += 30) {
        myservo.write(i); // Di chuyển servo
        delay(200);       // Chờ 200ms
      }
    } else if (t == 'b') {
      Serial.println("Returning servo to 0 degrees...");
      for (int i = 180; i >= 0; i -= 30) {
        myservo.write(i); // Di chuyển servo ngược lại
        delay(200);       // Chờ 200ms
      }
    } else {
      // Xử lý dữ liệu không hợp lệ
      Serial.println("Invalid command received!");
    }
  }

  // Gửi dữ liệu từ Serial Monitor tới Bluetooth (nếu có)
  if (Serial.available()) {
    char data = Serial.read();  // Đọc dữ liệu từ Serial Monitor
    BTSerial.write(data);       // Gửi dữ liệu tới Bluetooth
    Serial.print("Forwarded to master: ");
    Serial.println(data);
  }
}