int val = 0;
int lightpin = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(lightpin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(lightpin);
  Serial.println(val);
  delay(200);
}
