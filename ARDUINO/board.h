// /*
//  * MEGA2560.h
//  *
//  * Created: 19-03-2019 16:15:11
//  *  Author: Administrator
//  */ 


// #ifndef BOARD_H_
// #define BOARD_H_

// #include "\ArduinoEasy\SOFTWARE\COMMON\global.h"
// #include <avr/io.h>
// #include <avr/pgmspace.h>
// #include <util/delay.h>
// #include <avr/wdt.h>

// namespace hardware
// {	

// 	/////////////////////////////////////////////////	
// //#ifdef BOARD_MEGA2560	
// 	class BOARD
// 		{	
// 			public:	
			
// 			static void PORT_IN(unsigned char port,unsigned char val);
// 			static void PORT_OUT(unsigned char port,unsigned char val);
// 			static void PORT_HI(unsigned char port,unsigned char val);
// 			static void PORT_LO(unsigned char port,unsigned char val);
// 			static void PORT_UPDATE(unsigned char port,unsigned char val);
			 							
// 			static void DI(unsigned char pin_name);
// 			static void DO(unsigned char pin_name);
// 			static void PIN_High(unsigned char pin_name);
// 			static void PIN_Low(unsigned char pin_name);
// 			static unsigned char PIN_Status(unsigned char pin_name);
// 			static void sleep(long val);
			
// 			static bool I2C_Write(uint8_t addr, uint8_t data);
// 			static bool I2C_read(uint8_t addr, uint8_t *data);
// 			static bool I2C_Start_Not_Send(void);
// 			static void I2C_Send_Device_Addr_W(uint8_t SLA_W);
// 			static void I2C_Send_Addr(uint8_t addr);
// 			static void I2C_Send_Data(uint8_t data);
// 			static void I2C_Read_Data(uint8_t addr, uint8_t *data);
// 			static bool I2C_ACK_Not_Received();
// 			static bool I2C_Send_Stop_Not_OK(void);
			
// 			static void set_UBRR(unsigned char port_no, unsigned char val);			
// 			static unsigned int Get_UBRR_VAL(long Baud_Rate);
// 			static void serial0_Open(long Baud_Rate);
// 			static void serial1_Open(long Baud_Rate);
// 			static void serial2_Open(long Baud_Rate);
// 			static void serial3_Open(long Baud_Rate);
			
// 			static void serial0_byte_send(unsigned char val);
// 			static void serial1_byte_send(unsigned char val);
// 			static void serial2_byte_send(unsigned char val);
// 			static void serial3_byte_send(unsigned char val);

// 			static void Put2IEPROM(unsigned int uiAddress, unsigned char ucData);
// 			static unsigned char GetIEPROM(unsigned int uiAddress);
// 			static void set_all_port_as_INPUT(void);	
			
// 			static void ADC_setup(unsigned char ch);
// 			static unsigned char convert_pin_to_adc_channel(unsigned char pin_name);
// 			static unsigned int ADC_Get(unsigned char ch);		
							
// 		};// class		
// 		//////////////////////////////////////////////////////////////////////////////////////////
// 		void BOARD::PORT_IN(unsigned char port,unsigned char val)
// 		{
// 			switch(port)
// 			{
// 				case PA:		DDRA &=val;	break;
// 				case PB:		DDRB &=val;	break;
// 				case PC:		DDRC &=val;	break;
// 				case PD:		DDRD &=val;	break;
// 				case PE:		DDRE &=val;	break;
// 				case PF:		DDRF &=val;	break;
// 				case PG:		DDRG &=val;	break;
// 				case PH:		DDRH &=val;	break;
// 				case PJ:		DDRJ &=val;	break;
// 				case PK:		DDRK &=val;	break;
// 				case PL: 		DDRL &=val;	break;
				
// 				default:		break;
// 			}			
// 		}
// 		//______________________________________________________________________________________________________________________________________
// 		void BOARD::PORT_OUT(unsigned char port,unsigned char val)
// 		{
// 			switch(port)
// 			{
// 				case PA:		DDRA |=val;	break;
// 				case PB:		DDRB |=val;	break;
// 				case PC:		DDRC |=val;	break;
// 				case PD:		DDRD |=val;	break;
// 				case PE:		DDRE |=val;	break;
// 				case PF:		DDRF |=val;	break;
// 				case PG:		DDRG |=val;	break;
// 				case PH:		DDRH |=val;	break;
// 				case PJ:		DDRJ |=val;	break;
// 				case PK:		DDRK |=val;	break;
// 				case PL: 		DDRL |=val;	break;
				
// 				default:		break;
// 			}		
// 		}
// 		//______________________________________________________________________________________________________________________________________
// 		void BOARD::PORT_HI(unsigned char port,unsigned char val)
// 		{
// 			switch(port)
// 			{
// 				case PA:		PORTA |=val;	break;
// 				case PB:		PORTB |=val;	break;
// 				case PC:		PORTC |=val;	break;
// 				case PD:		PORTD |=val;	break;
// 				case PE:		PORTE |=val;	break;
// 				case PF:		PORTF |=val;	break;
// 				case PG:		PORTG |=val;	break;
// 				case PH:		PORTH |=val;	break;
// 				case PJ:		PORTJ |=val;	break;
// 				case PK:		PORTK |=val;	break;
// 				case PL: 		PORTL |=val;	break;
				
// 				default:		break;
// 			}				
// 		}
// 		//______________________________________________________________________________________________________________________________________
// 		void BOARD::PORT_LO(unsigned char port,unsigned char val)
// 		{
// 			switch(port)
// 			{
// 				case PA:		PORTA &=val;	break;
// 				case PB:		PORTB &=val;	break;
// 				case PC:		PORTC &=val;	break;
// 				case PD:		PORTD &=val;	break;
// 				case PE:		PORTE &=val;	break;
// 				case PF:		PORTF &=val;	break;
// 				case PG:		PORTG &=val;	break;
// 				case PH:		PORTH &=val;	break;
// 				case PJ:		PORTJ &=val;	break;
// 				case PK:		PORTK &=val;	break;
// 				case PL: 		PORTL &=val;	break;
				
