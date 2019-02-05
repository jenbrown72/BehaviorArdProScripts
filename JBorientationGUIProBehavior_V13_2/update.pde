void Update(boolean theFlag) {

  if (waitForUpdates) {
    if (theFlag==true) {
      if (newFileNeeded) {
      serialString("c","4",1); 
        updating = false;
        newFileVars();
        updateVariable();
        println("Finished variable updates");
        delay(1000);
        updateAngles(); // when you are updating angles always create a new file 
        println("Finished updates with new file");
      } else {
     // serialString("c","3",1); 
       // myPort.write('3'); 
        updating = true;
        updateVariable();

        delay(1000);
        println("Finished Updates");
      }
    }
  }
}