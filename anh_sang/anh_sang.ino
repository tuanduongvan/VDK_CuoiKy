//3 chân: 1VCC, 1GND, 1 light(A)

int light = 0;
int val = 0;
int led = 13;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);  

}

void loop() {
  // put your main code here, to run repeatedly:

  val = analogRead(light);
  Serial.println(val);
  if(val > 900)
  {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }
  delay(200);

}
