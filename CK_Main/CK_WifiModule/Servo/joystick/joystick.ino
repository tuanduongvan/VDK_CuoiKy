#include <ESP8266WiFi.h> 
#include <ESP8266WebServer.h> 
#include <WebSocketsServer.h> 
#include <Servo.h>

Servo myServo; 

int JoyStick_x = A0;
int JoyStick_z = D1;
int servoPin = D5;

// Thông tin Wi-Fi 
const char* ssid = "Lavie1"; // Thay bằng SSID Wi-Fi 
const char* password = "03102004"; // Thay bằng mật khẩu Wi-Fi 

// Tạo server HTTP và WebSocket 
ESP8266WebServer server(80); 
WebSocketsServer webSocket(81); 

// Biến lưu trạng thái 
int val_x = 0; 
int val_z = 0;  
int stepAngle = 0;       // Góc quay (°) 
bool motorRunning = false; // Trạng thái động cơ 

void setup() { 
  myServo.attach(servoPin, 500, 2500); // 0.5ms đến 2.5ms
  myServo.write(0);

  pinMode(JoyStick_z, INPUT_PULLUP);

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

  // Cập nhật thông tin nhiệt độ và độ ẩm 
  static unsigned long lastUpdate = 0; 
  if (millis() - lastUpdate > 1000) { 
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

  // Quay động cơ liên tục nếu trạng thái đang chạy 
  if (motorRunning) { 
    myServo.write((int)stepAngle);
    delay(1000); 
    myServo.write(0);
    delay(1000);
  } 

  delay (500);
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
      <h2>Val x: <span id="val_x">--</span></h2> 
      <h2>Val z: <span id="val_z">--</span></h2> 
    </div> 
    <div class="card"> 
      <h2>Control Stepper Motor</h2> 
      <input type="number" id="angle" placeholder="Enter angle (°)" /> 
      <button onclick="sendAngle()">Rotate</button> 
    </div> 
  </div> 
  <script> 
    const ws = new WebSocket(`ws://${location.hostname}:81/`); 
    ws.onmessage = (event) => { 
      const data = JSON.parse(event.data); 
      document.getElementById('val_x').innerText = data.val_x.toFixed(1); 
      document.getElementById('val_z').innerText = data.val_z.toFixed(1);  
    }; 

    function sendAngle() { 
      const angle = document.getElementById('angle').value; 
      ws.send(angle); 
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

    // Kiểm tra nếu góc = 0 thì dừng động cơ 
    if (stepAngle <= 0) { 
      motorRunning = false; 
    } else if (stepAngle > 180) { 
      motorRunning = true; 
      stepAngle = 180;
    } else {
      motorRunning = true;
    }

    // Ghi thông báo nhận được 
    Serial.print("Received angle: "); 
  } 
} 