void moveNewAngle()
{
  if (!localization)
  {
    while (positionCount < (requiredDistance)){
    digitalWrite(motor2StepPin, HIGH);
    delayMicroseconds(500);//1000
    digitalWrite(motor2StepPin, LOW);
    delayMicroseconds(500);
    positionCount++; // record this step
  //  doSerialPrint();
  }
    if (positionCount >= (requiredDistance))
    {
      // Check to see if we are at the end of our move
      count++;
      newAngleSelect = false;
      randomDelayFirst = true;
      positionCount = 0;
      // digitalWrite(motor1enablePin, LOW); // Put the break on the Position Motor
  }
  }
  else
  {
    selectNewLocation();
  }
  addHomeJitter();
}
    void selectNewLocation(){
   // localisation task - move to determined position
    addJitter = (stimPosition[blockSize[(count % trialBlockTotal)]]);
    count++;
    newAngleSelect = false;
    randomDelayFirst = true;
    positionCount = 0;
    }
