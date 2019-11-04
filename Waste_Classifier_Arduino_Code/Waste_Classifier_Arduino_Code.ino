#include <CapacitiveSensor.h>
CapacitiveSensor Sensor = CapacitiveSensor(2,3);


long val;
#define led 4
#define threshold 15000
#define hysteresis 5000

unsigned long delayStart = 0; // the time the delay started
bool lightOn = false; // true if still waiting for delay to finish
bool above = true; //

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);

}

void loop() {
  val = Sensor.capacitiveSensor(30);
  Serial.println(val);

  //Double checks value if reading is above threshhold 
  if (val >= threshold)
  {
    val = Sensor.capacitiveSensor(30);
  }

  if (above && val < (threshold-hysteresis))
  {
    above = false;
  }

  else if (!above && val >= threshold)
  {
    if (lightOn == false)
    {
      digitalWrite(led, HIGH);
      lightOn = true;
      delayStart = millis();
    }
  
    else
    {
      digitalWrite(led, LOW);
      lightOn = false;
    }
    above = true;
  }

  if (lightOn && ((millis() - delayStart) >= 300000))
  {
    lightOn = false;
    digitalWrite(led, LOW);
    
  }

  

}
