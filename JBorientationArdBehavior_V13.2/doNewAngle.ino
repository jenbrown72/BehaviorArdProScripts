void doNewAngle()
{

//  Serial.println("doNew Angle");
//  currMove = (stimPosition[blockSize[(count % trialBlockTotal)]]);
  currMoveNum = (numStim[blockSize[(count % trialBlockTotal)]]); // numStimPositions
  requiredDistance = (fullRevolutionStim + (fullRevolutionStim - lastMove) + (stimPosition[blockSize[(count % trialBlockTotal)]])); // Calculate how many steps the stimulusID motor needs to be moved to get into its new position
  lastMove = (stimPosition[blockSize[(count % trialBlockTotal)]]);
  currOpto = optoTrials[(count % trialBlockTotal)];
  currOptoLEDState = optoTrialsVoltage[(count % trialBlockTotal)];

  if (!linearExp){
 currCatch = catchTrials[(count % trialBlockTotal)];
  }
  else {
  currCatch = false;
  }
  
 
  lastAngle = (stimIdx[blockSize[(count % trialBlockTotal)]]);
  //lastAngle = (round(lastMove / stepsPerDegree));
  // Determine what the next stimulusID type is
  // first reset all to false
  GOtrial = false;
  NOGOtrial = false;
  midTrial = false;
  if (lastMove < midPointAngleStep)
  {
    if (orgGOangle)
    {
      GOtrial = true;
    }
    else
    {
      NOGOtrial = true;
    }
  }
  else
    if (lastMove > midPointAngleStep)
    {
      if (orgGOangle)
      {
        NOGOtrial = true;
      }
      else
      {
        GOtrial = true;
      }
    }
  else
    if (lastMove == midPointAngleStep)
    {
      midTrial = true;
    }
  // now move stim into next angle position
  newAngleSelect = true;
  positionCount = 0;
  newTrial = false;

    // TARGTE JITTER STATE
//  if (jitterTarget == true) { 
//    tempaddJitter = random(0, 3); //select a random amount of steps to move the stimulus further on
//    addJitter = randomJitterArray[tempaddJitter];
//    // addJitter = random(0, 100); //select a random amount of steps to move the stimulus further on
//    jitterCount = 0;
//  }
}

