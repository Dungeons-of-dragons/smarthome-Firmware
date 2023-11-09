// LCD display library
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
#include <SPI.h>
#include <MFRC522.h>
#include "defs.h"


// initializing the RFID card reader
MFRC522 mfrc522(SS_PIN, RST_PIN);  
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
  pinMode(buzzer, OUTPUT);
  pinMode(lock, OUTPUT);
  // LCD setup
  SPI.begin(); 
  lcd.init();
  lcd.backlight();
  lcd.begin(16,2);
  lcd.clear(); 
  lcd.print("Scan Card!");
  // initialize RFID card reader
  mfrc522.PCD_Init();   
  Serial.println();
}


bool checkcardispresent(){ 
   
}
void loop() 
{
  // Check if card is available for reading
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Read the serial number of the card/tag
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }  
  //Ask user to scan card
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Scan card");
  Serial.print("UID tag :");

  // printing out the cards information to serial
  String content= "";
  byte letter;
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
  lcd.print("Scan Card");    

  // Checks if the serial number in the card is given authorization (take information from DB)
  if (content.substring(1) == "73 78 D3 1C") // Make sure you change this with your own UID number
  {
    //access granted
    Serial.println("Authorised access");
    digitalWrite(buzzer, HIGH);    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.println("Authorised access");    
    digitalWrite(lock, LOW);
    Serial.println();
    delay(1000);
    digitalWrite(buzzer, LOW);
    delay(5000);
    digitalWrite(lock, HIGH); // if relay is closed HIGH
    delay(2500);    
  }
 
  // Access Denied
  else {
    Serial.println(" Access denied");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.println("Access denied");
    digitalWrite(lock, LOW); // if relay is open LOW
    delay(1000);    
  }
lcd.clear();
lcd.setCursor(0,0);
lcd.println("Scan Card");
}