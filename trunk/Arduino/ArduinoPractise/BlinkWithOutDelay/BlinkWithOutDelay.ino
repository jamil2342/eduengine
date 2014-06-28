/*
 * BlinkWithOutDelay.ino
 *
 * Created: 6/28/2014 12:23:37 PM
 * Author: MIR
 */ 

const int ledPin=13;
long long int lastUpdate=0;
const int delayTime=5000;
int ledState=LOW;
void setup()
{
	
	  /* add setup code here, setup code runs once when the processor starts */
	  pinMode(ledPin,OUTPUT);

}

void loop()
{

	  /* add main program code here, this code starts again each time it ends */
	  if (millis()-lastUpdate>delayTime)
	  {
		  if (ledState==LOW)
		  {
			  ledState=HIGH;
			  
		  }
		  else
		  {
			  ledState=LOW;
		  }
		  digitalWrite(ledPin,ledState);
		  lastUpdate=millis();
				
			
	  }

}
