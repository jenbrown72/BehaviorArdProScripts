/* Orientation Behaviour Jenny Brown
  Variable parameter value are sent from processing to arduino.
*/
void updateVariable() {
  delay(30);
  while (Serial.available() > 0)
  {
    c = Serial.read();

    if ((c >= '0') && (c <= '9')) //check if a digit was sent
    {
      v = 10 * v + c - '0'; //handle digit one by one and add to v
      inByte++;
    }
    else if (c == 'e')
    {
      serialData[k] = v;
      //  Serial.println(v);
      k = k + 1;
      v = 0;
    }
    else if (c == 'x')
    {
      v = 0;
      break;
    }
  }

  answerDuration = serialData[0];
  waitDuration = serialData[1];
  maskingPreTime = serialData[2];
  optoON = serialData[3];
  optoOFF = serialData[4];
  timeoutFA = serialData[5];
  puffDuration = serialData[6];
  stepsNeeded = serialData[7];

  stepsNeededAdapt = stepsNeeded;

  rewardDuration = serialData[8];
  preDuration = serialData[9];
  LEDVolt[0] = serialData[10];
  LEDVolt[1] = serialData[11];
  LEDVolt[2] = serialData[12];
  fractionOpto = serialData[13];
  fractionCatch = serialData[14];
  delayMIN = serialData[15];
  delayMAX = serialData[16];
  autoReward = serialData[17];
  optogenetics = serialData[18];
  timeout = serialData[19];
  fullCircle = serialData[20];
  homeJitter = serialData[21];
  negReinforcer = serialData[22];
  jitterTarget = serialData[23];
  baselineState = serialData[24];
  orgGOangle = serialData[25];
  AFC = serialData[26];
  localization = serialData[27];
  motor1MS1m1 = serialData[28];
  motor1MS2m1 = serialData[29];
  motor1MS3m1 = serialData[30];
  motor1MS1m2 = serialData[31];
  motor1MS2m2 = serialData[32];
  motor1MS3m2 = serialData[33];
  maskingLight = serialData[34];
  justRun = serialData[35];
  runReward = serialData[36];
  extTrig = serialData[37];
  stimCalibration = serialData[38];
  midPointStimulus = serialData[39];
   linearExp = serialData[40];
  calMicrostepping();
}

void updateStimuli() {
  //     if (controlSig != '3')
  delay(20);
  while (Serial.available() > 0)
  {
    c = Serial.read();

    if ((c >= '0') && (c <= '9')) //check if a digit was sent
    {
      v = 10 * v + c - '0'; //handle digit one by one and add to v
    }
    else if (c == 'e')
    {
      stimulusID[kk] = v;
      //   Serial.println(v);
      kk = kk + 1;
      v = 0;
    }
    else if (c == 'x')
    {
      v = 0;
      break;
    }
  }

  count = 0; // when count is 0 the next time the motor reaches the home position doAngleShuffle will run
  // if we're already at the home position - we need to declaire newTrials true again so that doAngleShuffle will be called
  if (!newTrial)
  {
    newTrial = true;
  }
}

void calMicrostepping()
{
  // MICROSTEPPING 1
  if ((!motor1MS1m1) && (!motor1MS2m1) && (!motor1MS3m1)) // LOW LOW LOW
  {
    motor1microStep = 1;
  }
  if ((motor1MS1m1) && (!motor1MS2m1) && (!motor1MS3m1)) // HIGH LOW LOW
  {
    motor1microStep = 2;
  }
  if ((!motor1MS1m1) && (motor1MS2m1) && (!motor1MS3m1)) // LOW HIGH LOW
  {
    motor1microStep = 4;
  }
  if ((motor1MS1m1) && (motor1MS2m1) && (!motor1MS3m1)) // HIGH HIGH LOW
  {
    motor1microStep = 8;
  }
  if ((motor1MS1m1) && (motor1MS2m1) && (motor1MS3m1)) // HIGH HIGH HIGH
  {
    motor1microStep = 16;
  }
  // MICROSTEPPING 2
  if ((!motor1MS1m2) && (!motor1MS2m2) && (!motor1MS3m2)) // LOW LOW LOW
  {
    motor1microStep2 = 1;
  }
  if ((motor1MS1m2) && (!motor1MS2m2) && (!motor1MS3m2)) // HIGH LOW LOW
  {
    motor1microStep2 = 2;
  }
  if ((!motor1MS1m2) && (motor1MS2m2) && (!motor1MS3m2)) // LOW HIGH LOW
  {
    motor1microStep2 = 4;
  }
  if ((motor1MS1m2) && (motor1MS2m2) && (!motor1MS3m2)) // HIGH HIGH LOW
  {
    motor1microStep2 = 8;
  }
  if ((motor1MS1m2) && (motor1MS2m2) && (motor1MS3m2)) // HIGH HIGH HIGH
  {
    motor1microStep2 = 16;
  }
}
