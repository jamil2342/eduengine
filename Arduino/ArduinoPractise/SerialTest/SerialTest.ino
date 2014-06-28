int len=0;

void setup() {
	Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop() {

	// send data only when you receive data:
	if (Serial.available()>0)
	{
		String str =Serial.readString();
		len=str.length();
		
		
		Serial.println(len);

		
	}

}