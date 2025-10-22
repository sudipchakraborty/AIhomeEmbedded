#include "ModbusSlave.h"

/* ============================
   Implementation
   ============================ */

ModbusSlave::ModbusSlave(uint8_t slaveId, uint8_t dePin, uint16_t maxRegisters, uint16_t maxCoils) {
  _slaveId = slaveId;
  _dePin = dePin;
  _maxRegisters = maxRegisters;
  _maxCoils = maxCoils;

  _registers = (uint16_t*)malloc(sizeof(uint16_t) * _maxRegisters);
  if (_registers) memset(_registers, 0, sizeof(uint16_t) * _maxRegisters);

  // allocate coil bytes (bit-packed)
  uint16_t coilBytes = (_maxCoils + 7) / 8;
  _coils = (uint8_t*)malloc(coilBytes);
  if (_coils) memset(_coils, 0, coilBytes);

  _rxLen = 0;
  _lastByteMs = 0;
  _frameTimeoutMs = 50UL; // default
  pinMode(_dePin, OUTPUT);
  digitalWrite(_dePin, LOW); // receive mode initially
}

void ModbusSlave::beginSerial(unsigned long baud) {
  Serial.begin(baud);
  while (!Serial) { /* wait? on Nano returns immediately */ }
  clearRx();
}

void ModbusSlave::setFrameTimeout(unsigned long ms) {
  _frameTimeoutMs = ms;
}

void ModbusSlave::process() {
  // read available bytes
  while (Serial.available()) {
    if (_rxLen < RX_BUF_SIZE) {
      _rxBuf[_rxLen++] = Serial.read();
      _lastByteMs = millis();
    } else {
      // buffer overflow, flush input
      (void)Serial.read();
    }
  }

  // if we have data and frame timeout expired, process frame
  if (_rxLen > 0) {
    if ((unsigned long)(millis() - _lastByteMs) >= _frameTimeoutMs) {
      // handle frame
      handleFrame();
      clearRx();
    }
  }
}

void ModbusSlave::clearRx() {
  _rxLen = 0;
  _lastByteMs = 0;
}

