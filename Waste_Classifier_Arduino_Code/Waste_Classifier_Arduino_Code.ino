#include <CapacitiveSensor.h>
CapacitiveSensor Sensor = CapacitiveSensor(4,6);


long val;
#define led 13
#define threshold 1000

unsigned long delayStart = 0; // the time the delay started
bool lightOn = false; // true if still waiting for delay to finish

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);

}

void loop() {
  val = Sensor.capacitiveSensor(30);
  Serial.println(val);

  if (val >= threshold && lightOn == false)
  {
    digitalWrite(led, HIGH);
    lightOn = true;
    delayStart = millis();
    delay (400);
  }

  else if (val >= threshold && lightOn == true)
  {
    digitalWrite(led, LOW);
    lightOn = false;
    delay (400);
  }

  if (lightOn && ((millis() - delayStart) >= 10000))
  {
    lightOn = false;
    digitalWrite(led, LOW);
    
  }

  

}
