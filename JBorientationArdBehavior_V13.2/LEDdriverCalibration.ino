void  LEDdriverCalibration(){
if (controlSig== '6'){
       while (Serial.available() <= 0) {}  //wait for user input
    CalvoltageSig = Serial.read();
    Serial.println(CalvoltageSig); //rewardedR
    analogWrite(LEDPin, CalvoltageSig);

}
   else if (controlSig== '7'){
       analogWrite(LEDPin, 0);  
  }
}

