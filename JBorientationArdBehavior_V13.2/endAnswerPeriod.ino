void endAnswerPeriod()
{
	answerPeriod = false;
	targetArea = false;
	digitalWrite(targetState, LOW);
	targetPos = false;
	if (maskingLight)
	{
		digitalWrite(maskingLED, LOW);
		maskingLEDstate = false;
	}
	if (optogenetics)
	{
		analogWrite(LEDPin, 0);
		LEDstate = false;
	}
}
