/* Orientation Behaviour Jenny Brown
  MAIN SCRIPT: Select Orientations and task parameters with JAVA - Programming code
  With NEW 2017 BBoard_V4:
  use top variables and pin declerations (NEW PCB 2017 BBoard_V4),
  digitalWrite(LEDPin, HIGH) and
  in doEncoder: if (diwgitalRead(encoder0PinA) != digitalRead(encoder0PinB)) { // B leads A = clockwise rotation, A leads B = anticlockwise
*/
// avr-libc library includes
// #include <avr/io.h>
#include <avr/interrupt.h>
//
// ////// ****NEW PCB 2017 BBoard_V4**** \\\\\// Set up Rotary Encoder Pins
const int encoder0PinA = 3; // A pulse from wheel encoder
const int encoder0PinB = 2; // B pulse from wheel encoder
// Set up Air puffer Pin
// const int airpuffPin = 7; // pin used to control values for air delivery
const int airpuffPin = 7; // pin used to control values for air delivery
// Set up  Lickport pin'A00 cs
// const int licksLPin = 10;  // photointerrupter for lick detection - optical
const int licksLPin = 17; // photointerrupter for lick detection - electrical 1
const int licksRPin = 18; // photointerrupter for lick detection (on interrupt pin 1)
// Set up solinoid Valve Pins for rewards
const int rewardPin = 23; // reward solenoid value
const int rewardPinR = 22; // reward solenoid value Right Side

//// **BIG EASY DRIVER 1 pins**
//// Position Motor (Nema 17)
//const int motor1DirPin = 46; // direction pulses for Stimulus Motor
//const int motor1StepPin = 48; // step pulses for Stimulus Motor
//const int motor1MS3Pin = 51; // Position Motor microstepper MS3
//const int motor1MS2Pin = 49; // Position Motor microstepper MS2
//const int motor1MS1Pin = 47; // Position Motor microstepper MS1
//const int motor1RST = 53; // Origional:26 New: 27 Stimulus Motor microstepper MS2
//const int motor1SLEEP = 52; // Origional:26 New: 27 Stimulus Motor microstepper MS2
//const int motor1VCC = 50; // Origional:26 New: 27 Stimulus Motor microstepper MS2
//const int motor1enablePin = 45; // Origional:13 New: 23 LED light pin
//const int motor1controlPin = 24; // Control Pin to switch between open and closed loop motor control

//// **BIG EASY DRIVER 3 pins**
//// Position Motor (Nema 17)
const int motor1DirPin = 28; // direction pulses for Stimulus Motor
const int motor1StepPin = 30; // step pulses for Stimulus Motor
const int motor1MS1Pin = 42;  // Origional:24 New: 25 Stimulus Motor microstepper MS1
const int motor1MS2Pin = 40;  // Origional:28 New: 29 Stimulus Motor microstepper MS3
const int motor1MS3Pin = 38;  // Origional:26 New: 27 Stimulus Motor microstepper MS2
const int motor1RST = 36;  // Origional:26 New: 27 Stimulus Motor microstepper MS2
const int motor1SLEEP = 34;  // Origional:26 New: 27 Stimulus Motor microstepper MS2
const int motor1VCC = 32;  // Origional:26 New: 27 Stimulus Motor microstepper MS2
const int motor1enablePin = 44;  // Origional:13 New: 23 LED light pin
const int motor1controlPin = 24;  // Control Pin to switch between open and closed loop motor control

//// **BIG EASY DRIVER 2 pins**
//// Stimulus Motor (Nema 8)
const int motor2DirPin = 43; // direction pulses for Stimulus Motor
const int motor2StepPin = 41; // step pulses for Stimulus Motor
const int motor2MS1Pin = 29; // Origional:24 New: 25 Stimulus Motor microstepper MS1
const int motor2MS3Pin = 31; // Origional:28 New: 29 Stimulus Motor microstepper MS3
const int motor2MS2Pin = 33; // Origional:26 New: 27 Stimulus Motor microstepper MS2
const int motor2RST = 35; // Origional:26 New: 27 Stimulus Motor microstepper MS2
const int motor2SLEEP = 37; // Origional:26 New: 27 Stimulus Motor microstepper MS2
const int motor2VCC = 39; // Origional:26 New: 27 Stimulus Motor microstepper MS2
const int motor2enablePin = 27; // Origional:13 New: 23 LED light pin

