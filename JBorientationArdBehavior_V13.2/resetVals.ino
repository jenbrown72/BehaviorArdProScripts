void resetVals()
{
 //Serial.println("Resetting");
  startTrial = true;
  digitalAngleSuccess = false;
  digCountSuccess = false;
  digJitterSuccess = false;
  sendDig = false;
  reachedHome = false;
  moveToTarget = false;
  encoder0Pos = 0;
  backToHome = false;
  homePos = false;
  newAngleSelect = false;
  targetPos = false;
  firstHome = false;
  randomDelay = false;
  preStimSet = false;
  TrialType = 0;
  newTrialStarted = true;
  positionCount = 0;
  lightONcounter=0;
  optoONSet=false;
  extraMoveSet = false;
//  if (jitterTarget)
//  {
//    // if bar position needs to be jittered - select randon jitter amount
//    addJitter = random(0, 100); // select a random amount of steps to move the stimulusID further on
//  }
// 
//  else if ((!jitterTarget) && (!localization))
//  {
//    addJitter = 0;
//  }
}
