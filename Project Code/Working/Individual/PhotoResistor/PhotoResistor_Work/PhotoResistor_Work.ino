// Sensor pin definitions

const int Sensor_1 = A2;
int Anas_1;

void setup() 
{
  Serial.begin(9600);  //Begin serial communcation
  

}

void loop() 
{
  //Reading the Sensors values
  Anas_1 = analogRead(Sensor_1);
  
  //Writing the Sensors values
  Serial.print("Sensor 1 = ");
  Serial.println(Anas_1);
  delay(200);
}
