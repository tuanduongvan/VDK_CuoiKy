#include <SoftwareSerial.h>
#include"DHT.h"
const int DHTPIN=4;
const int DHTTYPE=DHT11;
SoftwareSerial BTSerial(10, 11);
DHT dht(DHTPIN, DHTTYPE);
void setup() {

  Serial.begin(9600);
  BTSerial.begin(38400);
  dht.begin();
}

void loop() {
  unsigned long duration; // biến đo thời gian
  int distance;           // biến lưu khoảng cách
  /* Phát xung từ chân trig */
  float h=dht.readHumidity();
  float t=dht.readTemperature();
  Serial.print("Nhiet do: ");
  Serial.println(t);
  Serial.print("Do am: ");
  Serial.println(h);
  
  // Gửi dữ liệu qua Bluetooth
  if (h > 90 || t>33) {
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
