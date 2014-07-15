/*
* AnalogReadVoltage.ino
*
* Created: 7/15/2014 9:16:58 AM
* Author: MIR
*/
float sensorValue,analogValue;
void setup()
{	
	Serial.begin(9600);
}

void loop()
{
	sensorValue=analogRead(A0);
	analogValue =sensorValue*5/1023;
	Serial.println(analogValue);
	

}
