#include <ESP8266WiFi.h> 

 

// Thông tin Wi-Fi 

const char* ssid = "Raccoon"; // Thay bằng SSID Wi-Fi 

const char* password = "11062004"; // Thay bằng mật khẩu Wi-Fi 

 

// Định nghĩa chân LED 

#define LED1_PIN 5 // GPIO5 

#define LED2_PIN 4 // GPIO4 

 

// Trạng thái LED 

int led1on = LOW; 

int led2on = LOW; 

 

WiFiServer server(80); // Tạo server trên cổng 80 

 

void setup() { 

  // Cấu hình các chân LED là OUTPUT 

  pinMode(LED1_PIN, OUTPUT); 

  pinMode(LED2_PIN, OUTPUT); 

 

  // Mặc định tắt LED 

  digitalWrite(LED1_PIN, led1on); 

  digitalWrite(LED2_PIN, led2on); 

 

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

  server.begin(); 

} 

 

void loop() { 

  // Kiểm tra kết nối mới 

  WiFiClient client = server.available(); 

  if (!client) return; 

 

  // Đợi yêu cầu từ client 

  Serial.println("New client connected"); 

  String request = client.readStringUntil('\r'); 

  Serial.println(request); 

  client.flush(); 

 

  // Xử lý yêu cầu 

  if (request.indexOf("/1/on") != -1) { 

    led1on = HIGH; 

    digitalWrite(LED1_PIN, led1on); 

  }  

  else if (request.indexOf("/1/off") != -1) { 

    led1on = LOW; 

    digitalWrite(LED1_PIN, led1on); 

  } 

  else if (request.indexOf("/2/on") != -1) { 

    led2on = HIGH; 

    digitalWrite(LED2_PIN, led2on); 

  }  

  else if (request.indexOf("/2/off") != -1) { 

    led2on = LOW; 

    digitalWrite(LED2_PIN, led2on); 

  } 

 

  // Tạo giao diện HTML nâng cao 

  String htmlPage = "<!DOCTYPE html><html>"; 

  htmlPage += "<head>"; 

  htmlPage += "<title>ESP8266 LED Control</title>"; 

  htmlPage += "<style>"; 

  htmlPage += "body { font-family: Arial, sans-serif; text-align: center; background-color: #f4f4f9; margin: 0; padding: 20px; }"; 

  htmlPage += "h1 { color: #333; }"; 

  htmlPage += ".button { padding: 15px 30px; margin: 10px; border: none; color: white; font-size: 16px; cursor: pointer; border-radius: 5px; }"; 

  htmlPage += ".button-on { background-color: #28a745; }"; 

  htmlPage += ".button-off { background-color: #dc3545; }"; 

  htmlPage += ".card { background: white; margin: 20px auto; padding: 20px; max-width: 300px; box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2); border-radius: 10px; }"; 

  htmlPage += "</style>"; 

  htmlPage += "</head>"; 

  htmlPage += "<body>"; 

  htmlPage += "<h1>ESP8266 LED Control</h1>"; 

  htmlPage += "<div class='card'>"; 

  htmlPage += "<h2>LED 1</h2>"; 

  if (led1on == LOW) 

    htmlPage += "<a href=\"/1/on\"><button class='button button-on'>Turn ON</button></a>"; 

  else 

    htmlPage += "<a href=\"/1/off\"><button class='button button-off'>Turn OFF</button></a>"; 

  htmlPage += "</div>"; 

  htmlPage += "<div class='card'>"; 

  htmlPage += "<h2>LED 2</h2>"; 

  if (led2on == LOW) 

    htmlPage += "<a href=\"/2/on\"><button class='button button-on'>Turn ON</button></a>"; 

  else 

    htmlPage += "<a href=\"/2/off\"><button class='button button-off'>Turn OFF</button></a>"; 

  htmlPage += "</div>"; 

  htmlPage += "</body></html>"; 

 

  // Gửi phản hồi về client 

  client.print("HTTP/1.1 200 OK\r\n"); 

  client.print("Content-Type: text/html\r\n"); 

  client.print("Connection: close\r\n"); 

  client.print("\r\n"); 

  client.print(htmlPage); 

 

  delay(1); 

  Serial.println("Client disconnected"); 

} 