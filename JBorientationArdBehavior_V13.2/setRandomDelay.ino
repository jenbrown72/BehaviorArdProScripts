void setRandomDelay()
{
  
  if (!randomDelay)
  {
    if (TrialType == 2 && (timeout))
    {
      // FA and neg reinforcer was selected
      breakTime = ((millis()) + (random(delayMIN, delayMAX)) + timeoutFA); // random wait duration between 1 and 3 seconds
    }
    else
    {
      breakTime = ((millis()) + (random(delayMIN, delayMAX))); // random wait duration between 1 and 3 seconds
    }
    randomDelay = true;
  }

  if ((randomDelay) && (millis() > breakTime))
  {
    randomDelayFirst = false;
    resetVals();
  }
}
