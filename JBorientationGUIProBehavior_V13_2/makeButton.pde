 
void makeButton(String varNames[], String varValues[], int toggleButton[], float xLocation[], float allylocation[], float allvdiff[], int allnoOfRows[], String textLabel[], int alldivW[], int alldivH[], String allincomingVals[], int newDiv[], int screenNo[], int allalignText[], int fontSize[], int allswitchMode[])
{
  int multiplier = 0;
  color setColorCntr = color(255, 255, 255);
  color setColorStim = color(255, 0, 0);
  color setColor;
  PFont font = createFont("arial", 9);
  PFont fontT = createFont("arial", 10); // 24
  for (int i = 0; i < varNames.length; i++)
  {
    if (newDiv[i] == 1)
    {
      multiplier = 0;
    }
    float xLocationTemp = xLocation[i];
    float vdiff = allvdiff[i];
    float ylocation = allylocation[i];
    int divW = alldivW[i];
    int divH = alldivH[i];
    int noOfRows = allnoOfRows[i];
    int alignText = allalignText[i];
    int switchMode = allswitchMode[i];
    boolean incomingVal = Boolean.parseBoolean(allincomingVals[i]);

    if (incomingVal) //TEXTFIELDS MADE AFTER SUBMIT
    {
      if (toggleButton[i] == 1)
      {
        setColor = setColorCntr;
      } else
      {
        setColor = setColorStim;
      }
    //  font = createFont("arial", (fontSize[i]));
            font = createFont("arial", 16);


      cp5.addTextfield(varNames[i])
        .setColor(color(setColor))
        .setColorBackground(255)
        .setPosition((ScreenSizeW * xLocationTemp), (ScreenSizeH * (ylocation + (vdiff * multiplier))))
        .setSize(sizeTextBoxW/divW, sizeTextBoxH/divH)
        .setAutoClear(false)
        .setDecimalPrecision(1)
        .setVisible(false)
        .setFont(font)
        .getCaptionLabel()
        .setFont(font);
      ;
    } else
    {
      if (toggleButton[i] == 0) //TEXTFIELD
      {
        font = createFont("arial", (fontSize[i]));
        cp5.addTextfield(varNames[i])
          .setPosition((ScreenSizeW * xLocationTemp), (ScreenSizeH * (ylocation + (vdiff * multiplier))))
          .setSize(sizeTextBoxW/divW, sizeTextBoxH/divH)
          .setAutoClear(false)
          .setFont(font)
          .setText(varValues[i])
                  .getCaptionLabel()
        .setFont(fontT);

        if (screenNo[i] == 2)
        {
          cp5.get(Textfield.class, varNames[i]).setVisible(false);
        } else
        {
          cp5.get(Textfield.class, varNames[i]).setVisible(true);
        };
      } else //TOGGLE BUTTON
      {
        float tempBool = float(varValues[i]);
        cp5.addToggle(varNames[i])
          .setPosition((ScreenSizeW * xLocationTemp), (ScreenSizeH * (ylocation + (vdiff * multiplier))))
          .setSize(sizeTextBoxW/divW, sizeTextBoxH/divH)
          .setValue(tempBool)
          .setVisible(true);
        if (alignText == 1)
        {
          cp5.get(Toggle.class, varNames[i]).getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER);
        }
        if (switchMode == 1)
        {
          cp5.get(Toggle.class, varNames[i]).setMode(ControlP5.SWITCH);
        };
      }
    }
    // for incoming values
    if (multiplier == (noOfRows - 1))
    {
      multiplier = 0;
    } else
    {
      multiplier++;
    }
  }
}

void updateButton(String varNames[], String varValues[], int toggleButton[], float xLocation[], float allylocation[], float allvdiff[], int allnoOfRows[], String textLabel[], int alldivW[], int alldivH[], String allincomingVals[], int newDiv[], int screenNo[], int allalignText[], int fontSize[], int switchMode[])
{
  for (int i = 0; i < varNames.length - 4; i++)
  {
    boolean incomingVal = Boolean.parseBoolean(allincomingVals[i]);
    if (!incomingVal)
    {
      if (toggleButton[i] == 0)
      {
        Textfield txt = ((Textfield) cp5.getController(varNames[i]));
        txt.setText(varValues[i]);
       // ;
      } else
      {
        float tempBool = float(varValues[i]);
        cp5.get(Toggle.class, (varNames[i])).setValue(tempBool);
        ;
      }
    }
  }
}