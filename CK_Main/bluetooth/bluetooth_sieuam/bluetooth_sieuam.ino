#include <SoftwareSerial.h>

const int trig = 8; // chân trig
const int echo = 7; // chân echo
SoftwareSerial BTSerial(10, 11);

void setup() {
  pinMode(trig, OUTPUT); // chân trig sẽ phát tín hiệu
  pinMode(echo, INPUT);  // chân echo sẽ nhận tín hiệu

  Serial.begin(9600);
  BTSerial.begin(38400);
}

void loop() {
  unsigned long duration; // biến đo thời gian
  int distance;           // biến lưu khoảng cách
  /* Phát xung từ chân trig */
  digitalWrite(trig, 0);
  delayMicroseconds(2);
  digitalWrite(trig, 1);
  delayMicroseconds(10);
  digitalWrite(trig, 0);

  // Đo độ rộng xung HIGH ở chân echo.
  duration = pulseIn(echo, HIGH);
  // distance = (time * speed of sound) / 2
  distance = int(duration * 0.034 / 2);
  Serial.print(distance);
  Serial.println("cm");
  
  // Gửi dữ liệu qua Bluetooth
  if (distance > 20) {
    BTSerial.print("0");
  } else {
    BTSerial.print("1");
  }

  // Kiểm tra và chuyển tiếp dữ liệu từ Bluetooth đến Serial Monitor
  if (BTSerial.available()) {
    Serial.write(BTSerial.read());
  }
  if (Serial.available()) {
    BTSerial.write(Serial.read());
  }

  // Thêm độ trễ sau mỗi chu kỳ đo
  delay(500); // độ trễ 500ms (nửa giây)
}
