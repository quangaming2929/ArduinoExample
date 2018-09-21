/*
  QuangamingVn (R) 2015 - 2018 
  
  This code created by QuangamingVn collaborate with FRIT Club, all right covered at MIT license
  Idea: Nguyen Minh Quan
  Coder: Nguyen Minh Quan with help of Phan Manh

  Instruction: This will record and replay the sequence that user press.
  There are 2 button, 1 is for action record and 1 is for toggle mode between record and replay. Button can be reassign by change the varibles' value below
  When the Arduino start, the program will replay but since the Timeline don't have any data, the program is actually wait for record.
  When you change state to record, the 1st button (ledRep) will blink, you can change the blink interval by modify the varible below and the second button will light up.
  After hit the Toggle Button to change state, the first button will replay the user's press sequence by on or off. The Status LED will turn off.

  Record max length can by change by increase the timelineData's capaticy (cause more var memory, or change the interval to a bigger number (less accurate).
  You can change the blink interval when recording by change the 'btnStatusBlinkInterval' varible (unit: miliSecond)
  
*/


//set pinMode's number
int ledRep = 13;
int ledStat = 12;
int btnRec = 10;
int btnToggle = 9;

//data processing
bool timelineData[1024]; //depend on the size of the interval, this will change the time allow
int currentTimeline = 0;
int usedData = 0;
int keyframeInterval = 100; //Update the timeline (unit: ms)
bool isFullMem = false; //if the timelineData is full (1024)

//state information
bool isRec = false;
bool ledStatState = false;
int btnStatusBlinkInterval = 10;

void setup() {
  //init led, btn
  pinMode(ledRep, OUTPUT);
  pinMode(ledStat, OUTPUT);
  pinMode(btnRec, INPUT_PULLUP);
  pinMode(btnToggle, INPUT_PULLUP);
}

void loop() {
  //Use to swich mode between record and replay
  if(CheckPress(btnToggle))
  {
    isRec = !isRec;
    currentTimeline = 0; //reset the position when toggle mode

    //change the LED indication
    ledStatState = !ledStatState;
    digitalWrite(ledStat, ledStatState);
  }
 
  //Check the current mode
  if(isRec)
    Record();
  else
    Replay();
}

void Record()
{
  //Use for handle record  

  //if user just change mode to record, delete the last replay
  if(currentTimeline == 0)
    usedData = 0;

  //Write the replay
  timelineData[currentTimeline] = !digitalRead(btnRec);

  //Check if the mem is full or not
  if(usedData == 1023) //Change this if you change the array.
    isFullMem = true;

  //Make the LED blink when we are recording
  if(usedData % btnStatusBlinkInterval < 5)
  {
    digitalWrite(ledRep, HIGH);
  }
  else
  {
    digitalWrite(ledRep, LOW);
  }

  //Change the timeline position and usedData
  currentTimeline++;
  usedData++;
  delay(keyframeInterval - 10);
}

void Replay()
{
  //If there are nothing to play, quit the replay
  if(usedData == 0)
    return;
  
  //Use for handle replay
  digitalWrite(ledRep, timelineData[currentTimeline]);
  currentTimeline++;

  //If the replay end, replay again
  if(currentTimeline == usedData)
    currentTimeline = 0;

  // Delay for each keyframe
  delay(keyframeInterval); 
}

//pre-write
bool lastLow = false;
bool state = false;
  
bool CheckPress(int btnPin)
{

  if(digitalRead(btnPin) == HIGH)
  {
    lastLow = false;
  }
  if(digitalRead(btnPin) == LOW && !lastLow)
  {
  state = !state;
  lastLow= true;
  return true;
  } 
  delay(10);
  return false;
}
