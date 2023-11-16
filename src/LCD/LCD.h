#ifndef LCD_H
#define LCD_H

class LCD{
    public:
    void lcd_initialize();
    void display_tag();
    void displaydht(float temp, float humidity);
    void displayuserstate(bool userin);
    void displayauthorised(bool Response);
    void displaypower(double Watt, double AmpsRMS);
};

#endif