// Set up photostim Pins
const int LEDPin = 6; // LED light pin
// Set up push bottons
const int autoWater = 9; // push button
// Set up OUTPUT device information digital lines
int targetState = 26; // Digital taget area
const int digitalAnglePin = 13; // Digital angle output and catch output
const int digitalCountPin = 10; // Digital trial count output/BNC2
const int digitalTriggerPin = 4; // Digital trigger output / BNC2
const int extTrigPin = 5;
// //Set up photointerrups
const int targetPin = 15; // photointerrupter for target position (on interrupt pin 3)
// const int homePinB = 16; // photointerrupter for home position (on interrupt pin 2)
const int maskingLED = 11;

// SET UP COUNTERS
int stimINcount = 0; // no. of steps before going into slow stepping mode
int currstimINcount;
int currstimOUTcount;
int motor1microStep;
int motor1microStep2;
int diffTotalSteps;
int homeSETcount = 150;
int motor2microStep;
// SET UP ANGLE INFO
float fullRevolutionStim; // 200 steps / rev, 16th microstepping - this will depend on stepper motor used and microstepping settings - *Check StimMotorMicroStepping*
float stepsPerDegree; // divide total number of step by 360
float midPointAngleStep; // Always start with stim horizontal. So 0/360 degrees is horizontal. Vertical is 270 degrees.

// Set up StimulusMotor parameters
int stimulusIDNumber[] =
{
  1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13
};

int stimulusIDNumberTwo[] =
{
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
};

const byte maxStimNo = 13;
int numStim[maxStimNo];
int stimPosition[maxStimNo]; // create an empty array to store the active stim positions in. NB: one more element than total count is required, to hold the neccessary null character
int stimIdx[maxStimNo];
int numStimPositions = 0; // keep track of how many active stim positions have been inputted from JAVA
int halfStimPos;
int numLEDStates = 0;
int blockSize[500];
int optoTrials[500];
int catchTrials[500];
int optoTrialsVoltage[500];
int halffractionCatchNo;
int trialBlock;
float TemptrialBlock;
int fractionCatchNo;
int repetitions;
int MaxOptoTrials;
int MaxPerVoltOptoTrials;
int lastAngle;
int trialBlockTotal;
// int trialBlockCount;
int addJitter = 0; // select a random amount of steps to move the stimulusID further on
int delayMIN;
int delayMAX;
// For orientations which are vertical - there is a 50% chance of a reward begin given, set up these variables
int midPoint[] =
{
  1, 3
};

