// #include "avr\io.h"
// #include "\ArduinoEasy\SOFTWARE\COMMON\global.h"
// #include "\ArduinoEasy\SOFTWARE\COMMON\board.h"
// //_______________________________________________________________________________________________________________________
// namespace hardware
// {		
// 	class pin:public BOARD
// 	{
// 		public:
// 		pin(unsigned char board_pin_no);	// constructor
// 		pin(unsigned char board_pin_no, unsigned char direction);	// constructor
// 		pin(unsigned char board_pin_no, unsigned char direction,bool logic);	// constructor
// 		~pin();	// destructor
// 		//
// 		void test();
// 		void hi();
// 		void lo();
// 		void toggle();
// 		void blink();
// 		void on();
// 		void off();
// 		unsigned char pressed();
// 		unsigned char released();
// 		unsigned char opened();
// 		unsigned char closed();
				
// 		unsigned int delay_val=10000;
		
// 		private:
// 		unsigned char pin_no;
// 		unsigned char direction;
// 		unsigned char logic;
// 		bool state=0;
// 		unsigned int delay_reg=0;
			
// 		protected:
	 	
// 	};// class pin
// }// namespace hardware
// ///////////////////////////////////////////////////////////////////////////////////////////////////////





// ///////////////////////////////////////////////////////////////////////////////////////////////////////
// hardware::pin::pin(unsigned char board_pin_no)
// {
// 	DO(board_pin_no);
// 	this->pin_no=board_pin_no;
// }
// //______________________________________________________________________________________________________________
// hardware::pin::pin(unsigned char board_pin_no, unsigned char direction)
// {
// 	this->pin_no=board_pin_no;
// 	this->direction=direction;
	
// 	if(this->direction==input)
// 	{
// 		DI(board_pin_no);
// 	}else
// 	{
// 		DO(board_pin_no);
// 	}
// }
// //________________________________________________________________________________________________________________
// hardware::pin::pin(unsigned char board_pin_no, unsigned char direction,bool logic)	// constructor
// {
// 	this->pin_no=board_pin_no;
// 	this->direction=direction;
// 	this->logic=logic;
	
// 	if(this->direction==input)
// 	{
// 		DI(board_pin_no);
// 	}else
// 	{
// 		DO(board_pin_no);
// 	}
// }
// //______________________________________________________________________________________________________________
// hardware::pin::~pin()	// destructor
// {	
// }
// //______________________________________________________________________________________________________________
// void hardware::pin::test()
// {
// 	blink();
// }
// ////________________________________________________________________________________________________________________
// void hardware::pin::hi()
// {		
// 	PIN_High(this->pin_no);
// }
// //________________________________________________________________________________________________________________
// void hardware::pin::lo()
// {
// 	PIN_Low(this->pin_no);
// }
// //________________________________________________________________________________________________________________
// void hardware::pin::toggle()
// {
// 	if(state==0) state=1; else state=0;
// 	(state==1)? PIN_High(pin_no): PIN_Low(this->pin_no);
// }
// //________________________________________________________________________________________________________________
// void hardware::pin::blink()
// {
// 	if(delay_reg<delay_val)
// 	{
// 		this->delay_reg++;
// 	}
// 	else
// 	{
// 		this->delay_reg=0;
// 		if(state==0) state=1; else state=0;			
// 		(state==1)? PIN_High(pin_no): PIN_Low(this->pin_no);	 	
// 	}
// }
// //________________________________________________________________________________________________________________
// void hardware::pin::on()
// {
// 	(this->logic==1)? PIN_High(pin_no): PIN_Low(this->pin_no);	
// }
// //________________________________________________________________________________________________________________
// void hardware::pin::off()
// {	
// 	(this->logic==1)? PIN_Low(this->pin_no): PIN_High(pin_no);		
// }
// //________________________________________________________________________________________________________________
// unsigned char hardware::pin::pressed()
// {
// 	unsigned char state=PIN_Status(this->pin_no);
		
// 		if(this->logic==1)
// 		{
// 			if(state==1) return 1;	
// 			else return 0;			
// 		}
// 		else
// 		{
// 			if(state==1) return 0;
// 			else return 1;
// 		}		
// }
// //________________________________________________________________________________________________________________
// unsigned char hardware::pin::released()
// {
// 	if(this->logic==1)
// 	{
// 		if(state==1) return 1;
// 		else return 0;
// 	}
// 	else
// 	{
// 		if(state==1) return 0;
// 		else return 1;
// 	}	
// }
// //________________________________________________________________________________________________________________
// unsigned char hardware::pin::opened()
// {
// 		unsigned char state=PIN_Status(this->pin_no);
		
// 		if(this->logic==1)
// 		{
// 			if(state==1) return 1;
// 			else return 0;
// 		}
// 		else
// 		{
// 			if(state==1) return 0;
// 			else return 1;
// 		}	
// }
// //________________________________________________________________________________________________________________
// unsigned char hardware::pin::closed()
// {
// 	if(this->logic==1)
// 	{
// 		if(state==1) return 1;
// 		else return 0;
// 	}
// 	else
// 	{
// 		if(state==1) return 0; 
// 		else return 1;
// 	}	
// }
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////