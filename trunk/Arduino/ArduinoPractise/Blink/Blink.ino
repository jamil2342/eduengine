/*
 * Blink.ino
 *
 * Created: 6/28/2014 12:05:17 PM
 * Author: MIR
 */ 

#include "MyClass.h"

const int ledPin=13;
const int delay_time = 1000;

void setup()
{
	pinMode(ledPin,OUTPUT);
}

void loop()
{
	digitalWrite(ledPin,HIGH);
	delay(delay_time);
	digitalWrite(ledPin,LOW);
	delay(delay_time);
}
