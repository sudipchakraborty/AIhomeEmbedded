#ifndef EVENTSSEQ_H
#define EVENTSSEQ_H
#include "IRcut.h"

#define BUFFER_SIZE 50

class EventsSEQ{
  public:
    EventsSEQ();
    void begin(void);
    void run(void);
    void buffer_reset(void);
    void push(byte val);
    String get_buffer_as_string(void);
    byte index;
    ////////////////////////
    private:
    byte buffer[BUFFER_SIZE];

};
#endif // EVENTSSEQ_H