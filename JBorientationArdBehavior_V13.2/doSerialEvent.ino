void serialEvent()
{
  c = Serial.read(); //stimulusID being sent
  if (c == 'a')
  {
    updateStimuli();
  }

  else if (c == 'v')
  {
    updateVariable();
  }
  else
    if (c == 'c') //control signal
    {
      while (Serial.available() >= 0)
      {
        c = Serial.read();
        if ((c >= '0') && (c <= '9'))
          //check if a digit was sent
        {
          v = 10 * v + c - '0'; // handle digit one by one and add to v
        }
        else
          if (c == 'e')
          {
            controlSig = v;
          }
        else
          if (c == 'x')
          {
            v = 0;
            break;
          }
      }
      Serial.println(controlSig);
      if (controlSig == 1)
      {
        if ((!calFinished) && (!justRun))
        {
          calibrate = true;
          firstCalibration = true;
          targetPos = false;
          BackStep = false;
          fastSpeed = true;
          openloopControl(); // set motor properties for open loop control
          newTrialStarted = true;
          encoder0Pos = 0;
        }
        else
          if ((!calFinished) && (justRun))
          {
            calibrate = false;
            startSerial = true;
            calFinished = true;
            homePos = false;
            targetPos = false;
          positionCount = 0; 
            encoder0Pos = 0;
            pauseDuration = (pauseDuration + (millis() - pauseDurationStart));
            digitalWrite(motor1enablePin, HIGH); // Low enabled - the Position Motor
          }
        else
          if (calFinished)
          {
            startSerial = true;
            encoder0Pos = temp_encoder0Pos; // NEW
            temp_pauseDuration = (millis() - pauseDurationStart); // NEW
            positionCount = temp_positionCount;
            digitalWrite(motor1enablePin, temp_motorState);
           // encoder0Pos = 0; // NEW
            pauseDuration = (pauseDuration + (millis() - pauseDurationStart)); // NEW
          }
      }
      else
        if (controlSig == 0)
        {
          startSerial = false;
          temp_positionCount = positionCount;
          temp_encoder0Pos = encoder0Pos;
          temp_motorState = digitalRead(motor1enablePin);
          digitalWrite(motor1enablePin, HIGH);
          pauseDurationStart = millis();
              digitalWrite(rewardPin, LOW); //open valves
    digitalWrite(rewardPinR, LOW); //open valves
          k=0;
          kk=0;
        }
      else
        if (controlSig == 3 || controlSig == 4)
        {
          // update variables
          k=0;
         //  updateVariable();
        }
      else
        if (controlSig == '6' || controlSig == '7')
        {
          LEDdriverCalibration();
        }
    }

    else {
      Serial.println(c);
    }
}

