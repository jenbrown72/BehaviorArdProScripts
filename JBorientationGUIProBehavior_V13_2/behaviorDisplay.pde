
public void behaviorDisplay() {
  // Shift array values
  updateCountTotal();
  barChart.draw(ScreenSizeW*0.6, ScreenSizeH*(startingHeightChart), BinWidth, BinHeight);
  stroke(120, 120, 120); 
  strokeWeight(1); //stroke smaller

  if (catchTrial==1) {
    stroke(255, 0, 0); 
    text("CatchTrial", ScreenSizeW*0.41, ScreenSizeH*0.67);
  }

if ((targetArea==0) && (!first)) {
first = true;
}
  if ((targetArea==1) && (first)) {
first = false;

    if (catchTrial==0) {
      countTrialTally++;
    }

    if ((LEDstate==1) && (catchTrial==0)) {
      countStim++;
      updatePerformanceStim();
      StimTrial = true;
    } else if (LEDstate==0) { //new trial
      StimTrial = false;
    }

    if (catchTrial==1) {
      //if Detection task (S1) and catch
      if ((notCount) && (numStimPositions==1)) {
        notCount=true;
        countTrialTally++;
      } else if ((notCount)&& (numStimPositions!=1)) {
        catchTrialTally++;
        updateCatchCountTotal();
        notCount=false;
      }
      if (LEDstate==1) {
        countStim++;
        updatePerformanceStim();
        StimTrial = true;
      } else if (LEDstate==0) { //new trial
        StimTrial = false;
      }
    }
  }
  if (catchTrial==0 && trialType==0) {
    notCount=true;
  }

  //bar chart setup
  line(ScreenSizeW*0.6, ScreenSizeH*(startingHeightChart), ScreenSizeW*0.6+BinWidth, ScreenSizeH*(startingHeightChart));
  text("100%", ScreenSizeW*0.57, ScreenSizeH*(startingHeightChart));
  line(ScreenSizeW*0.6, ScreenSizeH*(startingHeightChart)+(BinHeight/4), ScreenSizeW*0.6+BinWidth, ScreenSizeH*(startingHeightChart)+(BinHeight/4));
  text("75%", ScreenSizeW*0.57, ScreenSizeH*(startingHeightChart)+(BinHeight/4));
  line(ScreenSizeW*0.6, ScreenSizeH*(startingHeightChart)+(BinHeight/2), ScreenSizeW*0.6+BinWidth, ScreenSizeH*(startingHeightChart)+(BinHeight/2));
  text("50%", ScreenSizeW*0.57, ScreenSizeH*(startingHeightChart)+(BinHeight/2));
  line(ScreenSizeW*0.6, ScreenSizeH*(startingHeightChart)+(BinHeight-(BinHeight/4)), ScreenSizeW*0.6+BinWidth, ScreenSizeH*(startingHeightChart)+(BinHeight-(BinHeight/4)));
  text("25%", ScreenSizeW*0.57, ScreenSizeH*(startingHeightChart)+(BinHeight-(BinHeight/4)));
  line(ScreenSizeW*0.6, ScreenSizeH*(startingHeightChart)+(BinHeight/1), ScreenSizeW*0.6+BinWidth, ScreenSizeH*(startingHeightChart)+(BinHeight/1));
  text("0%", ScreenSizeW*0.57, ScreenSizeH*(startingHeightChart)+(BinHeight/1));
  text("binned performance", ScreenSizeW*0.7, ScreenSizeH*(startingHeightChart+0.2));

  if (BinnedhitTally+BinnedmissTally+BinnedcorrectRejectionTally+BinnedfalseAlarmTally>0) {
    if ((((BinnedhitTally+BinnedmissTally+BinnedcorrectRejectionTally+BinnedfalseAlarmTally)%BinSize)==0) && (!reSetBins)) {
      TempbinnedPerformance = (((BinnedhitTally+BinnedcorrectRejectionTally)/BinSize)*100);
      BinnedPerformance.append(TempbinnedPerformance);
      float[] BinnedPerformanceF = BinnedPerformance.array();
      barChart.setData(BinnedPerformanceF);
      BinnedhitTally = 0;
      BinnedmissTally = 0;
      BinnedcorrectRejectionTally = 0;
      BinnedfalseAlarmTally = 0;
      reSetBins = true;
    }
    reSetBins = false;
  }

  if (lastTrialType==0 && trialType==1 && (notCount)) {

    if (!StimTrial) { //non stim trial
      hitTally++;
      BinnedhitTally++;
      updatePerformanceHIT(); 
      updatePerformance(); 
      lastTrialType=1;
    } else if (StimTrial) { // stim trial
      hitTallyStim++;
      BinnedhitTallyStim++;
      updatePerformanceHITStim(); 
      updatePerformanceStim(); 
      lastTrialType=1;
    }
  } else if (lastTrialType==0 && trialType==3 && (notCount)) {

    if (!StimTrial) {
      missTally++;
      BinnedmissTally++;
      updatePerformanceMISS();
      updatePerformance(); 
      lastTrialType=3;
    } else if (StimTrial) { // stim trial
      missTallyStim++;
      BinnedmissTallyStim++;
      updatePerformanceMISSStim(); 
      updatePerformanceStim(); 
      lastTrialType=3;
    }
  } else if (lastTrialType==0 && trialType==4 && (notCount)) {

    //delay(10);
    if (!StimTrial) {
      correctRejectionTally++;
      BinnedcorrectRejectionTally++;
      updatePerformanceCR(); 
      updatePerformance();
      lastTrialType=4;
    } else if (StimTrial) {
      correctRejectionTallyStim++;
      BinnedcorrectRejectionTallyStim++;
      updatePerformanceCRStim(); 
      updatePerformanceStim();
      lastTrialType=4;
    }
  } else if (lastTrialType==0 && trialType==2 && (notCount)) {
    if (!StimTrial) {
      falseAlarmTally++;
      BinnedfalseAlarmTally++;
      updatePerformanceFA();
      updatePerformance();
      lastTrialType=2;
    }

    if (StimTrial) {
      falseAlarmTallyStim++;
      BinnedfalseAlarmTallyStim++;
      updatePerformanceFAStim();
      updatePerformanceStim();
      lastTrialType=2;
    }
  } else if (trialType==0) {
    lastTrialType=0;
  }

  for (int i = 0; i < mx.length-1; i ++ ) {
    // Shift all elements down one spot. 
    // xpos[0] = xpos[1], xpos[1] = xpos = [2], and so on. Stop at the second to last element.
    mx[i] = mx[i+1]; 
    myLED[i] = myLED[i+1];
    myTA[i] = myTA[i+1];
    myLickL[i] = myLickL[i+1];
    myLickR[i] = myLickR[i+1];
    myReward[i] = myReward[i+1];
    myRewardR[i] = myRewardR[i+1];
    myNegReward[i] = myNegReward[i+1];
    myVelWheel[i] = myVelWheel[i+1]; //x time series
  }

  // New location
  mx[mx.length-1] = xPos; // Update the last spot in the array with the mouse location.
  myVelWheel[myVelWheel.length-1] = int(ScreenSizeH*(lineDisplayHeight) - (average*tickHeight));
  text("Run Velocity", ScreenSizeW*0.005, ScreenSizeH*(lineDisplayHeight));
  myLED[myLED.length-1] = int(ScreenSizeH*(lineDisplayHeight+0.04)  -(LEDstate*tickHeight));
  myTA[myTA.length-1] = int(ScreenSizeH*(lineDisplayHeight+0.04) -(targetArea*tickHeight));
  text("Response Window", ScreenSizeW*0.005, ScreenSizeH*(lineDisplayHeight+0.04));
  myLickL[myLickL.length-1] = int(ScreenSizeH*(lineDisplayHeight+0.08) -(licksL*tickHeight));
  text("Left Lick", ScreenSizeW*0.005, ScreenSizeH*(lineDisplayHeight+0.08));
  myReward[myReward.length-1] = int(ScreenSizeH*(lineDisplayHeight+0.12) - (rewarded*tickHeight));
  text("RewardDur", ScreenSizeW*0.005, ScreenSizeH*(lineDisplayHeight+0.12));
  //myLickR[myLickR.length-1] = int(ScreenSizeH*(lineDisplayHeight+0.16) -(licksR*tickHeight));
  //text("Right Lick", ScreenSizeW*0.005, ScreenSizeH*(lineDisplayHeight+0.16));

float state = cp5.get(Toggle.class,"Jitter").getValue();
  if (state==0) {
    myLickR[myLickR.length-1] = int(ScreenSizeH*(lineDisplayHeight+0.16) -(licksR*tickHeight));
    text("Right Lick", ScreenSizeW*0.005, ScreenSizeH*(lineDisplayHeight+0.16));
  } else {
    myLickR[myLickR.length-1] = int(ScreenSizeH*(lineDisplayHeight+0.16) -(0*tickHeight));
    text("Right Lick", ScreenSizeW*0.005, ScreenSizeH*(lineDisplayHeight+0.16));
  }
  myRewardR[myRewardR.length-1] = int(ScreenSizeH*(lineDisplayHeight+0.2) - (rewardedR*tickHeight));
  text("Right Reward", ScreenSizeW*0.005, ScreenSizeH*(lineDisplayHeight+0.2));
  myNegReward[myNegReward.length-1] = int(ScreenSizeH*(lineDisplayHeight+0.24) - (negReward*tickHeight));
  text("Neg Reinforcer", ScreenSizeW*0.01, ScreenSizeH*(lineDisplayHeight+0.24));


float optoState = cp5.get(Toggle.class,"Optogenetics").getValue();
  // Draw everything
  for (int i = 0; i < mx.length-1; i ++ ) {
    // Draw an ellipse for each element in the arrays. 
    // Color and size are tied to the loop's counter: i.
    strokeWeight(3);        //stroke wider   
    if (mx[i+1]==width/12) {
      continue;
    } else {
     // if (showLED) {
        if (optoState==1) {
        stroke(0, 0, 250);     //stroke color
        line(mx[i+1], myLED[i+1], mx[i], myLED[i]);
      }
      stroke(250, 250, 250);     //stroke color
      line(mx[i+1], myTA[i+1], mx[i], myTA[i]);
      stroke(128, 0, 128);     //stroke color
      line(mx[i+1], myLickL[i+1], mx[i], myLickL[i]);
      stroke(0, 250, 0);     //stroke color
      line(mx[i+1], myLickR[i+1], mx[i], myLickR[i]);
      stroke(128, 0, 128);     //stroke color
      line(mx[i+1], myReward[i+1], mx[i], myReward[i]);
      stroke(0, 250, 0);     //stroke color
      line(mx[i+1], myRewardR[i+1], mx[i], myRewardR[i]);
      stroke(40, 40, 40);     //stroke color
      line(mx[i+1], myNegReward[i+1], mx[i], myNegReward[i]);
      stroke(250, 0, 0);     //stroke color
      line(mx[i+1], myVelWheel[i+1], mx[i], myVelWheel[i]);
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
    
    for (int i = 0; i <activeAngle.length; i++) { 
    if (activeAngle[i]>0) {
      if ((activeAngle[i])!=lastMove) {
        drawStimPlot(i,4); 
      } 
      if (((activeAngle[i])==lastMove) && (lastMove>midPointAngle)) {
        drawStimPlot(i,3); //3
      } 
      if (((activeAngle[i])==lastMove) && (lastMove<midPointAngle)) {
        drawStimPlot(i,1); //1
      } if (((activeAngle[i])==lastMove) && (lastMove==midPointAngle)) {
        drawStimPlot(i,2);
      }
    }
  }
}