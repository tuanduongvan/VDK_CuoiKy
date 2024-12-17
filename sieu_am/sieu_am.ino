const int trig = 6;
const int echo = 3;
long duration;
long distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration / 2 * 0.034;

  Serial.print("Distance: ");
  Serial.println(distance);
  delay(200);



}