int previousHomeJitter = 0;
// StimulusMotor Properties
int requiredDistance; // At the end of a trial - stimulusID is rotated into next position, variable to calculate steps needed to reach this
// int currMove;
int currMoveNum;
int lastMove;
int randomNumber;
int angleNo = 0;
// Used to define if the trail was a Hit, Miss, Correct Rejection (CR) or False Alarm (FA)
int TrialType = 0; // Not Selected = 0, Hit=1,  FA = 2, Miss=3, CR = 4,
int count = 0; // Tally of total number of trials in session
int lightONcounter = 0;
// Set up booleans to monitor task performance
// SET UP TASK PARMS
int timeoutFA = 5000; // time out duration for FA
// VARIABLES FROM PROCESING
int blank;
int answerDuration; // duration mouse has to make his dicision following stimulusID presentation
int waitDuration; // duration between first lick and reward being delivered on HIT trials
int maskingPreTime; // duration masking light come on before target time
int optoON;
int optoOFF;
int stepsNeeded;
int stepsNeededAdapt;
int runRewardCount = 0;
int puffDuration;
int rewardDuration; // duration solenoid valve with be open
int preDuration;
int rewardDurationRight; // duration solenoid valve with be open
int LEDVolt[3];
float fractionOpto;
float fractionCatch;
// BOOLEANS FROM PROCESING
boolean autoReward; // Used in training to automatically give water reward when stimulusID passes whiskers
boolean optogenetics; // Used for photostimulation
boolean timeout; // are we delivering a neg reinforcer?
boolean fullCircle;
boolean homeJitter;
boolean negReinforcer;
boolean jitterTarget;
boolean baselineState;
boolean orgGOangle;
boolean AFC;
boolean localization; // object localization task
boolean motor1MS1m1;
boolean motor1MS2m1;
boolean motor1MS3m1;
boolean motor1MS1m2;
boolean motor1MS2m2;
boolean motor1MS3m2;
boolean maskingLight;
boolean justRun;
boolean extTrig;
boolean stimCalibration;
boolean runReward;
boolean linearExp;
boolean jitterAtHome=false;
int trialStructure[5];
int optoStructure[5];
int catchStructure[5];
int optoTrialsControl;
int optoTrialsCatch;
float noOptoReps;
float noControlReps;
float noOptoRepsCatch;
float noControlRepsCatch;
int tempaddJitter;
//int randomJitterArray[] = {25, 50, 75};
int randomJitterArray[] = {-4, 0, 4}; //testing for linear motor task

int jitterCount = 0;
int digAngle = 0;
int digCount = 0;
int digSendTime = 4000; //50
boolean digitalAngleSuccess = false;

boolean resetRunTimer = false;
unsigned long runRewardTimer;
unsigned long individualRewardTimer;
int runIncrement = 250;



int midPointStimulus;
// STIM (angle) ID FROM PROCESSING
int stimulusID[13]; // create empty array to store incoming stimulusID from JAVA
// TRANSISITION TOP LEVEL BOOLEANS
boolean startSerial = false;
boolean startTrial = false;
boolean startSample = false; // Sample period timing starts
boolean sendDig = false;
boolean moveToTarget = false;
boolean samplePeriod = false;
boolean backToHome = false; // open loop control after sample period to remove stim from whisker field
boolean reachedHome = false;
boolean newTrial = false;
// STATE TRANSITIONS SECOND LEVEL
boolean answerPeriod = false; // Stimulus within reach and mouse can make its dicission
boolean rewarded = false; // Mouse recieved water reward?
boolean rewardedR = false; // Mouse recieved water reward?
boolean pauseForReward = false; // Stimulus entered target area - broke target photobeam
boolean LEDstate = false; // State of photostimulusID - HIGH = on, LOW = off
boolean targetPos = false; // PositionMotor break target beam - target in sample area.
boolean targetArea = false; // HIGH is targetArea beam broken - i.e. stimulusID within target area.
boolean firstHome = false;
boolean randomDelayFirst = false;
boolean randomDelay = false;
int LEDvoltageState[(sizeof(LEDVolt) / sizeof(int))];
boolean giveReward = false;
boolean giveRewardR = false;
boolean givePuff = false;
boolean newAngleSelect = false; // HIGH if still moving, LOW if stopped moving
boolean falseAlarm = false;
boolean GOtrial = false;
boolean NOGOtrial = false;
boolean midTrial = false;
boolean currOpto = false;
int currOptoLEDState = 0;
boolean currCatch = false;
boolean maskingLEDstate = false;
boolean backTimer = false;
boolean calibrate = true;
boolean firstCalibration = false;
boolean secondCalibration = false;
boolean thirdCalibration = false;
boolean BackStep = false;
boolean calFinished = false;
boolean preStimSet = false;
boolean externalTrigSent = false;
boolean extraMoveSet = false;
boolean newTrialStarted = false;
boolean endSample = false;
boolean setTimers = false;
boolean maskingStepsSet = false;
boolean optoStepsSet = false;
int optoSteps;
int maskingSteps;
boolean optoONSet = false;
boolean newAngle = false;
boolean setSpeed1 = true;
boolean setSpeed2 = true;
boolean setSpeed3 = true;
boolean digJitterSuccess = false;
boolean digCountSuccess = false;
// Set up microstepping options for position motor
boolean fastSpeed = false;
boolean movem2 = false;
boolean setDistanceToMove = true;
int gotally = 0;
int nogotally = 0;
// Temporal aspects of the task
unsigned long rewardTimeLeft;
unsigned long rewardTimeRight;
unsigned long currWaitTime;
unsigned long answerPeriodTime;
unsigned long breakTime;
unsigned long loopTime;
unsigned long puffTime;
unsigned long rewardTimeAuto = 0;
unsigned long pauseDuration = 0;
unsigned long pauseDurationStart = 0;
unsigned long preStimONTime;
unsigned long preStimTimeMasking;
unsigned long homeStimTimeStimON;
unsigned long preStimTimeStimON;
unsigned long resetTimer;
boolean setDurationAuto = false;
boolean setJitter = false;
boolean jitterTargetCurr = false;

