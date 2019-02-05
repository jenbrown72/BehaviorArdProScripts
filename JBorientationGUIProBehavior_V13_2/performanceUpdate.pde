
public void updatePerformanceMISS() {
  Textfield txt = ((Textfield)cp5.getController("Miss"));
  txt.setValue(""+missTally);
}
public void updatePerformanceMISSStim() {
 Textfield txt = ((Textfield)cp5.getController("MissStim"));
 txt.setValue(""+missTallyStim);
}

public void updatePerformanceHIT() {
  Textfield txt = ((Textfield)cp5.getController("Hit"));
  txt.setValue(""+hitTally);
}

public void updatePerformanceHITStim() {
 Textfield txt = ((Textfield)cp5.getController("HitStim"));
 txt.setValue(""+hitTallyStim);
}

public void updatePerformanceCR() {
  Textfield txt = ((Textfield)cp5.getController("CR"));
  txt.setValue(""+correctRejectionTally);
}

public void updatePerformanceCRStim() {
Textfield txt = ((Textfield)cp5.getController("CRStim"));
txt.setValue(""+correctRejectionTallyStim);
}

public void updatePerformanceFA() {
 Textfield txt = ((Textfield)cp5.getController("FA"));
 txt.setValue(""+falseAlarmTally);
}

public void updatePerformanceFAStim() {
 Textfield txt = ((Textfield)cp5.getController("FAStim"));
 txt.setValue(""+falseAlarmTallyStim);
}

public void updateCountTotal() {
  Textfield txt = ((Textfield)cp5.getController("Count"));
  txt.setValue(""+int(countTrialTally));
}

public void updateCatchCountTotal() {
  Textfield txt = ((Textfield)cp5.getController("Catch"));
  txt.setValue(""+int(catchTrialTally));
}

public void updatePerformance() {
  Textfield txt = ((Textfield)cp5.getController("P"));
  //txt.setValue(""+((hitTally+correctRejectionTally)/(hitTally+correctRejectionTally+falseAlarmTally+missTally))*100);
    txt.setValue(""+((float(hitTally)+float(correctRejectionTally))/(float(hitTally)+float(correctRejectionTally)+float(falseAlarmTally)+float(missTally)))*100);
    Textfield txtd = ((Textfield)cp5.getController("d'"));

if ((hitTally==0) || (missTally==0)|| (falseAlarmTally==0) || (correctRejectionTally==0)){
tempHitTally = hitTally+0.5;
tempmissTally = missTally+0.5;
tempfalseAlarmTally = falseAlarmTally+0.5;
tempcorrectRejectionTally = correctRejectionTally+0.5;
}
else{
tempHitTally = hitTally;
tempmissTally = missTally;
tempfalseAlarmTally = falseAlarmTally;
tempcorrectRejectionTally = correctRejectionTally;
}
    float hitRate = (tempHitTally/(tempHitTally+tempmissTally));
    float FARate = (tempfalseAlarmTally/(tempfalseAlarmTally+tempcorrectRejectionTally));
   txtd.setValue(""+(hitRate-FARate));
}

public void updatePerformanceStim() {
 Textfield txt = ((Textfield)cp5.getController("P Stim"));
 txt.setValue(""+((float(hitTallyStim)+float(correctRejectionTallyStim))/(float(hitTallyStim)+float(correctRejectionTallyStim)+float(falseAlarmTallyStim)+float(missTallyStim)))*100);
 
  Textfield txtd = ((Textfield)cp5.getController("d'Stim"));
 txtd.setValue("");



if ((hitTallyStim==0) || (missTallyStim==0)|| (falseAlarmTallyStim==0) || (correctRejectionTallyStim==0)){
tempHitTallyStim = hitTallyStim+0.5;
tempmissTallyStim = missTallyStim+0.5;
tempfalseAlarmTallyStim = falseAlarmTallyStim+0.5;
tempcorrectRejectionTallyStim = correctRejectionTallyStim+0.5;
}
else{
tempHitTallyStim = hitTallyStim;
tempmissTallyStim = missTallyStim;
tempfalseAlarmTallyStim = falseAlarmTallyStim;
tempcorrectRejectionTallyStim = correctRejectionTallyStim;
}
    float hitRateStim = (tempHitTallyStim/(tempHitTallyStim+tempmissTallyStim));
    float FARateStim = (tempfalseAlarmTallyStim/(tempfalseAlarmTallyStim+tempcorrectRejectionTallyStim));
   txtd.setValue(""+(hitRateStim-FARateStim));



}

public void updateElapsedTime() {
  Textfield txt = ((Textfield)cp5.getController("Time"));
    txt.setValue(""+ String.format("%.2f",((time/1000)/60)));
}

public void updateElapsedTimeRUN() {
  Textfield txt = ((Textfield)cp5.getController("TimeRUN"));
    txt.setValue(""+ String.format("%.2f",((time/1000)/60)));
}

public void updateRunningDistance() {
  Textfield txt = ((Textfield)cp5.getController("DistanceRun"));
  txt.setValue(""+String.format("%.1f",totalDistance));
}

public void updateRunningVelocity() {
  Textfield txt = ((Textfield)cp5.getController("AvgVelocity"));
  txt.setValue(""+String.format("%.2f",totalDistance/(time/1000)));
}

public void updateRunRewards() {
  Textfield txt = ((Textfield)cp5.getController("runRewards"));
  txt.setValue(""+String.format("%.0f",count));
}