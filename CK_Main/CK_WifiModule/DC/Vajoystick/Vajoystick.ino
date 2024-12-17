#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>

const int enA = D6; // Chân PWM của động cơ
const int in1 = D8;
const int in2 = D7;

int JoyStick_x = A0;
int JoyStick_z = D1;

int stepAngle = 0;
// Biến lưu trạng thái 
int val_x = 0; 
int val_z = 0; 

const char* ssid = "yw.hnaht"; // Thay bằng SSID Wi-Fi
const char* password = "huythanhcute"; // Thay bằng mật khẩu Wi-Fi

ESP8266WebServer server(80);
WebSocketsServer webSocket(81);

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(JoyStick_z, INPUT_PULLUP);

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
  if (millis() - lastUpdate > 200) { 
    lastUpdate = millis(); 
    val_x = analogRead(JoyStick_x);
    val_z = digitalRead(JoyStick_z); 
    Serial.print("X: ");
    Serial.print(val_x);
    Serial.print(" | Z: ");
    Serial.println(val_z);
    Serial.println("------------------"); 
 
    // Gửi dữ liệu đến WebSocket 
    String data = "{\"val_x\":" + String(val_x) + ",\"val_z\":" + String(val_z) + "}";

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
      <h2>Joystick Data</h2>
      <p>X-Axis: <span id="val_x">--</span></p>
      <p>Z-Axis: <span id="val_z">--</span></p>
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
      document.getElementById('val_x').innerText = data.val_x; 
      document.getElementById('val_z').innerText = data.val_z; 
    };

    function controlMotor(state) {
      ws.send(state);
      const stateText = state === 1 ? 'Forward' : state === 2 ? 'Reverse' : 'Stopped';
      document.getElementById('motorState').innerText = stateText;
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