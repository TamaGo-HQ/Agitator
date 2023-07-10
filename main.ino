//--------------- Libraries --------------------------------------//
#include <Servo.h>
#include <Arduino.h>
#include "BasicStepperDriver.h"
#include <math.h> 


//--------------- Define -----------------------------------------//

#define LITTLE_SERVO_PIN 5
#define BIG_SERVO_PIN 3

#define CYCLE_DURATION 10000

//---------------- Objects ---------------------------------------//

Servo LittleServo;
Servo BigServo;

//--------------- declaring global variables ----------------------//
int inputCycle = 0;
bool stopCycle = false;

int rotationTime = 0;  
int d = 0;              //period between different command signals
int n = 0;              //number of toggles
int vitesseSens1 = 0;
int vitesseSens2 = 0;

//-------- Timers
unsigned long startCycleMillis;
unsigned long fullCycleMillis;
unsigned long cycleRunningTime;

//--------------- function headers---------------------------------//
int full_cycle();
int yoyo_cycle();
int sway_rotate();

int stop_cycle();



void setup() {
  Serial.begin(9600);
  
  LittleServo.attach(LITTLE_SERVO_PIN);  // attaches the servo on pin 9 to the servo object
                               // 400 and 500 are min and max values for write 
  
  BigServo.attach(BIG_SERVO_PIN);
  
  while (!Serial) {
    ;                          // wait for serial port to connect.
  }
  Serial.print("Starting : ");
  print_options();
  
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
  else{
    stop_cycle();
    print_options();
  }

}

int get_cycle(){
  // store user input in input_cylce
   if (Serial.available() > 0) {
    int userInput = Serial.read();
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
      stopCycle = false;
      inputCycle = userInput - 48;
      startCycleMillis = millis();
      break;
      
      default :
      Serial.print("invalid input\n");
      
    }
  }  
}

int full_cycle(){
  
   if(inputCycle == 1){
     //-- Get current time 
     fullCycleMillis = millis();
     
     //-- Calculate time period since the cycle started 
     cycleRunningTime = fullCycleMillis - startCycleMillis; 
     
     if (cycleRunningTime < CYCLE_DURATION){
        
        LittleServo.write(150);
        //-------- if the number of seconds is pair -> run clockwise
        if ((trunc((cycleRunningTime/1000) % 2)) == 0){
          BigServo.write(0); 
        }
        else{ //run counter counter clockwise
          BigServo.write(180); 
        } 
     }
     else{
      stop_cycle();
      print_cycle_done();
      inputCycle = 0;
     }
   }
}

int yoyo_cycle(){
   ;  
}

int sway_rotate(){
   ;  
}

int stop_cycle(){
  LittleServo.write(90);
  BigServo.write(0);
}

int print_options(){
  Serial.print("Ready for mixing!\n\
  Please choose an option :\n\
  \tType 1 for Full cycle\n\
  \tType 2 for Yoyo cycle\n\
  \tType 3 for Sway & Rotate cycle\n");
}

int print_cycle_done(){
  Serial.print("Cycle Done!");
}
