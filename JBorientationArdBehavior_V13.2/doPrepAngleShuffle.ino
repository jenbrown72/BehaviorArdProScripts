void doPrepAngleShuffle()
{
  //Serial.println("*******************DOING ANGLE PREP SHUFFLE");
//  float avgBlockSize = 50;
  float stimInSteps;
  numStimPositions = 0; // keep track of how many active stim positions have been inputted from JAVA
  // int repetitions;
  numLEDStates = 0;
  // Find how how many stim positons are active, and convert this into motor steps
  for (int i = 0; i < sizeof(stimulusID) / sizeof(int); i++)
  {
    if (stimulusID[i] > 0)
      //if a stimulus was sent
    {
      if (!localization)
      {
        stimInSteps = stimulusID[i] * stepsPerDegree; // calculate how many stepper motor steps to take for each angle
      }
      else
      {
        stimInSteps = stimulusID[i];
      }
      // angle positions
      stimPosition[numStimPositions] = stimInSteps;
      stimIdx[numStimPositions] = stimulusID[i];
      numStim[numStimPositions] = stimulusIDNumber[i];
      numStimPositions++;
    }
  }
  // see how many LEDstates are being used.
  for (int i = 0; i < sizeof(LEDVolt) / sizeof(int); i++)
  {
    if (LEDVolt[i] > 0)
    {
      LEDvoltageState[i] = LEDVolt[i];
      numLEDStates++;
    }
  }
  halfStimPos = ((numStimPositions + 2 - 1) / 2);
  float divFactor = 100;
  // Generate trial Sequence Template
  noOptoReps = (fractionOpto/numStimPositions);
  noControlReps = ((divFactor - fractionOpto) / numStimPositions);
  noOptoRepsCatch = (noOptoReps * (fractionCatch / divFactor));
  noControlRepsCatch = (noControlReps * (fractionCatch / divFactor));
  while ((noOptoRepsCatch < 1) || (noControlRepsCatch < 1))
  {
    noOptoReps = (noOptoReps * 2);
    noOptoRepsCatch = noOptoRepsCatch * 2;
    noControlReps = (noControlReps * 2);
    noControlRepsCatch = (noControlRepsCatch * 2);
  }
  noOptoReps = noOptoReps - noOptoRepsCatch;
  noControlReps = noControlReps - noControlRepsCatch;
  while (noOptoReps < numLEDStates)
  {
    noOptoReps = (noOptoReps * 2);
    noOptoRepsCatch = noOptoRepsCatch * 2;
    noControlReps = (noControlReps * 2);
    noControlRepsCatch = (noControlRepsCatch * 2);
  }
  noOptoReps = round(noOptoReps);
  noOptoRepsCatch = round(noOptoRepsCatch);
  noControlReps = round(noControlReps);
  noControlRepsCatch = round(noControlRepsCatch);
  // FRACTION CATCH TRIALS
  if (numStimPositions != 1)
    // all other trials except S1 make fraction of stim catch trials half
  {
    halffractionCatchNo = ((noOptoRepsCatch + noControlRepsCatch) /2);
    noOptoRepsCatch = halffractionCatchNo;
    noControlRepsCatch = halffractionCatchNo;
    // 
  }
  trialBlockTotal = (noOptoReps + noControlReps + noOptoRepsCatch + noControlRepsCatch) * numStimPositions;
  optoTrialsControl = ((noOptoReps * numStimPositions) /numLEDStates);
  optoTrialsCatch = ((noOptoRepsCatch * numStimPositions) /numLEDStates);
  trialStructure[0] = noControlReps;
  trialStructure[1] = noOptoReps;
  trialStructure[2] = noControlRepsCatch;
  trialStructure[3] = noOptoRepsCatch;
  optoStructure[0] = 0;
  optoStructure[1] = 1;
  optoStructure[2] = 0;
  optoStructure[3] = 1;
  catchStructure[0] = 0;
  catchStructure[1] = 0;
  catchStructure[2] = 1;
  catchStructure[3] = 1;
  // int i;
  for (int i = 0; i < sizeof(trialStructure) / sizeof(int); i++)
  {
    trialStructure[i] *= numStimPositions;
  }
//  count = 0; // when count is 0 the next time the motor reaches the home position doAngleShuffle will run
  // if we're already at the home position - we need to declaire newTrials true again so that doAngleShuffle will be called
  if (!newTrial)
  {
    newTrial = true;
  }
}
