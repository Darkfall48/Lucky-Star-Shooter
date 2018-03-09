// SERVO pin definitions

#include <Servo.h>

Servo Servo_1; 

const int servoAwake           = 0; // Awake
const int servoSleep           = 90; // Sleep

// Game States
const int GAME_STATE_RESET     = 0;
const int GAME_STATE_RUN       = 1;
const int GAME_STATE_GAME_OVER = 2;
const int GAME_STATE_WIN       = 3;
const int GAME_STATE_TARGET    = 4;

// Sensor pin definitions
const int Sensor_1 = A0;

int Anas_1;

// Game Variables
int randNumber;
int currentGameState;
int gameScore = 0;

void setup() {
  Serial.begin(9600);  //Begin serial communication
  randomSeed(analogRead(0));
  currentGameState = GAME_STATE_RESET;
  
  Servo_1.attach(9);
}

void loop() {
  switch(currentGameState) {
    // Set targets to down position and initialize game variables
    case GAME_STATE_RESET:
      gameScore = 0;
      currentGameState = GAME_STATE_TARGET;
      break;
    case GAME_STATE_TARGET:
      // Pick a target
      
      // Get reference target variables: sensor and servo
      
      currentGameState = GAME_STATE_RUN;
      break;
    case GAME_STATE_RUN:
      // Check reset button state, if on then change currentGameState to GAME_STATE_RESET
      
      // check sensor value: if hot then add 1 to score and change game state to GAME_STATE_TARGET
      
      // Keep track of time: if too long then change game state to GAME_STATE_GAME_OVER
      
      // Keep track of score: if higher than 30 then change game state to GAME_STATE_WIN
      
      break;
    case GAME_STATE_GAME_OVER;
      // Play loser sound
      break;
    case GAME_STATE_WIN:
      // Play winner sound
      break;
  }
  
  //Initialize the Servo
  Servo_1.write(servoSleep);
  delay(500);
  
  //Reading the Sensors values
  Anas_1 = analogRead(Sensor_1);
  
  //Writing the Sensors values
  Serial.print("Sensor 1 = ");
  Serial.println(Anas_1);
  delay(200);  

  if (Anas_1 > 90) {
      Servo_1.write(servoAwake);
      delay(500);
  }
    
  else {
    Serial.print("waiting for laser");
  }
}



