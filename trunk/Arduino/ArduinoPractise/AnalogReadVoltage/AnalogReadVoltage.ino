/*
* AnalogReadVoltage.ino
*
* Created: 7/15/2014 9:16:58 AM
* Author: MIR
*/
int sensorValue,outputValue;
int analogOutputPin=9;
void setup()
{	
	//Serial.begin(9600);
}

void loop()
{
	sensorValue=analogRead(A0);
	outputValue =map(sensorValue,0,123,0,255);
	analogWrite(analogOutputPin,outputValue);
	delay(2000);
	//Serial.println(outputValue);
	

}
