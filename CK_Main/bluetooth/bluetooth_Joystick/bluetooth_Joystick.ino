#include <SoftwareSerial.h>

int XPin = A0; // Chân analog đọc trục X của joystick
int YPin = A1; // Chân analog đọc trục Y của joystick
int xVal, yVal;
SoftwareSerial BTSerial(10, 11); // Khởi tạo Bluetooth Serial trên chân 10 và 11

void setup() {
  Serial.begin(9600);      // Serial monitor để debug
  BTSerial.begin(38400);   // Bluetooth module
}

void loop() {
  // Đọc giá trị từ joystick
  xVal = analogRead(XPin);
  yVal = analogRead(YPin);

  // Hiển thị giá trị trục X và Y lên Serial Monitor
  Serial.print("X: ");
  Serial.print(xVal);
  Serial.print(" Y: ");
  Serial.println(yVal);

  // Gửi dữ liệu qua Bluetooth nếu xVal và yVal lớn hơn 700
  if (xVal > 700 && yVal > 700) {
    BTSerial.print("1");
  } else {
    BTSerial.print("0");
  }

  // Kiểm tra và chuyển tiếp dữ liệu từ Bluetooth đến Serial Monitor
  if (BTSerial.available()) {
    Serial.write(BTSerial.read());
  }
  if (Serial.available()) {
    BTSerial.write(Serial.read());
  }

  // Thêm độ trễ sau mỗi chu kỳ đo
  delay(800); // Độ trễ 100ms
}