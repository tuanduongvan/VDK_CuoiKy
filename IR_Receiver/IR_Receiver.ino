#include <IRremote.hpp>
#include <Servo.h>

Servo myservo;
const int IR_RECEIVE_PIN = 8;

void setup() {
    Serial.begin(9600);
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);
    
    myservo.attach(11);
    myservo.write(0);
    delay(2000);
}

void loop() {
    Serial.println(IrReceiver.decode());
    if (IrReceiver.decode()) {
        Serial.println(IrReceiver.decodedIRData.command);
        IrReceiver.resume();
        
        if (IrReceiver.decodedIRData.command == 0x01) {
            // Quét servo từ 0 đến 180 độ, tăng dần 30 độ mỗi lần
            for (int i = 0; i <= 180; i += 30) {
              myservo.write(i); // Chuyển servo đến góc i
              delay(200); // Dừng 200ms để servo ổn định
            }

        } else if (IrReceiver.decodedIRData.command == 0x02) {
            // Quét servo từ 180 đến 0 độ, giảm dần 30 độ mỗi lần
            for (int i = 180; i >= 0; i -= 30) {
              myservo.write(i); // Chuyển servo đến góc i
              delay(200); // Dừng 200ms để servo ổn định
            }
        }
    }
    delay(500);
}