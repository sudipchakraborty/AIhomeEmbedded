#ifndef RTC1307_H
#define RTC1307_H
//////////////////////
class Rtc1307
{
    public:
           Rtc1307();
      void init(void);
      void set(long val);
      bool over(void);
      long count_Reg;
      long compare_val;  
    private:
        
};
///////////////////////











#endif