unsigned long temp_pauseDuration=0;
int temp_positionCount;
int temp_encoder0Pos;
int temp_motorState;
// Velocity smoothing variables for wheel encoder
int positionCount = 0;
int stimOUTcount = 0;
int addHomeposition = 0;
int minusCatchDistance = 100; // stop 100 steps early for catch trials
float controlSig;
float sampleTime;
int stepDelayTime = 1;
int CalvoltageSig;
boolean firstEver = true;
// Variable used by the interrupts
volatile unsigned int encoder0Pos = 0;
volatile boolean homePos = false;
volatile boolean licksL = false;
volatile boolean licksR = false;
volatile int encoder = 0;
volatile boolean rewardTrial = false;
volatile boolean rewardTrialR = false;
volatile boolean testWater = false;

String serialDataString;
String inString = "";
boolean submitText = true;
int k = 0;
int kk = 0;
int serialData[40];
int c;
int v = 0;
int vv = 0;
boolean initalSetUp = true;
boolean comsEstablished = true;
int inByte = 0;
String variab[] =
{
  "answerDuration", "waitDuration"
};

// File outputData;
void setup()
{
  // Setup INPUT Pins and States
  pinMode(encoder0PinA, INPUT);
  pinMode(encoder0PinB, INPUT);
  pinMode(licksLPin, INPUT);
  digitalWrite(licksLPin, LOW);
  pinMode(licksRPin, INPUT);
  pinMode(extTrigPin, INPUT);
  digitalWrite(extTrigPin, LOW);
  // Setup OUTPUT Pins and States
  pinMode(maskingLED, OUTPUT);
  digitalWrite(maskingLED, LOW);
  pinMode(motor1enablePin, OUTPUT);
  digitalWrite(motor1enablePin, HIGH);
  pinMode(LEDPin, OUTPUT);
  // digitalWrite(LEDPin, HIGH); // NEWER PCBs HIGH Older LOW
  pinMode(rewardPin, OUTPUT);
  digitalWrite(rewardPin, LOW);
   pinMode(rewardPinR, OUTPUT);
  digitalWrite(rewardPinR, LOW);
  pinMode(autoWater, INPUT);
  digitalWrite(autoWater, HIGH);
  pinMode(motor2StepPin, OUTPUT);
  pinMode(motor2DirPin, OUTPUT);
  pinMode(motor1StepPin, OUTPUT);
  pinMode(motor1DirPin, OUTPUT);
  digitalWrite(motor1DirPin, HIGH); // Was LOW but I think that rotates the motor the wrong direction,
  pinMode(motor1MS1Pin, OUTPUT);
  pinMode(motor1MS2Pin, OUTPUT);
  pinMode(motor1MS3Pin, OUTPUT);
  pinMode(motor1controlPin, OUTPUT);
  digitalWrite(motor1controlPin, LOW);
  pinMode(motor2MS1Pin, OUTPUT);
  pinMode(motor2MS2Pin, OUTPUT);
  pinMode(motor2MS3Pin, OUTPUT);
  pinMode(digitalCountPin, OUTPUT);
  pinMode(digitalAnglePin, OUTPUT);
  pinMode(digitalTriggerPin, OUTPUT);
  pinMode(motor2enablePin, OUTPUT);
  digitalWrite(motor2enablePin, HIGH);
  digitalWrite(motor2MS1Pin, HIGH);
  digitalWrite(motor2MS2Pin, HIGH);
  digitalWrite(motor2MS3Pin, HIGH);
  pinMode(airpuffPin, OUTPUT);
  digitalWrite(airpuffPin, LOW);
  pinMode(targetState, OUTPUT);
  digitalWrite(targetState, LOW);
  // ****Set Up Interrupt Pins NEW PCB 2017 BBoard_V4****
  attachInterrupt(encoder0PinA, doEncoder, CHANGE); // encoder pin on interrupt 0 - pin 2
  attachInterrupt(extTrigPin, doExtTrig, RISING); // encoder pin on interrupt 0 - pin 10
  attachInterrupt(autoWater, doAutoReward, FALLING);  // encoder pin on interrupt 0 - pin 2
  attachInterrupt(licksLPin, doLicksL, CHANGE); // CHANGE encoder pin on interrupt 1 - pin 3
  // attachInterrupt(homePinB, doHome, FALLING); // encoder pin on interrupt 2 - pin 21
  attachInterrupt(targetPin, doTarget, FALLING); // encoder pin on interrupt 3 - pin 20
  // attachInterrupt(licksRPin,doLicksR,CHANGE );  //doIndex,RISING encoder pin on interrupt 4 - pin 18

  // Begin Serial Communication
  Serial.begin(115200);
  // Initialise a pseudo-random number generator
  randomSeed(analogRead(0));
  establishCOMS(); // establish communication with processing
}

