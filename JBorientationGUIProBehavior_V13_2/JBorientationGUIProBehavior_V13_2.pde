/* //<>// //<>// //<>//
 
 MAIN SCRIPT: Select Orientations and task parameters with JAVA - Programming code
 
 Several variables need to be changed depending on if your running the code from a desktop or tablet:
 
 serialPortNo = 1; //1 for tablets, 5 for Mac
 screenStepSize =2; //2 for windo
 ws desktop 5 for tablets
 num = 200; //length of data to be displayed 200 for desktop, 100 for tablet
 
 String currPath = "C:/BehaviorDATA/"; //D drive used on tablets
 
 //Analogue control of LED intensity
 String LEDVoltVal1 = "255"; // 255 
 String LEDVoltVal2 = "0"; // 128
 String LEDVoltVal3 = "0"; // 64
 
 */

import processing.serial.*;   // import the Processing serial library //<>// //<>// //<>// //<>//
import controlP5.*;
import org.gicentre.utils.stat.*;   
ControlP5 cp5;

DropdownList p1;

//// **To change depending on computer being used** ////
int serialPortNo = 0; //1 for tablets/windows, 5 for Mac
int screenStepSize =2; //2 for windows desktop 5 for tablets
int num = 200; //length of data to be displayed 200 for desktop, 100 for tablet
int numRun = 500; //length of data to be displayed 200 for desktop, 100 for tablet
int tickHeight = 15; // Height of continous recording data 
int sampleRate = 115200;
String BoxNo = "10"; //Change box number to keep track of training rig being used

float minX = 170;
float maxX = 290;

float diffMinMax = maxX-minX;
float defaultY = 260; 


//Define position of the GUI window
int WindowX=0;
int WindowY=0;

// Initialize chart classes
BarChart barChart;
BarChart barChartVel;

String currPath = "C:/BehaviorDATA/"; //D drive used on tablets
String currFolder = currPath;

////**////
PrintWriter output;    // initialize the PrintWriter Java object
FloatList BinnedPerformance; 
FloatList BinnedPerformanceStim; 
FloatList BinnedRunningVel; 

Serial myPort;    // the serial port
// String dataReading;  // initialize variable for serial data from Arduino
// String [] dataOutput = {
// };

//Defaults for calculating running velocity from Wheel encoder
float stepPerResolution = 360*2; //steps (current code looks for up and down changes. 
float wheelDistancePerTurn = 47.75; //cm
float cmPerStep = wheelDistancePerTurn/stepPerResolution;
int  ref;

//GUI stuff
boolean startedRecording = false;
boolean canStart = false;
boolean establishCOMS=false;
boolean sendAngles=false;
boolean reSetBins=false;
boolean firstContact = false;
boolean sendParameters = false;
boolean readyToStart = false;
boolean waitForUpdates = false;
boolean updating = false;
boolean newFileNeeded = false;
boolean updateState = false;
boolean localization = false;
boolean localizationTab = false;
boolean justRunSettings = false;
boolean booleanVal = false;
boolean cleared = false;
boolean notCount=true;
boolean StimTrial = false;
//boolean otherAnglesInc = true;
boolean tabledLoaded=false;
boolean setButtonPositions=false;

//boolean drawStim = false;

//text box
int sizeTextBoxW = 200;
int sizeTextBoxH = 40;

float lineDisplayHeight = 0.85;

//Size of GUI
int ScreenSizeW = 800; //full screen size x pixels 800
int ScreenSizeH = 600; //full screen size y pixels 600

// initialize variables for incoming serial data from Arduino
float encoder0Pos;
float targetArea;
float rewarded;
float rewardedR;
float licksL;
float licksR;
float LEDstate;
float count;
float countTrialTally=0;
float countStim=0;
float time;
float autoReward;
float breakON;
float negReward;
float lastMove;
float trialType;
float loopTime;
float encoderStepNo = 1;
float catchTrial;
float LEDvolt;

String timeStr = str(time);
int numStimPositions=0;

