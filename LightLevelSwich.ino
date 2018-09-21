/*
  QuangamingVn (C) 2015 - 2018 
  
  This code created by QuangamingVn collaborate with FRIT Club, all right covered at MIT license
  Idea: Nguyen Minh Quan
  Coder: Nguyen Minh Quan with help of Phan Manh

  When you click the button, the LED get brighter an specific level, there are 4 light level
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
