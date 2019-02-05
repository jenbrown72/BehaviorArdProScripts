/* Orientation Behaviour Jenny Brown
  digital Count send a digital output of trial count
*/

void digitalCount() {

  // Amount of time given to send Digital data

  int purrTime = (millis()) + 500; //was 500

  // Send digital Trigger output
  digitalWrite(digitalTriggerPin, HIGH);
  delayMicroseconds(digSendTime);
  digitalWrite(digitalTriggerPin, LOW);

  //  // TARGTE JITTER STATE
  //  if (jitterTarget == true) {
  //    tempaddJitter = random(0, 3); //select a random amount of steps to move the stimulus further on
  //    addJitter = randomJitterArray[tempaddJitter];
  //    // addJitter = random(0, 100); //select a random amount of steps to move the stimulus further on
  //    jitterCount = 0;
  //  }

  // TARGTE JITTER STATE
  while (!digJitterSuccess) {
    digitalWrite(digitalCountPin, HIGH);
    delayMicroseconds(digSendTime);//
    digitalWrite(digitalCountPin, LOW);
    delayMicroseconds(digSendTime);//
    jitterCount = ++jitterCount;
    if (jitterCount >= (tempaddJitter + 1)) { // Check to see if we are at the end of our move
      digJitterSuccess = true;
      jitterCount = 0;
    }
  }

  delayMicroseconds(digSendTime * 3); //

  // CURRENT COUNT
  while (!digCountSuccess) {
    digitalWrite(digitalCountPin, HIGH);
    delayMicroseconds(digSendTime);//
    digitalWrite(digitalCountPin, LOW);
    delayMicroseconds(digSendTime);//
    digCount = ++digCount;

    if (digCount > (count) % 20) { // Check to see if we are at the end of our move
      digCountSuccess = true;
      digCount = 0;
    }
  }
  delayMicroseconds(digSendTime * 3); //

  // CURRENT ANGLE and CATCH
  while (!digitalAngleSuccess) {
    digitalWrite(digitalAnglePin, HIGH);
    delayMicroseconds(digSendTime);
    digitalWrite(digitalAnglePin, LOW);
    delayMicroseconds(digSendTime);
    digAngle = ++digAngle;

    if (digAngle >= (currMoveNum)) {  // Check to see if we are at the end of our move
      digitalAngleSuccess = true;
      digAngle = 0;

      if (currCatch) {
        delayMicroseconds(digSendTime * 3);
        digitalWrite(digitalAnglePin, HIGH);
        delayMicroseconds(digSendTime * 4);
        digitalWrite(digitalAnglePin, LOW);
      }
    }
  }

  while (millis() <= purrTime) {
  }
}
