void movePositionMotor()
{

  if (!linearExp){
	digitalWrite(motor1StepPin, HIGH); // Trigger one step forward
	delayMicroseconds(stepDelayTime);
	digitalWrite(motor1StepPin, LOW); // Pull step pin low so it can be triggered again
	delayMicroseconds(stepDelayTime);
	positionCount++;
  }

  else if ((linearExp) && (jitterAtHome)){
  digitalWrite(motor1StepPin, HIGH); // Trigger one step forward
  delayMicroseconds(stepDelayTime);
  digitalWrite(motor1StepPin, LOW); // Pull step pin low so it can be triggered again
  delayMicroseconds(stepDelayTime);
  positionCount++;
  }
    else if ((linearExp) && (!homePos)){
  positionCount++;
  }
}

void moveStimulusMotor()
{
	digitalWrite(motor2StepPin, HIGH); // Trigger one step forward
	delayMicroseconds(1);
	digitalWrite(motor2StepPin, LOW); // Pull step pin low so it can be triggered again
	delayMicroseconds(1);
	positionCount++;
}
