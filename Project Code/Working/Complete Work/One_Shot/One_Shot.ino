// SERVO pin definitions

#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// Pin Assignment
const int targetLightSensor_0 = A0;
const int targetLightSensor_1 = A1;
const int targetLightSensor_2 = A2;
const int targetLightSensor_3 = A3;

const int targetServoPin_0    = 2;
const int targetServoPin_1    = 3;
const int targetServoPin_2    = 4;
const int targetServoPin_3    = 5;

const int MAX_LIGHT_ALLOWED   = 75;
const int MAX_GAME_SCORE      = 5;
const int MAX_TIME_ALLOWED    = 8;

// Define Attached Components
Servo targetServo_0, targetServo_1, targetServo_2, targetServo_3; 

// Servo Positions
const int TARGET_UP            = 80; // Awake
const int TARGET_DOWN          = 0; // Sleep

// Game States
const int GAME_STATE_RESET     = 0;
const int GAME_STATE_RUN       = 1;
const int GAME_STATE_GAME_OVER = 2;
const int GAME_STATE_WIN       = 3;
const int GAME_STATE_TARGET    = 4;

int targetLightValue;

Servo targetServoList[4] = { targetServo_0, targetServo_1, targetServo_2, targetServo_3 };
int   targetSensorList[4] = { targetLightSensor_0, targetLightSensor_1, targetLightSensor_2, targetLightSensor_3 };


// Game Variables
int randNumber;
int currentGameState;
int gameScore = 0;
int scoreConfirm = 0;
int timeElapsed = 0;
int timeInMili = 0;

void setup() {
  Serial.begin(9600);  //Begin serial communication
  lcd.begin(16, 2);
  
  randomSeed(analogRead(0));
  currentGameState = GAME_STATE_RESET;
  
  targetServo_0.attach(targetServoPin_0);
  targetServo_1.attach(targetServoPin_1);
  targetServo_2.attach(targetServoPin_2);
  targetServo_3.attach(targetServoPin_3);
}

void loop() {
  switch(currentGameState) {
    // Set targets to down position and initialize game variables
    case GAME_STATE_RESET:
      for(int i = 0; i < 4; i++) {
        targetServoList[i].write(TARGET_DOWN);
      }
      gameScore = 0;
      timeElapsed = 0;
      currentGameState = GAME_STATE_TARGET;
      break;
    case GAME_STATE_TARGET:
      // Pick a target
      randNumber = random(1, 4);
      targetServoList[randNumber].write(TARGET_UP);
      targetLightValue = 0;
      
      currentGameState = GAME_STATE_RUN;
      break;
    case GAME_STATE_RUN:

      // Check reset button state, if on then change currentGameState to GAME_STATE_RESET
      
      // check sensor value: if hot then add 1 to score and change game state to GAME_STATE_TARGET
      targetLightValue = analogRead(targetSensorList[randNumber]);
     
      if(targetLightValue > MAX_LIGHT_ALLOWED) {
        
        if(scoreConfirm > 3) {
          gameScore++;
          scoreConfirm = 0;
          targetServoList[randNumber].write(TARGET_DOWN);
          currentGameState = GAME_STATE_TARGET;
        } else {
          scoreConfirm++;
        }
        
      }
      // Keep track of time: if too long then change game state to GAME_STATE_GAME_OVER
      timeInMili = millis();
      if((int)(timeInMili / 100) % 10 == 0) {
        timeElapsed++;
      }

      if(timeElapsed >= MAX_TIME_ALLOWED) {
        currentGameState = GAME_STATE_GAME_OVER;
      }
      
      // Keep track of score: if higher than 30 then change game state to GAME_STATE_WIN
      if(gameScore >= MAX_GAME_SCORE) {
        currentGameState = GAME_STATE_WIN;
      }

      Serial.print("Target  = ");
      Serial.print(randNumber);
      Serial.print(" - ");
      Serial.print(targetServoList[randNumber].read());
      Serial.print(" - light: ");
      Serial.print(targetLightValue);
      Serial.print(" - score: ");
      Serial.print(gameScore);    
      Serial.print(" - timeElapsedre: ");
      Serial.println(timeInMili);  

      lcd.setCursor(0, 0);
      lcd.print("Score: ");
      lcd.setCursor(10, 0);
      lcd.print(gameScore);
      
      delay(500);      
      
      break;
    case GAME_STATE_GAME_OVER:
      // Play loser sound
      Serial.println("Game Over");
      lcd.setCursor(0, 1);
      lcd.print("Game Over");
      delay(20000);      
      break;
    case GAME_STATE_WIN:
      // Play winner sound
      Serial.println("Player Wins");
      lcd.setCursor(0, 1);
      lcd.print("You Won");      
      delay(20000);
      break;
  }
  
  //Initialize the Servo
  //targetServo_0.write(TARGET_DOWN);
  //delay(500);
  
  //Reading the Sensors values
  //targetLightValue = analogRead(targetLightSensor_0);
  
  //Writing the Sensors values
  //Serial.print("Sensor 1 = ");
  //Serial.println(targetLightValue);
  //delay(200);  

  //if (targetLightValue > 90) {
  //    targetServo_0.write(TARGET_UP);
  //    delay(500);
  //}
    
  //else {
  //  Serial.print("waiting for laser");
  //}
}



