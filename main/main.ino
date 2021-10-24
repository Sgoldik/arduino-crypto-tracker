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
    printOnDisplay(strData);
    strData = "";
    recievedFlag = false;
  }  

 
  if (Serial.available()) {
    esp8266.write(Serial.read());
  }
}

void printOnDisplay(String string) {
  // length (with one extra character for the null terminator)
  int str_len = string.length() + 1; 
  
  // prepare the character array (the buffer) 
  char sz[str_len];
  
  // copy it over 
  string.toCharArray(sz, str_len);

  char *saveptr;
  char *crypto, *price;
  
  crypto = strtok_r(sz, ",", &saveptr);
  price = strtok_r(NULL, ",", &saveptr);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(crypto);
  lcd.setCursor(4, 1); // (16 - 8) / 2
  lcd.print(price);
  
  Serial.println(crypto);
  Serial.println(price);
}
