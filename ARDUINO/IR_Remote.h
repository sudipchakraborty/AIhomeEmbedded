#ifndef IR_REMOTE_H
#define IR_REMOTE_H
//////////////////////
#include "Arduino.h"

class IR_Remote
{
    public:
           IR_Remote();
      void init(void);
      char get(void);  
      bool pressed(void);
      char code;
      String strCode;
    private:
        
};
///////////////////////
#define BTN_MUTE      "0xE11E7F80"
#define BTN_PWR       "0xED127F80"
#define BTN_1         "0xF50A7F80"
#define BTN_2         "0xE41B7F80"
#define BTN_3         "0xE01F7F80"
#define BTN_4         "0xF30C7F80"
#define BTN_5         "0xF20D7F80"
#define BTN_6         "0xF10E7F80"
#define BTN_7         "0xFF007F80"
#define BTN_8         "0xF00F7F80"
#define BTN_9         "0xE6197F80"
#define BTN_0         "0xF8077F80"
///////////////
#define BTN_USDSCN    "0xF6097F80"
#define BTN_EQ        "0xFB047F80"
///////////////
#define BTN_VOL_PLUS  "0xF9067F80"
#define BTN_VOL_MINUS "0xFA057F80"
#define BTN_LEFT      "0xFD027F80"
#define BTN_RIGHT     "0xFC037F80"
#define BTN_PAUSE     "0xFE017F80"
#define BTN_RPT       "0xF7087F80"
#define BTN_MODE      "0x4CB0FADD"
///////////////
#define BTN_STAR1     "0xFD027F80"
#define BTN_STAR2     "0xFC037F80"
#define BTN_STAR3     "0xFA057F80"
#define BTN_STAR4     "0xF9067F80"
///////////////////////////////////






#endif
