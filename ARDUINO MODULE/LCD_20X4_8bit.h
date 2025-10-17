// #include "\ArduinoEasy\SOFTWARE\COMMON\global.h"
// #include "\ArduinoEasy\SOFTWARE\COMMON\board.h"
// #include <avr/io.h>
// #include <avr/pgmspace.h>
// #include <avr/pgmspace.h>
// #include <util/delay.h>
// #include <avr/wdt.h>

// using namespace hardware;



// //////////////////////////////////////////////////
// #define		Line1	0x01
// #define		Line2	0x02
// #define		Line3	0x03
// #define		Line4	0x04

// #define		lcd2Line5x7					0x38
// #define		lcdDsplCurOff				0x0c
// #define		lcdClr						0x01
// #define		LcdRo1Col1					0x80
// #define		LcdRo2Col1					0xC0
// #define		LcdRo3Col1					0x94
// #define		LcdRo4Col1					0xD4
// #define		DisplayOnCursorBlinking		0x0e
// #define		DisplayOnCursorBlinking2	0x0f
// #define		ForceCursor1stLine1stCol	0x80
// #define		ForceCursor2ndLine2ndCol	0xC0

// #define		HideCursor					0x00
// #define		DisplayCursor				0x01
// //-------------------------------------------
// #define		LCD_Delay_Val_8bit	1    //50
// #define     _cmd            0
// #define     _data           1
// #define		ColumnCount
// ///////////////////////////////////////////////////


// namespace Tools
// {


	
// class LCD_20X4_8bit:public BOARD,private helper
// 	{		
	
// 		public:
// 		LCD_20X4_8bit();
// 		LCD_20X4_8bit(unsigned char port,unsigned char rs, unsigned char en);
// 		void test(void);
		
// 		void update(void);
// 		void update(int val);
// 		void update(unsigned int val, unsigned char line_no);		
// 		void update(unsigned int val,unsigned char line_no,const char *label);
// 		void update(const char *label,unsigned int val);
		
// 		void update(const char *msg);
// 		void update(unsigned char *bfr);
// 		void update(unsigned char *bfr,unsigned char line_no);
		
// 		void update_all_lines(unsigned char *bfr);
				
// 		unsigned char default_line=1;	
// 		unsigned char default_column=0;
// 		unsigned char bfr[20];
// 		private:
// 		void Init_8bit_mode(void);	
// 		void Send_Val(unsigned type, unsigned char val);
// 		void send(volatile uint8_t val);
// 		void stb_trigger(void);
// 		void lcd_delay(unsigned char val);
		
// 		void LCD_Print(unsigned char line_no, const char * str);
// 		void LCD_Print(unsigned char line_no, const char * str,unsigned int val);
// 		void LCD_Print_int(unsigned char line_no, unsigned int val);
// 		void LCD_puts(unsigned char line_no,unsigned char*bfr);
// 		void LCD_puts_using_Coloumn_Count(unsigned char line_no,unsigned char*bfr);
		
// 		unsigned char port=PK,rs=D8,en=D9;
					
// 		protected:
// 	};
// 	//________________________________________________________________________________________________________________________________________
// 	LCD_20X4_8bit::LCD_20X4_8bit()
// 	{
// 		DO(rs);
// 		DO(en);
// 		PORT_OUT(port,0xff);
// 		Init_8bit_mode();	
// 	}
// 	//________________________________________________________________________________________________________________________________________
// 	LCD_20X4_8bit::LCD_20X4_8bit(unsigned char port,unsigned char rs, unsigned char en)
// 	{
// 		this->rs=rs;
// 		this->en=en;
// 		this->port=port;
		