// ** START OF VOID LOOP -- will repeat continuously**
void loop()
{
  // If at the start of session - do calibration code to identify steps needed to reach each photointerrupt
  if (calibrate)
  {
    doCalibration();
  }
  if (startSerial)
  {
    encoder = 0; // reset wheel encorder count and time to calculate running velocity per loop of arduino code
    loopTime = millis();

    if (testWater)
      // auto water button has been pressed
    {
      doTestWater();
    }
    else if (!justRun)
    {
      // MEET TRIAL START CRITERIOR
      if (startTrial)
      {
        if (((encoder0Pos >= stepsNeeded) && (!extTrig)) || (externalTrigSent))
        {
          // Either mouse meets running requirement or if (ExtTrif=true) an external trigger is sent
          startTrial = false;
          externalTrigSent = false;
          sendDig = true;
        }
      }
      // SEND DIGITAL INFO
      if (sendDig)
      {
        if (baselineState)
        {
          digitalCount(); // Digitally Send count and trial type info
        }

        BackStep = false;
        moveToTarget = true;
        fastSpeed = true;
         if (!linearExp){
        openloopControl();
         }
        sendDig = false;
      }
      // MOVE STIMULUS TO POSITION
      if (moveToTarget)
      {
        // Move stim into sample region
        movePositionMotor();
        // Set distance to travel
        if (setDistanceToMove)
        {
          calDistancesToMove();
        }
        if ((positionCount) >= (currstimINcount))
        {
          if (setSpeed1)
          {
            fastSpeed = false;
             if (!linearExp){
            openloopControl();
             }
            setSpeed1 = false;
          }
          // go from fast to slow motor speed on approach to target area only 1/2 then stim on for catch trials
          lightONcounter++;
          // start catch timing
          if (!preStimSet)
          {
            preStimONTime = ((millis()) + maskingPreTime); // maskingPreTime
            preStimSet = true;
            if (maskingLight)
            {
              // turn on masking light
              digitalWrite(maskingLED, HIGH);
              maskingLEDstate = true;
            }
          }
          if (!optoONSet)
          {
            if ((lightONcounter) >= (maskingSteps - optoSteps))
            {
              optoONSet = true;
              if (optogenetics == 1)
              {
                // turn on opto light
                if (currOpto)
                {
                  analogWrite(LEDPin, currOptoLEDState);
                  LEDstate = true;
                }
              }
            }
          }
          if (((millis()-temp_pauseDuration) >= preStimONTime) && (currCatch) && (preStimSet))
          {
            doTarget();
          }
        }
      }
      // SAMPLE PERIOD
       if ((targetPos) && (positionCount >= addJitter) && (!samplePeriod))
      //if ((targetPos) && (!samplePeriod))
      {
        moveToTarget = false;
        // Once in the target region, put the break on, if opto, turn on stim
        if (startSample)
        {
          // start timing - pause motor
          digitalWrite(motor1enablePin, HIGH); // Put the break on the Position Motor
          sampleTime = (millis() + (answerDuration + waitDuration));
          answerPeriodTime = ((millis()) + answerDuration);
          targetArea = true;
          digitalWrite(targetState, HIGH);
          answerPeriod = true;
          startSample = false;
        }
        samplePeriod = true;
      }
      if (samplePeriod)
        // if ((sampleTime > (millis())) && (samplePeriod))
      {
        taskOutcomes();
        // END OF ANSWER PERIOD TIME

        if ((millis() > (answerPeriodTime)) && (targetArea)) //NEW
//        if (((millis()) > (answerPeriodTime+pauseDuration)) && (targetArea)) //NEW
        {
          // Once answer period time is up make target area false and if optical stim was on - turn it off.
          answerPeriod = false;
          targetArea = false;
          digitalWrite(targetState, LOW);
          targetPos = false;
          if (maskingLight)
          {
            digitalWrite(maskingLED, LOW);
            maskingLEDstate = false;
          }
          if (optogenetics)
          {
            analogWrite(LEDPin, 0);
            LEDstate = false;
          }
        }
      }
      // END OF SAMPLE TIME - GIVE REWARD, RESET AND PREPARE TO MOVE MOTOR
      if ((sampleTime <= millis()) && (samplePeriod))
      {
        rewardDelivery();
      }
      // END OF TRIAL - RESET MOTOR TO START POSITION and SELECT NEW STIMULUS
      if (backToHome)
      {
        if (setSpeed2)
        {
          if (!fullCircle)
          {
            BackStep = true;
          }
          fastSpeed = false;

          if (!linearExp){
          openloopControl();
          }
        //  digitalWrite(motor1enablePin, LOW); // Take off motor break
          setSpeed2 = false;
        }
        movePositionMotor();
        if (((positionCount) >= (stimOUTcount + addJitter)))
        {
          if (setSpeed3)
            // switch to fast stepping
          {
            fastSpeed = true;
             if (!linearExp){
            openloopControl();
             }
            setSpeed3 = false;
          }
          if ((positionCount) >= (currstimOUTcount))
          {
            doHome();
          }
        }
      }
      // HOME POSITION REACHED - SELECT NEW ANGLE FOR NEXT TRIAL
      if (reachedHome)
      {
        if ((newTrial))
        {
          if (((count % trialBlockTotal) == 0))
          {
            doPrepAngleShuffle();
            doAngleShuffle();
          }
          doNewAngle();
        }
        // Move stimulusID Motor to new position
        if (newAngleSelect)
        {
          moveNewAngle();
        }
        if (randomDelayFirst)
        {
          setRandomDelay();
        }
      }
    }
    else
    {
      // just run training
      if (runReward)
      {
        currOptoLEDState = stepsNeededAdapt;
        doRunReward();
      }
    }
    doSerialPrint();
  }
}
