#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

WiFiClient client;

const char* ssid     = "AJapirak";  // Change your ssid wifi
const char* password = "v4biydKN";  // Change your password wifi
String api_key = "5T4WXGZFE1PZPS2K";   //  Change your api key


unsigned long previousMillis = 0;
const long interval = 15000;

void doHttpGet(float t, float h) {
  HTTPClient http;
  Serial.print("[HTTP] begin...\n");

  http.begin("http://api.thingspeak.com/update?api_key=" + api_key + "&field1=" + String(t) + "&field2=" + String(h)); //HTTP

  // start connection and send HTTP header
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    Serial.print("[CONTENT]\n");

    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

void setup() {
  Serial.begin(115200);
  delay(200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      doHttpGet(random(0, 10), random(10, 20));
    }
  }
  else  {
    Serial.println("connection lost, reconnect...");
    WiFi.begin(ssid, password);
    delay(500);
  }
}


