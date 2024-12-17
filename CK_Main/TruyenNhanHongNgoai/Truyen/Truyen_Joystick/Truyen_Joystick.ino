#include <IRremote.h>
//START JOYSTICK VARIABLE
int JoyStickX = 1; //A1
int JoyStickY = 2; // A2
int JoyStickZ = 4;

bool joystick(int thresholdX = 550, int thresholdY = 550, int thresholdZ= 1) {
  int x, y, z;
  x = analogRead(JoyStickX);
  y = analogRead(JoyStickY);
  z = digitalRead(JoyStickZ);
  Serial.println("JOYSTICK " + String(x) + ", " + String(y) + ", " + String(z) );
  int valSent = 0;
  if (x >= thresholdX  || y>=thresholdY || z == thresholdZ) {
    return true;
  } else {
    return false;
  }
}
void setup() { 
  Serial.begin(9600);
  IrSender.begin(3); 
  pinMode(JoyStickZ, INPUT_PULLUP);
} 
void loop(){
  Serial.print("Sent ");
  if(joystick()){
  Serial.println("1");
    IrSender.sendNECRaw(1); 
    delay(200);
  } else {
  Serial.println("0");
    IrSender.sendNECRaw(0); 
    delay(200);
  }
}