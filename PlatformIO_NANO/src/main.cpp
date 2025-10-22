#include <Arduino.h>
#include  "IRcut.h"

ircut ir;
        
//_____________________________________________________________________________________________________________________________________________________________________________________________________--
void setup() 
{
  ir.begin();
}
//_____________________________________________________________________________________________________________________________________________________________________________________________________--
void loop() 
{
  ir.FSM_Handler();
}
//_____________________________________________________________________________________________________________________________________________________________________________________________________--




// #include <Arduino.h>
// #include "ModbusSlave.h"

// // Wiring (example):
// // Arduino TX/RX -> MAX485 DI/RO
// // MAX485 DE & RE tied together to pin 2
// // Remember to connect A/B lines to RS485 bus

// const uint8_t DE_PIN = 2;
// const uint8_t SLAVE_ID = 1;

// ModbusSlave mb(SLAVE_ID, DE_PIN, 128, 256);

// void setup() {
//   Serial.begin(19200); // common Modbus baud
//   mb.beginSerial(19200);
//   mb.setFrameTimeout(50); // 50 ms frame timeout

//   // initialize some registers for demo
//   mb.setRegister(0, 0x1234);
//   mb.setRegister(1, 0xABCD);

//   // set coil 0 = ON
//   mb.setCoil(0, true);

//   Serial.println("Modbus slave demo started.");
// }

// unsigned long lastBlink = 0;
// void loop() {
//   mb.process();

//   // Demo: toggle register 10 every 2s
//   if (millis() - lastBlink > 2000) {
//     lastBlink = millis();
//     uint16_t v;
//     if (mb.getRegister(10, v)) {
//       v++;
//       mb.setRegister(10, v);
//       Serial.print("Reg10 now: "); Serial.println(v);
//     }
//   }
// }
