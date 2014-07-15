
int inputPin=2,ledPin=13;
volatile int state=LOW;

void setup()
{
	pinMode(ledPin,OUTPUT);
	pinMode(inputPin,INPUT_PULLUP);
	attachInterrupt(0,intFunction,RISING);
	
}

void loop()
{  
	digitalWrite(ledPin,state);
}

void intFunction()
{
	state=!state;  
}

