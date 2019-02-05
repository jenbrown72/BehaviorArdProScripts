
public void newFileVars() {

    PFont font = createFont("arial", 9);

  String mouseIDtemp = cp5.get(Textfield.class, "Mouse_ID").getText();
  String boxIDtemp = cp5.get(Textfield.class, "Box_No").getText();
  String fileName = "_"+str(year())+"_"+str(month())+"_"+str(day())+"_"+str(hour())+"_"+str(minute()); 
 
  output = createWriter(currFolder+mouseIDtemp+fileName+"_Box"+boxIDtemp+".txt"); 
  print("Creating new Data Storage File: ");
  println(currFolder+mouseIDtemp+fileName+"_Box"+boxIDtemp+".txt");
  println("");
 // output = createWriter("DataBuffer/"+mouseIDtemp+fileName+"_Box"+boxIDtemp+".txt");
  String CommentsTemp = cp5.get(Textfield.class, "Comments").getText();
  output.println("MouseID = " + "," + mouseIDtemp);
  output.println("BoxNo = " + "," + boxIDtemp);
  output.println("Comments = " + "," + CommentsTemp);
   readyToStart = true;
}