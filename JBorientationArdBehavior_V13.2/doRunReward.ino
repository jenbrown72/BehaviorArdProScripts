void doRunReward()
{
	if (resetRunTimer)
	{
		runRewardTimer = (millis());
		resetRunTimer = false;
	}
	if (encoder0Pos >= stepsNeededAdapt)
	{
		if (!setTimers)
		{
			setTimers = true;
			rewardTimeLeft = (millis() + rewardDuration);
			rewarded = true;
			digitalWrite(rewardPin, HIGH);
		}
		// GIVE REWARDS IF NEEDED
		if ((millis() >= rewardTimeLeft))
		{
			digitalWrite(rewardPin, LOW);
			setTimers = false;
			encoder0Pos = 0;
			count++;
			runRewardCount++;
			individualRewardTimer = (millis());
			// Increase Run Requirement
			if ((runRewardCount >= 10) && (millis() <= (runRewardTimer + 60000)))
			{
				// more than 10 rewards within 1 minute
				stepsNeededAdapt = stepsNeededAdapt + runIncrement;
				runRewardCount = 0;
				individualRewardTimer = (millis());
				resetRunTimer = true;
			}
		}
	}
	// Decrease Run Requirement
	if ((millis()) >= (individualRewardTimer + 60000)) // no reward within a minute
	{
		if (stepsNeededAdapt > runIncrement)
		{
			stepsNeededAdapt = stepsNeededAdapt - runIncrement;
		}
		runRewardCount = 0;
		individualRewardTimer = (millis());
		resetRunTimer = true;
	}
}
