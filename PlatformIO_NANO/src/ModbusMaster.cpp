#include "ModbusMaster.h"

// ----------------------------- Constructor ---------------------------------
ModbusMaster::ModbusMaster(Stream &serial, int8_t dePin)
    : _serial(serial), _dePin(dePin), _baud(19200), _defaultTimeout(1000), _debug(false) {
  if (_dePin >= 0) {
    pinMode(_dePin, OUTPUT);
    digitalWrite(_dePin, LOW); // receive mode by default
  }
}

// ----------------------------- Public API ---------------------------------
void ModbusMaster::begin(unsigned long baud) {
  _baud = baud;
  // If the Stream is a HardwareSerial, call begin on it.
  // We attempt a dynamic_cast-like check by testing for Stream subclass Serial class presence.
#if defined(UBRR0H) || defined(UBRR1H) || defined(UBRR2H) || defined(UBRR3H)
  // On AVR, Serial is available as a global HardwareSerial; user should call Serial.begin() before.
#endif
  _defaultTimeout = 1000;
}

/**
 * @brief Set per-request default timeout
 */
void ModbusMaster::setResponseTimeout(unsigned long ms) {
  _defaultTimeout = ms;
}

bool ModbusMaster::readHoldingRegisters(uint8_t slave, uint16_t start, uint16_t qty,
                                        uint16_t *outBuffer, unsigned long timeoutMs) {
  if (qty == 0 || qty > 125) return false;

  uint8_t pdu[5];
  pdu[0] = 0x03;
  pdu[1] = (uint8_t)(start >> 8);
  pdu[2] = (uint8_t)(start & 0xFF);
  pdu[3] = (uint8_t)(qty >> 8);
  pdu[4] = (uint8_t)(qty & 0xFF);

  uint8_t resp[256];
  int respLen = 0;
  if (!_sendRequestAndWait(slave, pdu, 5, resp, sizeof(resp), respLen, timeoutMs)) return false;

  // Expected response: slave, func(0x03), byteCount, data...
  if (respLen < 3) return false;
  if (resp[1] & 0x80) return false; // exception
  if (resp[1] != 0x03) return false;
  uint8_t byteCount = resp[2];
  if (respLen != (3 + byteCount + 2 - 2)) {
    // our _receiveRaw returns only PDU (no addr/crc) OR full frame? We implement receiveRaw to include full frame.
    // But here assume resp contains full frame starting with address; adjust accordingly below.
  }
  // resp currently contains full frame: addr, func, byteCount, data..., crcLo, crcHi
  if (respLen < (3 + byteCount + 2)) return false;
  // copy registers
  for (uint16_t i = 0; i < qty; ++i) {
    uint16_t hi = resp[3 + i*2];
    uint16_t lo = resp[3 + i*2 + 1];
    outBuffer[i] = (uint16_t)((hi << 8) | lo);
  }
  return true;
}

bool ModbusMaster::writeSingleRegister(uint8_t slave, uint16_t addr, uint16_t value,
                                       unsigned long timeoutMs) {
  uint8_t pdu[5];
  pdu[0] = 0x06;
  pdu[1] = (uint8_t)(addr >> 8);
  pdu[2] = (uint8_t)(addr & 0xFF);
  pdu[3] = (uint8_t)(value >> 8);
  pdu[4] = (uint8_t)(value & 0xFF);

  uint8_t resp[16];
  int respLen = 0;
  if (!_sendRequestAndWait(slave, pdu, 5, resp, sizeof(resp), respLen, timeoutMs)) return false;

  // Expected normal response echoes request (addr, func, addrHi, addrLo, valHi, valLo, crcLo, crcHi)
  if (respLen < 8) return false;
  if (resp[1] & 0x80) return false;
  if (resp[1] != 0x06) return false;
  // echo is validated by CRC in receive
  return true;
}

