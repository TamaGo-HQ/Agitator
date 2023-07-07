//--------------- Libraries --------------------------------------//
#include <Servo.h>
#include <Arduino.h>
#include "BasicStepperDriver.h"
#include <math.h> 


//--------------- Define -----------------------------------------//
#define ENA_PIN 8
#define DIR_PIN 2 
#define STEP_PIN 5
#define SERVO_PIN A0

//#define SLP 13

#define MOTOR_STEPS 200
#define RPM 120
#define MICROSTEPS 8
#define CYCLE_DURATION 10000

//---------------- Objects ---------------------------------------//

BasicStepperDriver stepper(MOTOR_STEPS, DIR_PIN, STEP_PIN);
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
  
  myservo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object
                               // 400 and 500 are min and max values for write 
  stepper.begin(RPM, MICROSTEPS);
  
  pinMode (DIR_PIN,  OUTPUT);
  pinMode (STEP_PIN, OUTPUT);
  pinMode (ENA_PIN,  OUTPUT);
  
  digitalWrite(ENA_PIN,  LOW);

  while (!Serial) {
    ;                          // wait for serial port to connect.
  }
  Serial.print("Starting : ");
  Serial.print("Ready for mixing!\n\
  Please choose an option :\n\
  \tType 1 for Full cycle\n\
  \tType 2 for Yoyo cycle\n\
  \tType 3 for Sway & Rotate cycle\n");
  
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
     fullCycleMillis = millis();
     cycleRunningTime = fullCycleMillis - startCycleMillis;
     stepper.setRPM(200);
     
     if (cycleRunningTime < CYCLE_DURATION){
        //-------- stepper 
        
       
        //-------- servo
        if ((trunc((cycleRunningTime/1000) % 2)) == 0){
          myservo.write(60); 
          stepper.rotate(10); 
        }
         
        else{
          myservo.write(130);
          stepper.rotate(-10);
        }
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
  myservo.write(90);
}
