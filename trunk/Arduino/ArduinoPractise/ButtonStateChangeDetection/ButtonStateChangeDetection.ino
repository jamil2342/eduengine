///*
//* ButtonStateChangeDetection.ino
//*
//* Created: 7/13/2014 6:24:19 AM
//* Author: MIR
//*/
//
int inputPin,outputPin,lastState,currentState,count;

void setup()
{
	
	inputPin=2;
	outputPin=13;
	lastState=LOW;
	count=0;
	
	pinMode(inputPin,INPUT);
	pinMode(outputPin,OUTPUT);
	Serial.begin(9600);
	

}

void loop()
{
	currentState=digitalRead(inputPin)	;
	if (currentState!=lastState)
	{
		if (currentState==HIGH)
		{
			count++;
			
		}
		else
		{
			
		}
		
	}
	currentState=lastState;
	
	if (count%4==0)
	{
		digitalWrite(outputPin,HIGH);
	} 
	else
	{
		digitalWrite(outputPin,LOW);
	}

}

