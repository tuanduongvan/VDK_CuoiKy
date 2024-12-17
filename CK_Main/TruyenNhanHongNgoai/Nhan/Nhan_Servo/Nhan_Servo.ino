#include <IRremote.h>
#include <Servo.h>
#define PIN_RECV 2

Servo myservo;
IRrecv receiver(PIN_RECV);
decode_results output;
int servo_pin = 9;

void setup() {
  myservo.attach(servo_pin);
  Serial.begin(9600);
  IrReceiver.begin(PIN_RECV, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    uint32_t val = IrReceiver.decodedIRData.decodedRawData; // Lấy giá trị mã NEC
    Serial.println(val, HEX); // In giá trị dưới dạng hệ 16 để dễ kiểm tra

    if (val == 1) { // So sánh với mã NEC tương ứng
      Serial.println("decode");
      myservo.write(120);
      delay(500);
      myservo.write(0);
      delay(500);
    } else if (val == 0) {
      Serial.println("decode2");
      myservo.write(0);
      delay(500);
    }
    IrReceiver.resume(); // Chuẩn bị nhận tín hiệu mới
  }
}
