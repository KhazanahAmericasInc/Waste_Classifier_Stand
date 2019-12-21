//Craig Crundwell
//Oct 30 2019
//This program is run on the arduino Nano inside the waste classifier
//The program reads a touch sensor and controls the LED lights

//Library for capacitive sensing
#include <CapacitiveSensor.h>

//Creates sensor object attached to pins 2 and 3
CapacitiveSensor Sensor = CapacitiveSensor(2,3);


long val; //used to store sensor reading 

#define led 4


//Adjust these value below to change touch sensitivity

//*************************************
#define threshold 100
#define hysteresis 50
//*************************************

int previous = 0;
int current = 0;
int diff = 0;

unsigned long delayStart = 0; // the time the delay started
bool lightOn = false; // true if light is on
bool above = true; //tracks hysterisis of sensor to avoid flashing

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  delay(500);
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);

}

void loop() {
  
  current = Sensor.capacitiveSensor(30); //Gets reading from sensor
  Serial.print(current);

  diff = current - previous;
  Serial.print("******  ");
  Serial.println(diff);

  if (diff > threshold)
  {
    if (lightOn == false)
    {
      digitalWrite(led, HIGH);
      lightOn = true;
      delayStart = millis();// Start tracking time for sleep timer
    }
  
    else
    {
      digitalWrite(led, LOW);
      lightOn = false;
    }
  }




  //Turn off light after 5 minutes
  if (lightOn && ((millis() - delayStart) >= 300000))
  {
    lightOn = false;
    digitalWrite(led, LOW);
    
  }

  previous = current;
  
}
