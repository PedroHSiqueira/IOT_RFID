#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 5

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);

  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Acesso Negado");
  Serial.println("Tap RFID/NFC Tag on reader");
}

void loop() {

  if (rfid.PICC_IsNewCardPresent()) {
    if (rfid.PICC_ReadCardSerial()) {
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
      Serial.print("RFID/NFC Tag Type: ");
      Serial.println(rfid.PICC_GetTypeName(piccType));
      String uid = "";
      for (byte i = 0; i < rfid.uid.size; i++) {
        uid += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
        uid += String(rfid.uid.uidByte[i], HEX);
      }
      uid.toUpperCase();
      Serial.print("UID da tag: ");
      Serial.println(uid);
      Serial.print("UID:");
      for (int i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
        Serial.print(rfid.uid.uidByte[i], HEX);
      }
      Serial.println();

      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();

      String uidAutorizado1 = "B365C60D";

      if (uid == uidAutorizado1) {
        digitalWrite(9, HIGH);
        digitalWrite(8, LOW);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Acesso Permitido");
        lcd.setCursor(0, 1);
      }
      delay(5000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Acesso Negado");
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
    }
  }
}