// 				default:		break;
// 			}		
// 		}
// 		//______________________________________________________________________________________________________________________________________
// 		void BOARD::PORT_UPDATE(unsigned char port,unsigned char val)
// 		{
// 			switch(port)
// 			{
// 				case PA:		PORTA =val;	break;
// 				case PB:		PORTB =val;	break;
// 				case PC:		PORTC =val;	break;
// 				case PD:		PORTD =val;	break;
// 				case PE:		PORTE =val;	break;
// 				case PF:		PORTF =val;	break;
// 				case PG:		PORTG =val;	break;
// 				case PH:		PORTH =val;	break;
// 				case PJ:		PORTJ =val;	break;
// 				case PK:		PORTK =val;	break;
// 				case PL: 		PORTL =val;	break;
				
// 				default:		break;
// 			}		
// 		}
// 		//______________________________________________________________________________________________________________________________________
// 		void BOARD::DI(unsigned char pin_name)
// 		{	
// 			switch(pin_name)
// 			{
// 				case A0:		DDRF &=0b11111110;	break;	
// 				case A1:		DDRF &=0b11111101;	break;	
// 				case A2:		DDRF &=0b11111011;	break;	
// 				case A3:		DDRF &=0b11110111;	break;
// 				case A4:		DDRF &=0b11101111;	break;	
// 				case A5:		DDRF &=0b11011111;	break;	
// 				case A6:		DDRF &=0b10111111;	break;	
// 				case A7:		DDRF &=0b01111111;	break;
// 				case A8:		DDRK &=0b11111110;	break;	
// 				case A9:		DDRK &=0b11111101;	break;	
// 				case A10: 		DDRK &=0b11111011;	break;	
// 				case A11:		DDRK &=0b11110111;	break;
// 				case A12:		DDRK &=0b11101111;	break;	
// 				case A13:		DDRK &=0b11011111;	break;	
// 				case A14:		DDRK &=0b10111111;	break;	
// 				case A15:		DDRK &=0b01111111;	break;
// 				case D2:		DDRE &=0b11101111;	break;	
// 				case D3:		DDRE &=0b11011111;	break;	
// 				case D4:		DDRG &=0b11011111;	break;	
// 				case D5:		DDRE &=0b11110111;	break;
// 				case D6:		DDRH &=0b11110111;	break;	
// 				case D7:		DDRH &=0b11101111;	break;	
// 				case D8:		DDRH &=0b11011111;	break;	
// 				case D9:		DDRH &=0b10111111;	break;
		
// 				case D10:	DDRB &=0b11101111;	break;
// 				case D11:	DDRB &=0b11011111;	break;
// 				case D12:	DDRB &=0b10111111;	break;
// 				case D13:	DDRB &=0b01111111;	break;
		
// 				case D14:	DDRJ &=0b11111101;	break;	//TX3
// 				case D15:	DDRJ &=0b11111110;	break;	//RX3
		
// 				case D16:	DDRH &=0b11111101;	break; // TX2
// 				case D17:	DDRH &=0b11111110;	break; // RX2
		
// 				case D18:	DDRD &=0b11110111;	break;	// TX1
// 				case D19:	DDRD &=0b11111011;	break;	// RX1
		
// 				case D20:	DDRD &=0b11111101;	break;	// SDA
// 				case D21:	DDRD &=0b11111110;	break;	// SCL
		
// 				case D22:	DDRA &=0b11111110;	break;
// 				case D23:	DDRA &=0b11111101;	break;
// 				case D24:	DDRA &=0b11111011;	break;
// 				case D25:	DDRA &=0b11110111;	break;
// 				case D26:	DDRA &=0b11101111;	break;
// 				case D27:	DDRA &=0b11011111;	break;
// 				case D28:	DDRA &=0b10111111;	break;
// 				case D29:	DDRA &=0b01111111;	break;
		
// 				case D30:	DDRC &=0b01111111;	break;
// 				case D31:	DDRC &=0b10111111;	break;
// 				case D32:	DDRC &=0b11011111;	break;
// 				case D33:	DDRC &=0b11101111;	break;
// 				case D34:	DDRC &=0b11110111;	break;
// 				case D35:	DDRC &=0b11111011;	break;
// 				case D36:	DDRC &=0b11111101;	break;
// 				case D37:	DDRC &=0b11111110;	break;
		
// 				case D38:	DDRD &=0b01111111;	break;
		
// 				case D39:	DDRG &=0b11111011;	break;
// 				case D40:	DDRG &=0b11111101;	break;
// 				case D41:	DDRG &=0b11111110;	break;
		
// 				case D42:	DDRL &=0b01111111;	break;
// 				case D43:	DDRL &=0b10111111;	break;
// 				case D44:	DDRL &=0b11011111;	break;
// 				case D45:	DDRL &=0b11101111;	break;
// 				case D46:	DDRL &=0b11110111;	break;
// 				case D47:	DDRL &=0b11111011;	break;
// 				case D48:	DDRL &=0b11111101;	break;
// 				case D49:	DDRL &=0b11111110;	break;
		
// 				case D50:	DDRB &=0b11110111;	break;
// 				case D51:	DDRB &=0b11111011;	break;
// 				case D52:	DDRB &=0b11111101;	break;
// 				case D53:	DDRB &=0b11111110;	break;
// 				default:		break;
// 			}
// 		}
// 		//______________________________________________________________________________________________________________________________________
// 		void BOARD::DO(unsigned char pin_name)
// 		{
// 				switch(pin_name)
// 				{
// 				case A0:		DDRF |=0b00000001;	break;
// 				case A1:		DDRF |=0b00000010;	break;
// 				case A2:		DDRF |=0b00000100;	break;
// 				case A3:		DDRF |=0b00001000;	break;
// 				case A4:		DDRF |=0b00010000;	break;
// 				case A5:		DDRF |=0b00100000;	break;
// 				case A6:		DDRF |=0b01000000;	break;
// 				case A7:		DDRF |=0b10000000;	break;
		
