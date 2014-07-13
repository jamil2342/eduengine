/*
* InputPullUp.ino
*
* Created: 7/13/2014 9:49:08 AM
* Author: MIR
*/
int inputPin=2,outputPin=13;
void setup()
{

	/* add setup code here, setup code runs once when the processor starts */
	pinMode(inputPin,INPUT);
	pinMode(outputPin,OUTPUT);

}

void loop()
{

	/* add main program code here, this code starts again each time it ends */
	int input=digitalRead(inputPin);
	if (input==HIGH)
	{
		digitalWrite(outputPin,LOW);
	} 
	else
	{
		digitalWrite(outputPin,HIGH);
	}

}
