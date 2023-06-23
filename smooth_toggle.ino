#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int rotation_time = 5000;
int d = 50;              //period between different command signals
int n = 4;               //number of toggles
int vitesse_sens1 = 1200;
int vitesse_sens2 = 1700;

void setup() {
  myservo.attach(9,400,2500);  // attaches the servo on pin 9 to the servo object
                               // 400 and 500 are min and max values for write
                               
  myservo.writeMicroseconds(1500); 
}

void loop() { 
  
  //-------------------- rotate servo in sens 1 with speed vitesse_sens1---------------------//
    myservo.writeMicroseconds(vitesse_sens1);              
    delay(rotation_time);

  //-------------------- toggle command singnal between stopping and previous rotation---------------------//
  for(int counter = 0; counter < n; counter++){
    myservo.writeMicroseconds(1500);                        
    delay(d);
    myservo.writeMicroseconds(vitesse_sens1);             
    delay(d);
  }

  for(int counter = 0; counter < n; counter++){
    myservo.writeMicroseconds(1500);                        
    delay(d);
    myservo.writeMicroseconds(vitesse_sens2);             
    delay(d);
  }


//-------------------- rotate servo in sens 1 with speed vitesse_sens1  ---------------------//
    myservo.writeMicroseconds(vitesse_sens2);
    delay(rotation_time);
    
//-------------------- toggle command singnal between stopping and previous rotation---------------------//
  for(int counter = 0; counter < n; counter++){
    myservo.writeMicroseconds(1500);                        
    delay(d);
    myservo.writeMicroseconds(vitesse_sens2);             
    delay(d);
  }
  for(int counter = 0; counter < n; counter++){
    myservo.writeMicroseconds(1500);                        
    delay(d);
    myservo.writeMicroseconds(vitesse_sens1);             
    delay(d);
  }
}


int rotate_servo(
