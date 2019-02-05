void serialEvent(Serial myPort) {  // use serialEvent() because of intermittent Arduino data

  String dataReading = myPort.readStringUntil('\n');  // use readStringUntil() to make sure we get entire serial package
  if (establishCOMS) { // if establishCOMS is set to true - this happens after all inputs are entered and we want to send angle values to arduino 
      dataReading = trim(dataReading); 
      if (dataReading.equals("A")) {
        myPort.clear();
        myPort.write("A");
        println("Contact made from Arduino to Processing");
        establishCOMS = false;
        newFileVars();
      }
  }  

  else if (canStart) { //if can start is set to true - this happens after all inputs are entered

    // Write the Arduino data to a file
    output.print(dataReading);  // write the output to .txt file as string (will just be number in text)
    print(dataReading);  // print trigger times to this display

    String[] items = split(dataReading, ','); //split the string into multiple strings where there is a ","
    float[] values = float(items);

    if (values.length >= 18) { //check that you have recieved over serial the right length of variables
      encoder0Pos = values[0];
      targetArea = values[1];
      rewarded = values[2];
      licksL = values[3];
      LEDstate = values[4];
      count = values[5];
      time = values[6];
      autoReward = values[7];
      breakON = values[8];
      negReward = values[9];
      lastMove = values[10];
      catchTrial = values[11];
      trialType = values[12];
      loopTime = values[13];
      encoderStepNo = values[14];
      licksR = values[15];
      rewardedR = values[16];
      LEDvolt = values[17];
    }
  }

 //  else if ((!startedRecording) && (!canStart)){
 // println("message recieved: "+trim(dataReading));

 //  }

  // else {

  //   println("off: "+trim(dataReading));
  // }
}

void serialString( String marker, String input, int end) {

if (marker.equals("0") == false){
      myPort.write(marker);
    }
      myPort.write(input);
      myPort.write('e');
      if (end==1){
      myPort.write('x');
  }
}