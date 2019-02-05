
void drawStimPlot(int i, int colorSelector)
{
  strokeWeight(4); 
  if (colorSelector == 1) { 
  stroke(128, 0, 128); // purple
  }
  else
    if (colorSelector == 2) {
      stroke(0, 255, 0); // green
    }
  else
    if (colorSelector == 3) {
      stroke(0, 250, 0);
    }
  else
    if (colorSelector == 4) {
      stroke(127, 127, 127); // grey
    }
  else
    if (colorSelector == 5) {
      stroke(0, 0, 0); // black
    }

    if (!localizationTab){
      line(center.x, center.y, xEcclips[i], yEcclips[i]);
    }
    else{
      line(xEcclips2[i], center.y, xEcclips2[i], yEcclips2[i]);
    }
}