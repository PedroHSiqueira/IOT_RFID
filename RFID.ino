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
    Serial.begin(9600);
    SPI.begin();      
    rfid.PCD_Init(); 
    
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

            Serial.print("UID:");
            for (int i = 0; i < rfid.uid.size; i++) {
                Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
                Serial.print(rfid.uid.uidByte[i], HEX);
            }
            Serial.println();

            rfid.PICC_HaltA();       
            rfid.PCD_StopCrypto1();  

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Acesso Concedido para:");
            lcd.setCursor(0, 1);
            for (int i = 0; i < rfid.uid.size; i++) {
                lcd.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
                lcd.print(rfid.uid.uidByte[i], HEX);
            }
            delay(5000);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Acesso Negado");
        }
    }
}