/*
 * Blink.ino
 *
 * Created: 6/28/2014 12:05:17 PM
 * Author: MIR
 */ 

#include "MyClass.h"

const int ledPin=13;

void setup()
{
	pinMode(ledPin,OUTPUT);
}

void loop()
{
	digitalWrite(ledPin,HIGH);
	delay(2000);
	digitalWrite(ledPin,LOW);
	delay(2000);
}
