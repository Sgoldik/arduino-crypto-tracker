#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial esp8266(3, 2);
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(115200);
  Serial.println("Started");

  esp8266.begin(115200);

  lcd.init();                     
  lcd.backlight();
  lcd.print("Bitcoin");
  
}

String strData = "";
boolean recievedFlag;

void loop() {

  while (esp8266.available() > 0) { 
    strData += (char)esp8266.read();
    recievedFlag = true;
    delay(2);
  }

  if (recievedFlag) {
    lcd.setCursor(4, 1);
    lcd.print(strData);
    Serial.println(strData);
    strData = "";
    recievedFlag = false;
  }

 
  if (Serial.available()) {
    esp8266.write(Serial.read());
  }
}
