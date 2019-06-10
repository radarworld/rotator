

float Temp; 
int val = 0;

void setup() 
{
  Serial.begin(9600);
  Serial.println('a');
  char a = 'b';
  while (a != 'a')
  {
    a = Serial.read();
  }
}

void loop() 
{
  while (Serial.available() == 0)
  {
  }
  
  if (Serial.available() > 0)
  {
   val = Serial.read();
   if (val == 'R')
   {
     getTemperature();
     Serial.println(Temp);
   } 
  }
  delay(20);
}

/////////////////////////////////////////////////////////////////////////
int getTemperature()
{
  
  Temp = 27;
  return Temp;
}
