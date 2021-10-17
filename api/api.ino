#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

const char* ssid = "TP-Link_408";
const char* password = "84570550";

#define CD_API "/v1/bpi/currentprice.json"
#define CD_URL "api.coindesk.com"

static char respBuffer[4096];
WiFiClient client;

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
  const char request[] =
  "GET " CD_API " HTTP/1.1\r\n"
  "User-Agent: ESP8266/0.1\r\n"
  "Accept: */*\r\n"
  "Host: " CD_URL "\r\n"
  "Connection: close\r\n"
  "\r\n";
  delay(100);

  if (!client.connect(CD_URL, 80)) {
    Serial.println("Connection failed");
    return;
  }

  client.print(request);
  client.flush();
  delay(1000);
  uint16_t index = 0;
  while(client.connected() || client.available()) {
    if(client.available()) {
      respBuffer[index++] = client.read();
      delay(1);
    }
  }

  char * json = strchr(respBuffer,'{');
  String json_str = String(json);
  uint16_t idx_d = json_str.lastIndexOf('d');
  json_str.remove(idx_d,3);
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, json);

  JsonObject bpi = doc["bpi"];
  JsonObject usd = bpi["USD"];
  String rate_float = usd["rate_float"];

  Serial.print(rate_float);
}
