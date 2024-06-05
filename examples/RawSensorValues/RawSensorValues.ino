#include <Wire.h>
#include "Tubetrode2.h"

Tubetrode2 tubetrode(0x14); // Example I2C address, adjust as needed

void setup()
{
  Serial.begin(9600);
  tubetrode.begin();
}

void loop()
{
  float rawSensorValues[7];
  tubetrode.readRawSensors(rawSensorValues, true);
  for (int i = 0; i < 7; i++)
  {
    Serial.print(rawSensorValues[i]);
    if (i < 6)
    {
      Serial.print(", ");
    }
  }
  Serial.println();
  delay(10);
}
