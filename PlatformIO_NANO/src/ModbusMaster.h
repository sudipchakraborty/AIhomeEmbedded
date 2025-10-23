#ifndef MODBUSMASTER_H
#define MODBUSMASTER_H

#include <Arduino.h>

/**
 * @file ModbusMaster.h
 * @brief Minimal Modbus RTU master for Arduino (blocking synchronous requests).
 *
 * Designed for use with RS-485 transceivers (e.g. MAX485). Supports basic
 * Modbus RTU function calls: Read Holding Registers (0x03), Read Coils (0x01),
 * Write Single Register (0x06) and Write Multiple Registers (0x10).
 *
 * Example:
 *   ModbusMaster mb(Serial, 2); // Serial stream and DE pin 2
 *   mb.begin(19200);
 *   uint16_t regs[10];
 *   if (mb.readHoldingRegisters(1, 0x0000, 4, regs, 1000)) {
 *     // success, regs[0..3] populated
 *   }
 */
class ModbusMaster {
public:
  /**
   * @brief Construct a new ModbusMaster object.
   * @param serial Reference to a Stream (Serial) object to use for Modbus RTU.
   * @param dePin Arduino pin connected to RS485 DE/RE (set HIGH to transmit). Use -1 to disable.
   */
  ModbusMaster(Stream &serial, int8_t dePin = -1);

  /**
   * @brief Initialize serial port parameters (call in setup()).
   * @param baud Baud rate (e.g. 19200)
   */
  void begin(unsigned long baud);

  /**
   * @brief Set response timeout (ms) for subsequent requests.
   * @param ms timeout in milliseconds (default 1000)
   */
  void setResponseTimeout(unsigned long ms);

  /**
   * @brief Read holding registers (function 0x03).
   *
   * @param slave slave address (1..247)
   * @param start starting register address
   * @param qty number of registers to read (1..125)
   * @param outBuffer pointer to buffer of uint16_t with at least qty entries
   * @param timeoutMs override timeout for this call (ms). If 0, use default.
   * @return true on success (outBuffer filled), false on failure
   */
  bool readHoldingRegisters(uint8_t slave, uint16_t start, uint16_t qty,
                            uint16_t *outBuffer, unsigned long timeoutMs = 0);

  /**
   * @brief Write single holding register (function 0x06).
   * @return true on success
   */
  bool writeSingleRegister(uint8_t slave, uint16_t addr, uint16_t value,
                           unsigned long timeoutMs = 0);

  /**
   * @brief Write multiple registers (function 0x10).
   * @param values pointer to uint16_t array with qty elements
   * @return true on success
   */
  bool writeMultipleRegisters(uint8_t slave, uint16_t start, const uint16_t *values,
                              uint16_t qty, unsigned long timeoutMs = 0);

  /**
   * @brief Read coils (function 0x01). Bits are packed LSB-first per Modbus spec.
   * @param outBits pointer to a byte buffer large enough to hold ceil(qty/8) bytes.
   * @return true on success
   */
  bool readCoils(uint8_t slave, uint16_t start, uint16_t qty,
                 uint8_t *outBits, unsigned long timeoutMs = 0);

  /**
   * @brief Enable or disable debug prints to Serial.
   * Debug uses Serial (not the stream passed to constructor).
   */
  void setDebug(bool enable) { _debug = enable; }

private:
  Stream &_serial;
  int8_t _dePin;
  unsigned long _baud;
  unsigned long _defaultTimeout;
  bool _debug;

  static const uint16_t RX_BUF_SIZE = 256;
  uint8_t _rxBuf[RX_BUF_SIZE];

  // helpers
  uint16_t _crc16(const uint8_t *buf, uint16_t len);
  void _txEnable();
  void _txDisable();
  void _sendRaw(const uint8_t *buf, uint16_t len);
  int _receiveRaw(uint8_t *buf, uint16_t maxLen, unsigned long timeoutMs);

  // build & parse helpers
  bool _sendRequestAndWait(uint8_t slave, const uint8_t *pdu, uint16_t pduLen,
                           uint8_t *respBuf, uint16_t respMaxLen, int &respLen,
                           unsigned long timeoutMs);
};

#endif // MODBUSMASTER_H
