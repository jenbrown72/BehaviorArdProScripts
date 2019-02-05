/* Orientation Behaviour Jenny Brown
  This interrupt is run when the photobeam or electrical signal from the lick port is active to record licking

*/


void doLicksR() {
  if (digitalRead(licksRPin) == HIGH) {
    licksR = true;
  }
  else {
    licksR = false;
  }
}