// 				case A8:		DDRK |=0b00000001;	break;
// 				case A9:		DDRK |=0b00000010;	break;
// 				case A10: 		DDRK |=0b00000100;	break;
// 				case A11:		DDRK |=0b00001000;	break;
// 				case A12: 		DDRK |=0b00010000;	break;
// 				case A13:		DDRK |=0b00100000;	break;
// 				case A14:		DDRK |=0b01000000;	break;
// 				case A15:		DDRK |=0b10000000;	break;
		
// 				case D2:		DDRE |=0b00010000;	break;
// 				case D3:		DDRE |=0b00100000;	break;
// 				case D4:		DDRG |=0b00100000;	break;
// 				case D5:		DDRE |=0b00001000;	break;
// 				case D6:		DDRH |=0b00001000;	break;
// 				case D7:		DDRH |=0b00010000;	break;
// 				case D8:		DDRH |=0b00100000;	break;
// 				case D9:		DDRH |=0b01000000;	break;
		
// 				case D10:	DDRB |=0b00010000;	break;
// 				case D11:	DDRB |=0b00100000;	break;
// 				case D12:	DDRB |=0b01000000;	break;
// 				case D13:	DDRB |=0b10000000;	break;
		
// 				case D14:	DDRJ |=0b00000010;	break;	//TX3
// 				case D15:	DDRJ |=0b00000001;	break;	//RX3
		
// 				case D16:	DDRH |=0b00000010;	break; // TX2
// 				case D17:	DDRH |=0b00000001;	break; // RX2
		
// 				case D18:	DDRD |=0b00001000;	break;	// TX1
// 				case D19:	DDRD |=0b00000100;	break;	// RX1
		
// 				case D20:	DDRD |=0b00000010;	break;	// SDA
// 				case D21:	DDRD |=0b00000001;	break;	// SCL
		
// 				case D22:	DDRA |=0b00000001;	break;
// 				case D23:	DDRA |=0b00000010;	break;
// 				case D24:	DDRA |=0b00000100;	break;
// 				case D25:	DDRA |=0b00001000;	break;
// 				case D26:	DDRA |=0b00010000;	break;
// 				case D27:	DDRA |=0b00100000;	break;
// 				case D28:	DDRA |=0b01000000;	break;
// 				case D29:	DDRA |=0b10000000;	break;
		
// 				case D30:	DDRC |=0b10000000;	break;
// 				case D31:	DDRC |=0b01000000;	break;
// 				case D32:	DDRC |=0b00100000;	break;
// 				case D33:	DDRC |=0b00010000;	break;
// 				case D34:	DDRC |=0b00001000;	break;
// 				case D35:	DDRC |=0b00000100;	break;
// 				case D36:	DDRC |=0b00000010;	break;
// 				case D37:	DDRC |=0b00000001;	break;
		
// 				case D38:	DDRD |=0b10000000;	break;
		
// 				case D39:	DDRG |=0b00000100;	break;
// 				case D40:	DDRG |=0b00000010;	break;
// 				case D41:	DDRG |=0b00000001;	break;
		
// 				case D42:	DDRL |=0b10000000;	break;
// 				case D43:	DDRL |=0b01000000;	break;
// 				case D44:	DDRL |=0b00100000;	break;
// 				case D45:	DDRL |=0b00010000;	break;
// 				case D46:	DDRL |=0b00001000;	break;
// 				case D47:	DDRL |=0b00000100;	break;
// 				case D48:	DDRL |=0b00000010;	break;
// 				case D49:	DDRL |=0b00000001;	break;
		
// 				case D50:	DDRB |=0b00001000;	break;
// 				case D51:	DDRB |=0b00000100;	break;
// 				case D52:	DDRB |=0b00000010;	break;
// 				case D53:	DDRB |=0b00000001;	break;
// 				default:		break;
// 				}
// 		}
// 		//////////////////////////////////////////
// 		void BOARD::PIN_High(unsigned char pin_name)
// 		{
 
// 				switch(pin_name)
// 				{
// 				case A0:	PORTF |=0b00000001;	break;
// 				case A1:	PORTF |=0b00000010;	break;
// 				case A2:	PORTF |=0b00000100;	break;
// 				case A3:	PORTF |=0b00001000;	break;
// 				case A4:	PORTF |=0b00010000;	break;
// 				case A5:	PORTF |=0b00100000;	break;
// 				case A6:	PORTF |=0b01000000;	break;
// 				case A7:	PORTF |=0b10000000;	break;
		
// 				case A8:	PORTK |=0b00000001;	break;
// 				case A9:	PORTK |=0b00000010;	break;
// 				case A10: 	PORTK |=0b00000100;	break;
// 				case A11:	PORTK |=0b00001000;	break;
// 				case A12:	PORTK |=0b00010000;	break;
// 				case A13:	PORTK |=0b00100000;	break;
// 				case A14:	PORTK |=0b01000000;	break;
// 				case A15:	PORTK |=0b10000000;	break;
		
// 				case D2:	PORTE |=0b00010000;	break;
// 				case D3:	PORTE |=0b00100000;	break;
// 				case D4:	PORTG |=0b00100000;	break;
// 				case D5:	PORTE |=0b00001000;	break;
// 				case D6:	PORTH |=0b00001000;	break;
// 				case D7:	PORTH |=0b00010000;	break;
// 				case D8:	PORTH |=0b00100000;	break;
// 				case D9:	PORTH |=0b01000000;	break;
		
// 				case D10:	PORTB |=0b00010000;	break;
// 				case D11:	PORTB |=0b00100000;	break;
// 				case D12:	PORTB |=0b01000000;	break;
// 				case D13:	PORTB |=0b10000000;	break;
		
// 				case D14:	PORTJ |=0b00000010;	break;	//TX3
// 				case D15:	PORTJ |=0b00000001;	break;	//RX3
		
