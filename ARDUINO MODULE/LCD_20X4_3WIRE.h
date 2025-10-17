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
// #define		LCD_Delay_Val	1000    //50
// #define     _cmd            0
// #define     _data           1
// #define		ColumnCount
// ///////////////////////////////////////////////////


// namespace Tools
// {


	
// class LCD_20X4_3WIRE:public BOARD,private helper
// 	{			
// 		public:
// 		LCD_20X4_3WIRE();
// 		LCD_20X4_3WIRE(unsigned char data,unsigned char clock, unsigned char strobe);
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
// 		void Init_4bit_mode(void);
// 		void Send_Val(unsigned type, unsigned char val);
// 		void send(volatile uint8_t val);
// 		void stb_trigger(void);
// 		void lcd_delay(unsigned char val);
		
// 		void LCD_Print(unsigned char line_no, const char * str);
// 		void LCD_Print(unsigned char line_no, const char * str,unsigned int val);
// 		void LCD_Print_int(unsigned char line_no, unsigned int val);
// 		void LCD_puts(unsigned char line_no,unsigned char*bfr);
// 		void LCD_puts_using_Coloumn_Count(unsigned char line_no,unsigned char*bfr);
		
// 		unsigned char pin_dat=D2,pin_clk=D3,pin_stb=D4;	
		
				
// 		protected:
// 	};
// 	//________________________________________________________________________________________________________________________________________
// 	LCD_20X4_3WIRE::LCD_20X4_3WIRE()
// 	{
// 		DO(pin_dat);
// 		DO(pin_clk);
// 		DO(pin_stb);	
// 		Init_4bit_mode();
// 	}
// 	//________________________________________________________________________________________________________________________________________
// 	LCD_20X4_3WIRE::LCD_20X4_3WIRE(unsigned char data,unsigned char clock, unsigned char strobe)
// 	{
// 		this->pin_dat=data;
// 		pin_clk=clock;
// 		pin_stb=strobe;
		
// 		DO(pin_dat);
// 		DO(pin_clk);
// 		DO(pin_stb);	
// 	}
// 	//________________________________________________________________________________________________________________________________________	
// 	void LCD_20X4_3WIRE::update(void)
// 	{
// 		static const char test[] PROGMEM = "TESTING LCD..";
// 		pgm2ram(test,&bfr[0]);
// 		LCD_puts(default_line,&bfr[default_column]);
// 	}
// 	//________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_3WIRE::update(int val)
// 	{
// 		Fill_Buffer(&bfr[0],0,20);
// 		ConvertInt2Ascii(val,&bfr[default_column],5,0);
// 		LCD_puts(default_line,&bfr[default_column]);		
// 	}
// 	//_________________________________ ________________________________________________________________________________________________________
// 	void LCD_20X4_3WIRE::update(unsigned int val, unsigned char line_no)
// 	{
// 		Fill_Buffer(&bfr[0],0,20);
// 		ConvertInt2Ascii(val,&bfr[default_column],5,0);
// 		LCD_puts(line_no,&bfr[default_column]);		
// 	}
// 	//__________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_3WIRE::update(unsigned int val,unsigned char line_no,const char *label)
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
// 	void LCD_20X4_3WIRE::update(const char *label,unsigned int val)
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
// 	void LCD_20X4_3WIRE::update(const char *msg)
// 	{
// 		pgm2ram(msg,&this->bfr[0]);
// 		LCD_puts(this->default_line,&bfr[default_column]);		
// 	}
// 	//__________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_3WIRE::update(unsigned char *bfr)
// 	{
// 		LCD_puts(default_line,bfr);		
// 	}
// 	//__________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_3WIRE::update(unsigned char *bfr,unsigned char line_no)
// 	{
// 		LCD_puts(line_no,bfr);		
// 	}
// 	//__________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_3WIRE::LCD_puts(unsigned char line_no,unsigned char*bfr)
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
// 	void LCD_20X4_3WIRE::test(void)
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
// 	void LCD_20X4_3WIRE::LCD_Print(unsigned char line_no, const char * str)
// 	{
// 		unsigned char bfr[25];
// 		pgm2ram(str, &bfr[0]);
// 		bfr[21]=0;
// 		LCD_puts(line_no,&bfr[0]);
// 	}
// 	//______________________________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_3WIRE::LCD_Print(unsigned char line_no, const char * str,unsigned int val)
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
// 	void LCD_20X4_3WIRE::LCD_Print_int(unsigned char line_no, unsigned int val)
// 	{
// 		unsigned char bfr[6];
// 		ConvertInt2Ascii(val,&bfr[0],5,0);
// 		bfr[5]=0;
// 		LCD_puts(line_no,&bfr[0]);
// 	}
// 	//________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_3WIRE::LCD_puts_using_Coloumn_Count(unsigned char line_no,unsigned char*bfr)
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
// 	//__________________________________________________________________________________________________________________________
// 	void LCD_20X4_3WIRE::Init_4bit_mode(void)
// 	{
// 		Send_Val(_cmd,0x03);
// 		lcd_delay(LCD_Delay_Val);

