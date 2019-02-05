
void newFile(boolean theFlag) {
  
  if (theFlag==true) {
    println("New File Created");
  updating = false;
    myPort.write('4'); 
    ResetVals();
    newFileVars();
    updateVariable();
    delay(1000);
    updateAngles();
  }
}