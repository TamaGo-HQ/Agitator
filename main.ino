//--------------- Libraries --------------------------------------//
#include <Servo.h>
#include <Arduino.h>
#include "BasicStepperDriver.h"
#include <math.h> 


//--------------- Define -----------------------------------------//
#define DIR_PIN 7
#define STEP_PIN 6

#define SLP 13
#define MOTOR_STEPS 200
#define RPM 120
#define MICROSTEPS 16

#define CYCLE_DURATION 10000

//---------------- Objects ---------------------------------------//

BasicStepperDriver stepper(MOTOR_STEPS, dir_pin, step_pin);
Servo myservo;

//--------------- declaring global variables ----------------------//
int inputCycle = 0;
bool stopCycle = false;

int rotation_time = 0;  
int d = 0;              //period between different command signals
int n = 0;              //number of toggles
int vitesse_sens1 = 0;
int vitesse_sens2 = 0;

//-------- Timers
unsigned long cycleStartMillis;

//--------------- function headers---------------------------------//
int full_cycle();
int yoyo_cycle();
int sway_rotate();



void setup() {
  Serial.begin(9600);
  
  myservo.attach(9,400,2500);  // attaches the servo on pin 9 to the servo object
                               // 400 and 500 are min and max values for write 
  stepper.begin(RPM, MICROSTEPS);
  
  pinMode (DIR_PIN,  OUTPUT);
  pinMode (STEP_PIN, OUTPUT);
  pinMode (SLP,      OUTPUT);
  digitalWrite(SLP,  LOW);

  while (!Serial) {
    ;                          // wait for serial port to connect.
  }
  Serial.print("Starting : ");
}



void loop() {
  //---------------   get the user input
  get_cycle(); 
  
  //case fc -> function rotate full cycle
  if(!stopCycle){
      full_cycle();
      yoyo_cycle();
      sway_rotate();
  }
  else stop_cycle();

}

int get_cycle(){
  Serial.print("Ready for mixing!\n\
  Please choose an option :\n\
  \tType 1 for Full cycle\n\
  \tType 2 for Yoyo cycle\n\
  \tType 3 for Sway & Rotate cycle\n");
  
  // store user input in input_cylce
   if (Serial.available() > 0) {
    userInput = Serial.read();
    switch (userInput) {
      case 's':
      stopCycle = true;
      Serial.print("Cycle Stopped\n");
      break;
      
      case 'c':
      stopCycle = false;
      Serial.print("Cycle Resumed\n");
      break;
      
      case '1' :
      case '2':
      case '3':
      inputCycle = userInput - 48;
      startCycleMillis = millis();
      break;
      
      default :
      Serial.print("invalid input\n");
      
    }
  }  
}

int full_cycle(){
  
   fullCycleMillis = millis();
   cycleRunningTime = fullCycleMillis - startCycleMillis;
   
   if (cycleRunninTime < CYCLE_DURATION){
      if ((trunc((cycleRunningTime/1000) % 2)) == 0)
      myservo.write(60);  
      else
      myservo.write(130);
   }
}

int yoyo_cycle(){
   myservo.write(60);  
   myservo.write(130);  
}

int sway_rotate(){
   myservo.write(0);  
   myservo.write(180);  
}