// 		DO(rs);
// 		DO(en);
// 		PORT_OUT(port,0xff);
// 		Init_8bit_mode();
// 	}
// 	//________________________________________________________________________________________________________________________________________	
// 	void LCD_20X4_8bit::update(void)
// 	{
// 		static const char test[] PROGMEM = "TESTING LCD..";
// 		pgm2ram(test,&bfr[0]);
// 		LCD_puts(default_line,&bfr[default_column]);
// 	}
// 	//________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_8bit::update(int val)
// 	{
// 		Fill_Buffer(&bfr[0],0,20);
// 		ConvertInt2Ascii(val,&bfr[default_column],5,0);
// 		LCD_puts(default_line,&bfr[default_column]);		
// 	}
// 	//_________________________________ ________________________________________________________________________________________________________
// 	void LCD_20X4_8bit::update(unsigned int val, unsigned char line_no)
// 	{
// 		Fill_Buffer(&bfr[0],0,20);
// 		ConvertInt2Ascii(val,&bfr[default_column],5,0);
// 		LCD_puts(line_no,&bfr[default_column]);		
// 	}
// 	//__________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_8bit::update(unsigned int val,unsigned char line_no,const char *label)
// 	{
// 		Fill_Buffer(&bfr[0],0,20);
// 		pgm2ram(label,&bfr[0]);
// 		int i=Index_Of(&bfr[0],0, 20);
// 		if(i != -1)
// 		{
// 			ConvertInt2Ascii(val,&bfr[i],5,0);
// 			LCD_puts(line_no,&bfr[default_column]);				
// 		}
// 	}
// 	//__________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_8bit::update(const char *label,unsigned int val)
// 	{
// 		Fill_Buffer(&bfr[0],0,20);
// 		pgm2ram(label,&bfr[0]);
// 		int i=Index_Of(&bfr[0],0, 20);
// 		if(i != -1)
// 		{
// 			ConvertInt2Ascii(val,&bfr[i],5,0);
// 			LCD_puts(default_line,&bfr[default_column]);
// 		}
// 	}
// 	//__________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_8bit::update(const char *msg)
// 	{
// 		pgm2ram(msg,&this->bfr[0]);
// 		LCD_puts(this->default_line,&bfr[default_column]);		
// 	}
// 	//__________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_8bit::update(unsigned char *bfr)
// 	{
// 		LCD_puts(default_line,bfr);		
// 	}
// 	//__________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_8bit::update(unsigned char *bfr,unsigned char line_no)
// 	{
// 		LCD_puts(line_no,bfr);		
// 	}
// 	//__________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_8bit::LCD_puts(unsigned char line_no,unsigned char*bfr)
// 	{
// 		switch(line_no)
// 		{
// 			case Line1:
// 			Send_Val(_cmd,0x80);
			
// 			while(*bfr)
// 			{
// 				Send_Val(_data,*bfr);
// 				bfr++;
// 			}
// 			break;
// 			//////////////////////////////
// 			case Line2:
// 			Send_Val(_cmd,0xC0);
			
// 			while(*bfr)
// 			{
// 				Send_Val(_data,*bfr);
// 				bfr++;
// 			}
// 			break;
// 			//////////////////////////////
// 			case Line3:
// 			Send_Val(_cmd,0x94);
			
// 			while(*bfr)
// 			{
// 				Send_Val(_data,*bfr);
// 				bfr++;
// 			}
// 			break;
// 			////////////////////////////////
// 			case Line4:
// 			Send_Val(_cmd,0xD4);
			
// 			while(*bfr)
// 			{
// 				Send_Val(_data,*bfr);
// 				bfr++;
// 			}
// 			break;
// 			//////////////////////////////////
// 			default:
// 			break;
// 		}
// 	}
// 	//______________________________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_8bit::test(void)
// 	{	
		
// 		unsigned char bfr[25];
// 		static const char test[] PROGMEM = "TESTING LCD..";
// 		Fill_Buffer(&bfr[0],0,25);
		
// 		LCD_puts(1,&bfr[0]);
// 		LCD_puts(2,&bfr[0]);
// 		LCD_puts(3,&bfr[0]);
// 		LCD_puts(4,&bfr[0]);

