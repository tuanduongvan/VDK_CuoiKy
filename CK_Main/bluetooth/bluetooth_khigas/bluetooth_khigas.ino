#include <SoftwareSerial.h>
int GasPin=0;
int val;
SoftwareSerial BTSerial(10, 11);
void setup() {

  Serial.begin(9600);
  BTSerial.begin(38400);
}

void loop() {
  val=analogRead(GasPin);
  Serial.println(val,DEC);

  
  // Gửi dữ liệu qua Bluetooth
  if (val > 500) {
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
  delay(200); // độ trễ 500ms (nửa giây)
}
