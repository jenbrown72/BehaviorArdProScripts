
public void clearScreen() {

Table table = loadTable("inputData.csv","header");
String variableName;
int screenNo;

for (int i=0;i<table.getRowCount();i++){
TableRow row = table.getRow(i);
variableName= row.getString("variable");
screenNo= row.getInt("screenNo");

if (screenNo==1){
cp5.getController(variableName).setVisible(booleanVal);
}
else if (screenNo==2){
cp5.getController(variableName).setVisible(!booleanVal);
}
else if (screenNo==3){ //Alwayd dissapear
cp5.getController(variableName).setVisible(false);
}
else if (screenNo==0){ //Alwayd stay
cp5.getController(variableName).setVisible(true);
}
}
}