#ifndef FM24C32_H
#define FM24C32_H

#include <Arduino.h>
#include <Wire.h>

/**
 * @file FM24C32.h
 * @brief Simple FRAM (FM24Cxx) helper for Arduino using Wire (I2C).
 *
 * Supports reading and writing byte arrays and Strings to a FM24C32-like device.
 * The class uses 16-bit memory addressing and handles chunked transfers
 * to work within the Wire (32 byte) buffer limit.
 *
 * Example:
 *   FM24C32 fram; // default I2C addr 0x50
 *   fram.begin();
 *   uint16_t last = fram.writeString(0x0100, "Hello FRAM");
 *   String s = fram.readString(0x0100, 11);
 */
class FM24C32 {
public:
    /**
     * @brief Construct a FM24C32 helper.
     * @param devAddr I2C 7-bit device address (default 0x50 typical for FM24C32)
     */
    FM24C32(uint8_t devAddr = 0x50);

    /**
     * @brief Initialize Wire (I2C) if needed.
     * @param wire Reference to TwoWire instance (optional, default Wire).
     * @return true if initialization ok (Wire always available on Arduino).
     */
    bool begin(TwoWire &wire = Wire);

    /**
     * @brief Write a String to FRAM starting at the specified memory address.
     *
     * Writes the bytes of the string (without any terminating null). The write
     * operation is performed in chunks to avoid exceeding the Wire buffer.
     *
     * @param memAddr 16-bit memory address to start writing at (0..(size-1))
     * @param data String data to write
     * @return uint16_t Last memory address written (memAddr + data.length() - 1),
     *         or 0xFFFF on error.
     */
    uint16_t writeString(uint16_t memAddr, const String &data);

    /**
     * @brief Read bytes from FRAM and return as String.
     *
     * Reads 'len' bytes beginning at memAddr. If len==0 returns empty String.
     *
     * @param memAddr start address
     * @param len number of bytes to read
     * @return String read from memory (empty string on error or len==0)
     */
    String readString(uint16_t memAddr, uint16_t len);

    /**
     * @brief Write raw bytes to FRAM.
     *
     * Handles chunking to avoid Wire buffer overflow.
     *
     * @param memAddr start memory address
     * @param buf pointer to data buffer
     * @param len number of bytes to write
     * @return true on success, false on I2C error
     */
    bool writeBytes(uint16_t memAddr, const uint8_t *buf, uint16_t len);

    /**
     * @brief Read raw bytes from FRAM.
     *
     * Handles chunked reads if len > 32.
     *
     * @param memAddr start memory address
     * @param buf pointer to buffer large enough to hold len bytes
     * @param len number of bytes to read
     * @return true on success, false on I2C error
     */
    bool readBytes(uint16_t memAddr, uint8_t *buf, uint16_t len);

    /**
     * @brief Return the configured 7-bit I2C device address.
     */
    uint8_t deviceAddress() const { return _devAddr; }

    /**
     * @brief Set an optional debug flag to enable Serial prints from the library.
     */
    void setDebug(bool enable) { _debug = enable; }

private:
    TwoWire *_wire;
    uint8_t _devAddr;
    bool _debug;

    // Max bytes we attempt to send in one I2C write after two address bytes.
    // Wire buffer is 32 bytes, we send 2 address bytes + data; so max data per transfer = 30.
    static const uint8_t MAX_I2C_WRITE_DATA = 30;
    static const uint8_t MAX_WIRE_BUFFER = 32;

    // internal helper to write a single chunk (address + data)
    bool writeChunk(uint16_t memAddr, const uint8_t *data, uint8_t chunkLen);

    // internal helper to set memory pointer (write address only, no data)
    bool setMemoryPointer(uint16_t memAddr);
};

#endif // FM24C32_H
