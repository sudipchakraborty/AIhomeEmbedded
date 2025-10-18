#ifndef BUTTON_H
#define BUTTON_H
//////////////////////
class button
{
    private:
    char pin;

    public:
      button(char pin);
      void begin(void);
      bool pressed(void);
      bool triggered(void);
 
};
///////////////////////











#endif
