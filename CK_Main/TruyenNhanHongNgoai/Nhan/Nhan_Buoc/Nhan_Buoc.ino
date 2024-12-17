#include <IRremote.h>
#include "Stepper.h"
#define PIN_RECV 2

const int stepsPerRevolution = 2048;
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

IRrecv receiver(PIN_RECV);
decode_results output;

int degreeToSteps(int degree, int STEPS = 2048){
  if (degree == 0) return 0;
  return STEPS / (360/degree);
}

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(PIN_RECV, ENABLE_LED_FEEDBACK);
  myStepper.setSpeed(15);
}

void loop() {
  //  Serial.println("Received something...");
  if (IrReceiver.decode()) {
    uint32_t val = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(val);
    if (val == 1) {
      Serial.print("decode");
      myStepper.step(degreeToSteps(90));
      // IrReceiver.resume();
    } else if (val == 0) {
      Serial.print("decode2");
      myStepper.step(degreeToSteps(-90));
      // IrReceiver.resume();
    }
    IrReceiver.resume();
  }
}
