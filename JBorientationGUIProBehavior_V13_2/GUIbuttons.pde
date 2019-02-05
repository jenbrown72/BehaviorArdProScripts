void GUIbuttons(Table table, int noInputs, int state){
PFont font = createFont("arial", 9);
PFont font2 = createFont("arial", 24); //24

String[] varNames = new String[noInputs];
String[] varValues = new String[noInputs];
int[] toggleButton = new int[noInputs];
float[] xLocationT = new float[noInputs];
float[] yLocationT = new float[noInputs];
float[] vdiff = new float[noInputs];
int[] noOfRowsT = new int[noInputs];
String[] textLabel = new String[noInputs];
int[] divW = new int[noInputs];
int[] divH = new int[noInputs];
String[] incomingVals = new String[noInputs];
int[] newDiv = new int[noInputs];
int[] screenNo = new int[noInputs];
int[] alignText = new int[noInputs];
int[] fontSize = new int[noInputs];
int[] switchMode = new int[noInputs];

for (int i=0;i<table.getRowCount();i++){
TableRow row = table.getRow(i);
varNames[i]= row.getString("variable");
varValues[i]= row.getString("value");
toggleButton[i]= row.getInt("toggleButton");
xLocationT[i]= row.getFloat("xLocation");
yLocationT[i]= row.getFloat("yLocation");
vdiff[i]= row.getFloat("vdiff");
noOfRowsT[i]= row.getInt("noOfRows");
textLabel[i]= row.getString("textLabel");
divW[i]= row.getInt("divW");
divH[i]= row.getInt("divH");
incomingVals[i]= row.getString("incomingVals");
newDiv[i]= row.getInt("newDiv");
screenNo[i]= row.getInt("screenNo");
alignText[i]= row.getInt("alignText");
fontSize[i]= row.getInt("fontSize");
switchMode[i]= row.getInt("switchMode");
}

if (state==1){
makeButton(varNames, varValues, toggleButton, xLocationT, yLocationT, vdiff, noOfRowsT, textLabel, divW, divH, incomingVals,newDiv,screenNo,alignText,fontSize,switchMode);
}
else{
updateButton(varNames, varValues, toggleButton, xLocationT, yLocationT, vdiff, noOfRowsT, textLabel, divW, divH, incomingVals,newDiv,screenNo,alignText,fontSize,switchMode);
}

}