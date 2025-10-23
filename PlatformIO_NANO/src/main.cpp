// #include <Arduino.h>
// #include "BRD_TimerModule.h"
// BRD_TimerModule tm;





// // /////////////
// // // #define brd_IrCut
// // #define BRD_TimerModule
// // /////////////

// // #ifdef brd_IrCut 
// //   #include  "IRcut.h"
// //   ircut ir;
// // #endif

// // #ifdef BRD_TimerModule
// //   #include "BRD_TimerModule.h"
// //   BRD_TimerModule tm;

// // #endif
        
// //_____________________________________________________________________________________________________________________________________________________________________________________________________--
// void setup() 
// {
//   // #ifdef brd_IrCut 
//   // ir.begin();
//   // #endif

  
// }
// //_____________________________________________________________________________________________________________________________________________________________________________________________________--
// void loop() 
// {
//   // #ifdef brd_IrCut 
//   // ir.FSM_Handler();
//   // #endif
// }
// //_____________________________________________________________________________________________________________________________________________________________________________________________________--












// ///////////////////////////////////////
#include <Arduino.h>
#include "BRD_TimerModule.h"
BRD_TimerModule tm;      
//________________________________
void setup() 
{
  tm.begin();
}
//_______________________________
void loop() 
{
   tm.FSM_Handler();
}
// //____________________________



// ////////////////////////////////////////////
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






// //////////////////////////////////////


// // #include <Arduino.h>
// // #include "ModbusSlave.h"

// // // Wiring (example):
// // // Arduino TX/RX -> MAX485 DI/RO
// // // MAX485 DE & RE tied together to pin 2
// // // Remember to connect A/B lines to RS485 bus

// // const uint8_t DE_PIN = 2;
// // const uint8_t SLAVE_ID = 1;

// // ModbusSlave mb(SLAVE_ID, DE_PIN, 128, 256);

// // void setup() {
// //   Serial.begin(19200); // common Modbus baud
// //   mb.beginSerial(19200);
// //   mb.setFrameTimeout(50); // 50 ms frame timeout

// //   // initialize some registers for demo
// //   mb.setRegister(0, 0x1234);
// //   mb.setRegister(1, 0xABCD);

// //   // set coil 0 = ON
// //   mb.setCoil(0, true);

// //   Serial.println("Modbus slave demo started.");
// // }

// // unsigned long lastBlink = 0;
// // void loop() {
// //   mb.process();

// //   // Demo: toggle register 10 every 2s
// //   if (millis() - lastBlink > 2000) {
// //     lastBlink = millis();
// //     uint16_t v;
// //     if (mb.getRegister(10, v)) {
// //       v++;
// //       mb.setRegister(10, v);
// //       Serial.print("Reg10 now: "); Serial.println(v);
// //     }
// //   }
// // }
