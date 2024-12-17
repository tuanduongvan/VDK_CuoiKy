#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Stepper.h>

// Network credentials
const char *SSID = "ESP8266-LQ";
const char *PSWD = "";

// Line Tracking Sensor
const int LINE_SENSOR_PIN = D2; // Digital pin for line sensor
int line_value;
char line_buf[8];

// Step Motor
#define STEPS 2048
#define IN1 D3
#define IN2 D4
#define IN3 D5
#define IN4 D6
Stepper stepper(STEPS, IN1, IN3, IN2, IN4);
const int step_speed = 15;
int step_num = STEPS / 12;
int step_delay = 200;
int step_dir = 1;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  // Line Tracking Sensor
  pinMode(LINE_SENSOR_PIN, INPUT);

  // Step motor
  stepper.setSpeed(step_speed);

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
  <title>ESP8266 Web Server</title>
  <style>
    html {
      font-family: Arial;
      display: inline-block;
      margin: 0px auto;
      text-align: center;
    }
    h1 {
      color: #0F3376;
      padding: 2vh;
    }
    p {
      font-size: 1.5rem;
    }
    .button {
      display: inline-block;
      background-color: #008CBA;
      border: none;
      border-radius: 4px;
      color: white;
      padding: 16px 40px;
      font-size: 30px;
      margin: 2px;
      cursor: pointer;
    }
    input[type="number"] {
      width: 60px;
      text-align: center;
    }
  </style>
</head>
<body>
  <h1>ESP8266 Web Server</h1>
  <h1>Line Tracking Sensor</h1>
  <p>
    <span class="sensor-labels">Line Sensor State</span>
    <span id="line_value"></span>
  </p>
  <h1>Step Motor</h1>
  <form action="">
    <label for="rotate-degree">Enter</label>
    <input type="number" id="rotate-degree" min="0" max="360" step="1" value="45">
    <input type="checkbox" id="CCW-checkbox">
    <label for="CCW-checkbox">CCW</label>
    <input type="button" id="submit-btn" value="Rotate" class="button" onclick="rotateStepper()">
  </form>
  <script>
    setInterval(() => {
      fetch('/line_value')
        .then(response => response.text())
        .then(line_value => {
          document.getElementById("line_value").textContent = line_value;
        });
    }, 200);

    function rotateStepper() {
      let degree = document.getElementById("rotate-degree").value;
      let ccw = document.getElementById("CCW-checkbox").checked;
      fetch(`/rotate?degree=${degree}&ccw=${ccw}`);
    }
  </script>
</body>
</html>
    )rawliteral");
  });

  server.on("/line_value", HTTP_GET, [](AsyncWebServerRequest *request) {
    String state = digitalRead(LINE_SENSOR_PIN) == HIGH ? "1" : "0";
request->send(200, "text/plain", state);
  });

  server.on("/rotate", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("degree") && request->hasParam("ccw")) {
      int degree = request->getParam("degree")->value().toInt();
      step_num = degree / 360.0 * STEPS;
      String ccw = request->getParam("ccw")->value();
      step_dir = (ccw == "true") ? -1 : 1;
      request->send(200, "text/plain", "Rotation successful");
    } else {
      request->send(400, "text/plain", "Missing degree or ccw parameter");
    }
  });

  server.begin();
}

void loop() {
  line_value = digitalRead(LINE_SENSOR_PIN);

  // Debug to Serial Monitor
  Serial.print("Line Sensor State: ");
  Serial.println(line_value);

  delay(200);
  stepper.step(step_num * step_dir);
  delay(step_delay);
}