// for licking, reward and stim area
float mx[] = new float[num]; //x time series
int myLED[] = new int[num]; //x time series
int myTA[] = new int[num]; //target area
int myLickL[] = new int[num]; //licking left
int myLickR[] = new int[num]; //licking right
int myReward[] = new int[num]; //rewards
int myRewardR[] = new int[num]; //rewards Right Port
int myNegReward[] = new int[num]; //rewards
int xPos=0; //current x position

// for running wheel velocity
int myVelWheel[] = new int[num]; //x time series
float mxRun[] = new float[numRun]; //x time series
int myVelWheelRun[] = new int[numRun]; //x time series

//To tally performance
int hitTally = 0;
int missTally = 0;
int correctRejectionTally = 0;
int falseAlarmTally = 0;
int lastTrialType=0;
int hitTallyStim = 0;
int missTallyStim = 0;
int correctRejectionTallyStim = 0;
int falseAlarmTallyStim = 0;
float preCount=0;

// initialize variable to store binned performance
float BinnedhitTally = 0;
float BinnedmissTally = 0;
float BinnedcorrectRejectionTally = 0;
float BinnedfalseAlarmTally = 0;
float BinnedhitTallyStim = 0;
float BinnedmissTallyStim = 0;
float BinnedcorrectRejectionTallyStim = 0;
float BinnedfalseAlarmTallyStim = 0;
float catchTrialTally = 0;
float TempbinnedPerformance;
float TempbinnedPerformanceStim;

int BinWidth = 250;
int BinHeight = 100;
float BinSize = 10; // Define the bin size for performance calculation

// initialize variable to store binned running Velocity
float Binnedrunning = 0;
float totalDistance=0;
float oldDistance=0;


float tempHitTally;
float tempmissTally;
float tempfalseAlarmTally;
float tempcorrectRejectionTally;

float tempHitTallyStim;
float tempmissTallyStim;
float tempfalseAlarmTallyStim;
float tempcorrectRejectionTallyStim;


float TempbinnedrunningVel;
float BinSizeVel = 100; // Define the bin size for performance calculation

// Velocity smoothing variables for wheel encoder
int numReadings = 10; // number of samples in buffer to average current velocity off of
float readings[] = new float[numReadings]; // the buffer of distances travelled in each reading
int readIndex = 0; // current location in buffer
float total = 0; // total distance travelled in buffer
float average = 0; // current velocity of the mouse

int numReadingsVel = 500; // number of samples in buffer to average current velocity off of **was 100
float readingsVel[] = new float[numReadingsVel]; // the buffer of distances travelled in each reading
int readIndexVel = 0; // current location in buffer
float totalVel = 0; // total distance travelled in buffer
float averageVel = 0; // current velocity of the mouse

float startingHeightChart = 0.6;
PVector center = new PVector(ScreenSizeW*0.3, ScreenSizeH*0.60);

Table table;
Table tableStimPos;

int numStim = 13;
int[] angles = new int[numStim];
float[] xEcclips = new float[angles.length];
float[] yEcclips = new float[angles.length];

float[] xEcclips2 = new float[angles.length];
float[] yEcclips2 = new float[angles.length];

float[] activeAngle = new float[angles.length];
int midPointAngle;
int idxAngles [];

float barWidthValue = 0.05;
float barWidthLineValue = barWidthValue+0.05;
float BinPositionWidthVel = ScreenSizeW*(barWidthValue+0.05);
float BinPositionHeightVel = ScreenSizeH*0.18;
float BinWidthVel = ScreenSizeW-(ScreenSizeW*(barWidthValue+0.05)*2);
float BinHeightVel = ScreenSizeH/3;


boolean firstSubmit=true;
boolean first=false;

