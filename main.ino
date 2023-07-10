//--------------- Libraries --------------------------------------//
#include <Servo.h>
#include <Arduino.h>
#include "BasicStepperDriver.h"
#include <math.h> 
#include "agitator_header.h"

//--------------- Define -----------------------------------------//

#define LITTLE_SERVO_PIN 5
#define BIG_SERVO_PIN 3

//--------------- declaring global variables ----------------------//

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
