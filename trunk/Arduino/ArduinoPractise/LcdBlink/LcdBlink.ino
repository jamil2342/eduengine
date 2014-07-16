/*
 * LcdBlink.ino
 *http://arduino.cc/en/Tutorial/LiquidCrystalBlink
 * Created: 7/16/2014 9:23:09 AM
 * Author: MIR
 */ 
#include <LiquidCrystal/LiquidCrystal.h>

LiquidCrystal lcd(12,11,3,2,1,0);

void setup()
{
	lcd.begin(16,1)  ;
	lcd.print("hello world");

}

void loop()
{
	lcd.noBlink();
	delay(3000);
	lcd.blink();
	delay(3000);
	//lcd.clear();
		//lcd.print("hello");
		//delay(3000);
			//lcd.clear();
		//lcd.print("world");
		//delay(3000); 

}
