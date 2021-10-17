#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

const char* ssid = "TP-Link_408";
const char* password = "84570550";

#define API "https://api.coindesk.com/v1/bpi/currentprice.json"

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  getData();
  delay(7650);
}

void getData() {
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  
  client->setInsecure();
  HTTPClient http;

  if (WiFi.status() == WL_CONNECTED) {
 
    HTTPClient http;
 
    http.begin(*client, API);
    int httpCode = http.GET();
 
    if (httpCode > 0) {
 
      String payload = http.getString();
      String json_str = String(payload);
      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, payload);
      
      JsonObject bpi = doc["bpi"];
      JsonObject usd = bpi["USD"];
      String rate_float = usd["rate_float"];
    
      Serial.print(rate_float); 
    }
 
    http.end();
  }
}
