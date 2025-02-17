#include <ESP8266WiFi.h>
#include <Wire.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Define your Wi-Fi credentials
const char* ssid = "POCO X3";
const char* password = "Sudhan2004";

// OpenWeatherMap API settings
const char* host = "api.api.thingspeak.com";
const int httpsPort = 443;
const char* weatherApiUrl = "/apps/thinghttp/send_request?api_key=3VO9WPVYL6S56SXP";

// Pin configurations
const int moisturePin = A0;
const int pumpPin = D1;

// Moisture threshold (adjust as needed)
const int moistThreshold = 1100; // Adjust this value based on your sensor's behavior

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Configure pumpPin as an OUTPUT
  pinMode(pumpPin, OUTPUT);
}

void loop() {
  // Read soil moisture value
  int moistureValue = analogRead(moisturePin);

  Serial.print("Moisture Level: ");
  Serial.println(moistureValue);

  // Check if moisture is below the threshold
  if (moistureValue < moistThreshold) {
    // Request weather data
    String weatherData = getWeatherData();

    // Check if weather indicates rain
    if (weatherData.indexOf("\"main\":\"Rain\"") != -1) {
      // It's raining, turn off the pump
      digitalWrite(pumpPin, LOW);
      Serial.println("Rain detected. Pump turned off.");
    } else {
      // No rain, turn on the pump
      digitalWrite(pumpPin,HIGH);
      Serial.println("No rain detected. Pump turned on.");
    }
  } else {
    // Moisture level is sufficient, turn off the pump
    digitalWrite(pumpPin, LOW);
    Serial.println("Moisture level is sufficient. Pump turned off.");
  }

  // Wait for 1 minute before checking again
  delay(60000);
}

String getWeatherData() {
  WiFiClientSecure client;

  if (!client.connect(host, httpsPort)) {
    Serial.println("Connection to OpenWeatherMap failed");
    return "";
  }

  Serial.println("Connected to OpenWeatherMap");

  client.print(String("GET ") + weatherApiUrl + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  while (!client.available()) {
    delay(1000);
    Serial.println("Waiting for data...");
  }

  String response = "";
  while (client.available()) {
    char c = client.read();
    response += c;
  }

  return response;
}