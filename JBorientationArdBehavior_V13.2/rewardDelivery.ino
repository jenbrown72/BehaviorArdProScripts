void rewardDelivery()
{

	if ((rewardTrial) || (rewardTrialR))
	{
		// Correctly lick for Go stim - reward being given after defined wait time
		if (!setTimers)
		{
			setTimers = true;
			rewardTimeLeft = (millis() + rewardDuration);
			rewardTimeRight = (millis() + rewardDurationRight);
			if ((rewardTrial) && (!currCatch))
			{
				rewarded = true;
				digitalWrite(rewardPin, HIGH);
			}
			else
				if ((rewardTrialR) && (!currCatch))
				{
					rewardedR = true;
					digitalWrite(rewardPinR, HIGH);
				}
		}

		// GIVE REWARDS IF NEEDED
		if ((rewarded) && (millis() > rewardTimeLeft))
		{
			rewarded = false;
			digitalWrite(rewardPin, LOW);
			rewardTrial = false;
			resetRewardVals();
		}
		else
			if ((rewardedR) && (millis() > rewardTimeRight))
			{
				rewardedR = false;
				digitalWrite(rewardPinR, LOW);
				rewardTrialR = false;
				resetRewardVals();
			}
	}
	else
	{
		resetRewardVals();
	}
}

void resetRewardVals()
{
//	Serial.println("RestRewardVCals");
	firstHome = true;
	backToHome = true;
	samplePeriod = false;
	setTimers = false;
	positionCount=0;
}
