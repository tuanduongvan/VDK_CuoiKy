#include <Servo.h> 
#define Servo_PWM 6 
#define LINE 2

Servo MG995_Servo; 
int val = 0;

void setup(){
  MG995_Servo.attach(6);
  Serial.begin(9600);
}
void loop(){
  val = digitalRead(LINE);
  Serial.println(val);
   if(val == 0){
    MG995_Servo.write(180); 
    delay(2000);
  }
  else{
    
    MG995_Servo.write(0);
    delay(2000);
  } 
  
    
}
