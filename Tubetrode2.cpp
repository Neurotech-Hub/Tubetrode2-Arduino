#include "Tubetrode2.h"

Tubetrode2::Tubetrode2(uint8_t address)
{
  _address = address;
}

void Tubetrode2::begin()
{
  Wire.begin();
  enableAveragingFilter();
}

void Tubetrode2::enableAveragingFilter()
{
  Wire.beginTransmission(_address);
  Wire.write(OPCODE_SINGLE_REGISTER_WRITE);
  Wire.write(OSR_CFG);
  Wire.write(0b00000111); // OSR=128
  Wire.endTransmission();
}

void Tubetrode2::readRawSensors(float *rawSensorValues, bool toVolts)
{
  for (uint8_t channel = 0; channel <= 6; channel++)
  {
    // Begin I2C write operation
    Wire.beginTransmission(_address);
    Wire.write(OPCODE_SINGLE_REGISTER_WRITE);
    Wire.write(CHANNEL_SEL);
    Wire.write(channel);
    uint8_t error = Wire.endTransmission();

    // Check for I2C transmission error
    if (error != 0)
    {
      Serial.print("I2C Transmission Error: ");
      Serial.println(error);
      delay(1000); // Wait for a second before retrying
      return;
    }

    // Request 2 bytes from the I2C device
    Wire.requestFrom(_address, 2);
    uint16_t buffer = 0;
    if (Wire.available() == 2)
    {
      uint8_t msb = Wire.read(); // Read first byte (MSB)
      uint8_t lsb = Wire.read(); // Read second byte (LSB)
      buffer = (msb << 8) | lsb; // Combine MSB and LSB
    }
    else
    {
      // Handle error (e.g., not enough data received)
      Serial.println("Error: Not enough data received");
    }

    // Convert to float and store in the array
    rawSensorValues[channel] = buffer;
    if (toVolts)
    {
      rawSensorValues[channel] = (float(buffer) / 65535.0) * 2.5; // Convert to volts
    }
  }
}

void Tubetrode2::estimatePosition()
{
  float rawSensorValues[7];
  readRawSensors(rawSensorValues, false);
  // Add processing logic here
}