// 		Send_Val(_cmd,0x03);
// 		lcd_delay(LCD_Delay_Val);

// 		Send_Val(_cmd,0x03);
// 		lcd_delay(LCD_Delay_Val);

// 		Send_Val(_cmd,0x02);
// 		lcd_delay(LCD_Delay_Val);

// 		Send_Val(_cmd,0x28);
// 		lcd_delay(LCD_Delay_Val);


// 		Send_Val(_cmd,0x0C);
// 		lcd_delay(LCD_Delay_Val);
// 		///////////////////////
// 		Send_Val(_cmd,0x01);         //Display Off, Cursor Off, Blink Off
// 		lcd_delay(LCD_Delay_Val);

// 		Send_Val(_cmd,4);
// 		lcd_delay(LCD_Delay_Val);

// 		Send_Val(_cmd,0x06);
// 		lcd_delay(LCD_Delay_Val);
// 	}
// 	//____________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_3WIRE::Send_Val(unsigned type, unsigned char val)
// 	{
// 		unsigned char i;
// 		i=val&0xF0;
// 		i |= 0x02;
// 		if(type==_data) i|=0x01;

// 		send(i);        // DATA+ EN HI
// 		stb_trigger();

// 		i &=0b11111101;
// 		send(i);        // Send EN LO
// 		stb_trigger();

// 		i=(val&0x0F)<<4;
// 		i |= 0x02;                 // EN HI
// 		if(type==_data) i|=0x01;   //RS=1 for data

// 		send(i);                // Write Lower nibble
// 		stb_trigger();

// 		i &=0b11111101;            // EN LO
// 		send(i);
// 		stb_trigger();
// 	}
// 	//__________________________________________________________________________________________________________________________
// 	void LCD_20X4_3WIRE::send(volatile uint8_t val)
// 	{
// 		register unsigned char j,k;
				 	
// 		for(j=0;j<=7;j++)
// 		{
// 			k = val & 128;
// 			switch (k)
// 			{
// 				case 0:			PIN_Low(this->pin_dat);	break;
// 				default:		PIN_High(this->pin_dat);	break;
// 			}
// 			PIN_High(pin_clk);
// 			PIN_Low(pin_clk);
// 			val =val <<1;
// 		}
// 	}
// 	//________________________________________________________________________________________________________________________________________________________________	
// 	void LCD_20X4_3WIRE::stb_trigger(void)
// 	{
// 		PIN_High(pin_stb);
// 		PIN_Low(pin_stb);
// 	}	 
// 	//________________________________________________________________________________________________________________________________________________________________
// 	void LCD_20X4_3WIRE::lcd_delay(unsigned char val)
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