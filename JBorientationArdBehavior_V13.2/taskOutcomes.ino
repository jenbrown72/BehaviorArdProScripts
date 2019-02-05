void taskOutcomes()
{
	int midPoint[] =
{
	1, 3
};
	// GO-NOGO task type
	// AUTO REWARD
	if ((!AFC) && (answerPeriod) && (millis() < answerPeriodTime) && (licksL)&& (autoReward))
	{
		if ((GOtrial))
		{
			if (!currCatch)
			{


				TrialType = 1;
				rewardTrial = true;
			}
			else
				if (currCatch)
				{
					TrialType = 2; // False Alarm
				}
			answerPeriod = false;
		}
	}
	// LICKS DETECTED DURING ANSWER PERIOD - HIT or FA
	else
		if ((!AFC) && (answerPeriod) && (millis() < answerPeriodTime) && (licksL))
		{
			// LICKED FOR A GO STIM - HIT
			if ((GOtrial))
			{
				if (!currCatch)
				{
					TrialType = 1; // Hit trial
					rewardTrial = true;
				}
				// CATCH Detection task - FA if lick
				if ((currCatch) && (numStimPositions == 1))
				{
					TrialType = 2; // False Alarm
					falseAlarm = true;
				}
				answerPeriod = false;
			}
			// LICKED FOR A Mid point STIM - 50/50 HIT/FA
			else
				if ((midTrial))
				{
					// mouse licked for Mid point stimulusID
					if (!currCatch)
					{

						long randomNumber = random(0, 2);
						TrialType = midPoint[randomNumber];
						if (TrialType == 1)
						{
							rewardTrial = true;
						}
					}
					answerPeriod = false;
				}
			// LICKED FOR A NOGO STIM - False Alarm
			else
				if ((NOGOtrial))
				{
					if (!currCatch)
					{
						TrialType = 2; // False Alarm
						falseAlarm = true;
					}
					answerPeriod = false;
				}
		}
	else
		if ((!AFC) && (answerPeriod) && (millis() > answerPeriodTime) && (autoReward))
		{
			// No LICK FOR A GO STIM - ON AUTO Trial
			if ((GOtrial))
			{
				if (!currCatch)
				{
					TrialType = 3; // Miss trial
					rewardTrial = true; // Still deliver reward on auto trials
				}
				// CATCH Detection task - CR if no lick
				if ((currCatch) && (numStimPositions == 1))
				{
					TrialType = 4; // Correct Rejection
				}
				answerPeriod = false;
			}
		}
	else
		if ((!AFC) && (answerPeriod) && (millis() > answerPeriodTime) && (!autoReward))
		{
			// No LICK FOR A GO STIM - MISS
			if (GOtrial)
			{
				if (!currCatch)
				{
					TrialType = 3; // Miss trial
				}
				// CATCH Detection task - CR if no lick
				if ((currCatch) && (numStimPositions == 1))
				{
					TrialType = 4; // Correct Rejection
				}
				answerPeriod = false;
			}
			// No LICK FOR A NOGO STIM - CORRECT REJECTION
			else
				if ((NOGOtrial))
				{
					if (!currCatch)
					{
						TrialType = 4; // Correct Rejection
					}
					answerPeriod = false;
				}
			// No LICK FOR A midtrial - 50/50 CR/MISS
			else
				if ((midTrial))
				{
					// mouse did not lick for Mid point stimulusID
					if (!currCatch)
					{
						TrialType = 3; // Miss trial
					}
					answerPeriod = false;
				}
			else
				if (AFC == 1)
				{
					// AFCscript();
				}
		}
		
							// NEGATIVE REINFORCER if FA
					if (negReinforcer && (!givePuff) && (falseAlarm))
					{
						// Deliver puff of air
						givePuff = true;
						puffTime = (millis() + puffDuration);
						falseAlarm = false;
						digitalWrite(airpuffPin, HIGH);
					}
					if ((givePuff) && (millis() > puffTime))
					{
						givePuff = false;
						digitalWrite(airpuffPin, LOW);
					}

					
}
