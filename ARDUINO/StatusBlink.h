#ifndef STATUSBLINK_H
#define STATUSBLINK_H
//////////////////////
class StatusBlink
{
    public:
           StatusBlink();
      void init(char pin,unsigned int speed);
      void blink();
      void on(void);
      void off(void);
    private:
      unsigned int  delay_reg;
      unsigned int  speed_val;
      char pin_no;
      char state;
};
///////////////////////











#endif