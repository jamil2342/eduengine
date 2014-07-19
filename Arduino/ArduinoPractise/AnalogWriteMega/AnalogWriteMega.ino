const int lowestPin = 2;
const int highestPin = 13;


void setup() {
	// set pins 2 through 13 as outputs:
	for (int thisPin =lowestPin; thisPin <= highestPin; thisPin++) {
		pinMode(thisPin, OUTPUT);
	}
}

void loop() {
	// iterate over the pins:
	for (int thisPin =lowestPin; thisPin <= highestPin; thisPin++) {
		// fade the LED on thisPin from off to brightest:
		for (int brightness = 0; brightness < 255; brightness++) {
			analogWrite(thisPin, brightness);
			delay(2);
		}
		// fade the LED on thisPin from brithstest to off:
		for (int brightness = 255; brightness >= 0; brightness--) {
			analogWrite(thisPin, brightness);
			delay(2);
		}
		// pause between LEDs:
		delay(100);
	}
}
