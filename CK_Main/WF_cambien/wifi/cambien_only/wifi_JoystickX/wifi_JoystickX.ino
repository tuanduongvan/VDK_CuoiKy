#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Network credentials
const char *SSID = "ESP8266-LQ";
const char *PSWD = "";

// Joystick
const int JOYSTICK_X_PIN = A0; // Chân analog của joystick cho trục X

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  // WiFi softAP
  WiFi.softAP(SSID, PSWD);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("http://");
  Serial.print(myIP);
  Serial.println("/");

  // Web server routes
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>ESP8266 Joystick Server</title>
  <style>
    html {
      font-family: Arial, sans-serif;
      display: inline-block;
      margin: 0 auto;
      text-align: center;
    }
    h1 {
      color: #0F3376;
      padding: 2vh;
    }
    p {
      font-size: 1.5rem;
    }
  </style>
</head>
<body>
  <h1>ESP8266 Joystick Server</h1>
  <h2>Joystick X Value</h2>
  <p>
    <span id="joystick-x">Loading...</span>
  </p>
  <script>
    setInterval(() => {
      fetch('/joystick-x')
        .then(response => response.text())
        .then(xValue => {
          document.getElementById("joystick-x").textContent = xValue;
        });
    }, 200);
  </script>
</body>
</html>
    )rawliteral");
  });

  server.on("/joystick-x", HTTP_GET, [](AsyncWebServerRequest *request) {
    int joystickXValue = analogRead(JOYSTICK_X_PIN); // Đọc giá trị từ joystick trục X
    String xValue = String(joystickXValue); // Chuyển giá trị thành chuỗi
    request->send(200, "text/plain", xValue); // Gửi giá trị x về cho client
  });

  server.begin();
}

void loop() {
  // Đọc giá trị từ joystick và hiển thị lên Serial Monitor
  int joystickXValue = analogRead(JOYSTICK_X_PIN); // Đọc giá trị từ joystick trục X
  Serial.print("Joystick X Value: ");
  Serial.println(joystickXValue); // Hiển thị giá trị của trục X trên Serial Monitor
  
  delay(500); // Đợi một khoảng thời gian trước khi đọc lại giá trị
}
