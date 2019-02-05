/* Orientation Behaviour Jenny Brown
  This interrupt is run when the position motor breaks the home photointerrupt

*/
void doHome() {

  if (calibrate) {
    homePos = true;
    falseAlarm = false;
    digitalWrite(digitalTriggerPin, LOW);
  }
  else if (firstHome) {
    homePos = true;
    newTrial = true;
    falseAlarm = false;
    firstHome = false; //dont allow this interrup to be called again until the end of next trial
    setDistanceToMove = true;
    reachedHome = true;
    digitalWrite(motor1enablePin, HIGH); // Put the break on the Position Motor
    backToHome = false;
    setSpeed1 = true;
    setSpeed2 = true;
    setSpeed3 = true;
    temp_pauseDuration = 0;
    //addJitter=0;
    digitalWrite(digitalTriggerPin, LOW);

//    if (linearExp) {
//
//      Serial.println("startinglinearhome");
//
//      // reset to center/ home position
//      if (previousHomeJitter < 0) { //negative from 0
//        BackStep = true;
//        openloopControl();
//        Serial.println("neg 1");
//      }
//      else if (previousHomeJitter > 0) {
//        BackStep = false;
//        openloopControl();
//        Serial.println("pos 1");
//      }
//
//      if (previousHomeJitter != 0) {
//        while (positionCount < (abs(previousHomeJitter))) {
//          Serial.println("moving motor 1");
//          Serial.println(positionCount);
//          movePositionMotor();
//          delay(100);
//        }
//      }
//
//      positionCount = 0;
//
//      //now move to new home jitter position
//
//      if (addHomeposition < 0) {
//        BackStep = false;
//        openloopControl();
//
//      }
//
//      else if (addHomeposition > 0) {
//        BackStep = true;
//        openloopControl();
//
//      }
//
//      if (addHomeposition != 0) {
//        while (positionCount < (abs(previousHomeJitter))) {
//          movePositionMotor();
//          delay(100);
//          Serial.println("moving motor 2");
//          Serial.println(positionCount);
//        }
//      }
//    }
  }
}


