
//#include "../CommonHeader.h"


int len=0;
int ledPin=13;
String strRev(String str)
{
	String strrev= "";
	for (int i=str.length()-1;i>=0;i--)
	{
		strrev+=str[i];
	}
	return strrev;
}
void setup() {
	pinMode(ledPin,OUTPUT);
	Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
	
}




void loop() {
	
	//Serial.write("hello");

	// send data only when you receive data:
	if (Serial.available()>0)
	{
		String str =Serial.readString();
		//Serial.println(strRev(str));
		if (str=="hello")
		{
			digitalWrite(ledPin,HIGH);
			delay(5000);
			digitalWrite(ledPin,LOW);
			delay(5000);
		}
	}

}
