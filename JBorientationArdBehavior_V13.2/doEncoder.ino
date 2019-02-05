/* Orientation Behaviour Jenny Brown
  This interrupt is used to monitor direction and steps of the running wheel
  If pinA and pinB are both high or both low, it is spinning
  forward. If they're different, it's going backward.

*/

void doEncoder() {

  //NEW PCBS
 if (digitalRead(encoder0PinA) != digitalRead(encoder0PinB)) { // B leads A = clockwise rotation, A leads B = anticlockwise
    //OLDER PCBS

// if (digitalRead(encoder0PinA) == digitalRead(encoder0PinB)) { // B leads A = clockwise rotation, A leads B = anticlockwise

    if (encoder0Pos == 0) {
      encoder0Pos = 0;
    }
    else {
      encoder0Pos--;
    }
    encoder++;
  }
  else {  // forwards
    encoder0Pos++;
    encoder++;
  }
}


