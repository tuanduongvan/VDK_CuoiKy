#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>

// Cấu hình cảm biến khí gas
const int GasPin = A0; // Chân analog để đọc giá trị khí gas

// Cấu hình động cơ DC
const int enA = D6; // Chân PWM của động cơ
const int in1 = D8;
const int in2 = D7;
int stepAngle = 0;

// Thông tin Wi-Fi
const char* ssid = "Lavie1"; // Thay bằng SSID Wi-Fi
const char* password = "03102004"; // Thay bằng mật khẩu Wi-Fi

// Tạo server HTTP và WebSocket
ESP8266WebServer server(80);
WebSocketsServer webSocket(81);

// Biến lưu trạng thái
int gasValue = 0; // Giá trị khí gas

void setup() {
  // Cài đặt động cơ DC
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  // Kết nối Wi-Fi
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

  // Bắt đầu server
  server.on("/", handleRoot);
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  // Cập nhật server và WebSocket
  server.handleClient();
  webSocket.loop();

  // Đọc giá trị từ cảm biến khí gas
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 2000) {
    lastUpdate = millis();
    gasValue = analogRead(GasPin);
    Serial.print("Gia tri khi gas: ");
    Serial.println(gasValue);
    Serial.println("------------------");

    // Gửi dữ liệu đến WebSocket
    String data = "{\"gasValue\":" + String(gasValue) + "}";
    webSocket.broadcastTXT(data);
  }

  // Điều khiển động cơ DC dựa trên stepAngle
  if (stepAngle == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    delay(500);
  } else if (stepAngle == 1) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 255);
    delay(500);
  } else if (stepAngle == 2) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, 255);
    delay(500);
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
      <h2>Gas Value: <span id="gasValue">--</span></h2>
    </div>
    <div class="card">
      <h2>Control DC Motor</h2>
      <button onclick="quaytoi()">Quay tới</button>
      <button onclick="quaylui()">Quay lui</button>
    </div>
  </div>

  <script>

    const ws = new WebSocket(`ws://${location.hostname}:81/`);
    ws.onmessage = (event) => {
      const data = JSON.parse(event.data);
      document.getElementById('gasValue').innerText = data.gasValue;
    };

    function quaytoi() {
      ws.send(1);
    }

    function quaylui() {
      ws.send(2);
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

    // Ghi thông báo nhận được
    Serial.print("Received stepAngle: ");
    Serial.println(stepAngle);
  }
}
