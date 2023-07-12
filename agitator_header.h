//--------------- function headers---------------------------------//
int full_cycle();
int yoyo_cycle();
int sway_rotate();
int pause_cycle();
int exit_cycle();
int print_cycle_done();
int print_options();
int print_cycle_done();
int resume_cycle();
int go_to_cycle();

//--------------- Define -----------------------------------------//
#define CYCLE_DURATION 10000

//---------------- Objects ---------------------------------------//

Servo BigServo;
Servo LittleServo;

//--------------- declaring global variables ----------------------//
int   inputCycle = 0;             // takes (1,2,3 for cycles, and 0 by default or when cycle is exited/completed)
bool  pausedCycle = false;        // false by default and true when cycle is paused


//-------- Timers
unsigned long startCycleMillis  = 0; // when the user pressed start cycle 
unsigned long currentTimeMillis = 0;// literally, what time is it now
unsigned long cycleRunningTime  = 0; // time period where the cycle was actually running (without pause)
unsigned long cyclePausedTime   = 0;  // time period where the cycle was paused
unsigned long pauseCycleMillis  = 0; // intialisition to this variable is necessary
unsigned long totalPausedTime   = 0;  // using it for now, maybe not optimal solution, but functional nevertheless

int get_cycle(){
  // store user input in input_cylce
   if (Serial.available() > 0) {
    int userInput = Serial.read();

    switch (userInput) {
      case 'x' :
        exit_cycle();
        break;

      case 'p':
        pause_cycle();
        break;
      
      case 'c':
        resume_cycle();   
        break;
      
      case '1' :
      case '2':
      case '3':
        go_to_cycle();
        break;
        
      default :
        Serial.print("invalid input\n");
    }
  }  
}

int full_cycle(){
  
   if(inputCycle == 1){
     //-- Get current time 
     currentTimeMillis = millis(); //lacks clarity in naming && no definition
     
     //-- Calculate time period since the cycle started 
     cycleRunningTime = currentTimeMillis - startCycleMillis - totalPausedTime; 
    
     //--  for debugging
     Serial.print("cycleRunningTime = "); Serial.print(cycleRunningTime);Serial.print("\n");
     Serial.print("cyclePausedtime\t");Serial.print(cyclePausedTime);Serial.print("\n");
     
     if (cycleRunningTime < CYCLE_DURATION){
        
        LittleServo.write(150);
        //-- if the number of seconds is pair -> run clockwise
        /*if ((trunc((cycleRunningTime/1000) % 2)) == 0){
          BigServo.write(50); 
        }
        else{ //run counter clockwise
          BigServo.write(150); 
        } */
     }
     else{
      exit_cycle();
     }
   }
}

int yoyo_cycle(){
   ;  
}

int sway_rotate(){
   ;  
}

int exit_cycle(){
  LittleServo.write(90);
  print_cycle_done();
  print_options();
  totalPausedTime = 0; // cycle finished -> reset totalPausedTime 
  inputCycle = 0; 
}

int pause_cycle(){
  if(!pausedCycle){ // without this condition, if user hits pause when its already paused, will reset the variable
    LittleServo.write(90);
    Serial.print("Cycle Paused\n"); 
    pauseCycleMillis = millis();   // time when the user last pressed pause
    pausedCycle = true;           // ? ambiguous variable, hmmmmm ?
  } 
}

int resume_cycle(){
  if(pausedCycle){
    pausedCycle = false;
    Serial.print("Cycle Resumed\n");
    totalPausedTime += cyclePausedTime;
  }
}

int idle_state(){
  LittleServo.write(90);

  if((millis() % 500 ) == 0)
  Serial.print("idle\n");

  if(inputCycle){ // if there s an ongoing cycle
    cyclePausedTime = millis() - pauseCycleMillis; //time passed since last time pause was pressed

    if((millis() % 500 ) == 0){
      Serial.print("cyclePausedtime\t");Serial.print(cyclePausedTime);Serial.print("\n");
    }
  }
}

int go_to_cycle(){
  if(!inputcycle){ // will ignore your request if there s an ongoing cycle
    pausedCycle = false;
    inputCycle = userInput - 48;
    startCycleMillis = millis();
    Serial.print(startCycleMillis);
  }
}

int print_options(){
  Serial.print("Ready for mixing!\n\
  Please choose an option :\n\
  \tType 1 for Full cycle\n\
  \tType 2 for Yoyo cycle\n\
  \tType 3 for Sway & Rotate cycle\n");
}

int print_cycle_done(){
  Serial.print("Cycle Done!\n");
}

