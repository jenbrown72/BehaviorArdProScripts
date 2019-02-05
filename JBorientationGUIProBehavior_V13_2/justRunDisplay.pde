//public void justRunDisplay() {


void justRunDisplay(){
//bar chart of running Velocity

updateElapsedTime(); 
updateRunRewards();
updateRunRequirement();
// calculate smoothered velocity
calVelocity();
drawRunGraph(); 

if (loopTime==0) {
 loopTime=1;
}

//Display running
for (int i = 0; i < mxRun.length-1; i++) { // xpos[0] = xpos[1], xpos[1] = xpos = [2], and so on. Stop at the second to last element.
  mxRun[i] = mxRun[i+1]; 
  myVelWheelRun[i] = myVelWheelRun[i+1]; //x time series
}

mxRun[mxRun.length-1] = xPos; // Update the last spot in the array with the mouse location.
myVelWheelRun[myVelWheelRun.length-1] = int(ScreenSizeH*(lineDisplayHeight) - (average*tickHeight));
text("Run Velocity", ScreenSizeW*0.005, ScreenSizeH*(lineDisplayHeight));

// Draw everything
for (int i = 0; i < mxRun.length-1; i++) {
  strokeWeight(3); //stroke wider   
  if (mxRun[i+1]==width/12) {
    continue;
  } else {
    stroke(250, 0, 0); //stroke color
    line(mxRun[i+1], myVelWheelRun[i+1], mxRun[i], myVelWheelRun[i]);
  }
}

//velocity zero line
strokeWeight(1);  
stroke(155, 0, 0);     //stroke color
line(width/12, ScreenSizeH*(lineDisplayHeight), width/1.1, ScreenSizeH*(lineDisplayHeight));

//   at the edge of the window, go back to the beginning:
if (xPos >= width/1.1) {
  xPos = width/12;
  background(0);  //Clear the screen.
} else { 
  xPos=xPos+screenStepSize; // increment the horizontal position:
}

//UPDATE CUMMULATIVE PLOT OF RUNNING VELOCITY
if (readIndexVel >=numReadingsVel) {
  for (int i=0; i<readingsVel.length; ++i)
  {
    averageVel +=readingsVel[i];
  }
  averageVel/=(float)(readingsVel.length);
  readIndexVel = 0; //wrap around to the beginning
  BinnedRunningVel.append(averageVel);
  float[] BinnedPerformanceVelF = BinnedRunningVel.array();
  barChartVel.setData(BinnedPerformanceVelF);
  updateRunningDistance();
  updateRunningVelocity();
}
}

void drawRunGraph(){

barChartVel.draw(BinPositionWidthVel, BinPositionHeightVel, BinWidthVel, BinHeightVel);
stroke(120, 120, 120); 
fill(120,120,120);
strokeWeight(1); //stroke smaller

line(ScreenSizeW*barWidthLineValue, BinPositionHeightVel, ScreenSizeW*barWidthLineValue+BinWidthVel, BinPositionHeightVel);
text("200", ScreenSizeW*barWidthValue, BinPositionHeightVel);
line(ScreenSizeW*barWidthLineValue, BinPositionHeightVel+(BinHeightVel/4), ScreenSizeW*barWidthLineValue+BinWidthVel, BinPositionHeightVel+(BinHeightVel/4));
text("150", ScreenSizeW*barWidthValue, BinPositionHeightVel+(BinHeightVel/4));
line(ScreenSizeW*barWidthLineValue, BinPositionHeightVel+(BinHeightVel/2), ScreenSizeW*barWidthLineValue+BinWidthVel, BinPositionHeightVel+(BinHeightVel/2));
text("100", ScreenSizeW*barWidthValue, BinPositionHeightVel+(BinHeightVel/2));
line(ScreenSizeW*barWidthLineValue, BinPositionHeightVel+(BinHeightVel-(BinHeightVel/4)), ScreenSizeW*barWidthLineValue+BinWidthVel, BinPositionHeightVel+(BinHeightVel-(BinHeightVel/4)));
text("50", ScreenSizeW*barWidthValue, BinPositionHeightVel+(BinHeightVel-(BinHeightVel/4)));
line(ScreenSizeW*barWidthLineValue, BinPositionHeightVel+(BinHeightVel/1), ScreenSizeW*barWidthLineValue+BinWidthVel, BinPositionHeightVel+(BinHeightVel/1));
text("0%", ScreenSizeW*barWidthValue, BinPositionHeightVel+(BinHeightVel/1));
text("time", ScreenSizeW*0.5, ScreenSizeH*0.6);
float x=ScreenSizeW*0.03;
float y=ScreenSizeH*0.3;
pushMatrix();
translate(x, y);
rotate(HALF_PI);
text("velocity cm/s", 0, 0);
popMatrix(); 
}


void calVelocity(){
totalVel = totalVel - readingsVel[readIndexVel]; //subtract last line
totalDistance = (oldDistance + (encoderStepNo*cmPerStep));
oldDistance = totalDistance;
readingsVel[readIndexVel] = ((encoderStepNo*cmPerStep)/(loopTime/1000));// calculate loop velocity
totalVel = totalVel +readingsVel[readIndexVel]; //add the readings to the total
readIndexVel = readIndexVel + 1; //advance to the next position in the array
}

void updateRunRequirement(){

  Textfield txt = ((Textfield)cp5.getController("RunToInitiate"));
    txt.setValue(""+ String.format("%.2f",(LEDvolt)));
}