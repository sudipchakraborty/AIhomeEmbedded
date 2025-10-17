/*
 * DS1302.h
 *
 * Created: 05-03-2019 09:12:01
 *  Author: Administrator
 */ 


#ifndef DS1302_H_
#define DS1302_H_

namespace hardware
{

class DS1302:public BOARD,public helper
{
	 #define DS1302_SECONDS           0x80
	 #define DS1302_MINUTES           0x82
	 #define DS1302_HOURS             0x84
	 #define DS1302_DATE              0x86
	 #define DS1302_MONTH             0x88
	 #define DS1302_DAY               0x8A
	 #define DS1302_YEAR              0x8C
	 #define DS1302_ENABLE            0x8E
	 #define DS1302_TRICKLE           0x90
	 #define DS1302_CLOCK_BURST       0xBE
	 #define DS1302_CLOCK_BURST_WRITE 0xBE
	 #define DS1302_CLOCK_BURST_READ  0xBF
	 #define DS1302_RAMSTART          0xC0
	 #define DS1302_RAMEND            0xFC
	 #define DS1302_RAM_BURST         0xFE
	 #define DS1302_RAM_BURST_WRITE   0xFE
	 #define DS1302_RAM_BURST_READ    0xFF
	 	
	
	public:
	DS1302();
	unsigned char RTC_CLK=D23,RTC_CE=D22,RTC_IO=D24;
		
