// LASER pin definitions

#define Laser 2

// Sensor pin definitions

const int Sensor_1 = A0;
int Anas_1 = 0;

void setup()
{
   pinMode(Laser, OUTPUT);
   pinMode(Sensor_1, INPUT);
}


void loop()
{
   digitalWrite(Laser, HIGH); // Turn Laser On

   Anas_1 = analogRead(Sensor_1);
   
   delay(100);
   Serial.println("Sensor 1 = ");
   Serial.print(Anas_1);
   if (Sensor_1 > 0)
   {
    Serial.println("Yolo");
   }
}

