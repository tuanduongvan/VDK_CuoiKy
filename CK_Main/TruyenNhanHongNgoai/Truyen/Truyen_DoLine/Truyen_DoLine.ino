#define PIN_SEND 3
#include <IRremote.h> 
#define LINE 2

int val = 0;


void setup() { 
  pinMode(LINE, INPUT);
  Serial.begin(9600);
  IrSender.begin(PIN_SEND); 
} 
  
void loop() { 
  Serial.println("bat dau:");
  delay(2000);
  val = digitalRead(LINE);
  Serial.println(val);
  if (val == 0) {
    IrSender.sendNECRaw(0); 
    delay(200);
  }
  else{
    IrSender.sendNECRaw(1);
    delay(200);
  }

}
