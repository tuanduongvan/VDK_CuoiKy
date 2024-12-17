#include <IRremote.h>
int val = 0;
int LIGHT = 0;

void setup() { 
  Serial.begin(9600);
  IrSender.begin(3); 
} 
  
void loop() {
  delay(1000);
  val = analogRead(LIGHT);
  Serial.println(val);
  if (val > 900) {
    IrSender.sendNECRaw(0); 
    delay(200);
  }
  else{
    IrSender.sendNECRaw(1);
    delay(200);
  }
      
}