// 				case D16:	PORTH |=0b00000010;	break; // TX2
// 				case D17:	PORTH |=0b00000001;	break; // RX2
		
// 				case D18:	PORTD |=0b00001000;	break;	// TX1
// 				case D19:	PORTD |=0b00000100;	break;	// RX1
		
// 				case D20:	PORTD |=0b00000010;	break;	// SDA
// 				case D21:	PORTD |=0b00000001;	break;	// SCL
		
// 				case D22:	PORTA |=0b00000001;	break;
// 				case D23:	PORTA |=0b00000010;	break;
// 				case D24:	PORTA |=0b00000100;	break;
// 				case D25:	PORTA |=0b00001000;	break;
// 				case D26:	PORTA |=0b00010000;	break;
// 				case D27:	PORTA |=0b00100000;	break;
// 				case D28:	PORTA |=0b01000000;	break;
// 				case D29:	PORTA |=0b10000000;	break;
		
// 				case D30:	PORTC |=0b10000000;	break;
// 				case D31:	PORTC |=0b01000000;	break;
// 				case D32:	PORTC |=0b00100000;	break;
// 				case D33:	PORTC |=0b00010000;	break;
// 				case D34:	PORTC |=0b00001000;	break;
// 				case D35:	PORTC |=0b00000100;	break;
// 				case D36:	PORTC |=0b00000010;	break;
// 				case D37:	PORTC |=0b00000001;	break;
		
// 				case D38:	PORTD |=0b10000000;	break;
		
// 				case D39:	PORTG |=0b00000100;	break;
// 				case D40:	PORTG |=0b00000010;	break;
// 				case D41:	PORTG |=0b00000001;	break;
		
// 				case D42:	PORTL |=0b10000000;	break;
// 				case D43:	PORTL |=0b01000000;	break;
// 				case D44:	PORTL |=0b00100000;	break;
// 				case D45:	PORTL |=0b00010000;	break;
// 				case D46:	PORTL |=0b00001000;	break;
// 				case D47:	PORTL |=0b00000100;	break;
// 				case D48:	PORTL |=0b00000010;	break;
// 				case D49:	PORTL |=0b00000001;	break;
		
// 				case D50:	PORTB |=0b00001000;	break;
// 				case D51:	PORTB |=0b00000100;	break;
// 				case D52:	PORTB |=0b00000010;	break;
// 				case D53:	PORTB |=0b00000001;	break;
// 				default:		break;
// 				}
// 		}
// 		///////////////////////////////////////////
// 		void BOARD::PIN_Low(unsigned char pin_name)
// 		{
 
// 				switch(pin_name)
// 				{
// 				case A0:	PORTF &=0b11111110;	break;
// 				case A1:	PORTF &=0b11111101;	break;
// 				case A2:	PORTF &=0b11111011;	break;
// 				case A3:	PORTF &=0b11110111;	break;
// 				case A4:	PORTF &=0b11101111;	break;
// 				case A5:	PORTF &=0b11011111;	break;
// 				case A6:	PORTF &=0b10111111;	break;
// 				case A7:	PORTF &=0b01111111;	break;
		
// 				case A8:	PORTK &=0b11111110;	break;
// 				case A9:	PORTK &=0b11111101;	break;
// 				case A10: 	PORTK &=0b11111011;	break;
// 				case A11:	PORTK &=0b11110111;	break;
// 				case A12:	PORTK &=0b11101111;	break;
// 				case A13:	PORTK &=0b11011111;	break;
// 				case A14:	PORTK &=0b10111111;	break;
// 				case A15:	PORTK &=0b01111111;	break;
		
// 				case D2:	PORTE &=0b11101111;	break;
// 				case D3:	PORTE &=0b11011111;	break;
// 				case D4:	PORTG &=0b11011111;	break;
// 				case D5:	PORTE &=0b11110111;	break;
// 				case D6:	PORTH &=0b11110111;	break;
// 				case D7:	PORTH &=0b11101111;	break;
// 				case D8:	PORTH &=0b11011111;	break;
// 				case D9:	PORTH &=0b10111111;	break;
		
// 				case D10:	PORTB &=0b11101111;	break;
// 				case D11:	PORTB &=0b11011111;	break;
// 				case D12:	PORTB &=0b10111111;	break;
// 				case D13:	PORTB &=0b01111111;	break;
		
// 				case D14:	PORTJ &=0b11111101;	break;	//TX3
// 				case D15:	PORTJ &=0b11111110;	break;	//RX3
		
// 				case D16:	PORTH &=0b11111101;	break; // TX2
// 				case D17:	PORTH &=0b11111110;	break; // RX2
		
// 				case D18:	PORTD &=0b11110111;	break;	// TX1
// 				case D19:	PORTD &=0b11111011;	break;	// RX1
		
// 				case D20:	PORTD &=0b11111101;	break;	// SDA
// 				case D21:	PORTD &=0b11111110;	break;	// SCL
		
// 				case D22:	PORTA &=0b11111110;	break;
// 				case D23:	PORTA &=0b11111101;	break;
// 				case D24:	PORTA &=0b11111011;	break;
// 				case D25:	PORTA &=0b11110111;	break;
// 				case D26:	PORTA &=0b11101111;	break;
// 				case D27:	PORTA &=0b11011111;	break;
// 				case D28:	PORTA &=0b10111111;	break;
// 				case D29:	PORTA &=0b01111111;	break;
		
// 				case D30:	PORTC &=0b01111111;	break;
// 				case D31:	PORTC &=0b10111111;	break;
// 				case D32:	PORTC &=0b11011111;	break;
// 				case D33:	PORTC &=0b11101111;	break;
// 				case D34:	PORTC &=0b11110111;	break;
// 				case D35:	PORTC &=0b11111011;	break;
// 				case D36:	PORTC &=0b11111101;	break;
// 				case D37:	PORTC &=0b11111110;	break;
		
// 				case D38:	PORTD &=0b01111111;	break;
		
// 				case D39:	PORTG &=0b11111011;	break;
// 				case D40:	PORTG &=0b11111101;	break;
// 				case D41:	PORTG &=0b11111110;	break;
		
