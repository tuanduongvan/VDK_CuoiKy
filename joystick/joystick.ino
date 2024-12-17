int VRx = 1;
int VRy = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int x = analogRead(VRx);
  int y = analogRead(VRy);
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(", Y: ");
  Serial.println(y);

  delay(200);


}
