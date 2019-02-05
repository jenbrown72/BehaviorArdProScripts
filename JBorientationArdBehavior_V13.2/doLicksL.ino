/* Orientation Behaviour Jenny Brown
  This interrupt is run when the photobeam or electrical signal from the lick port is active to record licking

*/

// Licking PhotoInterrupt Pin

void doLicksL() {
  if (digitalRead(licksLPin) == HIGH) {
  //  Serial.println("LICK");
    licksL = true;
  }
  else {
  licksL = false;
  }
}
