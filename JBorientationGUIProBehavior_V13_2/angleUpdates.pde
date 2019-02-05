
void midpoint(boolean theFlag) {
  int idxAngles [] = {6};
    prepStims(idxAngles, theFlag, updateState);
}

void S1(boolean theFlag) {
  int idxAngles [] = {0};
    prepStims(idxAngles, theFlag, updateState);
}

void S1_Opp(boolean theFlag) {
  int idxAngles [] = {12};
    prepStims(idxAngles, theFlag, updateState);
}

void S2(boolean theFlag) {
  int idxAngles [] = {0, 12};
    prepStims(idxAngles, theFlag, updateState);
}

void S6(boolean theFlag) {
  int idxAngles [] = {0, 1, 2, 10, 11, 12};
    prepStims(idxAngles, theFlag, updateState);
}

void S8(boolean theFlag) {
  int idxAngles [] = {0, 1, 2, 3, 9, 10, 11, 12};
    prepStims(idxAngles, theFlag, updateState);
}

void S10(boolean theFlag) {
  int idxAngles [] = {0, 1, 2, 3, 4, 8, 9, 10, 11, 12};
    prepStims(idxAngles, theFlag, updateState);
}

void S12(boolean theFlag) {
  int[] idxAngles = {0, 1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12};
  prepStims(idxAngles, theFlag, updateState);
}

void S13(boolean theFlag) {
  int idxAngles [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    prepStims(idxAngles, theFlag, updateState);
}

void prepStims(int idxAngles[], boolean theFlag, boolean updateState) {
   numStimPositions=idxAngles.length;
  if ( theFlag==true) {
    if (updateState) {
      newFileNeeded = true;
    }
      for (int i = 0; i<idxAngles.length; i++) { 
    ref = idxAngles[i];
    activeAngle[ref] = angles[ref];
  }

  } else {
      for (int i = 0; i<idxAngles.length; i++) {
    ref = idxAngles[i];
    activeAngle[ref] = 0;
  }
  }
}


public void updateAngles() {
  myPort.write('a'); //send a to tell arduino to expect new angles.
  for (int i=0; i<activeAngle.length; i++) {
 int curInt = (int)activeAngle[i];
 serialString("0", str(curInt),0);
 output.println("Orientation Selected = " + "," + str(curInt));
  }
 myPort.write('x');


 
  ResetVals();
  sendAngles = false;
}


void setUPstim(){
for (int i = 0; i <activeAngle.length; i++) {

 if (activeAngle[i]>0) {
      if ((activeAngle[i])<midPointAngle) {
        drawStimPlot(i,1); 
      } 
         else if ((activeAngle[i])==midPointAngle) {
        drawStimPlot(i,1); 
      } 
            else if ((activeAngle[i])>midPointAngle) {
        drawStimPlot(i,2); 
      } 
}
      else
         {
        drawStimPlot(i,4); 
      } 
}
}