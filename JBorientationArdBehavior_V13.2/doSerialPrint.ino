   void doSerialPrint() {
    Serial.print(encoder0Pos);
    Serial.print(",");
    Serial.print(targetArea); //targetArea
    Serial.print(",");
    Serial.print(rewarded);
    Serial.print(",");
    Serial.print(licksL);//licksL
    Serial.print(",");
    Serial.print(LEDstate); //LEDstate
    Serial.print(",");
    Serial.print(count); //count
    Serial.print(",");
    Serial.print(millis() - pauseDuration); //millis() - pauseDuration
    Serial.print(",");
    Serial.print(autoReward);
    Serial.print(",");
    Serial.print(maskingLEDstate); // //maskingLEDstate
    Serial.print(",");
    Serial.print(givePuff); //givePuff
    Serial.print(",");
    Serial.print(lastAngle); //round(lastMove / stepsPerDegree)
    Serial.print(",");
    Serial.print(currCatch); // testWater
    Serial.print(",");
    Serial.print(TrialType); //TrialType
    Serial.print(",");
    Serial.print((millis()-loopTime)); //(millis()-loopTime)
    Serial.print(",");
    Serial.print(encoder); //encoder
    Serial.print(",");
    Serial.print(addHomeposition); //JitterValue licksR addJitter
    Serial.print(",");
    Serial.print(rewardedR); //rewardedR   waitDuration
    Serial.print(",");
    Serial.println(currOptoLEDState); //currOptoLEDState previousHomeJitter = addHomeposition;
   }
