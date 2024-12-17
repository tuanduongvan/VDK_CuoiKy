#define PIN_SEND 3
#include <IRremote.h> 

int GasPin = 0;
int val;

void setup() { 
  Serial.begin(9600);
  IrSender.begin(PIN_SEND); 
} 
  
void loop() { 
  delay(2000);
  val = analogRead(GasPin);
  Serial.println(val, DEC);
  if (val > 210) {
    IrSender.sendNECRaw(1); 
    delay(200);
  }
  else{
    IrSender.sendNECRaw(0); 
    delay(200);
  }
      
}