	private:
		void setup(unsigned char RTC_CE,unsigned RTC_CLK, unsigned char RTC_IO);
		void Send_byte(unsigned char data);
		unsigned char Read_byte(void);
		unsigned char Read(unsigned char addr);
		void Write(unsigned char cmd, unsigned char data);
		void Test_Date_Time_Write(void);
		unsigned char Date_Matched_With_Running_Date(unsigned char *bfr);
		unsigned char Time_Matched_With_Running_Time(unsigned char *bfr);
		void Put_Formatted_Date_Time(unsigned char *bfr);
		void Get_Time_as_hhmm(unsigned char *bfr);
		void Get_Date_Time_as_ssmmhhddDDMMyy(unsigned char *bfr);
		void Get_Formatted_Date_Time(unsigned char *bfr);
	protected:
};
//________________________________________________________________________________________________________________________________
DS1302::DS1302()
{
	DO(RTC_CE);
	DO(RTC_CLK);
	DO(RTC_IO);
	
	PIN_Low(RTC_IO);
	PIN_Low(RTC_CE);
	PIN_Low(RTC_CLK);	
}
//___________________________________________________________________________________________________________________________



//_____________________________________________________________________________________________________________________________
void DS1302::Write(unsigned char cmd, unsigned char data)
{
	PIN_High(RTC_CE);
	Send_byte(cmd);
	Send_byte(data);
	PIN_Low(RTC_CE);
}
////______________________________________________________________________________
unsigned char DS1302::Read(unsigned char addr)
{
	register unsigned char i;
	DO(RTC_IO);
	PIN_High(RTC_CE);
	Send_byte(addr);
	i=Read_byte();
	PIN_Low(RTC_CE);
	return i;
}







void  DS1302::Send_byte(unsigned char data)
{
register unsigned char i;
 PIN_High(RTC_IO);
//_NOP();
//_NOP();
//
for(i=0;i<8;i++)
{
	if((data & 0b00000001)==0x00) ? PIN_Low(RTC_IO):PIN_High(RTC_IO);
}

 PIN_High(RTC_CLK);
//_NOP();
//_NOP();
PIN_Low(RTC_CLK);
//_NOP();
//_NOP();
data=data>>1;
}
}
//______________________________________________________________________________
void  DS1302::DS1302::Read_byte(void)
{
register unsigned char i,data;
DI(RTC_IO);
//_NOP();
//_NOP();
//	brd_rtc.sleep(1);

data=0;

if(PIN_Status(RTC_IO))
{
data |=0b10000000;
}

for(i=0;i<7;i++)
{
data=data>>1;
	PIN_High(RTC_CLK);
//_NOP();
//_NOP();
//	brd_rtc.sleep(1);
	PIN_Low(RTC_CLK);
//_NOP();
//_NOP();
//	brd_rtc.sleep(1);

if(PIN_Status(RTC_IO))
{
data |=0b10000000;
}
//_NOP();
//_NOP();
//	brd_rtc.sleep(1);
}

return data;
}
//______________________________________________________________________________
void DS1302::Test_Date_Time_Write(void)
{
	Write(DS1302_DATE,0x12);
	Write(DS1302_MONTH,0x12);
	Write(DS1302_YEAR,0x18);
	Write(DS1302_HOURS,0x09);
	Write(DS1302_MINUTES,0x04);
	Write(DS1302_SECONDS,0x00);
	Write(DS1302_DAY,0);
}
//______________________________________________________________________________
void DS1302::Get_Formatted_Date_Time(unsigned char *bfr) // 12-07-17,11:22:33
{
	register unsigned char i;
	
	i=Read(DS1302_DATE+1);
	ConvertBCD2Ascii(i, bfr); bfr +=2;
	*bfr='-'; bfr++;
	
	i=Read(DS1302_MONTH+1);
	ConvertBCD2Ascii(i, bfr); bfr +=2;
	*bfr='-'; bfr++;
	
	i=Read(DS1302_YEAR+1);
	ConvertBCD2Ascii(i, bfr); bfr +=2;
	*bfr=','; bfr++;
	
	i=Read(DS1302_HOURS+1);
	ConvertBCD2Ascii(i, bfr); bfr +=2;
	*bfr=':'; bfr++;
	
	i=Read(DS1302_MINUTES+1);
	ConvertBCD2Ascii(i, bfr); bfr +=2;
	*bfr=':'; bfr++;
	
	i=Read(DS1302_SECONDS+1);
	ConvertBCD2Ascii(i, bfr); bfr +=2;
	*bfr=0;
}
//______________________________________________________________________________
void DS1302::Get_Date_Time_as_ssmmhhddDDMMyy(unsigned char *bfr)
{
	*bfr=Read(DS1302_SECONDS+1); bfr++;
	*bfr=Read(DS1302_MINUTES+1); bfr++;
	*bfr=Read(DS1302_HOURS+1);   bfr++;
	*bfr=Read(DS1302_DAY+1);     bfr++;
	*bfr=Read(DS1302_DATE+1);    bfr++;
	*bfr=Read(DS1302_MONTH+1);   bfr++;
	*bfr=Read(DS1302_YEAR+1);
}
//______________________________________________________________________________
void DS1302::Get_Time_as_hhmm(unsigned char *bfr) // 12-07-17,11:22:33
{
	register unsigned char i;
	
	i=Read(DS1302_HOURS+1);
	ConvertBCD2Ascii(i, bfr);
	bfr +=2;
	
	
	i=Read(DS1302_MINUTES+1);
	ConvertBCD2Ascii(i, bfr);
}
//______________________________________________________________________________
void DS1302::Put_Formatted_Date_Time(unsigned char *bfr)
{
	unsigned char i;
	
	i=ConvertAscii2BCD(bfr);
	Write(DS1302_DATE,i);
	bfr +=4;
	
	i=ConvertAscii2BCD(bfr);
	Write(DS1302_MONTH,i);
	bfr +=4;
	
	i=ConvertAscii2BCD(bfr);
	Write(DS1302_YEAR,i);
	bfr +=4;
	//////////////////////////
	i=ConvertAscii2BCD(bfr);
	Write(DS1302_HOURS,i);
	bfr +=4;
	
	i=ConvertAscii2BCD(bfr);
	Write(DS1302_MINUTES,i);
	bfr +=4;
	
	i=ConvertAscii2BCD(bfr);
	Write(DS1302_SECONDS,i);
	
	Write(DS1302_DAY,0);
}



}// namespace

#endif /* DS1302_H_ */
 
