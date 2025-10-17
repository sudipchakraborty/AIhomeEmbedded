#ifndef BUTTON_H
#define BUTTON_H
//////////////////////
class button
{
    public:
           button();
      void init(char pin);
      bool pressed();
    private:
    char sw_pin;
};
///////////////////////











#endif