// 				case D42:	PORTL &=0b01111111;	break;
// 				case D43:	PORTL &=0b10111111;	break;
// 				case D44:	PORTL &=0b11011111;	break;
// 				case D45:	PORTL &=0b11101111;	break;
// 				case D46:	PORTL &=0b11110111;	break;
// 				case D47:	PORTL &=0b11111011;	break;
// 				case D48:	PORTL &=0b11111101;	break;
// 				case D49:	PORTL &=0b11111110;	break;
		
// 				case D50:	PORTB &=0b11110111;	break;
// 				case D51:	PORTB &=0b11111011;	break;
// 				case D52:	PORTB &=0b11111101;	break;
// 				case D53:	PORTB &=0b11111110;	break;
// 				default:		break;
// 				}	  
// 		}
// 		//------------------------------------------------
// 		unsigned char BOARD::PIN_Status(unsigned char pin_name)
// 		{
// 			switch(pin_name)
// 			{
// 				case A0:	if(PINF &=0b00000001) return 1; else return 0;		break;
// 				case A1:	if(PINF &=0b00000010) return 1; else return 0;		break;
// 				case A2:	if(PINF &=0b00000100) return 1; else return 0;		break;
// 				case A3:	if(PINF &=0b00001000) return 1; else return 0;		break;
// 				case A4:	if(PINF &=0b00010000) return 1; else return 0;		break;
// 				case A5:	if(PINF &=0b00100000) return 1; else return 0;		break;
// 				case A6:	if(PINF &=0b01000000) return 1; else return 0;		break;
// 				case A7:	if(PINF &=0b10000000) return 1; else return 0;		break;
				
// 				case A8:	if(PINK &=0b00000001) return 1; else return 0;		break;
// 				case A9:	if(PINK &=0b00000010) return 1; else return 0;		break;
// 				case A10: 	if(PINK &=0b00000100) return 1; else return 0;		break;
// 				case A11:	if(PINK &=0b00001000) return 1; else return 0;		break;
// 				case A12:	if(PINK &=0b00010000) return 1; else return 0;		break;
// 				case A13:	if(PINK &=0b00100000) return 1; else return 0;		break;
// 				case A14:	if(PINK &=0b01000000) return 1; else return 0;		break;
// 				case A15:	if(PINK &=0b10000000) return 1; else return 0;		break;

// 				case D2:	if(PINE &=0b00010000) return 1; else return 0;		break;
// 				case D3:	if(PINE &=0b00100000) return 1; else return 0;		break;
// 				case D4:	if(PING &=0b00100000) return 1; else return 0;		break;
// 				case D5:	if(PINE &=0b00001000) return 1; else return 0;		break;
// 				case D6:	if(PINH &=0b00001000) return 1; else return 0;		break;
// 				case D7:	if(PINH &=0b00010000) return 1; else return 0;		break;
// 				case D8:	if(PINH &=0b00100000) return 1; else return 0;		break;
// 				case D9:	if(PINH &=0b01000000) return 1; else return 0;		break;
				
// 				case D10:	if(PINB &=0b00010000) return 1; else return 0;		break;
// 				case D11:	if(PINB &=0b00100000) return 1; else return 0;		break;
// 				case D12:	if(PINB &=0b01000000) return 1; else return 0;		break;
// 				case D13:	if(PINB &=0b10000000) return 1; else return 0;		break;

// 				case D14:	if(PINJ &=0b00000010) return 1; else return 0;		break;	//TX3
// 				case D15:	if(PINJ &=0b00000001) return 1; else return 0;		break;	//RX3
				
// 				case D16:	if(PINH &=0b00000010) return 1; else return 0;		break; // TX2
// 				case D17:	if(PINH &=0b00000001) return 1; else return 0;		break; // RX2
				
// 				case D18:	if(PIND &=0b00001000) return 1; else return 0;		break;	// TX1
// 				case D19:	if(PIND &=0b00000100) return 1; else return 0;		break;	// RX1
				
// 				case D20:	if(PIND &=0b00000010) return 1; else return 0;		break;	// SDA
// 				case D21:	if(PIND &=0b00000001) return 1; else return 0;		break;	// SCL
				
// 				case D22:	if(PINA &=0b00000001) return 1; else return 0;		break;
// 				case D23:	if(PINA &=0b00000010) return 1; else return 0;		break;
// 				case D24:	if(PINA &=0b00000100) return 1; else return 0;		break;
// 				case D25:	if(PINA &=0b00001000) return 1; else return 0;		break;
// 				case D26:	if(PINA &=0b00010000) return 1; else return 0;		break;
// 				case D27:	if(PINA &=0b00100000) return 1; else return 0;		break;
// 				case D28:	if(PINA &=0b01000000) return 1; else return 0;		break;
// 				case D29:	if(PINA &=0b10000000) return 1; else return 0;		break;

// 				case D30:	if(PINC &=0b10000000) return 1; else return 0;		break;
// 				case D31:	if(PINC &=0b01000000) return 1; else return 0;		break;
// 				case D32:	if(PINC &=0b00100000) return 1; else return 0;		break;
// 				case D33:	if(PINC &=0b00010000) return 1; else return 0;		break;
// 				case D34:	if(PINC &=0b00001000) return 1; else return 0;		break;
// 				case D35:	if(PINC &=0b00000100) return 1; else return 0;		break;
// 				case D36:	if(PINC &=0b00000010) return 1; else return 0;		break;
// 				case D37:	if(PINC &=0b00000001) return 1; else return 0;		break;

// 				case D38:	if(PIND &=0b10000000) return 1; else return 0;		break;
				
// 				case D39:	if(PING &=0b00000100) return 1; else return 0;		break;
// 				case D40:	if(PING &=0b00000010) return 1; else return 0;		break;
// 				case D41:	if(PING &=0b00000001) return 1; else return 0;		break;

