// public void updateVariable() {
void updateVariable()
{
  // Load outputData file
  println("Searching for outputData.csv file to load in current folder");
  Table tableOUT = loadTable("outputData.csv", "header");
  println("File loaded");
  println("");
  println("....SENDING EXPERIMENTAL SETUP TO ARDUINO....");
  println("");
  String variableName;
  int printToTxt;
  int getTxtVals;
  tabledLoaded = true;
  myPort.write('v');

  String str1 = "midPointStim";
  //send blank so that the first variable we recieve sends correctly
 //serialString("0", "1", 0);

  for (int i = 0; i < tableOUT.getRowCount(); i++)
  {
 //   println(i);
    TableRow row = tableOUT.getRow(i);
    variableName = row.getString("variable");
    printToTxt = row.getInt("printToTxt");
    getTxtVals = row.getInt("getTxtVals");


    if (getTxtVals == 1)
    {
      String tempVal = cp5.get(Textfield.class, variableName).getText();
      serialString("0", tempVal, 0);
      if (printToTxt == 1)
      {
        output.println(variableName + "," + tempVal);
      }
    }
    // if these are TogglesString tempVal
    else
    {

if (str1.equals(variableName) ==true){

serialString("0", str(midPointAngle), 0);

}

else{
      // Find out if toggle is true or false
      float state = cp5.get(Toggle.class,(variableName)).getValue();
      if (state == 1)
      {
        serialString("0", "1", 0);
        if ((!updating) && (printToTxt == 1))
        {
          // only prit to txt file when a new file has been created, not when just updating
          output.println(variableName + "," + 1);
        }
      }
      else
      {
        serialString("0", "0", 0);
        if ((!updating) && (printToTxt == 1))
        {
          output.println(variableName + "," + 0);
        }
      }
    }
  }
  }
  myPort.write('x');
}