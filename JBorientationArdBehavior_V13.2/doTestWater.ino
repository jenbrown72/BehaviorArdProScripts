void doTestWater() {

  // if (!setDurationAuto) {
  //   rewardTimeAuto = (millis() + 50);
  //   digitalWrite(rewardPin, HIGH); //open valves
  //   digitalWrite(rewardPinR, HIGH); //open valves
  //   setDurationAuto = true;
  // }
  // if ((setDurationAuto) && (millis() > rewardTimeAuto)) {
  if (((millis()) > rewardTimeAuto)) {
    digitalWrite(rewardPin, LOW); //close valves
    digitalWrite(rewardPinR, LOW); //close valves
    testWater = false;
    setDurationAuto = false;
  }
}
