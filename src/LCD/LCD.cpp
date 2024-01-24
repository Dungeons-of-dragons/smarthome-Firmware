#include <LiquidCrystal_I2C.h>
#include "defs.h"
#include "LCD.h"
#include <SPI.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

/**
 * @brief This function asks user to scan card on the RFID card reader through the LCD.
 *
 */
void LCD::display_tag()
{
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Scan card");
    Serial.print("UID tag :");
}

/**
 * @brief This function initializes and sets up the LCD
 *
 */
void LCD::lcd_initialize()
{
    lcd.init();
    lcd.backlight();
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome to D.O.D");
}

/**
 * @brief The function displays the value of temperature and humidity.
 *
 * @param temp This is the value of temperature.
 * @param humidity This is the value of humidity.
 */
void LCD::displaydht(float temp, float humidity)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println("temp:");
    lcd.print(temp);
    lcd.setCursor(0, 1);
    lcd.println("humidity:");
    lcd.print(humidity);
}
/**
 * @brief Clears LCD
 *
 * @param userin
 */
void LCD::displayuserdenied()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("locked out");
}

/**
 * @brief Checks if user is authorized to enter house and displays
 * appropriate message based on the RFID access.
 *
 * @param Response This parameter is an input from the reponse of the
 * accessibility. True for authorised and false for unauthorised.
 */
void LCD::displayauthorised(bool Response)
{
    if (Response == true)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.println("Authorised access");
        lcd.setCursor(0, 1);
        lcd.println("Welcome to DoD");
    }
    else if (Response == false)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.println("Access denied");
        lcd.setCursor(0, 1);
        lcd.println("Try Again");
    }
}

/**
 * @brief This function displays Power and current values on the LCD
 *
 * @param Watt This is the value of voltage
 * @param AmpsRMS This is the value of current drawn by the system
 */
void LCD::displaypower(double Watt, double AmpsRMS)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.println("Power:");
    lcd.print(Watt);
    lcd.setCursor(0, 1);
    lcd.println("Current:");
    lcd.print(AmpsRMS);
}
