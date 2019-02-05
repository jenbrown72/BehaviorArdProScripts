/* Orientation Behaviour Jenny Brown
SET Microstepping for Stim Motor
KEY: Use Microstepping Resolution Truth Table for Big Easy Driver
MS1 MS2 MS3
L L L - full Step
H L L - half step
L H L - quarter Step
H H L - Eighth Step
H H H - Sixteenth Step
*/
void stimMotorMicroStepping()
{
  boolean motor2MS1m1 = 1;
  boolean motor2MS2m1 = 0;
  boolean motor2MS3m1 = 0;

  digitalWrite(motor2enablePin, LOW);
  digitalWrite(motor2DirPin, HIGH);

  digitalWrite(motor2MS1Pin, motor2MS1m1);
  digitalWrite(motor2MS2Pin, motor2MS2m1);
  digitalWrite(motor2MS3Pin, motor2MS3m1);

  if (motor2MS3m1 == 0){
    if (motor2MS2m1 == 0){
      if (motor2MS1m1 == 0) {
        motor2microStep = 1; // LOW LOW LOW
      }
      if (motor2MS1m1 == 1){
        motor2microStep = 2;  // HIGH LOW LOW
      }
    }
    else {
      if (motor2MS1m1 == 0) {
        motor2microStep = 4; // LOW HIGH LOW
      }
      if (motor2MS1m1 == 1) {
        motor2microStep = 8; // HIGH HIGH LOW
      }
    }
  }
  else
  {
      motor2microStep = 16; // HIGH HIGH HIGH
  }
  
  fullRevolutionStim = 200 * motor2microStep; // 200 steps / rev, 16th microstepping - this will depend on stepper motor used and microstepping settings - *Check StimMotorMicroStepping*
  stepsPerDegree = (fullRevolutionStim / 360); // divide total number of step by 360
  midPointAngleStep = (midPointStimulus * stepsPerDegree); // Always start with stim horizontal. So 0/360 degrees is horizontal. Vertical is 270 degrees.
}
