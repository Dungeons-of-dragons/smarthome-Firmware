#include <LiquidCrystal_I2C.h>
#include "defs.h"
#include "main.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
/**
 * @brief LCD is a class that has all possible cases of using the LCD to display information in different cases.
 * 
 */
class LCD{
    public:
    LCD(){
        lcd.clear();
    }
    void displaydht(float temp, float humidity);
    void displayuserstate(bool userin);
    void displayauthorised(bool Response);
    void displaypower(double Watt, double AmpsRMS);
};
/**
 * @brief The function displays the value of temperature and humidity.
 * 
 * @param temp This is the value of temperature.
 * @param humidity This is the value of humidity.
 */
void LCD::displaydht(float temp, float humidity){
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
void LCD::displayuserstate(bool userin){
  lcd.clear();
  lcd.setCursor(0,0);
}

/**
 * @brief Checks if user is authorized to enter house and displays
 * appropriate message based on the RFID access.
 * 
 * @param Response This parameter is an input from the reponse of the
 * accessibility. True for authorised and false for unauthorised.
 */
void LCD::displayauthorised(bool Response){
    if(Response == true){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.println("Authorised access"); 
        lcd.setCursor(0,1);
        lcd.println("Welcome to DoD");
    }
    else if(Response == false){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.println("Access denied");
        lcd.setCursor(0,1);
        lcd.println("Try Again");
    }
}

/**
 * @brief This function displays Power and current values on the LCD
 * 
 * @param Watt This is the value of voltage
 * @param AmpsRMS This is the value of current drawn by the system
 */
void LCD::displaypower(double Watt, double AmpsRMS){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.println("Power used: ");
    lcd.print(Watt);
    lcd.println("Current Drawn: ");
    lcd.print(AmpsRMS);
}

