#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int time = 1000;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  
}

void loop() {
  
    myservo.write(80);              // tell servo to go to position in variable 'pos'
    delay(time);
    
    myservo.detach();
    delay(10);
    myservo.attach(9);
    
    myservo.write(110);              // tell servo to go to position in variable 'pos'
    delay(time);
      
    myservo.detach();
    delay(10);
    myservo.attach(9);                 
    
} 
