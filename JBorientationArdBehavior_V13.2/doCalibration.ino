void doCalibration()
{
  if (firstCalibration)
  {
    // Move to Target position
    movePositionMotor();
  }
  if ((targetPos) && (!secondCalibration) && (!thirdCalibration))
  {
    // Once the target area is reached - start counting back
    positionCount=0;
    homePos = false;
    delay(1000);
    backTimer = false;
    firstCalibration = false;
    BackStep = true;
    fastSpeed = false;
    openloopControl();
    secondCalibration = true;
  }
  if (secondCalibration)
  {
    if (!backTimer)
    {
      preStimTimeMasking = ((millis()) + maskingPreTime); // calculate no. of step in masking pretime
      preStimTimeStimON = ((millis()) + optoON);
      homeStimTimeStimON = ((millis()) + preDuration);
      backTimer = true;
    }
    if ((!maskingStepsSet) || (!optoStepsSet) && (backTimer))
    {
      movePositionMotor();
      stimOUTcount++;
      if ((millis()) >= (preStimTimeMasking) && (!maskingStepsSet))
      {
        maskingSteps = stimOUTcount;
        maskingStepsSet = true;
      }
      if ((millis()) >= (preStimTimeStimON) && (!optoStepsSet))
      {
        optoSteps = stimOUTcount;
        optoStepsSet = true;
      }
    }
    else
    {
      secondCalibration = false;
      thirdCalibration = true;
      positionCount = 0;
      fastSpeed = true;
      openloopControl();
    }
  }
  if ((thirdCalibration) && (!homePos))
  {
    movePositionMotor();
    stimINcount++;
  }
  if (((millis()) >= (homeStimTimeStimON)) && (thirdCalibration))
  {
    doHome();
    if (fullCircle)
    {
      // Calculate how many steps to get back to home
      // TotalSteps at slow speed in 1/16 microstepping
      int maxMicroStepSize = 16;
      int totalMicroStep = 400 * maxMicroStepSize;
      int tempTotalSlow = ((stimOUTcount + stimOUTcount) /motor1microStep) * maxMicroStepSize;
      int tempTotalFast = ((stimINcount) /motor1microStep2) * maxMicroStepSize;
      diffTotalSteps = ((totalMicroStep - (tempTotalSlow + tempTotalFast)) /maxMicroStepSize) * motor1microStep2;
    }
    calibrate = false;
    startSerial = true;
    calFinished = true;
    BackStep = false;
    homePos = false;
    sendDig = false;
    targetPos = false;
    positionCount = 0;
    addHomeposition = 0;
    encoder0Pos = 0;
    pauseDuration = (pauseDuration + (millis() - pauseDurationStart) - 4);
    delay(200);
    reachedHome = true;
    firstHome = true;
    newTrial = true;
    stimMotorMicroStepping(); 
  }
  else
    if ((homePos) && (secondCalibration))
    {
      delay(1000);
      Serial.println("MOVE HOME AREA BACK... not enough time to complete slow stepping/ maskinglight pretime");
      exit(0);
      delay(2000);
    }
  delay(4);
}
