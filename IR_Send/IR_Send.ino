#include <IRremote.h>
const int IR_SEND_PIN = 8;

const int LINE = 3;      // Chân kết nối với cảm biến line (digital sensor)
int val = 0;

void setup() {
  Serial.begin(9600); 
  pinMode(LINE, INPUT);

  IrSender.begin(IR_SEND_PIN);
  IrSender.enableIROut(38);
}

void loop() {
  val = digitalRead(LINE);
  Serial.print("Giá trị cảm biến: ");
  Serial.println(val);

  uint8_t sAddress = 0x00;
  uint8_t sCommand = (val == 0) ? 0x02 : 0x01;
  uint8_t sRepeats = 0;
  
  Serial.print("Send now: address=0x00, command=0x");
  Serial.print(sCommand, HEX);
  Serial.println();

  IrSender.sendRC5(sAddress, sCommand, sRepeats, false);
  Serial.println("Sent");
  delay(1000);
}