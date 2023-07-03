unsigned long blinkStartMillis;
unsigned long fadeStartMillis;
unsigned long currentMillis;
const unsigned long blinkPeriod = 1000;  //blink period
const unsigned long fadePeriod = 10;  //fade period
const byte blinkLedPin = 13;    //this LED will blink
const byte fadeLedPin = 10;    //this LED will fade
byte brightness = 0;  //initial brightness of LED
byte increment = 1;  //amount to change PWM value at each change
bool stopBlinking = false;
char userInput;


void setup()
{
  Serial.begin(9600);  //start Serial in case we need to print debugging info
  pinMode(blinkLedPin, OUTPUT);
  blinkStartMillis = millis();  //start time of blinking LED
  fadeStartMillis = millis();  //start time of fading LED
}

void loop()
{ 
  check_user_input();
  if(!stopBlinking){
  currentMillis = millis();  //get the current time
  blink();
  fade();
  }
}

void blink()  //function to blink an LED if the blink period has ended
{
  if (currentMillis - blinkStartMillis >= blinkPeriod)  //test whether the period has elapsed
  {
    digitalWrite(blinkLedPin, !digitalRead(blinkLedPin));  //if so, change the state of the LED
    blinkStartMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
  }
}

void check_user_input(){
  if (Serial.available() > 0) {
    userInput = Serial.read();
    if (userInput == 's') {
      stopBlinking = true;
      Serial.print("Blinking Stopped\n");
    } else if (userInput == 'c') {
      stopBlinking = false;
      Serial.print("Blinking Resumed\n");
    }else Serial.print("unvalid input\n");
  }
}

void fade()    //function to fade an LED
{
  if (currentMillis - fadeStartMillis >= fadePeriod)  //test whether the period has elapsed
  {
    analogWrite(fadeLedPin, brightness);    //set the brightness of the LED
    brightness += increment;    //will wrap round because brightness is an unsigned data type
    fadeStartMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
  }
}
