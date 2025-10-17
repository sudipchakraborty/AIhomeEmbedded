// #include <avr/io.h>
// #include <avr/pgmspace.h>
// #include <util/delay.h>
// #include <avr/wdt.h>
// #include <avr/interrupt.h>

// namespace Tools
// {
// 	class adc:public BOARD,public helper
// 	{
// 		public:
		
// 		unsigned char adc_pin=A0;
// 		unsigned int min_count=0;
// 		unsigned int max_count=1024;
// 		unsigned int min_disp=0;
// 		unsigned int max_disp=500;
// 		unsigned char digit_count=3;
// 		unsigned char decimal_pos=1;

// 		const char* header_text;
// 		const char *unit;
		
// 		float multi_factor=0;
	 
						
// 		adc();
// 		adc(unsigned char adc_pin);	
// 		adc(unsigned char adc_pin, unsigned int max_disp);
// 		adc(unsigned char adc_pin, unsigned int max_disp, unsigned char digit_count,unsigned char decimal_pos);
// 		adc(unsigned char adc_pin, unsigned int max_disp, unsigned char digit_count,unsigned char decimal_pos,  const char *unit);
// 		adc(unsigned char adc_pin, unsigned int min_count, unsigned int max_count, unsigned int min_disp, unsigned int max_disp, unsigned char digit_count,unsigned char decimal_pos, const char* header_text, const char *unit);
		
			
// 		unsigned int Get_Raw_Value(void);
// 		unsigned int Get_Value(void);
// 		void Get_Value(const char * pre_txt, unsigned char *bfr, unsigned char digit_count, unsigned char decimal_pos, unsigned char unit);
		
// 		void Get_Value(unsigned char *bfr);
// 		bool high(void);
// 		bool low(void);
// 		bool Not_between(void);
		
		
// 		private:
		
		
		
// 		protected:	
// 	};
// 	//__________________________________________________________________________________________________________________
// 	adc::adc()
// 	{
// 		ADC_setup(adc_pin);	
// 		multi_factor=(float)(max_disp/max_count);
		
// 		const char default_hdr[] PROGMEM="TEMPERATURE=";
// 		header_text=default_hdr;
		
// 		static const char default_unit[] PROGMEM="C";
// 		unit=default_unit;		
// 	}
// 	//__________________________________________________________________________________________________________________
// 	adc::adc(unsigned char adc_pin)
// 	{
// 		this->adc_pin=adc_pin;
// 		ADC_setup(adc_pin);
// 		multi_factor=(float)(max_disp/max_count);
// 	}
// 	//__________________________________________________________________________________________________________________
// 	adc::adc(unsigned char adc_pin, unsigned int max_disp)
// 	{
// 		this->adc_pin=adc_pin;
// 		this->max_disp=max_disp;		
// 		ADC_setup(adc_pin);
// 		multi_factor=(float)(max_disp/max_count);
// 	}
// 	//__________________________________________________________________________________________________________________
// 	adc::adc(unsigned char adc_pin, unsigned int max_disp, unsigned char digit_count,unsigned char decimal_pos)
// 	{
		
		
// 	}
// 	//__________________________________________________________________________________________________________________
// 	adc::adc(unsigned char adc_pin, unsigned int max_disp, unsigned char digit_count,unsigned char decimal_pos,  const char *unit)
// 	{
		
		
// 	}
// 	//__________________________________________________________________________________________________________________
// 	adc::adc(unsigned char adc_pin, unsigned int min_count, unsigned int max_count, unsigned int min_disp, unsigned int max_disp, unsigned char digit_count,unsigned char decimal_pos, const char* header_text, const char *unit)
// 	{
// 		this->adc_pin=adc_pin;
		
// 		this->min_count=min_count;
// 		this->max_count=max_count;
		
// 		this->min_disp=0;
// 		this->max_disp=500;
		
// 		this->digit_count=3;
// 		this->decimal_pos=1;

// 		this->header_text=header_text;
// 		this->unit=unit;
				
// 	}
// 	//__________________________________________________________________________________________________________________
	
	
	
	
	
	
// 	//__________________________________________________________________________________________________________________
// 	unsigned int adc::Get_Raw_Value(void)
// 	{
// 		unsigned int result;
// 		result=ADC_Get(this->adc_pin);
// 		return result;	
// 	}
// 	//__________________________________________________________________________________________________________________
// 	unsigned int adc::Get_Value(void)
// 	{
// 		int result= Get_Raw_Value();
// 		return result *= multi_factor;
// 	}
// 	//__________________________________________________________________________________________________________________
// 	void adc::Get_Value(const char * pre_txt, unsigned char *bfr, unsigned char digit_count, unsigned char decimal_pos, unsigned char unit)
// 	{		
// 		int val=Get_Value();
// 		pgm2ram(pre_txt,bfr);
// 		int len=Get_length(pre_txt);	
// 		ConvertInt2Ascii(val, bfr+len,digit_count,decimal_pos);	
// 		*(bfr+len+digit_count)=unit;
// 		*(bfr+len+digit_count+1)=0;
// 	}
// 	//__________________________________________________________________________________________________________________
	
	
	
	
	
// 	//const char * Hello()
// 	//{
// 		//static const char text[] = "Hello";
// 		//return text;
// 	//}
	
	
// }// namespace
// //__________________________________________________________________________________________________________________

// //void MEGA2560::ADC_setup(unsigned char ch)
// //{
// //DI(ch);
// //DI_Disable(ch);
// //// Select Vref=AVcc
// //ADMUX |= (1<<REFS0);
// ////set prescaller to 128 and enable ADC
// //ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
// //}
// ////____________________________________________________________________________________________________________________________________________________________
// //void MEGA2560::DI_Disable(unsigned char pin_name)
// //{
// //switch(pin_name)
// //{
// //case A0:	DIDR0 &= 0b00000001;	break;
// //case A1:	DIDR0 &= 0b00000010;	break;
// //case A2:	DIDR0 &= 0b00000100;	break;
// //case A3:	DIDR0 &= 0b00001000;	break;
// //case A4:	DIDR0 &= 0b00010000;	break;
// //case A5:	DIDR0 &= 0b00100000;	break;
// //default:							break;
// //}
// //}
// ////______________________________________________________________________________________________________________________________________
 