// 		pgm2ram(test,&bfr[0]);
// 		LCD_puts(1,&bfr[0]);
// 		sleep(100);
				
// 		Fill_Buffer(&bfr[0],' ',25);
// 		bfr[20]=0;
// 		LCD_puts(1,&bfr[0]);		
// 		sleep(100);		
// 	}
// 	//______________________________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_8bit::LCD_Print(unsigned char line_no, const char * str)
// 	{
// 		unsigned char bfr[25];
// 		pgm2ram(str, &bfr[0]);
// 		bfr[21]=0;
// 		LCD_puts(line_no,&bfr[0]);
// 	}
// 	//______________________________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_8bit::LCD_Print(unsigned char line_no, const char * str,unsigned int val)
// 	{
// 		unsigned char bfr[21];
// 		int i=0;
// 		while ((bfr[i]= pgm_read_byte(str++)))
// 		{
// 			i++;
// 		}
// 		ConvertInt2Ascii(val,&bfr[i],5,0);
// 		bfr[20]=0;
// 		LCD_puts(line_no,&bfr[0]);
// 	}
// 	//______________________________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_8bit::LCD_Print_int(unsigned char line_no, unsigned int val)
// 	{
// 		unsigned char bfr[6];
// 		ConvertInt2Ascii(val,&bfr[0],5,0);
// 		bfr[5]=0;
// 		LCD_puts(line_no,&bfr[0]);
// 	}
// 	//________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_8bit::LCD_puts_using_Coloumn_Count(unsigned char line_no,unsigned char*bfr)
// 	{
// 	unsigned char col;
// 	col=4;
	
// 	switch(line_no)
// 	{
// 	case Line1:
// 	Send_Val(_cmd, LcdRo1Col1);
	
// 	while(col>0)
// 	{
// 	Send_Val(_data,*bfr);
// 	bfr++;
// 	col--;
// 	}
// 	break;
// 	//////////////////////////////
// 	case Line2:
// 	Send_Val(_cmd, LcdRo2Col1);
	
// 	while(col>0)
// 	{
// 	Send_Val(_data,*bfr);
// 	bfr++;
// 	col--;
// 	}
// 	break;
// 	//////////////////////////////
// 	case Line3:
// 	Send_Val(_cmd, LcdRo3Col1);
	
// 	while(col>0)
// 	{
// 	Send_Val(_data,*bfr);
// 	bfr++;
// 	col--;
// 	}
// 	break;
// 	////////////////////////////////
// 	case Line4:
// 	Send_Val(_cmd, LcdRo4Col1);
	
// 	while(col>0)
// 	{
// 	Send_Val(_data,*bfr);
// 	bfr++;
// 	col--;
// 	}
// 	break;
// 	//////////////////////////////////
// 	default:
// 	break;
// 	}
// 	}
// 	//____________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_8bit::Init_8bit_mode(void)
// 	{
// 		Send_Val(_cmd,lcd2Line5x7);
// 		Send_Val(_cmd,lcdDsplCurOff);	
// 		Send_Val(_cmd,lcdClr);
// 	}
// 	//____________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_8bit::Send_Val(unsigned type, unsigned char val)
// 	{
// 		PORT_UPDATE(port,val);

// 		if(type==_cmd)
// 		{
// 			PIN_Low(rs);	// for command
// 		}
		 
// 		if(type==_data)	//RS=1 for data
// 		{
// 			PIN_High(rs);
// 		}

// 		 PIN_High(en);
// 		 PIN_Low(en);
// 	}
	 
// 	//________________________________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_8bit::lcd_delay(unsigned char val)
// 	{
// 		unsigned int temp;
// 		do
// 		{
// 		for(temp=0;temp<10;temp++);	//#ifdef		PIC18F4520_H001
// 		val--;						// more delay for 4520 chip
// 		}while(val !=0);
// 	}
// 	//_______________________________________________________________________________________________________________________________________
	
// }// namespace