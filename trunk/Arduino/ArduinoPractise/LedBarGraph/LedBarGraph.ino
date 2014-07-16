/*
 * LedBarGraph.ino
 *http://arduino.cc/en/Tutorial/BarGraph
 * Created: 7/16/2014 7:05:56 AM
 * Author: MIR
 */ 

int ledPin[]={2,3,4,5,6,7,8,9,10,11};
const int ledPinCount=10;	
void setup()
{
	for (int i=0;i<ledPinCount;i++)
	{
		pinMode(ledPin[i],OUTPUT);
	}
}

void loop()
{	  
	int sensorReading=analogRead(A0);
	int output=map(sensorReading,0,1023,0,ledPinCount);
	for (int i=0;i<ledPinCount;i++)
	{
		if (i<output)
		{
			digitalWrite(ledPin[i],HIGH);
		}
		else
		{
			digitalWrite(ledPin[i],LOW);
		}
		
	}
}
