#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

const char* ssid = "TP-Link_408";
const char* password = "84570550";

const int timeout = 300000; // timeout between next API query

const String API_URL = "https://cmc-reducer.herokuapp.com/crypto";
const String CRYPTO = "?slug=bitcoin,ethereum,litecoin,waves,binance-coin,monero,stellar,pancakeswap,biswap,eos,dogecoin,zcash";
#define API_KEY "2831fae4-a23b-4b17-85ee-cce0a4520df2"

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
  Serial.print("WiFi ok.");
}

void loop() {
  getData();
}

void getData() {
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  
  client->setInsecure();
  HTTPClient http;

  if (WiFi.status() == WL_CONNECTED) {
 
    HTTPClient http;
 
    http.begin(*client, API_URL + CRYPTO);
    http.addHeader("X-CMC_PRO_API_KEY", API_KEY); 
    int httpCode = http.GET();
 
    if (httpCode > 0) {
 
      String payload = http.getString();

      String json_str = String(payload);

      DynamicJsonDocument doc(4096);
      DeserializationError error = deserializeJson(doc, payload);
      if (error) {
        Serial.print(F("json failed:,"));
        Serial.print(error.c_str());
        return;
      }
      JsonArray data = doc["data"];
      int arraySize = data.size();

      for (int i = 0; i < arraySize; i++) {
        JsonObject crypto = data[i];
        String name = crypto["name"];
        String price = crypto["price"];
      
        Serial.print(name + ",$" + price);
        delay(timeout / arraySize);
      }
    }
    http.end();
  }
}
