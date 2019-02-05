
void Submit(boolean theFlag) {
   if (theFlag==true) {
  establishCOMS = true;
  println("");
  println("....MAKING CONTACT WITH ARDUINO....");
  println("");
}
}

void ResetVals() {
  // initialize variable to store cummulative performance
  println("Reset Vals");
  hitTally = 0;
  missTally = 0;
  correctRejectionTally = 0;
  falseAlarmTally = 0;

  hitTallyStim = 0;
  missTallyStim = 0;
  correctRejectionTallyStim = 0;
  falseAlarmTallyStim = 0;

  count = 0;
  catchTrialTally=0;
  countTrialTally=0;
  countStim=0;

  updatePerformanceHIT(); 
  updatePerformanceMISS();
  updatePerformanceCR(); 
  updatePerformanceFA();
  updatePerformance(); 
  updatePerformanceHITStim(); 
  updatePerformanceMISSStim();
  updatePerformanceCRStim(); 
 updatePerformanceFAStim();
 updatePerformanceStim(); 
  updateCountTotal();
  updateCatchCountTotal();
}