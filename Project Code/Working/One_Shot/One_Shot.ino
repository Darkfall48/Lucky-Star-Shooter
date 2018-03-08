// SERVO pin definitions

#include <Servo.h>

Servo Servo_1; 

const int servoAwake = 0; // Awake
const int servoSleep = 90; // Sleep

// Sensor pin definitions

const int Sensor_1 = A0;
int Anas_1;

// Game Variables

int randNumber;

void setup() 
{
  Serial.begin(9600);  //Begin serial communcation
  randomSeed(analogRead(0));
  
  Servo_1.attach(9);
}

void loop() 
{
  //Initialize the Servo
  Servo_1.write(servoSleep);
  delay(500);
  
  //Reading the Sensors values
  Anas_1 = analogRead(Sensor_1);
  
  //Writing the Sensors values
  Serial.print("Sensor 1 = ");
  Serial.println(Anas_1);
  delay(200);  

  if (Anas_1 > 90)
    {
      Servo_1.write(servoAwake);
      delay(500);
    }
    
  else
  {
    Serial.print("waiting for laser");
  }
}

