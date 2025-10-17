#ifndef LEDFRONT_H
#define LEDFRONT_H
//////////////////////
#define   PIN_LED_R   7
#define   PIN_LED_G   4
#define   PIN_LED_Y   5
#define   PIN_LED_V   6
class LedFront
{
    public:
           LedFront();
      void init(void);
      void test(void);
      void healthy(void);
      void ok(void);
      void abnormal(void);
      void error(void);
    private:      
};
///////////////////////











#endif
