
#ifndef DS1307_H_
#define DS1307_H_


#include "avr/io.h"
#include "\ArduinoEasy\SOFTWARE\COMMON\global.h"
#include "\ArduinoEasy\SOFTWARE\COMMON\board.h"

using namespace Tools;

namespace hardware
{
	
class DS1307:public BOARD,public helper
{
		
	public:
		DS1307();
		void setup(void);
		void Get_Date_Time_ASCII(unsigned char *bfr);
		unsigned char* Get_Date_Time_As_DDMMYY_hhmmss(void);
		
	private:
	bool Read_Date_Time_BCD(unsigned char * bfr);
	
	
	
	bool initialized=false;
	protected:
	
	
	
	
	
	
	};
	//////////////////////////////////////////////////////////////////////////////////////////
	DS1307::DS1307()
	{
		
	}
	//_________________________________________________________________________________________
	void DS1307::setup(void)
	{
		DO(D20);
		DO(D21);
		TWCR=0b00000100;
		I2C_Write(7,0b10010000);
	}
	//_________________________________________________________________________________________
		void DS1307::Get_Date_Time_ASCII(unsigned char *bfr)
		{
			register unsigned char i;
			unsigned char bfr_rtc[7];
			
			Read_Date_Time_BCD(&bfr_rtc[0]);
			
			ConvertBCD2Ascii(bfr_rtc[4], bfr); bfr +=2;
			*bfr='-'; bfr++;
			
			ConvertBCD2Ascii(bfr_rtc[5], bfr); bfr +=2;
			*bfr='-'; bfr++;
			
			ConvertBCD2Ascii(bfr_rtc[6], bfr); bfr +=2;
			*bfr=','; bfr++;
			
			ConvertBCD2Ascii(bfr_rtc[2], bfr); bfr +=2;
			*bfr=':'; bfr++;

			ConvertBCD2Ascii(bfr_rtc[1], bfr); bfr +=2;
			*bfr=':'; bfr++;
			
			ConvertBCD2Ascii(bfr_rtc[0], bfr); bfr +=2;
			*bfr=0;
		}
		//___________________________________________________________________________________________	
	unsigned char* DS1307::Get_Date_Time_As_DDMMYY_hhmmss(void)
	{
		register unsigned char i;
		unsigned char bfr_rtc[7];
		unsigned char bfr_return[18];
				
		Read_Date_Time_BCD(&bfr_rtc[0]);
				
		ConvertBCD2Ascii(bfr_rtc[4], &bfr_return[0]);	bfr_return[2]='-';  
		ConvertBCD2Ascii(bfr_rtc[5], &bfr_return[3]);	bfr_return[5]='-';  
		ConvertBCD2Ascii(bfr_rtc[6], &bfr_return[6]);	bfr_return[8]=',';  
		ConvertBCD2Ascii(bfr_rtc[2], &bfr_return[9]);	bfr_return[11]=':';  
		ConvertBCD2Ascii(bfr_rtc[1], &bfr_return[12]);	bfr_return[14]=':'; 	
		ConvertBCD2Ascii(bfr_rtc[0], &bfr_return[15]);	bfr_return[17]=0;
		return bfr_return;
	}
	//__________________________________________________________________________________________
	bool DS1307::Read_Date_Time_BCD(unsigned char * bfr)
	{
		I2C_read(0,bfr+0);
		I2C_read(1,bfr+1);
		I2C_read(2,bfr+2);
		I2C_read(3,bfr+3);
		I2C_read(4,bfr+4);
		I2C_read(5,bfr+5);
		I2C_read(6,bfr+6);
		
		return true;
	}
	//_________________________________________________________________________________________
	
	
}// namespace
 
#endif /* DS1307_H_ */







//
//
//
 //
////____________________________________________________________________________________________
//DS1307::DS1307()
//{
	//
//}
////____________________________________________________________________________________________
//void DS1307::setup(void)
//{
	//brd1307.DO(20);
	//brd1307.DO(21);
	//TWCR=0b00000100;
	//brd1307.I2C_Write(7,0b10010000);
//}
////____________________________________________________________________________________________
//unsigned char DS1307::Save_Date_Time_OK(uint8_t *bfr)
//{
	//uint8_t i=*bfr;
	//brd1307.I2C_Write(0,i);
	//
	//i=*(bfr+1);
	//brd1307.I2C_Write(1,i);
	//
	//i=*(bfr+2);
	//brd1307.I2C_Write(2,i);
	///////////////////
	//i=*(bfr+4);
	//brd1307.I2C_Write(4,i);
	//
	//i=*(bfr+5);
	//brd1307.I2C_Write(5,i);
	//
	//i=*(bfr+6);
	//brd1307.I2C_Write(6,i);
//}
////____________________________________________________________________________________________
//unsigned char DS1307::Date_Available(unsigned char *bfr)
//{
	//brd1307.I2C_read(4,bfr+0);
	//brd1307.I2C_read(5,bfr+1);
	//brd1307.I2C_read(6,bfr+2);
	//
	//return true;
//}
////____________________________________________________________________________________________
//unsigned char DS1307::Time_Available(unsigned char *bfr)
//{
	//brd1307.I2C_read(0,bfr+0);
	//brd1307.I2C_read(1,bfr+1);
	//brd1307.I2C_read(2,bfr+2);
//
	//return true;
//}
////____________________________________________________________________________________________
//unsigned char DS1307::Save_Time_OK(uint8_t *bfr)
//{
	//
	//
	//return true;
//}
////____________________________________________________________________________________________

////____________________________________________________________________________________________
//
//
//
//
//
//
//#endif /* DS1307_H_ */
