void StartStop(boolean theFlag)
{
  if (readyToStart)
  {
    if (theFlag == true)
    {
      updateState = true;
      // myPort.write('c');
      serialString("c", "0", 1);
      println("Stop Recording");
      startedRecording = false;
      // controlSig = true;
      // canStart = false;
      waitForUpdates = true;
      booleanVal = true;
    }
    else
    {
      newFileNeeded = false;
      if (firstSubmit)
      {
        updateVariable();
        delay(1000);
        updateAngles();
        firstSubmit = false;
      }
      serialString("c", "1", 1);
      
      delay(100);
      println("Start Recording");
     // output.println("1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1");
      startedRecording = true;
      canStart = true;
      booleanVal = false;
      // controlSig = false;
      cp5.getController("Update").setValue(0);
      cp5.getController("newFile").setValue(0);
    }
  }
}