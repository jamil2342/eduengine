/*
* Button_3.ino
*
* Created: 7/10/2014 6:44:39 AM
* Author: MIR
*/
int inputPin,outputPin,input,testpin=10;
void setup()
{
	inputPin=2;
	outputPin=13;
	/* add setup code here, setup code runs once when the processor starts */
	pinMode(inputPin,INPUT);
	pinMode(outputPin,OUTPUT);
	//pinMode(testpin,OUTPUT);
	//digitalWrite(testpin,HIGH);

}

void loop()
{

	/* add main program code here, this code starts again each time it ends */
	input=digitalRead(inputPin);
	if (input==HIGH)
	{
		digitalWrite(outputPin,HIGH);
	}
	else
	{
		digitalWrite(outputPin,LOW);
	}

}
