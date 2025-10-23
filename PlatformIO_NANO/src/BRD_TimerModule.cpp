#include "BRD_TimerModule.h"
#include "Rtc1307.h"
#include <Arduino.h>
#include <Wire.h>
#include "FM24C32.h"


Rtc1307 rtc;


FM24C32 fram(0x50); // typical 7-bit address for FM24C32

// helper: print raw buffer as hex
void printHex(const uint8_t *buf, size_t len) {
  for (size_t i = 0; i < len; ++i) {
    if (buf[i] < 16) Serial.print('0');
    Serial.print(buf[i], HEX);
    if (i < len - 1) Serial.print(' ');
  }
  Serial.println();
}





BRD_TimerModule::BRD_TimerModule(){

}
//_____________________________________________________________________________________________________   
void BRD_TimerModule::begin() {
        rtc.begin();
        Serial.begin(9600);
        ////////////////////
     
  while (!Serial) { delay(1); } // wait for Serial on some boards

  Serial.println();
  Serial.println("=== FM24C32 Test ===");

  fram.setDebug(true);
  if (!fram.begin()) {
    Serial.println("FRAM begin returned false (but continuing).");
  } else {
    Serial.print("FM24C32 begin OK at address 0x");
    Serial.println(fram.deviceAddress(), HEX);
  }

  // ---------- Test 1: write/read a text string ----------
  const uint16_t textAddr = 0x0100;
  String msg = "Hello FRAM!";            // 11 bytes (without terminating '\0' in stored bytes)
  Serial.print("Writing text \"");
  Serial.print(msg);
  Serial.print("\" to address 0x");
  Serial.println(textAddr, HEX);

  uint16_t lastAddr = fram.writeString(textAddr, msg);
  if (lastAddr == 0xFFFF) {
    Serial.println("writeString() failed!");
  } else {
    Serial.print("writeString() succeeded. last address = 0x");
    Serial.println(lastAddr, HEX);
  }

  // read back as String (exact length)
  String readBack = fram.readString(textAddr, msg.length());
  Serial.print("Read back (String): \"");
  Serial.print(readBack);
  Serial.println("\"");

  // read raw bytes into buffer and hex dump
  uint8_t rawBuf[32];
  memset(rawBuf, 0xFF, sizeof(rawBuf));
  if (fram.readBytes(textAddr, rawBuf, msg.length())) {
    Serial.print("Hex dump: ");
    printHex(rawBuf, msg.length());
  } else {
    Serial.println("readBytes() failed for text region.");
  }

  // ---------- Test 2: write/read binary data including zero bytes ----------
  const uint16_t binAddr = 0x0200;
  uint8_t binData[] = { 0xDE, 0xAD, 0x00, 0xBE, 0xEF, 0x01, 0x02 };
  const uint16_t binLen = sizeof(binData);

  Serial.print("Writing binary data to 0x");
  Serial.println(binAddr, HEX);
  Serial.print("Binary: ");
  printHex(binData, binLen);

  bool ok = fram.writeBytes(binAddr, binData, binLen);
  Serial.print("writeBytes() returned: ");
  Serial.println(ok ? "OK" : "FAIL");

  // read it back
  uint8_t binRead[16];
  memset(binRead, 0, sizeof(binRead));
  if (fram.readBytes(binAddr, binRead, binLen)) {
    Serial.print("Binary read back: ");
    printHex(binRead, binLen);
  } else {
    Serial.println("readBytes() failed for binary region.");
  }

  Serial.println("=== FM24C32 Test Completed ===");
 

}
//_____________________________________________________________________________________________________   
void BRD_TimerModule::update() {
     
}
//_____________________________________________________________________________________________________   
void BRD_TimerModule::FSM_Handler() {
     String s=rtc.readDateTimeString();
     Serial.println(s);
     delay(100);
}
//_____________________________________________________________________________________________________   