bool ModbusMaster::writeMultipleRegisters(uint8_t slave, uint16_t start, const uint16_t *values,
                                          uint16_t qty, unsigned long timeoutMs) {
  if (qty == 0 || qty > 123) return false;
  uint16_t byteCount = qty * 2;
  // PDU: func(1) + start hi lo + qty hi lo + byteCount + data...
  uint8_t pdu[5 + 246]; // safe
  pdu[0] = 0x10;
  pdu[1] = (uint8_t)(start >> 8);
  pdu[2] = (uint8_t)(start & 0xFF);
  pdu[3] = (uint8_t)(qty >> 8);
  pdu[4] = (uint8_t)(qty & 0xFF);
  pdu[5] = (uint8_t)byteCount;
  for (uint16_t i = 0; i < qty; ++i) {
    pdu[6 + i*2] = (uint8_t)(values[i] >> 8);
    pdu[6 + i*2 + 1] = (uint8_t)(values[i] & 0xFF);
  }
  uint8_t resp[16];
  int respLen = 0;
  if (!_sendRequestAndWait(slave, pdu, 6 + byteCount, resp, sizeof(resp), respLen, timeoutMs)) return false;

  // Expected response: addr, func(0x10), startHi, startLo, qtyHi, qtyLo, crcLo, crcHi
  if (respLen < 8) return false;
  if (resp[1] & 0x80) return false;
  if (resp[1] != 0x10) return false;
  return true;
}

bool ModbusMaster::readCoils(uint8_t slave, uint16_t start, uint16_t qty,
                             uint8_t *outBits, unsigned long timeoutMs) {
  if (qty == 0 || qty > 2000) return false;
  uint8_t pdu[5];
  pdu[0] = 0x01;
  pdu[1] = (uint8_t)(start >> 8);
  pdu[2] = (uint8_t)(start & 0xFF);
  pdu[3] = (uint8_t)(qty >> 8);
  pdu[4] = (uint8_t)(qty & 0xFF);

  uint8_t resp[256];
  int respLen = 0;
  if (!_sendRequestAndWait(slave, pdu, 5, resp, sizeof(resp), respLen, timeoutMs)) return false;

  if (respLen < 5) return false;
  if (resp[1] & 0x80) return false;
  if (resp[1] != 0x01) return false;
  uint8_t byteCount = resp[2];
  if (respLen < (3 + byteCount + 2)) return false;

  // copy byteCount bytes to outBits
  uint16_t bytesNeeded = (qty + 7) / 8;
  if (byteCount < bytesNeeded) return false;
  for (uint16_t i = 0; i < bytesNeeded; ++i) outBits[i] = resp[3 + i];
  return true;
}

// ----------------------------- Private helpers -----------------------------

/**
 * @brief Compute Modbus CRC16 (polynomial 0xA001).
 */
uint16_t ModbusMaster::_crc16(const uint8_t *buf, uint16_t len) {
  uint16_t crc = 0xFFFF;
  for (uint16_t pos = 0; pos < len; pos++) {
    crc ^= (uint16_t)buf[pos];
    for (int i = 0; i < 8; ++i) {
      if (crc & 0x0001) {
        crc >>= 1;
        crc ^= 0xA001;
      } else {
        crc >>= 1;
      }
    }
  }
  return crc;
}

void ModbusMaster::_txEnable() {
  if (_dePin >= 0) {
    digitalWrite(_dePin, HIGH);
    // allow driver to enable
    delayMicroseconds(10);
  }
}

void ModbusMaster::_txDisable() {
    if (_dePin >= 0) {
        // wait for serial to finish transmitting
        _serial.flush(); // just call flush, no if-check needed
        digitalWrite(_dePin, LOW);
        delayMicroseconds(10);
    }
}


void ModbusMaster::_sendRaw(const uint8_t *buf, uint16_t len) {
  _txEnable();
  // write raw bytes
  for (uint16_t i = 0; i < len; ++i) _serial.write(buf[i]);
  _serial.flush(); // block until sent
  _txDisable();
}

/**
 * @brief Receive raw frame into buffer (full Modbus RTU frame: addr func ... crcLo crcHi).
 * @return number of bytes received, or -1 on timeout/error
 */
