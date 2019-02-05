void addHomeJitter()
{
  if ((!extraMoveSet) && (homeJitter))
  {
    previousHomeJitter = addHomeposition;

    if (linearExp) {
      tempaddJitter = random(0, 3); //select a random amount of steps to move the stimulus further on
      addHomeposition = randomJitterArray[tempaddJitter];

      // reset to center/ home position
      if (previousHomeJitter < 0) { //negative from 0
        BackStep = true;
        openloopControl();
//        Serial.println("neg 1");
      }
      else if (previousHomeJitter > 0) {
        BackStep = false;
        openloopControl();
//        Serial.println("pos 1");
      }

      if (previousHomeJitter != 0) {
        jitterAtHome = true;
         digitalWrite(motor1enablePin, LOW); // Take off motor break
        while (positionCount < (abs(previousHomeJitter))) {
//          Serial.println("moving motor 1");
//          Serial.println(positionCount);
          movePositionMotor();
          delay(10);
        }
        jitterAtHome = false;
      }
      
      positionCount = 0;

      //now move to new home jitter position
//      Serial.println("addHomeposition");
//      Serial.println(addHomeposition);

      if (addHomeposition < 0) {
        BackStep = false;
        openloopControl();
      }

      else if (addHomeposition > 0) {
        BackStep = true;
        openloopControl();

      }

      if (addHomeposition != 0) {
        jitterAtHome = true;
        digitalWrite(motor1enablePin, LOW); // Take off motor break
        while (positionCount < (abs(addHomeposition))) {
          movePositionMotor();
          delay(10);
//          Serial.println("moving motor 2");
//          Serial.println(positionCount);
        }
       
        jitterAtHome = false;
      }
       digitalWrite(motor1enablePin, HIGH); // Turn ON motor break
      //    }
    }
    else
    {
      addHomeposition = random(0, 100); // randomly set how much further from home position stim will go to ensure each trial motor moves an unpredictable amount
    }
    positionCount = 0;
    extraMoveSet = true;
  }
  else
  {
    addHomeposition = 0;
  }
}

void calDistancesToMove()
{
  if (!fullCircle)
  {
    currstimINcount = (stimINcount + previousHomeJitter);
    currstimOUTcount = (stimINcount + stimOUTcount + addJitter + addHomeposition);
  }
  else
  {
    currstimINcount = (stimINcount - previousHomeJitter);
    currstimOUTcount = (diffTotalSteps + (stimOUTcount - addJitter)) + addHomeposition;
  }
  if (currCatch)
  {
    currstimINcount = currstimINcount - minusCatchDistance;
    if (!fullCircle)
    {
      currstimOUTcount = currstimOUTcount - minusCatchDistance;
    }
    else
    {
      currstimOUTcount = currstimOUTcount + minusCatchDistance;
    }
  }
  setDistanceToMove = false;
}
