/* Orientation Behaviour Jenny Brown

  SET Microstepping for Position Motor

  KEY: Use Microstepping Resolution Truth Table for Big Easy Driver
  MS1 MS2 MS3
  L L L - full Step
  H L L - half step
  L H L - quarter Step
  H H L - Eighth Step
  H H H - Sixteenth Step

  Closed Loop control between motor and running wheel - the microstepping needs to be selected.

*/

void closedloopControl() {
  digitalWrite(motor1enablePin, LOW); // Low enabled - the Position Motor
  digitalWrite(motor1controlPin, LOW); //switch from open to closed loop control
  digitalWrite(motor1MS1Pin, HIGH);
  digitalWrite(motor1MS2Pin, HIGH);
  digitalWrite(motor1MS3Pin, HIGH); //switch to half step microstepping
}

