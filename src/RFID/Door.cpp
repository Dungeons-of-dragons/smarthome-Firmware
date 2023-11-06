// LCD display library
#include <LiquidCrystal_I2C.h>
// installing libraries necessary for the RFID card reader
#include <Wire.h>
#include <EEPROM.h>

#include <SPI.h>
#include <MFRC522.h>

// RFID card reader pins
#define SS_PIN 10
#define RST_PIN 9

// LED pinouts
#define red 5
#define blue 3
#define green 4

// Electromagnetic lock and buzzer pinouts
#define lock 6
#define buzzer 2

// initializing the RFID card reader
MFRC522 mfrc522(SS_PIN, RST_PIN);  
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{
  Serial.begin(9600);  

  //setting pin modes for actuators and signal devices.
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
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
  digitalWrite(blue, HIGH); 

  // Checks if the serial number in the card is given authorization (take information from DB)
  if (content.substring(1) == "73 78 D3 1C") // Make sure you change this with your own UID number
  {
    //access granted
    Serial.println("Authorised access");
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(buzzer, HIGH);    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.println("Authorised access");    
    digitalWrite(lock, LOW);
    Serial.println();
    delay(1000);
    digitalWrite(green, LOW);
    digitalWrite(blue, HIGH);
    digitalWrite(buzzer, LOW);
    delay(5000);
    digitalWrite(lock, HIGH); // if relay is closed HIGH
    delay(2500);    
  }
 
  // Access Denied
  else {
    Serial.println(" Access denied");
    digitalWrite(blue, LOW);
    digitalWrite(red, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.println("Access denied");
    digitalWrite(lock, LOW); // if relay is open LOW
    delay(1000);
    digitalWrite(red, LOW);
    digitalWrite(blue, HIGH);
    delay(2500);
    
  }
lcd.clear();
lcd.setCursor(0,0);
lcd.println("Scan Card");
}