
// SERVO pin definitions

#include <Servo.h>

Servo Servo_1; 
Servo Servo_2; 
Servo Servo_3; 
Servo Servo_4; 

int servoPos_1 = 45;
int servoPos_2 = 45;
int servoPos_3 = 45;
int servoPos_4 = 45;

const int servoAwake = 45; // Awake
const int servoSleep = 142; // Sleep

// LED pin definitions

#define LED_1  12
#define LED_2  11
#define LED_3  10
#define LED_4  9

#define LED_Begin    6
#define LED_Finish   5

// LASER pin definitions

#define Laser 4

// Sensor definitions

const int Min_Sensor_Value = 300;

// Sensor pin definitions

#define Sensor_1  A0
#define Sensor_2  A1
#define Sensor_3  A2
#define Sensor_4  A3

int Anas_1 = 0;
int Anas_2 = 0;
int Anas_3 = 0;
int Anas_4 = 0;

// Buzzer definitions

#define Speaker  3

#define Tone_1   220
#define Tone_2   262
#define Tone_3   330
#define Tone_4   392

#define Tone_Duration 250

// Game Variables

int randNumber;
int Game_Speed = 4000;
int Game_Status = 0;
int Game_Points = 0;
int Game_Step = 0;
int Read_Step = Game_Step;

// Game Setup
void setup() 

{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  Servo_1.attach(9);
  Servo_2.attach(10);
  Servo_3.attach(11);
  Servo_4.attach(12);
  
  pinMode(Laser, OUTPUT);
  
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  
  pinMode(LED_Begin, OUTPUT);
  pinMode(LED_Finish, OUTPUT);
  
  pinMode(Sensor_1, INPUT);
  pinMode(Sensor_2, INPUT);
  pinMode(Sensor_3, INPUT);
  pinMode(Sensor_4, INPUT);
  
  pinMode(Speaker, OUTPUT);

}

void loop()
{
  digitalWrite(Laser, HIGH); // Turn Laser On
  
  //Reading the Sensors values
  Anas_1 = analogRead(Sensor_1);
  Anas_2 = analogRead(Sensor_2);
  Anas_3 = analogRead(Sensor_3);
  Anas_4 = analogRead(Sensor_4);
  
  //Writing the Sensors values
  Serial.println("Sensor 1 = ");
  Serial.print(Anas_1);
  Serial.println("Sensor 2 = ");
  Serial.print(Anas_2);
  Serial.println("Sensor 3 = ");
  Serial.print(Anas_3);
  Serial.println("Sensor 4 = ");
  Serial.print(Anas_4);
{
  
  // In what mode are we?
  switch(Game_Status)
  {
    case 0:
      beginGame(); // Almost Finish - Tones
      break;
    case 1:
      Score(); // To-Do
      break;
    case 2:
      resetGame(); // To-Do
      break;
    case 3:
      playSequence(); // Maybe
      break;
    case 4:
      readSequence(); // Maybe
      break;
    case 5:
      gameOver(); // To-Do
      break;
  }
 }
}

void beginGame() // Case 0
{
  Game_Status = 0;
  
  //Initializing the positions of the Servo to Sleep.
  Servo_1.write(servoSleep);
  Servo_2.write(servoSleep);
  Servo_3.write(servoSleep);
  Servo_4.write(servoSleep);
  
  // print a random number from 1 to 4
  randNumber = random(1, 5);
  Serial.println(randNumber);
  delay(Game_Speed);

  // Servo_1 Step
  if (randNumber = 1)
  { //Initialize Servo_1 to Awake
    Servo_1.write(servoAwake);
    //Read Sensor_1
    if(Anas_1 > Min_Sensor_Value)
    {
      digitalWrite(LED_1, HIGH);
      Servo_1.write(servoSleep);
      Game_Points =+50;
    
      delay(Game_Speed);
      digitalWrite(LED_1, LOW);
      Servo_1.write(servoAwake);
    }
  }
  
  // Servo_2 Step
  if (randNumber = 2)
  { //Initialize Servo_2 to Awake
    Servo_2.write(servoAwake);
    //Read Sensor_2
    if(Anas_2 > Min_Sensor_Value)
    {
      digitalWrite(LED_2, HIGH);
      Servo_2.write(servoSleep);
      Game_Points =+50;
    
      delay(Game_Speed);
      digitalWrite(LED_2, LOW);
      Servo_2.write(servoAwake);
    }
  }
  
  // Servo_3 Step
  if (randNumber = 3)
  { //Initialize Servo_3 to Awake
    Servo_3.write(servoAwake);
    //Read Sensor_3
    if(Anas_3 > Min_Sensor_Value)
    {
      digitalWrite(LED_3, HIGH);
      Servo_3.write(servoSleep);
      Game_Points =+50;
    
      delay(Game_Speed);
      digitalWrite(LED_3, LOW);
      Servo_3.write(servoAwake);
    }
  }
  
  // Servo_4 Step
  if (randNumber = 4)
  { //Initialize Servo_4 to Awake
    Servo_4.write(servoAwake);
    //Read Sensor_4
    if(Anas_4 > Min_Sensor_Value)
    {
      digitalWrite(LED_4, HIGH);
      Servo_4.write(servoSleep);
      Game_Points =+50;
    
      delay(Game_Speed);
      digitalWrite(LED_4, LOW);
      Servo_4.write(servoAwake);
    }
  }

  // Score Atteigned
  if (Game_Points > 200)
  {
    Game_Status = 1; // Go to Case 1 (Score)
  }
}

void Score() // Case 1
{
  Serial.println("YOU WIN!!!");
}

void resetGame() // Case 2
{
}

void playSequence() // Case 3
{
}

void readSequence() // Case 4
{
}

void gameOver() // Case 5
{
}

