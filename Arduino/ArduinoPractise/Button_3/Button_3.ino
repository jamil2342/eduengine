/*
 * Button_3.ino
 *
 * Created: 7/10/2014 6:44:39 AM
 * Author: MIR
 */ 
int inputPin,outputPin,input;
void setup()
{

	  /* add setup code here, setup code runs once when the processor starts */
	  pinMode(inputPin,INPUT);
	  pinMode(outputPin,OUTPUT);

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