int ModbusMaster::_receiveRaw(uint8_t *buf, uint16_t maxLen, unsigned long timeoutMs) {
  unsigned long start = millis();
  uint16_t idx = 0;
  // We read bytes until timeout without new bytes (inter-byte gap)
  // Wait for first byte until timeoutMs
  while (millis() - start < timeoutMs) {
    if (_serial.available()) break;
  }
  if (!_serial.available()) return -1; // timeout waiting for first byte

  unsigned long lastByte = millis();
  while (true) {
    while (_serial.available() && idx < maxLen) {
      buf[idx++] = (uint8_t)_serial.read();
      lastByte = millis();
    }
    // if no data for 3.5 char times we consider frame finished; approximate using 5 ms at high baud,
    // but use timeoutMs short window here: stop when no new data arrives for 20 ms
    if (millis() - lastByte > 20) break;
    if (millis() - start > timeoutMs) break;
  }
  // minimal length check: must include at least addr, func, 2 CRC
  if (idx < 4) return -1;
  // verify CRC
  uint16_t rcvCrc = (uint16_t)buf[idx - 2] | ((uint16_t)buf[idx - 1] << 8);
  uint16_t calc = _crc16(buf, idx - 2);
  if (rcvCrc != calc) {
    if (_debug) {
      Serial.println("ModbusMaster: CRC mismatch on response");
    }
    return -1;
  }
  return (int)idx;
}

/**
 * @brief Send PDU to slave (build ADU = addr + pdu + crc) and wait for response into respBuf.
 *
 * @param slave slave id
 * @param pdu pointer to PDU bytes (function code + data)
 * @param pduLen length of PDU
 * @param respBuf buffer to store response frame
 * @param respMaxLen capacity of respBuf
 * @param respLen output length of received frame (including CRC)
 * @param timeoutMs per-call timeout in ms
 *
 * @return true on valid response received (CRC ok), false on error/timeout/exception
 */
bool ModbusMaster::_sendRequestAndWait(uint8_t slave, const uint8_t *pdu, uint16_t pduLen,
                                       uint8_t *respBuf, uint16_t respMaxLen, int &respLen,
                                       unsigned long timeoutMs) {
  if (timeoutMs == 0) timeoutMs = _defaultTimeout;
  // Build ADU: addr + pdu
  uint8_t adu[256];
  if (pduLen + 3 > sizeof(adu)) return false;
  adu[0] = slave;
  memcpy(&adu[1], pdu, pduLen);
  uint16_t crc = _crc16(adu, (uint16_t)(1 + pduLen));
  adu[1 + pduLen] = (uint8_t)(crc & 0xFF);
  adu[1 + pduLen + 1] = (uint8_t)((crc >> 8) & 0xFF);
  uint16_t aduLen = (uint16_t)(1 + pduLen + 2);

  if (_debug) {
    char tmp[80];
    snprintf(tmp, sizeof(tmp), "ModbusMaster -> slave=%u func=0x%02X len=%u", slave, pdu[0], pduLen);
    Serial.println(tmp);
  }

  // Purge any incoming bytes before sending
  while (_serial.available()) _serial.read();

  // send
  _sendRaw(adu, aduLen);

  // wait for response
  int got = _receiveRaw(respBuf, respMaxLen, timeoutMs);
  if (got < 0) {
    if (_debug) Serial.println("ModbusMaster: response timeout or CRC error");
    respLen = 0;
    return false;
  }
  respLen = got;
  // Verify frame address matches slave
  if (respBuf[0] != slave) {
    if (_debug) {
      Serial.print("ModbusMaster: response addr mismatch: ");
      Serial.print(respBuf[0]);
      Serial.print(" expected ");
      Serial.println(slave);
    }
    return false;
  }
  // check for Modbus exception
  if (respBuf[1] & 0x80) {
    if (_debug) {
      Serial.print("ModbusMaster: exception code ");
      Serial.println(respBuf[2], DEC);
    }
    return false;
  }
  return true;
}
