#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>

const int enA = D6; // Chân PWM của động cơ
const int in1 = D8;
const int in2 = D7;

const int trigPin = D0;
const int echoPin = D1;

int stepAngle = 0;
// Biến lưu trạng thái 
long duration;
float d_cm; 

const char* ssid = "anhtuan"; // Thay bằng SSID Wi-Fi
const char* password = "33333333"; // Thay bằng mật khẩu Wi-Fi

ESP8266WebServer server(80);
WebSocketsServer webSocket(81);

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Tắt động cơ ban đầu
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  Serial.begin(115200);
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  server.handleClient();
  webSocket.loop();

  static unsigned long lastUpdate = 0; 
  if (millis() - lastUpdate > 1000) { 
    lastUpdate = millis(); 
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    d_cm = duration * 0.034 / 2;
    Serial.print("Distance: ");
    Serial.print(d_cm);
    Serial.println("cm");
    
    // Gửi dữ liệu đến WebSocket 
    String data = "{\"d_cm\":" + String(d_cm) + ",\"stepAngle\":" + String(stepAngle) + "}";
    webSocket.broadcastTXT(data); 
  }
}

void handleRoot() {
  // Tạo giao diện HTML
  String htmlPage = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>SmartHome Control</title>
  <style>
    body { font-family: Arial, sans-serif; text-align: center; }
    .container { max-width: 600px; margin: 50px auto; }
    .card { border: 1px solid #ddd; padding: 20px; margin: 20px; border-radius: 10px; }
    input, button { padding: 10px; margin: 10px; font-size: 16px; }
  </style>
</head>
<body>
  <div class="container">
    <h1>SmartHome Control</h1>
    <div class="card">
      <h2>Ultrasonic Sensor</h2>
      <p>Distance: <span id="distance">--</span> cm</p>
    </div>
    <div class="card">
      <h2>Motor Control</h2>
      <button onclick="controlMotor(1)">Forward</button>
      <button onclick="controlMotor(2)">Reverse</button>
      <button onclick="controlMotor(0)">Stop</button>
      <p>Current State: <span id="motorState">Stopped</span></p>
    </div>
  </div>
  <script>
    const ws = new WebSocket(`ws://${location.hostname}:81/`);
    ws.onmessage = (event) => {
      const data = JSON.parse(event.data);
      document.getElementById('distance').innerText = data.d_cm.toFixed(2);
      const motorStates = ["Stopped", "Forward", "Reverse"];
      document.getElementById('motorState').innerText = motorStates[data.stepAngle];
    };

    function controlMotor(state) {
      ws.send(state);
    }
  </script>
</body>
</html>
  )rawliteral";

  server.send(200, "text/html", htmlPage);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  if (type == WStype_TEXT) {
    String message = String((char*)payload);
    stepAngle = message.toInt();
    Serial.print("Received state: ");
    Serial.println(stepAngle);

    if (stepAngle == 0) {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
    } else if (stepAngle == 1) {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, 255);
    } else if (stepAngle == 2) {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(enA, 255);
    }
  }
}
