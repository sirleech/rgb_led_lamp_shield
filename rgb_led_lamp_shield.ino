const int REDPin = 3;    // RED pin of the LED to PWM pin 4 
const int GREENPin = 5;  // GREEN pin of the LED to PWM pin 5
const int BLUEPin = 6;   // BLUE pin of the LED to PWM pin 6

const int REDPin2 = 9;    // RED pin of the LED to PWM pin 4 
const int GREENPin2 = 10;  // GREEN pin of the LED to PWM pin 5
const int BLUEPin2 = 11;   // BLUE pin of the LED to PWM pin 6

int brightnessRed = 0; // LED brightness
int brightnessGreen = 0; // LED brightness
int brightnessBlue = 0; // LED brightness

const int redPot = 0;
const int greenPot = 1;
const int bluePot = 2;

int rVal = 0;
int gVal = 0;
int bVal = 0;
boolean on = false;
boolean previousState = false;
String onStr = "";

const int buttonPin = 2;    // the pin that the pushbutton is attached to
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
int buttonPushCounter = 0;

void setup()
{
  pinMode(REDPin, OUTPUT); 
  pinMode(GREENPin, OUTPUT); 
  pinMode(BLUEPin, OUTPUT); 
  pinMode(REDPin2, OUTPUT); 
  pinMode(GREENPin2, OUTPUT); 
  pinMode(BLUEPin2, OUTPUT); 

  Serial.begin(9600);
}

void loop()
{

  // get pot vals
  rVal = analogRead(redPot);
  gVal = analogRead(greenPot);
  bVal = analogRead(bluePot);

  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter++;
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter, DEC);
    } 
    else {
      // if the current state is LOW then the button
      // wend from on to off:
      toggle();
      Serial.print("toggled: "); 
      Serial.println(onStr); 
    }
  }
  // save the current state as the last state, 
  //for next time through the loop
  lastButtonState = buttonState;

  if (on) {
    fadeOn();
  } 
  else {
    fadeToBlack();
  } 

  analogWrite(REDPin, brightnessRed);
  analogWrite(GREENPin, brightnessGreen);
  analogWrite(BLUEPin, brightnessBlue);
  analogWrite(REDPin2, brightnessRed);
  analogWrite(GREENPin2, brightnessGreen);
  analogWrite(BLUEPin2, brightnessBlue);
}

void toggle(){
  //toggle on or off
  on = !on;
  //save the previous state
  previousState = on;

  //strings
  if (on){
    onStr = "On";
  } 
  else {
    onStr = "Off";
  }
}

void fadeOn(){

  if(brightnessRed < map(rVal,0,1025,0,255)) 
    brightnessRed++;
  else
    brightnessRed = map(rVal,0,1025,0,255);

  if(brightnessBlue < map(bVal,0,1025,0,255))
    brightnessBlue++;
  else
    brightnessBlue =  map(bVal,0,1025,0,255);

  if (brightnessGreen < map(gVal,0,1025,0,255))
    brightnessGreen++;
  else
    brightnessGreen = map(gVal,0,1025,0,255);

  delay(5);
}

void fadeToBlack(){
  if (brightnessRed-- < 1)
    brightnessRed = 0;
  if (brightnessGreen-- < 1)
    brightnessGreen = 0;
  if (brightnessBlue-- < 1)
    brightnessBlue = 0;

  delay(10);
}






