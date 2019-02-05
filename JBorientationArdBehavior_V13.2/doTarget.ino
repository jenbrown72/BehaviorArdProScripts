/* Orientation Behaviour Jenny Brown
  This interrupt is run when the position motor breaks the target photointerrupt

*/


void doTarget() {
  /* If indexPin went from HIGH to LOW - moter just went through the target position sensor. Re set values.
  */

	// Serial.print("DoTarget: ");
	// Serial.print(targetPos);
	// Serial.print("");
	// Serial.println(newTrialStarted);
 if ((!targetPos) && (newTrialStarted)){
 //	Serial.println("past Target");
  targetPos = true;
  //moveToTarget=false;
   positionCount=0;
  startSample = true;
  newTrialStarted = false;
  }
}
