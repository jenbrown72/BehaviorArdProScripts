/* Orientation Behaviour Jenny Brown
SET Microstepping for Position Motor
KEY: Use Microstepping Resolution Truth Table for Big Easy Driver
MS1 MS2 MS3
L L L - full Step
H L L - half step
L H L - quarter Step
H H L - Eighth Step
H H H - Sixteenth Step
Open Loop control between motor and running wheel - the microstepping needs to be selected.
*/
void openloopControl()
{
  if (!fastSpeed)
  {
    // (SLOW approaching target area)
    digitalWrite(motor1MS1Pin, motor1MS1m1); // MS1
    digitalWrite(motor1MS2Pin, motor1MS2m1); // MS2
    digitalWrite(motor1MS3Pin, motor1MS3m1); // MS3
  }
  else
    if (fastSpeed)
    {
      // (FAST outside of target area)
      digitalWrite(motor1MS1Pin, motor1MS1m2); // MS1
      digitalWrite(motor1MS2Pin, motor1MS2m2); // MS2
      digitalWrite(motor1MS3Pin, motor1MS3m2); // MS3
    }
  // Select direction of motor stepping
  if (!BackStep)
  {
    digitalWrite(motor1DirPin, HIGH); // Pull direction pin low to move "forward"
  }
  else
  {
    digitalWrite(motor1DirPin, LOW); // Pull direction pin low to move "backwards"
  }
  digitalWrite(motor1controlPin, HIGH); // switch to open loop control
  digitalWrite(motor1enablePin, LOW); // low enabled
}
