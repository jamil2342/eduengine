/*
 * AnalogReadVoltageLcd.ino
 *
 * Created: 7/16/2014 9:40:30 AM
 * Author: MIR
 */ 

#include <LiquidCrystal/LiquidCrystal.h>

LiquidCrystal lcd(12,11,3,2,1,0);

void setup()
{
	lcd.begin(16,1);
	//lcd.printFloat(1.6);
	char * str;
	sprintf(str,"%f",1.6);
	int a=10;
	lcd.print(a);

}

void loop()
{

	  

}