uint16_t ModbusSlave::computeCRC(const uint8_t *buf, uint16_t len) {
  uint16_t crc = 0xFFFF;
  for (uint16_t pos = 0; pos < len; pos++) {
    crc ^= (uint16_t)buf[pos];
    for (int i = 0; i < 8; i++) {
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

void ModbusSlave::handleFrame() {
  // frame minimum: addr(1) + func(1) + CRC(2)
  if (_rxLen < 4) return;

  // verify CRC
  uint16_t rcvCrc = (uint16_t)_rxBuf[_rxLen - 2] | ((uint16_t)_rxBuf[_rxLen - 1] << 8);
  uint16_t calc = computeCRC(_rxBuf, _rxLen - 2);
  if (rcvCrc != calc) {
    // CRC mismatch - ignore
    return;
  }

  uint8_t addr = _rxBuf[0];
  if (addr != _slaveId && addr != 0) { // 0 = broadcast; only certain functions allowed for broadcast
    return;
  }

  uint8_t func = _rxBuf[1];
  uint8_t *pdu = &_rxBuf[2];
  uint16_t pduLen = _rxLen - 4; // exclude addr, func, crc(2)
  // pdu points to function-specific payload

  // handle supported functions
  switch (func) {
    case 0x03: // Read Holding Registers
      handleReadHoldingRegisters(pdu, pduLen);
      break;
    case 0x06: // Write Single Register
      handleWriteSingleRegister(pdu, pduLen);
      break;
    case 0x10: // Write Multiple Registers
      handleWriteMultipleRegisters(pdu, pduLen);
      break;
    case 0x01: // Read Coils
      handleReadCoils(pdu, pduLen);
      break;
    default:
      sendException(func, MB_EX_ILLEGAL_FUNCTION);
      break;
  }
}

/* -------------------------
   Function handlers
   ------------------------- */

// PDU for Read Holding Registers (0x03):
// Byte 0-1: starting address
// Byte 2-3: quantity of registers
void ModbusSlave::handleReadHoldingRegisters(uint8_t *pdu, uint16_t pduLen) {
  if (pduLen < 4) { sendException(0x03, MB_EX_ILLEGAL_VALUE); return; }
  uint16_t start = (pdu[0] << 8) | pdu[1];
  uint16_t qty = (pdu[2] << 8) | pdu[3];
  if (qty == 0 || qty > 125) { sendException(0x03, MB_EX_ILLEGAL_VALUE); return; } // limit per spec
  if (start + qty > _maxRegisters) { sendException(0x03, MB_EX_ILLEGAL_ADDRESS); return; }

  // build response: addr, func, byteCount, data..., crc
  uint8_t resp[5 + 250]; // safe
  uint16_t idx = 0;
  resp[idx++] = _slaveId;
  resp[idx++] = 0x03;
  resp[idx++] = qty * 2;
  for (uint16_t i = 0; i < qty; i++) {
    uint16_t val = _registers[start + i];
    resp[idx++] = (uint8_t)(val >> 8);
    resp[idx++] = (uint8_t)(val & 0xFF);
  }
  uint16_t crc = computeCRC(resp, idx);
  resp[idx++] = crc & 0xFF;
  resp[idx++] = (crc >> 8) & 0xFF;
  sendResponse(resp, idx);
}

// PDU for Write Single Register (0x06):
// Byte0-1 address, Byte2-3 value
void ModbusSlave::handleWriteSingleRegister(uint8_t *pdu, uint16_t pduLen) {
  if (pduLen < 4) { sendException(0x06, MB_EX_ILLEGAL_VALUE); return; }
  uint16_t addr = (pdu[0] << 8) | pdu[1];
  uint16_t val = (pdu[2] << 8) | pdu[3];
  if (addr >= _maxRegisters) { sendException(0x06, MB_EX_ILLEGAL_ADDRESS); return; }
  _registers[addr] = val;

  // response: echo request (addr, func, address hi lo, value hi lo, CRC)
  uint8_t resp[8 + 1];
  uint16_t idx = 0;
  resp[idx++] = _slaveId;
  resp[idx++] = 0x06;
  resp[idx++] = (uint8_t)(addr >> 8);
  resp[idx++] = (uint8_t)(addr & 0xFF);
  resp[idx++] = (uint8_t)(val >> 8);
  resp[idx++] = (uint8_t)(val & 0xFF);
  uint16_t crc = computeCRC(resp, idx);
  resp[idx++] = crc & 0xFF;
  resp[idx++] = (crc >> 8) & 0xFF;
  sendResponse(resp, idx);
}

// PDU for Write Multiple Registers (0x10):
// Byte0-1 start addr, Byte2-3 qty, Byte4 bytecount, Byte5.. data
void ModbusSlave::handleWriteMultipleRegisters(uint8_t *pdu, uint16_t pduLen) {
  if (pduLen < 5) { sendException(0x10, MB_EX_ILLEGAL_VALUE); return; }
  uint16_t start = (pdu[0] << 8) | pdu[1];
  uint16_t qty = (pdu[2] << 8) | pdu[3];
  uint8_t byteCount = pdu[4];
  if (qty == 0 || qty > 123) { sendException(0x10, MB_EX_ILLEGAL_VALUE); return; }
  if (byteCount != qty * 2) { sendException(0x10, MB_EX_ILLEGAL_VALUE); return; }
  if (start + qty > _maxRegisters) { sendException(0x10, MB_EX_ILLEGAL_ADDRESS); return; }
  if (pduLen < (uint16_t)(5 + byteCount)) { sendException(0x10, MB_EX_ILLEGAL_VALUE); return; }

  for (uint16_t i = 0; i < qty; i++) {
    uint16_t val = (pdu[5 + i*2] << 8) | pdu[5 + i*2 + 1];
    _registers[start + i] = val;
  }

  // Response: address, func, start hi lo, qty hi lo, CRC
  uint8_t resp[8];
  uint16_t idx = 0;
  resp[idx++] = _slaveId;
  resp[idx++] = 0x10;
  resp[idx++] = (uint8_t)(start >> 8);
  resp[idx++] = (uint8_t)(start & 0xFF);
  resp[idx++] = (uint8_t)(qty >> 8);
  resp[idx++] = (uint8_t)(qty & 0xFF);
  uint16_t crc = computeCRC(resp, idx);
  resp[idx++] = crc & 0xFF;
  resp[idx++] = (crc >> 8) & 0xFF;
  sendResponse(resp, idx);
}

// PDU for Read Coils (0x01):
// Byte0-1 start addr, Byte2-3 qty (bits)
void ModbusSlave::handleReadCoils(uint8_t *pdu, uint16_t pduLen) {
  if (pduLen < 4) { sendException(0x01, MB_EX_ILLEGAL_VALUE); return; }
  uint16_t start = (pdu[0] << 8) | pdu[1];
  uint16_t qty = (pdu[2] << 8) | pdu[3];
  if (qty == 0 || qty > 2000) { sendException(0x01, MB_EX_ILLEGAL_VALUE); return; }
  if (start + qty > _maxCoils) { sendException(0x01, MB_EX_ILLEGAL_ADDRESS); return; }

  uint16_t byteCount = (qty + 7) / 8;
  uint8_t resp[5 + 256];
  uint16_t idx = 0;
  resp[idx++] = _slaveId;
  resp[idx++] = 0x01;
  resp[idx++] = byteCount;
  // pack bits LSB first into bytes
  for (uint16_t b = 0; b < qty; b++) {
    bool bit = coilGetBit(start + b);
    uint16_t outByteIndex = idx + (b / 8);
    uint8_t bitPos = b % 8;
    // ensure bytes exist (initialize)
    if ((idx + (b / 8)) >= idx + byteCount) continue;
    // We'll fill after ensuring space: initialize bytes to 0
    if (b % 8 == 0) resp[idx + (b / 8)] = 0;
    if (bit) resp[idx + (b / 8)] |= (1 << bitPos);
  }
  idx += byteCount;
  uint16_t crc = computeCRC(resp, idx);
  resp[idx++] = crc & 0xFF;
  resp[idx++] = (crc >> 8) & 0xFF;
  sendResponse(resp, idx);
}

/* -------------------------
   Helpers
   ------------------------- */

void ModbusSlave::sendException(uint8_t functionCode, uint8_t exceptionCode) {
  uint8_t resp[5];
  uint16_t idx = 0;
  resp[idx++] = _slaveId;
  resp[idx++] = functionCode | 0x80;
  resp[idx++] = exceptionCode;
  uint16_t crc = computeCRC(resp, idx);
  resp[idx++] = crc & 0xFF;
  resp[idx++] = (crc >> 8) & 0xFF;
  sendResponse(resp, idx);
}

void ModbusSlave::txEnable() {
  digitalWrite(_dePin, HIGH);
  // small delay to allow transceiver to switch
  delayMicroseconds(10);
}

void ModbusSlave::txDisable() {
  // wait until Serial finished
  Serial.flush();
  digitalWrite(_dePin, LOW);
  delayMicroseconds(10);
}

void ModbusSlave::sendResponse(const uint8_t *buf, uint16_t len) {
  txEnable();
  for (uint16_t i = 0; i < len; i++) Serial.write(buf[i]);
  Serial.flush();
  txDisable();
}

inline bool ModbusSlave::coilGetBit(uint16_t idx) {
  if (idx >= _maxCoils) return false;
  uint16_t byteIdx = idx / 8;
  uint8_t bit = idx % 8;
  return (_coils[byteIdx] >> bit) & 1;
}

inline void ModbusSlave::coilSetBit(uint16_t idx, bool v) {
  if (idx >= _maxCoils) return;
  uint16_t byteIdx = idx / 8;
  uint8_t bit = idx % 8;
  if (v) _coils[byteIdx] |= (1 << bit);
  else _coils[byteIdx] &= ~(1 << bit);
}

bool ModbusSlave::setRegister(uint16_t index, uint16_t value) {
  if (index >= _maxRegisters) return false;
  _registers[index] = value;
  return true;
}

bool ModbusSlave::getRegister(uint16_t index, uint16_t &value) {
  if (index >= _maxRegisters) return false;
  value = _registers[index];
  return true;
}

bool ModbusSlave::setCoil(uint16_t index, bool value) {
  if (index >= _maxCoils) return false;
  coilSetBit(index, value);
  return true;
}

bool ModbusSlave::getCoil(uint16_t index, bool &value) {
  if (index >= _maxCoils) return false;
  value = coilGetBit(index);
  return true;
}