// 				case D42:	if(PINL &=0b10000000) return 1; else return 0;		break;
// 				case D43:	if(PINL &=0b01000000) return 1; else return 0;		break;
// 				case D44:	if(PINL &=0b00100000) return 1; else return 0;		break;
// 				case D45:	if(PINL &=0b00010000) return 1; else return 0;		break;
// 				case D46:	if(PINL &=0b00001000) return 1; else return 0;		break;
// 				case D47:	if(PINL &=0b00000100) return 1; else return 0;		break;
// 				case D48:	if(PINL &=0b00000010) return 1; else return 0;		break;
// 				case D49:	if(PINL &=0b00000001) return 1; else return 0;		break;

// 				case D50:	if(PINB &=0b00001000) return 1; else return 0;		break;
// 				case D51:	if(PINB &=0b00000100) return 1; else return 0;		break;
// 				case D52:	if(PINB &=0b00000010) return 1; else return 0;		break;
// 				case D53:	if(PINB &=0b00000001) return 1; else return 0;		break;
// 				default:		break;
// 			}
// 			return 0;
// 		}
// 		//-------------------------------------------------------------------------------
// 		void BOARD::sleep(long val)
// 		{
// 			while(val!=0)
// 			{
// 				_delay_ms(1);
// 				wdt_reset();
// 				val--;
// 			}
// 		}
// 		//---------------------------------------------------------------------------------
				
// 		bool BOARD::I2C_Write(uint8_t addr, uint8_t data)
// 		{
// 		if(I2C_Start_Not_Send())		return false;
	
// 		I2C_Send_Device_Addr_W(0b11010000);
// 		if(I2C_ACK_Not_Received())		return false;
	
// 		I2C_Send_Addr(addr);
// 		if(I2C_ACK_Not_Received())		return false;
		
// 		I2C_Send_Data(data);
// 		if(I2C_ACK_Not_Received())		return false;
	
// 		if(I2C_Send_Stop_Not_OK())		return false;
// 		return true;
// 		}
// //________________________________________________________________________________________
// 	bool BOARD::I2C_read(uint8_t addr, uint8_t *data)
// 	{
// 	if(I2C_Start_Not_Send())		return false;
	
// 	I2C_Send_Device_Addr_W(0b11010000);
// 	if(I2C_ACK_Not_Received())		return false;
	
// 	I2C_Send_Addr(addr);
// 	if(I2C_ACK_Not_Received())		return false;
// 	//////////////////////////////////////////////
// 	if(I2C_Start_Not_Send())		return false;
// 	I2C_Send_Device_Addr_W(0b11010001);
	
// 	I2C_Send_Addr(addr);
// 	if(I2C_ACK_Not_Received())		return false;
	
// 	I2C_Read_Data(addr, data);
// 	if(I2C_Send_Stop_Not_OK())		return false;
	
// 	return true;
// 	}
// //_______________________________________________________________________________________
// bool BOARD::I2C_Start_Not_Send(void)
// {
// 	/// Send START condition
// 	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	
// 	//Wait for TWINT Flag set. This indicates that the START condition has been transmitted
// 	while (!(TWCR & (1<<TWINT)));
	
