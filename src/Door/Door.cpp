// LCD display library
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
#include <MFRC522.h>
#include "defs.h"

// setup
MFRC522 mfrc522(SS_PIN, RST_PIN);

void door_initialize()
{
  pinMode(buzzer, OUTPUT);
  pinMode(lock_pin, OUTPUT);

  // initialize RFID card reader
  mfrc522.PCD_Init();
}

bool card_authorization()
{
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "73 78 D3 1C") // Make sure you change this with your own UID number
  {
    // access granted
    Serial.println("Authorised access");
    digitalWrite(buzzer, HIGH);
    digitalWrite(lock_pin, LOW);
    return true;
  }
  else
  {
    Serial.println(" Access denied");
    digitalWrite(lock_pin, LOW); // if relay is open LOW
    delay(1000);
    return false;
  }
}

void check_for_card()
{
  // Check if card is available for reading
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Read the serial number of the card/tag
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
}
