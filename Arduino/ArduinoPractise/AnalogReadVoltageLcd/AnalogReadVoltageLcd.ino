/*
 * AnalogReadVoltageLcd.ino
 *
 * Created: 7/16/2014 9:40:30 AM
 * Author: MIR
 */ 

#include <LiquidCrystal/LiquidCrystal.h>

LiquidCrystal lcd(12,11,3,2,1,0);

int sensorValue, outputVoltage;
void setup()
{
	lcd.begin(16,1);


}

void loop()
{
	sensorValue=analogRead(A0);
	outputVoltage=(int)((5/1023)*sensorValue);
	lcd.clear();
	lcd.print(sensorValue);
	delay(2000);
	  

}
