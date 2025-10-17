#ifndef KEY44_H
#define KEY44_H
//////////////////////
#include <Arduino.h>

class Key44
{
    public:
           Key44();
      void init(void);
      char get(void);
      bool pressed(void);
      char code=0;
     
    private:
        
};
///////////////////////
#define   R1          23
#define   R2          25
#define   R3          27
#define   R4          29

#define   C1          31
#define   C2          33
#define   C3          35
#define   C4          37







#endif