// 	//if ((TWSR & 0xF8) != START)
// 	//ERROR();
// 	return false;
// }
// //_______________________________________________________________________________________
// void BOARD::I2C_Send_Device_Addr_W(uint8_t SLA_W)
// {
// 	// Load SLA_W into TWDR Register. Clear TWINT bit in TWCR to start transmission of address
// 	TWDR = SLA_W;
// 	TWCR = (1<<TWINT) |(1<<TWEN);
// 	while (!(TWCR & (1<<TWINT)));
// }
// //_______________________________________________________________________________________
// void BOARD::I2C_Send_Addr(uint8_t addr)
// {
// 	// Load SLA_W into TWDR Register. Clear TWINT bit in TWCR to start transmission of address
// 	TWDR = addr;
// 	TWCR = (1<<TWINT) |(1<<TWEN);
// 	while (!(TWCR & (1<<TWINT)));
// }
// //_________________________________________________________________________________________
// void BOARD::I2C_Send_Data(uint8_t data)
// {
// 	// Load DATA into TWDR Register. Clear TWINT bit in TWCR to start transmission of data
// 	TWDR = data;
// 	TWCR = (1<<TWINT) |(1<<TWEN);
// 	while (!(TWCR & (1<<TWINT)));
// }
// //_________________________________________________________________________________________
// void BOARD::I2C_Read_Data(uint8_t addr, uint8_t *data)
// {
// 	*data=TWDR;
// 	TWCR = (1<<TWINT) |(1<<TWEN);
// }
// //_________________________________________________________________________________________
// bool BOARD::I2C_ACK_Not_Received()
// {
// 	// Check value of TWI Status Register. Mask prescaler bits. If status different from MT_SLA_ACK go to ERROR
// 	//if ((TWSR & 0xF8) !=MT_SLA_ACK)
// 	//ERROR();	
// 	return false;
// }
// //_________________________________________________________________________________________
// bool BOARD::I2C_Send_Stop_Not_OK(void)
// {
// 	//Transmit STOP condition
// 	TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);
// 	return false;
// }
// //__________________________________________________________________________________________
// void BOARD::Put2IEPROM(unsigned int uiAddress, unsigned char ucData)
// {
// while(EECR & (1<<EEPE));
// EEAR = uiAddress;
// EEDR = ucData;
// EECR |= (1<<EEMPE);
// EECR |= (1<<EEPE);
// }
// //________________________________________________________________________________________________________
// unsigned char BOARD::GetIEPROM(unsigned int uiAddress)
// {
// while(EECR & (1<<EEPE));
// EEAR = uiAddress;
// EECR |= (1<<EERE);
// return EEDR;
// }
// //________________________________________________________________________________________________________
// void BOARD::serial0_Open(long Baud_Rate)
// {
// 	UBRR0H =0x0;
// 	UBRR0L =Get_UBRR_VAL(Baud_Rate);
// 	UCSR0A=0b00000010;
// 	UCSR0B=0b10011000;
// 	UCSR0C=0b00000110;
// }
// //________________________________________________________________________________________________________
// void BOARD::serial1_Open(long Baud_Rate)
// {
// 	UBRR1H =0x0;
// 	UBRR1L =Get_UBRR_VAL(Baud_Rate);
// 	UCSR1A=0b00000010;	//UCSR1A=0b00000000;
// 	UCSR1B=0b10011000;
// 	UCSR1C=0b00000110;
// }
// //________________________________________________________________________________________________________
// void BOARD::serial2_Open(long Baud_Rate)
// {
// 	UBRR2H =0x0;
// 	UBRR2L =Get_UBRR_VAL(Baud_Rate);
// 	UCSR2A=0b00000010;
// 	UCSR2B=0b10011000;
// 	UCSR2C=0b00000110;
// }
// //________________________________________________________________________________________________________
// void BOARD::serial3_Open(long Baud_Rate)
// {
// 	UBRR3H =0x0;
// 	UBRR3L =Get_UBRR_VAL(Baud_Rate);
// 	UCSR3A=0b00000010;
// 	UCSR3B=0b10011000;
// 	UCSR3C=0b00000110;
// }
// //________________________________________________________________________________________________________
// unsigned int BOARD::Get_UBRR_VAL(long Baud_Rate)
// {
// switch(Baud_Rate)
// {
// case 2400:		return 416;	break;
// case 4800:		return 207;	break;
// case 9600:		return 207;	break;
// case 19200:		return 103;	break;
// case 38400:		return 51;	break;
// case 57600:		return 34;	break;
// case 115200:	return 16;	break;
// case 230400:	return 8;	break;
// case 460800:	return 3;	break;
// case 921600:	return 1;	break;
// default:		return 207;	break;	// 9600
// }}
// //________________________________________________________________________________________________________
// void BOARD::serial0_byte_send(unsigned char val)
// {
// while (!( UCSR0A & (1<<UDRE0)));
// UDR0 = val;
// }
// //________________________________________________________________________________________________________
// void BOARD::serial1_byte_send(unsigned char val)
// {
// while ( !( UCSR1A & (1<<UDRE1)));
// UDR1 = val;
// }
// //________________________________________________________________________________________________________
// void BOARD::serial2_byte_send(unsigned char val)
// {
// while ( !( UCSR2A & (1<<UDRE2)));
// UDR2 = val;
// }
// //________________________________________________________________________________________________________
// void BOARD::serial3_byte_send(unsigned char val)
// {
// while ( !( UCSR3A & (1<<UDRE3)));
// UDR3 = val;
// }
// //________________________________________________________________________________________________________
// void BOARD::set_UBRR(unsigned char port_no, unsigned char val)
// {
// 	switch(port_no)
// 	{
// 		case 0:	UBRR0L=val; break;
// 		case 1:	UBRR1L=val; break;
// 		case 2:	UBRR2L=val; break;
// 		case 3:	UBRR3L=val; break;
// 		default:			break;	
// 	}	
// }
// //________________________________________________________________________________________________________
// void BOARD::set_all_port_as_INPUT(void)
// {
// 	DDRA=0x00;	PORTA=0x00;
// 	DDRB=0x00;	PORTB=0x00;
// 	DDRC=0x00;	PORTC=0x00;
// 	DDRD=0x00;	PORTD=0x00;
// 	DDRE=0x00;	PORTE=0x00;	
// 	DDRF=0x00;	PORTF=0x00;	
// 	DDRG=0x00;	PORTG=0x00;		
// 	DDRH=0x00;	PORTH=0x00;
// 	DDRJ=0x00;	PORTJ=0x00;
// 	DDRK=0x00;	PORTK=0x00;	
// }
// //________________________________________________________________________________________________________
// void BOARD::ADC_setup(unsigned char ch)
// {
// 	DI(ch);
// 	//DI_Disable(ch);
// 	// Select Vref=AVcc
// 	ADMUX |= (1<<REFS0);
// 	//set prescaller to 128 and enable ADC
// 	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
// }
// //________________________________________________________________________________________________________
// unsigned char BOARD::convert_pin_to_adc_channel(unsigned char pin_name)
// {
// 	switch(pin_name)
// 	{
// 		case A0:	return 0;	break;
// 		case A1:	return 1;	break;
// 		case A2:	return 2;	break;
// 		case A3:	return 3;	break;
// 		case A4:	return 4;	break;
// 		case A5:	return 5;	break;
// 		default:				break;
// 	}
// }
// //________________________________________________________________________________________________________
// unsigned int BOARD::ADC_Get(unsigned char ch)
// {
// 	ch=convert_pin_to_adc_channel(ch);
// 	ADMUX = (ADMUX & 0xF0) | (ch & 0x0F);	//select ADC channel with safety mask
// 	ADCSRA |= (1<<ADSC);					//single conversion mode	
// 	while( ADCSRA & (1<<ADSC) );			// wait until ADC conversion is complete
// 	return ADC;
// }
// //__________________________________________________________________________________________________________________________________________


 
// }// namespace
// #endif
// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	
	
	
	
	
	
