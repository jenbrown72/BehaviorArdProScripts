void localization(boolean theFlag)
{
  if (!establishCOMS){
  if (theFlag == true) {
    localizationTab = true;
  }
  else {
    localizationTab = false;
  }
}
}

void JustRun(boolean theFlag)
{
  if (theFlag == true)
  {
    justRunSettings = true;
    screenStepSize = 1;
  }
}

void Reset(boolean theFlag)
{
  if (theFlag == true)
  {
    ResetVals();
  }
}

void SelectUser(boolean theFlag)
{
  if (theFlag == true)
  {
    File folderToStartFrom = new File(currPath);
    selectFolder("Select a folder to process:", "folderSelected", folderToStartFrom);
  }
}

void selectFiles(boolean theFlag)
{
  if (theFlag == true)
  {
    File csvFileToLoad = new File(currPath);
    selectInput("Select csv file to load:", "fileSelected", csvFileToLoad);
  }
}

void selectStim(boolean theFlag)
{
  if (theFlag == true)
  {
    File csvStimFileToLoad = new File(currPath);
    selectInput("Select csv file to load:", "stimSelected", csvStimFileToLoad);
  }
}

void folderSelected(File selection)
{
  if (selection == null)
  {
    println("Window was closed or the user hit cancel.");
    currFolder = currPath;
    println("User selected " + currFolder);
  }
  else
  {
    currFolder = (selection.getAbsolutePath() + "/");
    println("User selected " + currFolder);
  }
}

void fileSelected(File selection)
{
  if (selection == null)
  {
  }
  else
  {
    String file = selection.getName();
    table = loadTable(file, "header");
    int noInputs = table.getRowCount();
    GUIbuttons(table, noInputs, 0);
    println("Loaded specific file " + selection);
  }
}

void stimSelected(File selection)
{
  if (selection == null)
  {
  }
  else
  {
    String file = selection.getName();
    tableStimPos = loadTable(file, "header");
    int noStim = tableStimPos.getRowCount();
    stimSetup(tableStimPos, noStim);
  }
}