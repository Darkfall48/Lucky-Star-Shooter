// SERVO pin definitions

#include <Servo.h>

Servo Servo_1; 

const int servoAwake = 80; // Awake
const int servoSleep = 0; // Sleep

// Game Variables

int randNumber;

void setup() 
{
  
  Serial.begin(9600);
  randomSeed(analogRead(0));

  Servo_1.attach(3);

  
}

void loop() 
{
  Servo_1.write(servoSleep);
  delay(500);
  Servo_1.write(servoAwake);
  delay(500);

}
