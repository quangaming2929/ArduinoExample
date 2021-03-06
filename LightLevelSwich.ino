/*
  Nguyen Minh Quan (C) 2018 
  
  This code was created by Nguyen Minh Quan with collaboration from the FRIT club. Licensed under the MIT license
  Idea: Nguyen Minh Quan
  Coder: Nguyen Minh Quan with help of Phan Manh

  When you click the button, the LED light gets brighter. There are 4 different brightness levels.
*/


bool state = false;
bool lastLOW = false;
int ledPin = 11;
int btnPin = 8;
int value = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
}

void loop() {
  if(digitalRead(btnPin) == HIGH)
  {
    lastLOW = false;
  }
  
  if(digitalRead(btnPin) == LOW && !lastLOW)
  {
    state = !state;
    value += 64;
    analogWrite(ledPin, value % 256);
    lastLOW = true;
  } 
}
