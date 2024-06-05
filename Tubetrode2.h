#ifndef TUBETRODE2_H
#define TUBETRODE2_H

#include <Wire.h>

// TLA2528
#define OPCODE_SINGLE_REGISTER_READ 0b00010000
#define OPCODE_SINGLE_REGISTER_WRITE 0b00001000
#define OPCODE_SET_BIT 0b00011000
#define OPCODE_CLEAR_BIT 0b00100000
#define OPCODE_READ_CONTINUOUS_BLOCK 0b00110000
#define OPCODE_WRITE_CONTINUOUS_BLOCK 0b00101000

#define SYSTEM_STATUS 0x0
#define GENERAL_CFG 0x1
#define DATA_CFG 0x2
#define OSR_CFG 0x3
#define OPMODE_CFG 0x4
#define PIN_CFG 0x5
#define GPIO_CFG 0x7
#define GPO_DRIVE_CFG 0x9
#define GPO_VALUE 0xB
#define GPI_VALUE 0xD
#define SEQUENCE_CFG 0x10
#define CHANNEL_SEL 0x11
#define AUTO_SEQ_CH_SEL 0x12

// Addressing
#define R1_0_R2_DNP 0x17
#define R1_11k_R2_DNP 0x16
#define R1_33k_R2_DNP 0x15
#define R1_100k_R2_DNP 0x14
#define R1_DNP_R2_DNP 0x10
#define R1_DNP_R2_11k 0x11
#define R1_DNP_R2_33k 0x12
#define R1_DNP_R2_100k 0x13

class Tubetrode2
{
public:
  Tubetrode2(uint8_t address);
  void begin(void);
  void readRawSensors(float *rawSensorValues, bool toVolts);
  void estimatePosition(void);

private:
  uint8_t _address;
  void enableAveragingFilter(void);
};

#endif // TUBETRODE2_H
