#include <ESP8266WebServer.h>  
#include <WebSocketsServer.h>  
#include "DHT.h"  
const int DHTPIN = D1; // GPIO5 (D1)  
const int DHTTYPE = DHT11;  
DHT dht(DHTPIN, DHTTYPE);
const int enA = D6; // Chân PWM của động cơ 
const int in1 = D8;  
const int in2 = D7;  
int stepAngle = 0; 

const char* ssid = "Lavie1"; // Thay bằng SSID Wi-Fi  
const char* password = "03102004"; // Thay bằng mật khẩu Wi-Fi  

ESP8266WebServer server(80);  
WebSocketsServer webSocket(81);  
float temperature = 0;  
float humidity = 0;   

void setup() {  
  pinMode(enA, OUTPUT); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  // Tắt động cơ ban đầu 
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  dht.begin();  
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
  if (millis() - lastUpdate > 2000) { 
    lastUpdate = millis();  
    temperature = dht.readTemperature();  
    Serial.print("Nhiet do: ");  
    Serial.println(temperature);  
    humidity = dht.readHumidity();  
    Serial.print("Do am: ");  
    Serial.println(humidity); 
    Serial.println("------------------");  
    // Gửi dữ liệu đến WebSocket  
    String data = "{\"temperature\":" + String(temperature) +  
                  ",\"humidity\":" + String(humidity) + "}";  
    webSocket.broadcastTXT(data);  
  }  
  // Quay động cơ liên tục nếu trạng thái đang chạy  
  if (stepAngle == 0) {  
    digitalWrite(in1, LOW); 
    digitalWrite(in2, LOW); 
    delay(500); 
  }  
  else if (stepAngle == 1) {  

    digitalWrite(in1, HIGH); 
    digitalWrite(in2, LOW); 
    analogWrite(enA, 255); 
    delay(500); 
  } 
  else if(stepAngle == 2) {  
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

      <h2>Temperature: <span id="temperature">--</span> °C</h2>  

      <h2>Humidity: <span id="humidity">--</span> %</h2>  

    </div>  

    <div class="card">  

      <h2>Quay tới và quay lui</h2>    

      <button onclick="quaytoi()" id="quaytoi">Quay tới</button> 
      <button onclick="quaylui()" id="quaylui">Quay lui</button>

    </div>  

  </div>  

  <script>  

    const ws = new WebSocket(`ws://${location.hostname}:81/`);  

    ws.onmessage = (event) => {  

      const data = JSON.parse(event.data);  

      document.getElementById('temperature').innerText = data.temperature.toFixed(1);  

      document.getElementById('humidity').innerText = data.humidity.toFixed(1);  

    };  

  

    function quaytoi() {    

      ws.send(1);   

    }  

    function quaylui() {  

      const angle = document.getElementById('quaylui').value;  

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

  

    // Kiểm tra nếu góc = 0 thì dừng động cơ  

    
  

    // Ghi thông báo nhận được  

    Serial.print("Received type: ");  

    Serial.println(stepAngle);  

  }  

} 