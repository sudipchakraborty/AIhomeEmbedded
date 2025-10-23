#include "FM24C32.h"

FM24C32::FM24C32(uint8_t devAddr)
    : _wire(&Wire), _devAddr(devAddr), _debug(false) {}

/**
 * @brief Initialize Wire instance (default Wire).
 */
bool FM24C32::begin(TwoWire &wire) {
    _wire = &wire;
    _wire->begin();
    // no way to probe reliably without a write/read cycle; assume ok
    if (_debug) {
        char buf[48];
        snprintf(buf, sizeof(buf), "FM24C32: initialized at 0x%02X", _devAddr);
        Serial.println(buf);
    }
    return true;
}

/**
 * @brief Write a String to FRAM. Returns last memory address written or 0xFFFF on error.
 */
uint16_t FM24C32::writeString(uint16_t memAddr, const String &data) {
    if (data.length() == 0) return 0xFFFF;
    const uint8_t *buf = (const uint8_t *)data.c_str();
    uint16_t len = (uint16_t)data.length();

    bool ok = writeBytes(memAddr, buf, len);
    if (!ok) return 0xFFFF;
    return (uint16_t)(memAddr + len - 1);
}

/**
 * @brief Read len bytes and return as String.
 */
String FM24C32::readString(uint16_t memAddr, uint16_t len) {
    if (len == 0) return String();

    uint8_t *buf = (uint8_t *)malloc(len);
    if (!buf) {
        if (_debug) Serial.println("FM24C32: malloc failed in readString");
        return String();
    }

    bool ok = readBytes(memAddr, buf, len);
    String s;
    if (ok) {
        // Build string preserving any bytes (including zeroes) by appending chars explicitly
        s = String(); s.reserve(len);
        for (uint16_t i = 0; i < len; ++i) s += (char)buf[i];
    } else {
        if (_debug) Serial.println("FM24C32: readBytes failed");
    }

    free(buf);
    return s;
}

/**
 * @brief Write raw bytes with chunking.
 */
bool FM24C32::writeBytes(uint16_t memAddr, const uint8_t *buf, uint16_t len) {
    if (len == 0) return true;
    uint16_t remaining = len;
    uint16_t offset = 0;
    while (remaining > 0) {
        uint8_t chunkLen = (remaining > MAX_I2C_WRITE_DATA) ? MAX_I2C_WRITE_DATA : (uint8_t)remaining;
        if (_debug) {
            char tmp[64];
            snprintf(tmp, sizeof(tmp), "FM24C32: writeChunk addr=0x%04X len=%u", (unsigned int)(memAddr + offset), chunkLen);
            Serial.println(tmp);
        }
        bool ok = writeChunk((uint16_t)(memAddr + offset), buf + offset, chunkLen);
        if (!ok) return false;
        remaining -= chunkLen;
        offset += chunkLen;
        // FRAM: no long write cycle required, but small pause is polite
        delayMicroseconds(50);
    }
    return true;
}

/**
 * @brief Read raw bytes with chunked requests.
 */
bool FM24C32::readBytes(uint16_t memAddr, uint8_t *buf, uint16_t len) {
    if (len == 0) return true;
    uint16_t remaining = len;
    uint16_t offset = 0;

    while (remaining > 0) {
        // Request up to MAX_WIRE_BUFFER bytes per call
        uint8_t chunk = (remaining > MAX_WIRE_BUFFER) ? MAX_WIRE_BUFFER : (uint8_t)remaining;

        if (!_wire) return false;

        // Set memory pointer (2 address bytes) with repeated start
        _wire->beginTransmission(_devAddr);
        _wire->write((uint8_t)(((memAddr + offset) >> 8) & 0xFF));
        _wire->write((uint8_t)(((memAddr + offset)     ) & 0xFF));
        if (_wire->endTransmission(false) != 0) { // send restart (false)
            if (_debug) Serial.println("FM24C32: endTransmission failed in readBytes (set pointer)");
            return false;
        }

        // request chunk bytes
        uint8_t got = (uint8_t)_wire->requestFrom((int)_devAddr, (int)chunk);
        if (got != chunk) {
            if (_debug) {
                char tmp[64];
                snprintf(tmp, sizeof(tmp), "FM24C32: requestFrom got=%u expected=%u", got, chunk);
                Serial.println(tmp);
            }
            return false;
        }
        for (uint8_t i = 0; i < got; ++i) {
            if (_wire->available()) {
                buf[offset + i] = _wire->read();
            } else {
                if (_debug) Serial.println("FM24C32: unexpected no data");
                return false;
            }
        }
        remaining -= got;
        offset += got;
    }
    return true;
}

/**
 * @brief Internal helper: write a single chunk (addr + data) - returns false on I2C error.
 */
bool FM24C32::writeChunk(uint16_t memAddr, const uint8_t *data, uint8_t chunkLen) {
    if (!_wire) return false;
    _wire->beginTransmission(_devAddr);
    _wire->write((uint8_t)((memAddr >> 8) & 0xFF)); // high address
    _wire->write((uint8_t)(memAddr & 0xFF));        // low address
    // write chunkLen bytes (<= MAX_I2C_WRITE_DATA)
    for (uint8_t i = 0; i < chunkLen; ++i) _wire->write(data[i]);
    uint8_t res = _wire->endTransmission(); // res=0 -> success
    if (res != 0) {
        if (_debug) {
            char tmp[48];
            snprintf(tmp, sizeof(tmp), "FM24C32: writeChunk endTransmission error %u", res);
            Serial.println(tmp);
        }
        return false;
    }
    return true;
}

/**
 * @brief Optional: set memory pointer only (not used externally currently)
 */
bool FM24C32::setMemoryPointer(uint16_t memAddr) {
    if (!_wire) return false;
    _wire->beginTransmission(_devAddr);
    _wire->write((uint8_t)((memAddr >> 8) & 0xFF));
    _wire->write((uint8_t)(memAddr & 0xFF));
    uint8_t res = _wire->endTransmission(false); // repeated start
    return (res == 0);
}
