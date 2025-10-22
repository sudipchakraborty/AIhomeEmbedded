#ifndef MODBUSSLAVE_H
#define MODBUSSLAVE_H

#include <Arduino.h>

/**
 * @file ModbusSlave.h
 * @brief Simple Modbus RTU Slave for Arduino (supports basic function codes).
 *
 * Designed for Arduino Nano using the hardware Serial port and a MAX485-style RS-485 transceiver.
 * Provide a DE/RE pin (often tied together) to control direction when transmitting.
 *
 * NOTE: Call `process()` frequently from loop() to handle incoming frames.
 */

/** Modbus exception codes */
#define MB_EX_ILLEGAL_FUNCTION     0x01
#define MB_EX_ILLEGAL_ADDRESS      0x02
#define MB_EX_ILLEGAL_VALUE        0x03
#define MB_EX_SLAVE_FAILURE        0x04

class ModbusSlave {
public:
  /**
   * @brief Construct a new Modbus Slave.
   * 
   * @param slaveId Modbus slave ID (1..247)
   * @param dePin Arduino pin used for RS485 DE/RE control (set HIGH to transmit)
   * @param maxRegisters number of 16-bit holding registers to allocate
   * @param maxCoils number of coils (bits) to allocate
   */
  ModbusSlave(uint8_t slaveId, uint8_t dePin, uint16_t maxRegisters=128, uint16_t maxCoils=256);

  /** Initialize Serial peripheral and DE pin. 
   *  Call in setup(): beginSerial(baudRate) */
  void beginSerial(unsigned long baud);

  /** Call frequently in loop() to parse and respond to Modbus RTU frames */
  void process();

  /** Access register values (0..maxRegisters-1) */
  bool setRegister(uint16_t index, uint16_t value);
  bool getRegister(uint16_t index, uint16_t &value);

  /** Access coil values (0..maxCoils-1) */
  bool setCoil(uint16_t index, bool value);
  bool getCoil(uint16_t index, bool &value);

  /** Optional: send raw response (internal use) */
  void sendResponse(const uint8_t *buf, uint16_t len);

  /** Set frame timeout (idle time in ms to consider frame complete). Default 50ms. */
  void setFrameTimeout(unsigned long ms);

private:
  uint8_t _slaveId;
  uint8_t _dePin;
  uint16_t _maxRegisters;
  uint16_t _maxCoils;

  uint16_t *_registers; // dynamically allocated
  uint8_t *_coils;      // bit-packed coils array

  // Serial buffer for incoming frame
  static const uint16_t RX_BUF_SIZE = 256;
  uint8_t _rxBuf[RX_BUF_SIZE];
  uint16_t _rxLen;
  unsigned long _lastByteMs;
  unsigned long _frameTimeoutMs;

  void handleFrame();
  void handleReadHoldingRegisters(uint8_t *pdu, uint16_t pduLen);
  void handleWriteSingleRegister(uint8_t *pdu, uint16_t pduLen);
  void handleWriteMultipleRegisters(uint8_t *pdu, uint16_t pduLen);
  void handleReadCoils(uint8_t *pdu, uint16_t pduLen);

  // helper
  uint16_t computeCRC(const uint8_t *buf, uint16_t len);
  void sendException(uint8_t functionCode, uint8_t exceptionCode);
  void txEnable();
  void txDisable();
  void clearRx();
  inline bool coilGetBit(uint16_t idx);
  inline void coilSetBit(uint16_t idx, bool v);
};

#endif
