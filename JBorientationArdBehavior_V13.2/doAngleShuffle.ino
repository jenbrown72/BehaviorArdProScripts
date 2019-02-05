void doAngleShuffle()
{
  // Serial.println("doing Angle Shuffle");
  int gg = 0;
  int runningTotal = 0;
  int angleNo = 0;
  int optoControlTally = 0;
  for (int k = 0; k < trialBlockTotal; k++)
  {
    // Serial.println(numStimPositions);
    if ((angleNo % ((numStimPositions))) == 0)
    {
      angleNo = 0;
    }
    if (k == trialStructure[gg] + runningTotal)
    {
      runningTotal = runningTotal + trialStructure[gg];
      gg++;
    }
    blockSize[k] = stimulusIDNumberTwo[angleNo];
    catchTrials[k] = catchStructure[gg];
    optoTrials[k] = optoStructure[gg];
    if ((optoStructure[gg] == 1) && (catchStructure[gg] == 0))
    {
      if (optoControlTally < optoTrialsControl)
      {
        optoTrialsVoltage[k] = LEDvoltageState[0];
      }
      else
        if (optoControlTally < (optoTrialsControl * 2))
        {
          optoTrialsVoltage[k] = LEDvoltageState[1];
        }
      else
        if (optoControlTally < (optoTrialsControl * 3))
        {
          optoTrialsVoltage[k] = LEDvoltageState[2];
        }
      optoControlTally++;
    }
    if ((optoStructure[gg] == 1) && (catchStructure[gg] == 1))
    {
      // Randomly pic LED state
      int r = random(0, numLEDStates);
      optoTrialsVoltage[k] = LEDvoltageState[r];
    }
    angleNo++;
  }
//   for (int i = 0; i < trialBlockTotal; i++)
//   {
//     Serial.print(numStimPositions);
//     Serial.print(",");
//     Serial.print(optoTrialsVoltage[i]);
//     Serial.print(",");
//     Serial.print(numLEDStates);
//     Serial.print(",");
//     Serial.print(blockSize[i]);
//     Serial.print(",");
//     Serial.print(i);
//     Serial.print(",");
//     Serial.print(optoTrials[i]);
//     Serial.print(",");
//     Serial.println(catchTrials[i]);
//     delay(10);
//     if (i == trialBlockTotal - 1)
//     {
//       Serial.println(" ");
//       Serial.println(" ");
//       delay(2000);
//     }
//   }
  int repeatMax = 3; // number of the same stim type allowed sequencially
  boolean GoAngle = true;
  boolean Reshuffle = false;
  for (int a = 0; a < trialBlockTotal; a++)
  {
    int r = random(a, trialBlockTotal); // random (min, max)
    if ((blockSize[r]) < (halfStimPos))
    {
      // Serial.println("check1");
      // Serial.println((blockSize[r]));
      gotally++;
      nogotally = 0;
      GoAngle = true;
    }
    else
      if ((blockSize[r]) >= (halfStimPos))
      {
        // Serial.println("check2");
        // Serial.println((blockSize[r]));
        nogotally++;
        gotally = 0;
        GoAngle = false;
      }
    if (numStimPositions > 1)
    {
      if ((gotally > repeatMax) || (nogotally > repeatMax))
      {
        Reshuffle = true;
        int outofTrials = 1;
        // Serial.println("ReShuffled");
        while (Reshuffle)
        {
          // 3 of the same in a row; reshuffle and check again
          r = random(a, trialBlockTotal); // random (min, max)
          if ((GoAngle) && ((blockSize[r]) >= (halfStimPos)))
          {
            // goAngle
            // Serial.println("check3");
            Reshuffle = false;
            gotally = 0;
            GoAngle = false;
            nogotally = 1;
          }
          else
            if ((!GoAngle) && ((blockSize[r]) < (halfStimPos)))
            {
              // Serial.println("check4");
              Reshuffle = false;
              gotally = 1;
              GoAngle = true;
              nogotally = 0;
            }
          else
          {
            outofTrials++;
            if ((outofTrials > 3) && ((blockSize[r]) < (halfStimPos)))
            {
              // Serial.println("check4");
              Reshuffle = false;
              gotally = 1;
              GoAngle = true;
              nogotally = 0;
            }
            else
              if ((outofTrials > 3) && ((blockSize[r]) >= (halfStimPos)))
              {
                // goAngle
                // Serial.println("check3");
                Reshuffle = false;
                gotally = 0;
                GoAngle = false;
                nogotally = 1;
              }
          }
        }
      }
    }
    int temp = blockSize[a];
    blockSize[a] = blockSize[r];
    blockSize[r] = temp;
    int tempOpto = optoTrials[a];
    optoTrials[a] = optoTrials[r];
    optoTrials[r] = tempOpto;
    int tempOptoLED = optoTrialsVoltage[a];
    optoTrialsVoltage[a] = optoTrialsVoltage[r];
    optoTrialsVoltage[r] = tempOptoLED;
    int tempCatch = catchTrials[a];
    catchTrials[a] = catchTrials[r];
    catchTrials[r] = tempCatch;
  }
  // for (int i = 0; i < trialBlockTotal; i++)
  // {
  //   Serial.print(numStimPositions);
  //   Serial.print(",");
  //   Serial.print(optoTrialsVoltage[i]);
  //   Serial.print(",");
  //   Serial.print(numLEDStates);
  //   Serial.print(",");
  //   Serial.print(blockSize[i]);
  //   Serial.print(",");
  //   Serial.print(i);
  //   Serial.print(",");
  //   Serial.print(optoTrials[i]);
  //   Serial.print(",");
  //   Serial.println(catchTrials[i]);
  // }
}
