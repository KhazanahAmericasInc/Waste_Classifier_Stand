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
#define threshold 15000
#define hysteresis 5000
//*************************************


unsigned long delayStart = 0; // the time the delay started
bool lightOn = false; // true if light is on
bool above = true; //tracks hysterisis of sensor to avoid flashing

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);

}

void loop() {
  val = Sensor.capacitiveSensor(30); //Gets reading from sensor
  Serial.println(val);

  //Double checks value if reading is above threshhold 
  if (val >= threshold)
  {
    val = Sensor.capacitiveSensor(30);
  }

  //If value was above threshold and has now dropped below, set above to false so light can be touched again
  if (above && val < (threshold-hysteresis))
  {
    above = false;
  }

  //Toggle light if touched
  else if (!above && val >= threshold)
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
    above = true;
  }


  //Turn off light after 5 minutes
  if (lightOn && ((millis() - delayStart) >= 300000))
  {
    lightOn = false;
    digitalWrite(led, LOW);
    
  }
}
