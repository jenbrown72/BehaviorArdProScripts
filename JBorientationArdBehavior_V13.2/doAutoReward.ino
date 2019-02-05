/* Orientation Behaviour Jenny Brown
  Auto Reward is used during training - if called reward is automatically delivered when stimulusID is in target region
*/

void doAutoReward() {


if (!testWater) {
    testWater = true;
    rewardTimeAuto = ((millis()) + 100);
    digitalWrite(rewardPin, HIGH); //open valves
    digitalWrite(rewardPinR, HIGH); //open valves
}
}

