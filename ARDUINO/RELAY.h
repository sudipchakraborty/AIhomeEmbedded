#ifndef RELAY_H
#define RELAY_H

#include "Arduino.h"
//////////////////////

#define   Relay_1     53
#define   Relay_2     51
#define   Relay_3     49
#define   Relay_4     47
#define   Relay_5     45
#define   Relay_6     43
#define   Relay_7     41
#define   Relay_8     39

class Relay
{
    public:
           Relay();
      void init(void);
      void update(String str);
    private:       
};
///////////////////////











#endif
