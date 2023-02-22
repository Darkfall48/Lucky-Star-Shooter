# Lucky Star Shooter

This project is an electronic game that I created for my school in just two weeks. While I worked on the project solo, my grandfather provided some physical assistance.

![alt text](https://lh3.googleusercontent.com/pw/AM-JKLW0b_vyckFcauG9ON37M0rmIh1aLeO-MaazDg8t2idlpXRpFyka7RZmp5s428cVRruJHI53FMH5IG7Djn7jdTCRY7xFOZF5AOSQdLiNXK4po-gnPz6piPa-czFuzDYPJHoyus14sqrqvajUiDJzNHYhnw)

### Overview

The project is called **Lucky Star Shooter**, and it was built using Arduino as its main component. The game features four targets that rise one after the other during a set time period. The player must aim and hit the center of the targets using the laser gun provided to them within the time limit. The score is displayed in real-time on an LCD screen.

### Components
The project used the following components:

- Arduino Uno x1
- Servo motors (Micro-Servo) x4
- Light Sensor (Photo-Resistor) x4
- Laser Diode x1
- Button x2
- 9v Battery x2
- LCD display (Liquid Crystal) x1
- Potentiometer x1
- Capacitors/Resistors/Cables x1

Although sound was intended to be included, I was unable to complete this feature due to time constraints.

### Awards
My project was selected by my school to participate in an international competition at Tel-Aviv University.

## The Global Idea

<img src="https://user-images.githubusercontent.com/35638060/181654793-c03af573-6e5f-4a4b-8e00-0648daa31b18.png" width="400">

## The Laser Gun

### Global Schematic

<img src="https://user-images.githubusercontent.com/35638060/181654843-eba6293b-2000-4d00-aff7-d7dd85b5d5d5.png" width="400">

### Electronic Shematic

<img src="https://user-images.githubusercontent.com/35638060/181654898-3f8396d3-6303-4775-a881-a10abeabbc35.png" width="400">

## The Targets

### Global Schematic

<img src="https://user-images.githubusercontent.com/35638060/181654977-4cae27e4-fc13-4724-8663-947f6321c430.png" width="400">

### Connectics

<img src="https://user-images.githubusercontent.com/35638060/181655158-8b33d0dd-5f29-438b-b729-a4f7db23be80.png" width="350">

## The Code

### Global Shematic (In Hebrew)

<img src="https://user-images.githubusercontent.com/35638060/181655059-de8f5fd7-eeb7-41ff-8774-3236076a25b4.png" width="350">

### The Code
```C#
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
```

## Deployment

+ Arduino Uno

## Built With

* [Arduino Software](https://www.arduino.cc/en/Main/Software) - The coding program I used
* [Fritzing Software](https://fritzing.org/) - The schematic design software I used

## Authors

* **Sidney Sebban** - *Initial work* - [Darkfall48](https://github.com/Darkfall48)

### You can follow me on

* [My Website](http://darkfall48.wix.com/darkfall48/)
* [My Youtube Channel](https://youtube.com/darkfall48/)

## Acknowledgments

* Inspiration: Lucky Luke

## More Pictures and Videos

* [💡Projet Électronique💡 - 🏹Lucky Star Shooter🎯](https://photos.app.goo.gl/C8r7bQkPRmpScWuZ6)

## Project Documentation

* [Lucky Star Shooter - Documentation (In Hebrew)](https://github.com/Darkfall48/Lucky-Star-Shooter/files/9215014/Lucky.Star.Shooter.-.Project.Electronic.-.Sidney.Sebban.For.GitHub.pdf)
