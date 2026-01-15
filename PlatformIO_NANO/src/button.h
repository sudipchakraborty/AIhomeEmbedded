#ifndef BUTTON_H
#define BUTTON_H
//////////////////////
class button
{
    private:
    char pin;

    public:
      bool logic;
      button(char pin);
      button(char sw_pin, bool state_logic);
      void begin(void);
      bool pressed(void);
      bool triggered(void);
 
};
///////////////////////











#endif
