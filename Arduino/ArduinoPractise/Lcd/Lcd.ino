#include <LiquidCrystal/LiquidCrystal.h>

LiquidCrystal lcd(12,11, 3,2,1,0);

void setup() {
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
	// Print a message to the LCD.
	lcd.print("hello, world!");
}

void loop() {
	// set the cursor to column 0, line 1
	// (note: line 1 is the second row, since counting begins with 0):
	lcd.setCursor(5, 1);
	// print the number of seconds since reset:
	lcd.print(millis()/1000);
}