void setup() {

  size(800, 700); //from600
  surface.setLocation(WindowX,WindowY);
  background(0);
  smooth();

  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  // initialize all the readings to 0:
  for (int thisReadingVel = 0; thisReadingVel < numReadingsVel; thisReadingVel++) {
    readingsVel[thisReadingVel] = 0;
  }

  // Initialize all elements of each array to zero.
  for (int i = 0; i < mx.length; i ++ ) {
    mx[i] = 0; 
    myLED[i] = 0;
    myTA[i] = 0; //target area
    myLickL[i] = 0; //target area
    myLickR[i] = 0; //target area
    myReward[i] = 0; //target area
    myRewardR[i] = 0; //target area
    myNegReward[i] = 0;
  }

  //SET UP GUI INPUTSrow.getString("variable");
  cp5 = new ControlP5(this);

//Load Default settings
  Table table = loadTable("inputData.csv","header");
 int noInputs = table.getRowCount();
   GUIbuttons(table,noInputs, 1);

//set Time
cp5.get(Textfield.class,"Time").setText(timeStr);

  //PerformanceBarChart
  BinnedPerformance = new FloatList();
  float[] BinnedPerformanceF = BinnedPerformance.array();
  barChart = new BarChart (this);
  barChart.setData(BinnedPerformanceF);
  barChart.setMinValue(0);
  barChart.setMaxValue(100);

  //runningBarChart
  BinnedRunningVel = new FloatList();
  float runVelGraphMax = 200;
  barChartVel = new BarChart (this);
  barChartVel.setMinValue(0);
  barChartVel.setMaxValue(runVelGraphMax);
  barChartVel.setBarColour(color(255, 255, 255));


//Load default stimulus Positions
    Table tableStimPos = loadTable("stimulusPos.csv","header");
 int noStim = tableStimPos.getRowCount();
stimSetup(tableStimPos, noStim);


  //Select the correct serial port and band rate
  print("COM ports avaliable: ");
  println(Serial.list());

    print("COM port selected: ");
  println(Serial.list()[serialPortNo]);


  myPort = new Serial(this, Serial.list()[serialPortNo], sampleRate); 
  myPort.bufferUntil('\n'); // buffer until a new line
  
}

void draw() {
 
  if (!startedRecording) {
  background(0);
  setUPstim();
    //text(currFolder, ScreenSizeW*0.05, ScreenSizeH*0.03);
  }
  updateElapsedTime(); 
  if (startedRecording) { 
    if ((justRunSettings) && (!cleared) ) {
      booleanVal = false;
      clearScreen();
      cleared = true;
    } else if (!justRunSettings) {
      booleanVal = true;
      clearScreen();
    }
    background(0);
    text(currFolder, ScreenSizeW*0.05, ScreenSizeH*0.03);

    if (justRunSettings) {
if (!setButtonPositions){
cp5.getController("RunToInitiate").setPosition((ScreenSizeW * 0.41), (ScreenSizeH * (0.05 + (0 * 0))));
cp5.getController("RunToInitiate").setSize(sizeTextBoxW/2, sizeTextBoxH/1);
setButtonPositions = true;
}


      justRunDisplay();
    }
        else if (!justRunSettings) {
      behaviorDisplay();
    }

    if (loopTime==0) {
      loopTime=1;
    }
    // calculate smoothered velocity
    total = total - readings[readIndex]; //subtract last line
    readings[readIndex] = (encoderStepNo/loopTime);// calculate loop velocity
    total = total +readings[readIndex]; //add the readings to the total
    readIndex = readIndex + 1; //advance to the next position in the array

    //if we're at the end of the array
    if (readIndex >=numReadings) {
      readIndex = 0; //wrap around to the beginning
    }

    //calculate the average
    average = total/numReadings;
  }
}

void repositionCanvas(){
while (!frame.isVisible()) delay(2);
surface.setLocation(WindowX,WindowY);
}

void stimSetup(Table tableStimPos, int noInputs){

println("stimSetUp");

for (int i=0;i<tableStimPos.getRowCount();i++){
TableRow rowStim = tableStimPos.getRow(i);
angles[i]= rowStim.getInt("Vals");
}

TableRow rowStim = tableStimPos.getRow(0);
midPointAngle = rowStim.getInt("Midpoint");

float maxAngle = max(angles);
float divFactor = maxAngle/diffMinMax;

float x;
float y;

//Set up stimulus display
  for (int i = 0; i <angles.length; i++) {

//PREPARE FOR LINEAR STIM

  xEcclips2[i] = ((angles[i])/divFactor)+minX;
  yEcclips2[i] = defaultY;

//PREPARE FOR ANGULAR STIM
xEcclips[i] = center.x + cos(radians(angles[i]))*100;
yEcclips[i] = center.y + sin(radians(angles[i]))*100;

  // drawStimPlot(i, 4);
  }
}
