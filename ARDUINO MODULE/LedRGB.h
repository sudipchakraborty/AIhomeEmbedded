#ifndef LEDRGB_H
#define LEDRGB_H
//////////////////////
class LedRGB
{
    public:
           LedRGB();
      void init(void);
      void set(long val);
      bool over(void);
      long count_Reg;
      long compare_val;  
    private:
        
};
///////////////////////











#endif