// 	//
// 	//
// 	//
// 		//
// //#ifdef  BOARD_UNO
// 	//class BOARD
// 	//{
// 		//public:
// 		//BOARD();
// 		//static void DI(unsigned char pin_name);
// 		//static void DO(unsigned char pin_name);
// 		//static void PIN_High(unsigned char pin_name);
// 		//static void PIN_Low(unsigned char pin_name);
// 		//static void sudip(void);
// 		 //
// 		//
// 	//};// class
// 	/////////////////////////////////////////////////////
// 	//BOARD::BOARD()
// 	//{
// 		//
// 	//}
// 	//void BOARD::sudip(void)
// 	//{
// 		//
// 		//
// 	//}
// 	//void BOARD::DI(unsigned char pin_name)
// 	//{		 
// 		//switch(pin_name)
// 		//{
// 			//case A0:	DDRC &= 0b11111110;	break;
// 			//case A1:	DDRC &= 0b11111101;	break;
// 			//case A2:	DDRC &= 0b11111011;	break;
// 			//case A3:	DDRC &= 0b11110111;	break;
// 			//case A4:	DDRC &= 0b11101111;	break;
// 			//case A5:	DDRC &= 0b11011111;	break;
// 			//case D2:	DDRD &= 0b11111011;	break;
// 			//case D3:	DDRD &= 0b11110111;	break;
// 			//case D4:	DDRD &= 0b11101111;	break;
// 			//case D5:	DDRD &= 0b11011111;	break;
// 			//case D6:	DDRD &= 0b10111111;	break;
// 			//case D7:	DDRD &= 0b01111111;	break;
// 			//case D8:	DDRB &= 0b11111110;	break;
// 			//case D9:	DDRB &= 0b11111101;	break;
// 			//case D10:	DDRB &= 0b11111011;	break;
// 			//case D11:	DDRB &= 0b11110111;	break;
// 			//case D12:	DDRB &= 0b11101111;	break;
// 			//case D13:	DDRB &= 0b11011111;	break;
// 			//default:						break;
// 		//}
// 		//
// 		//
// 	//}
// 	////______________________________________________________________________________________________________________________________________
// 	//void BOARD::DO(unsigned char pin_name)
// 	//{
// 		 //
// 		//switch(pin_name)
// 		//{
// 			//case A0:	DDRC |= 0b00000001;		break;
// 			//case A1:	DDRC |= 0b00000010;		break;
// 			//case A2:	DDRC |= 0b00000100;		break;
// 			//case A3:	DDRC |= 0b00001000;		break;
// 			//case A4:	DDRC |= 0b00010000;		break;
// 			//case A5:	DDRC |= 0b00100000;		break;
// 			////case A6:	DDRD |= 0b01000000;		break;
// 			////case A7:	DDRD |= 0b10000000;		break;
// 			//
// 			//case D2:	DDRD |= 0b00000100;		break;
// 			//case D3:	DDRD |= 0b00001000;		break;
// 			//case D4:	DDRD |= 0b00010000;		break;
// 			//case D5:	DDRD |= 0b00100000;		break;
// 			//case D6:	DDRD |= 0b01000000;		break;
// 			//case D7:	DDRD |= 0b10000000;		break;
// 			//
// 			//case D8:	DDRB |= 0b00000001;		break;
// 			//case D9:	DDRB |= 0b00000010;		break;
// 			//case D10:	DDRB |= 0b00000100;		break;
// 			//case D11:	DDRB |= 0b00001000;		break;
// 			//case D12:	DDRB |= 0b00010000;		break;
// 			//case D13:	DDRB |= 0b00100000;		break;
// 			//default:							break;
// 		//}
// 		//
// 	//}
// 	////////////////////////////////////////////
// 	//void BOARD::PIN_High(unsigned char pin_name)
// 	//{
//  //
// 		//switch(pin_name)
// 		//{
// 			//case A0:	PORTC |= 0b00000001;		break;
// 			//case A1:	PORTC |= 0b00000010;		break;
// 			//case A2:	PORTC |= 0b00000100;		break;
// 			//case A3:	PORTC |= 0b00001000;		break;
// 			//case A4:	PORTC |= 0b00010000;		break;
// 			//case A5:	PORTC |= 0b00100000;		break;
// 			////case A6:	DDRD |= 0b01000000;		break;
// 			////case A7:	DDRD |= 0b10000000;		break;
// 			//
// 			//case D2:	PORTD |= 0b00000100;		break;
// 			//case D3:	PORTD |= 0b00001000;		break;
// 			//case D4:	PORTD |= 0b00010000;		break;
// 			//case D5:	PORTD |= 0b00100000;		break;
// 			//case D6:	PORTD |= 0b01000000;		break;
// 			//case D7:	PORTD |= 0b10000000;		break;
// 			//
// 			//case D8:	PORTB |= 0b00000001;		break;
// 			//case D9:	PORTB |= 0b00000010;		break;
// 			//case D10:	PORTB |= 0b00000100;		break;
// 			//case D11:	PORTB |= 0b00001000;		break;
// 			//case D12:	PORTB |= 0b00010000;		break;
// 			//case D13:	PORTB |= 0b00100000;		break;
// 			//default:								break;
// 		//}
// 		//
// 	//}
// 	/////////////////////////////////////////////
// 	//void BOARD::PIN_Low(unsigned char pin_name)
// 	//{
//  	//
// 		//switch(pin_name)
// 		//{
// 			//case A0:	PORTC &= 0b11111110;		break;
// 			//case A1:	PORTC &= 0b11111101;		break;
// 			//case A2:	PORTC &= 0b11111011;		break;
// 			//case A3:	PORTC &= 0b11110111;		break;
// 			//case A4:	PORTC &= 0b11101111;		break;
// 			//case A5:	PORTC &= 0b11011111;		break;
// 			//
// 			//case D2:	PORTD &= 0b11111011;		break;
// 			//case D3:	PORTD &= 0b11110111;		break;
// 			//case D4:	PORTD &= 0b11101111;		break;
// 			//case D5:	PORTD &= 0b11011111;		break;
// 			//case D6:	PORTD &= 0b10111111;		break;
// 			//case D7:	PORTD &= 0b01111111;		break;
// 			//
// 			//case D8:	PORTB &= 0b11111110;		break;
// 			//case D9:	PORTB &= 0b11111101;		break;
// 			//case D10:	PORTB &= 0b11111011;		break;
// 			//case D11:	PORTB &= 0b11110111;		break;
// 			//case D12:	PORTB &= 0b11101111;		break;
// 			//case D13:	PORTB &= 0b11011111;		break;
// 			//default:								break;
// 		//}
// 	//}
// 	////________________________________________________________________________________________________________
	
// //
// //
// 	//
	
// //#endif		
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //#ifdef  BOARD_NANO
// //#endif		
// 		//
//  	//
// 		//
// //}// namespace
// //
// ////#endif