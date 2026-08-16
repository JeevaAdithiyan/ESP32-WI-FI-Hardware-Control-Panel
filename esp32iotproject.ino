#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* ssid = "******";
const char* password = "*******";

WebServer server(80);

const int ledPin = 13;
const int servoPin = 18;

Servo myServo;

bool ledState = false;
int servoAngle = 0;


// ================= WEBPAGE =================

void handleRoot() {

  String ledStatus;

  if (ledState) {
    ledStatus = "ON";
  } else {
    ledStatus = "OFF";
  }

  String gateStatus;

  if (servoAngle >= 45) {
    gateStatus = "OPEN";
  } else {
    gateStatus = "CLOSED";
  }

  String page = "<!DOCTYPE html>";
  page += "<html>";
  page += "<head>";
  page += "<meta charset='UTF-8'>";
  page += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  page += "<title>ESP32 Smart Gate</title>";

  page += "<style>";

  page += "body {";
  page += "font-family: Arial;";
  page += "text-align: center;";
  page += "background: #f2f2f2;";
  page += "margin: 0;";
  page += "padding: 20px;";
  page += "}";

  page += ".container {";
  page += "max-width: 500px;";
  page += "margin: auto;";
  page += "background: white;";
  page += "padding: 25px;";
  page += "border-radius: 20px;";
  page += "box-shadow: 0 4px 15px rgba(0,0,0,0.15);";
  page += "}";

  page += ".card {";
  page += "padding: 20px;";
  page += "margin: 15px 0;";
  page += "background: #f7f7f7;";
  page += "border-radius: 15px;";
  page += "}";

  page += "button {";
  page += "padding: 14px 22px;";
  page += "margin: 6px;";
  page += "border: none;";
  page += "border-radius: 10px;";
  page += "font-size: 16px;";
  page += "}";

  page += ".slider {";
  page += "width: 90%;";
  page += "}";

  page += ".status {";
  page += "font-size: 20px;";
  page += "font-weight: bold;";
  page += "}";

  page += "</style>";
  page += "</head>";

  page += "<body>";

  page += "<div class='container'>";

  page += "<h1>ESP32 SMART GATE</h1>";


  // LED
  page += "<div class='card'>";

  page += "<h2>LED</h2>";

  page += "<p class='status'>";
  page += "LED STATUS: ";
  page += ledStatus;
  page += "</p>";

  page += "<a href='/led/on'>";
  page += "<button>LED ON</button>";
  page += "</a>";

  page += "<a href='/led/off'>";
  page += "<button>LED OFF</button>";
  page += "</a>";

  page += "</div>";


  // GATE
  page += "<div class='card'>";

  page += "<h2>GATE</h2>";

  page += "<p class='status'>";
  page += "GATE STATUS: ";
  page += gateStatus;
  page += "</p>";

  page += "<a href='/servo/open'>";
  page += "<button>OPEN</button>";
  page += "</a>";

  page += "<a href='/servo/close'>";
  page += "<button>CLOSE</button>";
  page += "</a>";

  page += "</div>";


  // SERVO ANGLE
  page += "<div class='card'>";

  page += "<h2>SERVO ANGLE</h2>";

  page += "<p>";
  page += "Angle: <span id='angle'>";
  page += String(servoAngle);
  page += "</span>&deg;";
  page += "</p>";

  page += "<input type='range'";
  page += " min='0'";
  page += " max='180'";
  page += " value='";
  page += String(servoAngle);
  page += "'";
  page += " class='slider'";
  page += " oninput='updateServo(this.value)'>";

  page += "</div>";


  // SYSTEM STATUS
  page += "<div class='card'>";

  page += "<h3>SYSTEM STATUS</h3>";
  page += "<p>Wi-Fi: CONNECTED</p>";
  page += "<p>ESP32: ONLINE</p>";

  page += "</div>";

  page += "</div>";


  // JAVASCRIPT
  page += "<script>";

  page += "function updateServo(value) {";
  page += "document.getElementById('angle').innerHTML = value;";
  page += "fetch('/servo?angle=' + value);";
  page += "}";

  page += "</script>";

  page += "</body>";
  page += "</html>";

  server.send(200, "text/html", page);
}


// ================= LED =================

void ledOn() {

  digitalWrite(ledPin, HIGH);

  ledState = true;

  server.sendHeader("Location", "/");
  server.send(303);
}


void ledOff() {

  digitalWrite(ledPin, LOW);

  ledState = false;

  server.sendHeader("Location", "/");
  server.send(303);
}


// ================= SERVO =================

void servoOpen() {

  servoAngle = 90;

  myServo.write(servoAngle);

  server.sendHeader("Location", "/");
  server.send(303);
}


void servoClose() {

  servoAngle = 0;

  myServo.write(servoAngle);

  server.sendHeader("Location", "/");
  server.send(303);
}


void servoControl() {

  if (server.hasArg("angle")) {

    servoAngle = server.arg("angle").toInt();

    servoAngle = constrain(servoAngle, 0, 180);

    myServo.write(servoAngle);
  }

  server.send(200, "text/plain", "OK");
}


// ================= SETUP =================

void setup() {

  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LOW);

  myServo.attach(servoPin);

  myServo.write(0);

  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");
  }

  Serial.println();

  Serial.println("WiFi connected!");

  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());


  server.on("/", handleRoot);

  server.on("/led/on", ledOn);

  server.on("/led/off", ledOff);

  server.on("/servo/open", servoOpen);

  server.on("/servo/close", servoClose);

  server.on("/servo", servoControl);


  server.begin();

  Serial.println("Web server started!");
}


// ================= LOOP =================

void loop() {

  server.handleClient();
}
