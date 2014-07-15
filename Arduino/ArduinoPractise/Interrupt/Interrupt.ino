/*
* Interrupt.ino
*
* Created: 7/15/2014 6:34:53 AM
* Author: MIR
*/


const int inputPin=2,ledPin=13;
int state=1;
void setup()
{
	pinMode(ledPin,OUTPUT)	;
	pinMode(inputPin,INPUT_PULLUP);
	attachInterrupt(inputPin,interrruptFunction_2,CHANGE);

}

void loop()
{
	digitalWrite(ledPin,(int)state);

}

void interrruptFunction_2()
{
	state=!state;
}

