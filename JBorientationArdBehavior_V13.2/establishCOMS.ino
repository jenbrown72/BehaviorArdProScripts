/* Orientation Behaviour Jenny Brown
  This interrupt is run during set up to establish communication between JAVA and arduino

*/
void establishCOMS() {
  // Extablish Contact : send a byte to establish contact and wait until receiver responds
  while (Serial.available() <= 0) {
    Serial.println('A');
    delay(300);
  }
  char a = 'b';
  while (a != 'A')
  {
    a = Serial.read();
  }
   //stimMotorMicroStepping(); // put break on stim motor so it holds in place
}
