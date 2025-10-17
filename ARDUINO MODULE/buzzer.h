#ifndef BUZZER_H
#define BUZZER_H
//////////////////////
class buzzer
{
    public:
           buzzer();
      void init(char pin);
      void beep(void);
      void beep_key();
      void beep(unsigned int val);
      void on(void);
      void off(void);
    private:
    char bzr_pin;
       
};
///////////////////////











#endif
