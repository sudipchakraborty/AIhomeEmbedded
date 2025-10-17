#ifndef ESP8266_H_
#define ESP8266_H_
// To change baud rate in ESP8266 AT+UART_DEF=115200,8,1,0,0
namespace hardware
{	
	
class ESP8266:public BOARD,public helper,public SERIAL
{
	enum{ led_init,led_module_present,led_connect,led_disconnect};
	
	public:
		unsigned char Led_R=D11,Led_G=D13,Led_B=D12,CH_PD=D29,RST=D27;
		bool initialized=false;
		unsigned char port_no=3;
		long baud_rate=115200;
		unsigned char connected=false;
		unsigned char present=false;
		bool Display_Debug_message=true;
		unsigned char channel=0;
		unsigned char command_buffer[0xff];
		bool connected_with_router=false;
		
		ESP8266();
		ESP8266(unsigned char port_no, unsigned char CH_PD, unsigned char RST);
		ESP8266(unsigned char port_no, long baud_rate, char CH_PD, unsigned char RST);
		
		void start_serever(void);
		void start_client(const char * wifi_router_id, const char *wifi_router_password);
				
		void request_process(void);
		void flash(void);
		void Purse_Received_Data_Packet(unsigned char *bfr);
		

		void send(unsigned char *bfr);
		bool Send_To_Wifi(const char * str_cmd,const char * str_reply, unsigned int delay);
		bool Send_To_Wifi_Not_Success(const char * str_cmd,const char * str_reply, unsigned int pkt_chk_delay,int chk_count, int try_count);
		bool Send_To_Wifi_Not_Success(unsigned char *bfr,const char * str_reply, unsigned int pkt_chk_delay,int chk_count, int try_count);
		bool Found_in_Receive_Buffer(const char * str_reply, unsigned int pkt_chk_delay,int chk_count);
		
		bool Not_Connected_With_Thingspeak_Webserver(void);
		void Send_Request_To_ThingSpeak_Server(void);
		bool Not_Responseded(const char * str_cmd,unsigned int pkt_chk_delay,int chk_count);
		bool Not_Responseded(unsigned char *bfr,unsigned int pkt_chk_delay,int chk_count);
		bool String_found_in_rx_buffer(const char * str);
		void Receive_Packet_Monitor(void);
				
		void Led(unsigned char mode);
		//static void setup(unsigned char port_no, long baud_rate, unsigned char led_red, unsigned char led_yellow, unsigned char led_green);
		//static void Read(unsigned char val);
		//static void flash_ESP8266(void);	
		//static void Init(void);
		//static unsigned char Send_To_Wifi_Not_Success(const char * str_cmd,const char * str_reply, unsigned int delay_val);
		//static void State_Handler(void);
		void Get_rx_data(unsigned char *bfr);
	private:
		
	//
	//
	//
	protected:
	//
	//
	//
	//
	};// class ESP8266
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ESP8266::ESP8266()
	{
		DO(CH_PD);
		DO(RST);
		PIN_High(CH_PD);
		PIN_High(RST);
		Port_Open(port_no,115200);
		sei();
	}
	//____________________________________________________________________________________________________________
	ESP8266::ESP8266(unsigned char port_no, unsigned char CH_PD, unsigned char RST)
	{
		this->port_no=port_no;
		this->CH_PD=CH_PD;
		this->RST=RST;
		
		DO(CH_PD);
		DO(RST);
		PIN_High(CH_PD);
		PIN_High(RST);
		Port_Open(port_no,115200);
		sei();
	}
	//____________________________________________________________________________________________________________
	ESP8266::ESP8266(unsigned char port_no, long baud_rate, char CH_PD, unsigned char RST)
	{
		this->port_no=port_no;
		this->baud_rate=baud_rate;
		this->CH_PD=CH_PD;
		this->RST=RST;
		
		DO(CH_PD);
		DO(RST);
		PIN_High(CH_PD);
		PIN_High(RST);
		Port_Open(port_no,115200);
		sei();
	}
	//____________________________________________________________________________________________________________
	void ESP8266::start_serever(void)
	{
		
		//debug_CRLF();
		//debug_divider();
		//Led(led_init);
		//sleep(10000);
				//
		//static const char  esp_init[] PROGMEM = "\r\nSystem is Going to Initialize ESP8266\r\n";
		//if(Display_Debug_message)	debug(esp_init);
		////=== Send ECHO OFF===============================================================================
		//static const char  OK[] PROGMEM = "OK";
		//static const char  ATE0[] PROGMEM = "ATE0\r\n";
		//static const char  ATE0_accepted[] PROGMEM = "ATE0 Accepted\r\n";
		//static const char  ATE0_Not_accepted[] PROGMEM = "ATE0 Not Accepted\r\n";
		//int i=0;
		//do
		//{
			//if(Send_To_Wifi_Not_Success(ATE0,OK,100,3))
			//{
				//if(Display_Debug_message)	debug(ATE0_Not_accepted);
				//sleep(1000);
				//i++;
				//if(i>3)
				//{
					//return;
				//}
			//}
			//else
			//{
				//if(Display_Debug_message)	debug(ATE0_accepted);
				//break;
			//}
		//}while(i<100);
		////=====================================
		//sleep(10);
		//
		////=== Send AT==========================
		//static const char AT[] PROGMEM = "AT\r\n";
		//static const char AT_Accepted[] PROGMEM = "AT Accepted \r\n";
		//static const char AT_Not_Accepted[] PROGMEM = "AT Not Accepted \r\n";
		//
		//if(Send_To_Wifi_Not_Success(AT,OK,100,3))
		//{
			//if(Display_Debug_message) debug(AT_Not_Accepted);
			//return;
		//}
		//else
		//{
			//if(Display_Debug_message)	debug(AT_Accepted);
		//}
		////=====================================
		//
		//
		//
		////=== Send AT+RST======================
		////const char AT_plus_RST[]  PROGMEM= "AT+RST\r\n";
		////if(Send_To_Wifi_Not_Success(AT_plus_RST,OK,100))
		////{
		////terminal.print_Two_String(AT_plus_RST,'>',send_error);
		////return;
		////}
		////else
		////{
		////terminal.print_Two_String(AT_plus_RST,'>',send_success);
		////}
		////=====================================
		//
		//
		////=== Send AT_plus_CWMODE_3=============
		//static const char AT_plus_CWMODE_3[] PROGMEM = "AT+CWMODE=3\r\n";
		//static const char AT_plus_CWMODE_3_Accepted[]  PROGMEM= "AT+CWMODE=3 Accepted \r\n";
		//static const char AT_plus_CWMODE_3_Not_Accepted[] PROGMEM = "AT+CWMODE=3 Not Accepted\r\n";
		//
		//if(Send_To_Wifi_Not_Success(AT_plus_CWMODE_3,OK,100,100,10,))
		//{
			//if(Display_Debug_message) debug(AT_plus_CWMODE_3_Not_Accepted);
			//return;
		//}
		//else
		//{
			//if(Display_Debug_message) debug(AT_plus_CWMODE_3_Accepted);
		//}
		////=====================================
		//sleep(50);
		//
		//
		////=== Send AT_plus_CIPMUX_1=============
		//static const char AT_plus_CIPMUX_1[] PROGMEM= "AT+CIPMUX=1\r\n";
		//static const char AT_plus_CIPMUX_1_Accepted[] PROGMEM = "AT+CIPMUX=1 Accepted \r\n";
		//static const char AT_plus_CIPMUX_1_Not_Accepted[] PROGMEM= "AT+CIPMUX=1 not Accepted \r\n";
		//
		//if(Send_To_Wifi_Not_Success(AT_plus_CIPMUX_1,OK,100,100,10,3))
		//{
			//if(Display_Debug_message) debug(AT_plus_CIPMUX_1_Not_Accepted);
			//return;
		//}
		//else
		//{
			//if(Display_Debug_message) debug(AT_plus_CIPMUX_1_Accepted);
		//}
		////=====================================
		//
		////=== Send AT_plus_CIPSERVER_1_6000=============
		//static const char AT_plus_CIPSERVER_1_502[] PROGMEM = "AT+CIPSERVER=1,502\r\n";
		//static const char AT_plus_CIPSERVER_1_502_accepted[]  PROGMEM= "AT+CIPSERVER=1,502 accepted\r\n";
		//static const char AT_plus_CIPSERVER_1_502_not_accepted[]  PROGMEM= "AT+CIPSERVER=1,502 not accepted\r\n";
		//
		//if(Send_To_Wifi_Not_Success(AT_plus_CIPSERVER_1_502,OK,100,3))
		//{
			//if(Display_Debug_message) debug (AT_plus_CIPSERVER_1_502_not_accepted);
			//return;
		//}
		//else
		//{
			//if(Display_Debug_message) debug(AT_plus_CIPSERVER_1_502_accepted);
		//}
		////=====================================
		//sleep(1000);
		//
		//////flush();
		//////s.bfr_tx[0]='A';
		//////s.bfr_tx[1]='T';
		//////s.bfr_tx[2]='+';
		//////s.bfr_tx[3]='C';
		//////s.bfr_tx[4]='I';
		//////s.bfr_tx[5]='F';
		//////s.bfr_tx[6]='S';
		//////s.bfr_tx[7]='R';
		//////send_2_Esp(&s.bfr_tx);
		//////_delay_ms(2000);
		//////Send_2_Terminal(&s.bfr_rx);
		//
		//static const char esp_init_success[] PROGMEM= "ESP8266 Initialize successfully....";
		//debug(esp_init_success);
		//flash();
		//
		//present=true;
		//connected=false;
		//
		////LED_WIFI_RED_OFF;
		////LED_WIFI_GREEN_OFF;
		////LED_WIFI_BLUE_ON;
		////return;
		//
		////
		//
		////
		//
		//
		//
		//////////////////////////////////////////////////
		////const char  PROGMEM=
		////const char send_success[]  PROGMEM= "SEND OK";
		////const char send_error[] PROGMEM = "SEND Not Success";
		//////////////////////////////////////////////////
		
	}
	//_____________________________________________________________________________________________________________________________________________________
	void ESP8266::start_client(const char * wifi_router_id, const char *wifi_router_password)
	{
		unsigned char bfr[50];
		ESP8266();
		Fill_Buffer(&bfr[0],0,50);
		ConvertInt2Ascii(230,&bfr[0],4,0);

		static const char  esp_client[] PROGMEM = "\r\nInitializing ESP8266 as Client..\r\n";
		if(Display_Debug_message)	debug(esp_client);
		sleep(50000);
		//=== Send ECHO OFF==================== 
		static const char  OK[] PROGMEM = "OK";
		static const char  ATE0[] PROGMEM = "ATE0\r\n";
		if(Send_To_Wifi_Not_Success(ATE0,OK,1,5,5)) return;		
				
		//=== Send AT==========================
		static const char AT[] PROGMEM = "AT\r\n";
		if(Send_To_Wifi_Not_Success(AT,OK,1,5,5)) return;
		//=====================================
				
		//=== Send AT_plus_CWMODE=1=============
		static const char AT_plus_CWMODE_1[] PROGMEM = "AT+CWMODE=1\r\n";		
		if(Send_To_Wifi_Not_Success(AT_plus_CWMODE_1,OK,1,5,2)) return;	
		//=====================================
				
		//=== Set Single connection============
		static const char CIPMUX[] PROGMEM = "AT+CIPMUX=0\r\n";
		if(Send_To_Wifi_Not_Success(CIPMUX,OK,1,5,2)) return;		
		static const char wifi_init[] PROGMEM = "\r\nInitialize WiFi Module";
		if(Display_Debug_message)	debug(wifi_init);
		//---------------------------------------
		
				
		//=== connecting with router=============
		static const char connecting_with_router[] PROGMEM = "\r\nPlease Wait.... Connecting with Router";
		if(Display_Debug_message)	debug(connecting_with_router);
		
		unsigned char b[50];
		Fill_Buffer(&b[0],0,50);
		
		static const char AT_plus_CWJAP[] PROGMEM= "AT+CWJAP=";	
		pgm2ram(AT_plus_CWJAP,&b[0]);		
		b[9]='"';
		pgm2ram(wifi_router_id,&b[10]);
		
		int p=Get_length(wifi_router_id);	
		b[10+p]='"';
		b[10+p+1]=',';
		b[10+p+2]='"';
		pgm2ram(wifi_router_password,&b[10+p+3]);	
		int q=Get_length(wifi_router_password);
		b[10+p+q+3]='"';
		
		b[10+p+q+4]='\r';
		b[10+p+q+5]='\n';
		
		if(Not_Responseded(&b[0],1000,100)) 
		{
			static const char router_not_respond[] PROGMEM="ERROR!!!!....Router Not Responded";	
			if(Display_Debug_message)	debug(router_not_respond);
			connected_with_router=false;
			return;
		}
		static const char wifi_disconnect[] PROGMEM="WIFI DISCONNECT";		
		if(String_found_in_rx_buffer(wifi_disconnect))
		{
			static const char discon[] PROGMEM="Unable to connected with Wifi, Error:WIFI DISCONNECT";
			debug(discon);
			return;
		}
		//////////////
		static const char wifi_connect[] PROGMEM="WIFI CONNECT";		
		if(String_found_in_rx_buffer(wifi_connect))
		{
			static const char wifi_connect[] PROGMEM="Connected with router";
			debug(wifi_connect);
			connected_with_router=true;
		}		
	}
	//_____________________________________________________________________________________________________________________________________________________
	void ESP8266::request_process(void)
	{
		unsigned char bfr[0xff];
		
		if(ptr_rx[port_no]==0)return;	
		sleep(100);	//sleep(9);
		
		Get_rx_data(&bfr[0]);
		debug(&bfr[0]);
		///////////////////////////////////////////////////////
		static const char IPD[] PROGMEM= "+IPD";
		if(String_found_in_bfr(IPD, &bfr[0],0xff, 0))
		{
			static const char data_received[] PROGMEM="Request Received from Client";
			if(Display_Debug_message) debug(data_received);	
			Purse_Received_Data_Packet(&bfr[0]);
			flash();
			return;		
		}
		///////////////////////////////////////////////////////
		static const char connect[] PROGMEM= "CONNECT";
		if(String_found_in_bfr(connect, &bfr[0],0xff, 0))
		{
			static const char device_connected[] PROGMEM="Connected with Client";
			if(Display_Debug_message)	debug(device_connected);
			 //connected=true;
			 //LED_WIFI_BLUE_OFF;
			 //LED_WIFI_GREEN_ON;
			 //flash_ESP8266();
			flash();
			return;
		}
		///////////////////////////////////////////////////////
		static const char close[] PROGMEM= "CLOSED";
		static const char device_closed[] PROGMEM="Client Disconnected";
		if(String_found_in_bfr(close, &bfr[0],0xff, 0))
		{
			if(Display_Debug_message)	debug(device_closed);
			flash();
			 //connected=false;
			 //LED_WIFI_BLUE_ON;
			 //LED_WIFI_GREEN_OFF;
			 //flash_ESP8266();
			return;
		}
		///////////////////////////////////////////////////////
		 flash();
	}
	//____________________________________________________________________________________________________________	
	void ESP8266:: Purse_Received_Data_Packet(unsigned char *bfr)
	{		 
			channel=*(bfr+7);
			static const char ch[] PROGMEM="Received Channel=";
			if(Display_Debug_message)	debug(ch,channel);
						
			int first_coma=Index_Of(bfr,',',0xff,0);
			static const char first_c[] PROGMEM="First Comma at=";
			if(Display_Debug_message)	debug(first_c,first_coma);
			
			int second_coma=Index_Of(bfr,',',0xff,first_coma+1);
			static const char second_c[] PROGMEM="Second Comma at=";
			if(Display_Debug_message)	debug(second_c,second_coma);
			
			int colon_pos=Index_Of(bfr,':',0xff,second_coma+1);
			static const char col_pos[] PROGMEM="Colon Position at=";
			if(Display_Debug_message)	debug(col_pos,colon_pos);
			
			int received_data_count=ConvertAscii2Decimal(bfr+second_coma+1,colon_pos-(second_coma+1));
			static const char recv_char[] PROGMEM="Received Char Count=";
			if(Display_Debug_message)	debug(recv_char,received_data_count);
						
			Fill_Buffer(&command_buffer[0],0,0xff);
			Copyram2ram((bfr+colon_pos+1),&command_buffer[0],received_data_count);
			static const char recv_cmd[] PROGMEM="Command Received=";
			if(Display_Debug_message)	debug(recv_cmd,&command_buffer[0]);	
			
			//sleep(10000);
			unsigned char temp[50];
			Fill_Buffer(&temp[0],0,50);
			static const char ok2[] PROGMEM="Today is Rainy Day";
			pgm2ram(ok2,&temp[0]);
			send(&temp[0]);			
	}
	//____________________________________________________________________________________________________________
	void ESP8266::flash(void)
	{
		ptr_rx[port_no]=0;
		
		for(int i=0;i<0xff;i++)
		{
			bfr_rx3[i]=0;
		}
	}
	//____________________________________________________________________________________________________________
	bool ESP8266::String_found_in_rx_buffer(const char * str)
	{
		unsigned char rx[0xff];
		Fill_Buffer(&rx[0],0,0xff);
		Get_rx_data(&rx[0]);
		if(String_found_in_bfr(str,&rx[0],0xff,0))
		{
			return true;
		}
		else
		{
			return false;			
		}		
	}
	//____________________________________________________________________________________________________________
	bool ESP8266::Send_To_Wifi_Not_Success(const char * str_cmd,const char * str_reply, unsigned int pkt_chk_delay,int chk_count, int try_count)
	{
		unsigned char bfr_tx[0xff];
		unsigned char rx[0xff];
		int temp_chk_count;	
		
		flash();
		Fill_Buffer(&bfr_tx[0],0,0xff);
		pgm2ram(str_cmd, &bfr_tx[0]);
						
		do
		{
			temp_chk_count=0;
			puts_to_serial3(&bfr_tx[0]);
			
			do{
				sleep(pkt_chk_delay);
				Get_rx_data(&rx[0]);
				
				if(String_found_in_bfr(str_reply,&rx[0],0xff,0)) 
				{
					if(Display_Debug_message)	debug_terminated_by(&bfr_tx[0],'\r');
					static const char reply_ok[] PROGMEM=">Reply Received";
					if(Display_Debug_message)	debug(reply_ok);
					return false;
				}
				else
				{
					temp_chk_count++;
					static const char tmp_chk[] PROGMEM="Check Count=";
					if(Display_Debug_message)	debug(tmp_chk,temp_chk_count);
				}
			}while(temp_chk_count <chk_count);
			
			try_count--;
			static const char t_count[] PROGMEM="Try Count=";
			if(Display_Debug_message) debug(t_count,try_count);			
			
		}while(try_count>0);
		
		if(Display_Debug_message)	debug(&bfr_tx[0]);
		static const char send_error[] PROGMEM="Command Send Error!!!!!";
		debug(send_error);
		 
		return true;
 
	}
	//_________________________________________________________________________________________________________________________________________
	bool ESP8266::Not_Responseded(const char * str_cmd,unsigned int pkt_chk_delay,int chk_count)
	{
		unsigned char bfr_tx[0xff];
		unsigned char rx[0xff];
		int temp_chk_count=0;
		
		flash();
		Fill_Buffer(&bfr_tx[0],0,0xff);
		pgm2ram(str_cmd, &bfr_tx[0]);
		
		puts_to_serial3(&bfr_tx[0]);
			
		do{
			sleep(pkt_chk_delay);
				
			Get_rx_data(&rx[0]);
			if(Get_length(&rx[0])!=0)
			{
				return false;
			}
			else	 
			{
				temp_chk_count++;
				static const char tmp_chk[] PROGMEM="Check Count=";
				if(Display_Debug_message)	debug(tmp_chk,temp_chk_count);
			}
		}while(temp_chk_count<chk_count);	
		 
		return true;
	}
	//________________________________________________________________________________________________________________________________________________________
	bool ESP8266::Not_Responseded(unsigned char *bfr,unsigned int pkt_chk_delay,int chk_count)
	{
		unsigned char rx[0xff];
		int temp_chk_count=0;
		
		flash(); 
		puts_to_serial3(bfr);
		
		do{
			sleep(pkt_chk_delay);
			
			Get_rx_data(&rx[0]);
			if(Get_length(&rx[0])!=0)
			{
				if(Display_Debug_message) debug(&rx[0]);
				return false;
			}
			else
			{
				temp_chk_count++;
				static const char tmp_chk[] PROGMEM="Check Count=";
				if(Display_Debug_message)	debug(tmp_chk,temp_chk_count);
			}
		}while(temp_chk_count<chk_count);
		
		return true;
	}
	//________________________________________________________________________________________________________________________________________________________
	void ESP8266::Receive_Packet_Monitor(void)
	{
		unsigned char bfr_rx[0xff];
		Fill_Buffer(&bfr_rx[0],0,0xff);
		while (1)
		{
			Get_rx_data(&bfr_rx[0]);
			debug(&bfr_rx[0]);
			sleep(10000);
		}			
	}
	//________________________________________________________________________________________________________________________________________________________	
	bool ESP8266::Send_To_Wifi_Not_Success(unsigned char *bfr,const char * str_reply, unsigned int pkt_chk_delay,int chk_count, int try_count)
	{
		unsigned char rx[0xff];
		int temp_chk_count;	
		flash();
	
		do
		{
			temp_chk_count=0;	
			puts_to_serial3(bfr);
			
			do{
				sleep(pkt_chk_delay);
				Get_rx_data(&rx[0]);
				debug(&rx[0]);
				if(String_found_in_bfr(str_reply,&rx[0],0xff,0)) return false;
				else
				{
					temp_chk_count++;
					static const char tmp_chk[] PROGMEM="Check Count=";
					debug(tmp_chk,temp_chk_count);
				}								
			}while(temp_chk_count !=chk_count);
			
			try_count--;
			static const char t_count[] PROGMEM="Try Count=";
			debug(t_count,try_count);
			
		}while(try_count>0);
		
		return true;
	}
	//________________________________________________________________________________________________________________________________________________________
	bool ESP8266::Found_in_Receive_Buffer(const char * str_reply, unsigned int pkt_chk_delay,int chk_count)
	{
		unsigned char rx[0xff];
	
		do
		{
			sleep(pkt_chk_delay);
			Get_rx_data(&rx[0]);
			debug(&rx[0]);
			
			if(String_found_in_bfr(str_reply,&rx[0],0xff,0)) return true;
			else
			{
				chk_count++;
				static const char chk[] PROGMEM="Check Count=";
				debug(chk,chk_count);
			}
		}while(chk_count>0);
		
		return false;
	}
	//______________________________________________________________________________________________________________________________________________________
	bool ESP8266::Send_To_Wifi(const char * str_cmd,const char * str_reply, unsigned int delay)
	{
		unsigned char bfr_tx[0xff];
		unsigned char rx[0xff];
		
		debug_divider();
		flash();
		Fill_Buffer(&bfr_tx[0],0,0xff);
		pgm2ram(str_cmd, &bfr_tx[0]);
			 
		if(Display_Debug_message)	debug(&bfr_tx[0]);
		puts_to_serial3(&bfr_tx[0]);
		sleep(delay);
		Get_rx_data(&rx[0]);
		if(Display_Debug_message) debug(&rx[0]);
		 
		if(String_found_in_bfr(str_reply,&rx[0],0xff,0)) 
		{
			//static const char reply_ok[] PROGMEM="Reply String found";
			//debug(reply_ok);
			return true;
		}
		else
		{
			if(Display_Debug_message)	debug(&bfr_tx[0]);
			static const char send_error[] PROGMEM="Command Send Error!!!!!";
			debug(send_error);
			return false;
		}
	}
	//________________________________________________________________________________________________________________________________________________________
	void ESP8266::Get_rx_data(unsigned char *bfr)
	{
		for(int i=0;i<0xff;i++)
		{
			*bfr=bfr_rx3[i];
			bfr++;
		}		
	}
	//________________________________________________________________________________________________________________________________________________________
	void ESP8266::send(unsigned char *bfr)
	{
		
		debug_divider();	
		static const char sending[] PROGMEM="Start Sending to wifi.....";
		debug(sending);
		
		unsigned char tx[20];
		Fill_Buffer(&tx[0],0,20);
		flash();
	
		static const char CIPSEND[] PROGMEM ="AT+CIPSEND=";
		pgm2ram(CIPSEND, &tx[0]);
		tx[11]=channel;
		tx[12]=',';
		////////////////////////////////////
	    int cmd_length=Get_length(bfr);
	
		if(cmd_length>99)
		{
		ConvertInt2Ascii(cmd_length,&tx[13],3,0);
		tx[16]='\r';
		tx[17]='\n';
		}
		else if(cmd_length>9)
		{
		ConvertInt2Ascii(cmd_length,&tx[13],2,0);
		tx[15]='\r';
		tx[16]='\n';
		}
		else
		{
		ConvertInt2Ascii(cmd_length,&tx[13],1,0);
		tx[14]='\r';
		tx[15]='\n';
		}
		/////////////////////////////////
		debug(tx);
		puts_to_serial3(tx);	
		sleep(100);

		unsigned char bfr_rx[0xff];
		Get_rx_data(&bfr_rx[0]);
		static const char prompt[] PROGMEM= ">";
		if(String_found_in_bfr(prompt,&bfr_rx[0],0xff,0))
		{
			static const char Prompt_Found[] PROGMEM= "Prompt Found";
			if(Display_Debug_message) debug(Prompt_Found);
			puts_to_serial3(bfr);
		}
		else
		{
			static const char Prompt_Not_Found[] PROGMEM= "Prompt Not Found";
			if(Display_Debug_message)	debug(Prompt_Not_Found);
		}
			sleep(10);

		static const char tx_done[] PROGMEM= "Transmit Done. Exited";
		if(Display_Debug_message)	debug(tx_done);
		flash();
	}	
	//_______________________________________________________________________________________________________________________________________________________________________
	void ESP8266::Led(unsigned char mode)
	{
		switch(mode)
		{
			case led_init:
						
						//unsigned int i;
						//connected=false;
						//present=false;
						//
						//LED_WIFI_GREEN_OFF;
						//LED_WIFI_BLUE_OFF;
						//LED_WIFI_RED_ON;
						//

			break;
			
			case led_module_present:
			break;
			
			case led_disconnect:
			break;
		
			
			default:
			break;
		}	
	}
	//______________________________________________________________________________________________________________________________________________
	
	
	
	
	
}// namespace hardware
#endif /* ESP8266_H_ */


 
 ////_____________________________________________________________________________________________________________________________________
 //ESP8266::ESP8266()
 //{ 	 
 //}
////________________________________________________________________________________________________________________________________________
//void ESP8266::setup(unsigned char port_no, long baud_rate, unsigned char led_red, unsigned char led_yellow, unsigned char led_green)
//{
	//port=port_no;
	//brd_esp.Serial_Setup(port_no,115200);	
	//flash_ESP8266();
	//Display_Debug_message=true;
	//
	//LED_R=led_red;
	//LED_Y=led_yellow;
	//LED_G=led_green;
	//
	//brd_esp.DO(LED_R);
	//brd_esp.DO(LED_Y);
	//brd_esp.DO(LED_G);	
	//
	//brd_esp.PIN_High(LED_R);
	//brd_esp.PIN_High(LED_Y);
	//brd_esp.PIN_High(LED_G);
//}
////________________________________________________________________________________________________________________________________________
//void ESP8266::Read(unsigned char val)
//{
	//bfr_rx[bfr_ptr_rx]=val;
	//bfr_ptr_rx++;
//}
////________________________________________________________________________________________________________________________________________
//void ESP8266::flash_ESP8266(void)
//{
	//present=false;
	//connected=false;
	//bfr_ptr_rx=0;
	//command_received=false;
	//hlp_esp.Fill_Buffer(&bfr_rx[0],0, bfr_count_esp);
	//hlp_esp.Fill_Buffer(&bfr_tx[0],0, bfr_count_esp);
//}	

	////_____________________________________________________________________________________________________________________________________________________
	
	
	//////________________________________________________________________________________________________________________________________________________________
	////void ESP_Power_Reset(void)
	////{
		////ESP_Power_Reset_PIN_HI;
		////sleep(1000);
		////ESP_Power_Reset_PIN_LO;
		////sleep(1000);
	////}
	//////________________________________________________________________________________________________________________________________________________________
	////void ESP_Hardware_Reset(void)
	////{
		////ESP_Hard_Reset_PIN_LO;
		////sleep(100);
		////ESP_Hard_Reset_PIN_HI;
		////sleep(100);
		////
		////
	////}
	//////________________________________________________________________________________________________________________________________________________________
	////unsigned char Init_ESP8266_Client(void)
	////{
		////
		////
		////
		////
		////
	////}
	//////___________________________________________________________________________________________________________________________________
	//////void Send_Wifi_Id_Password(void)
	//////{
	//////	unsigned int i,j;
	//////	unsigned char count,total;
	//////
	//////	Fill_Buffer(&wifi.bfr_data,0x00,30);
	//////	flash();
	//////
	//////	Send_Cmd_To_ESP8266("AT+CWSAP?",10000);
	//////
	//////	i=Find_And_Get_Position(":");					// 0x22= "(double quote)
	//////	j=Find_And_Get_Next_Pos(i,",");
	//////	count= ((j-2)-(i+1));
	//////
	//////
	//////	wifi.bfr_data[0]='<';
	//////	Copyram2ram(&com.bfr[i+1],&wifi.bfr_data[1],count);
	//////
	//////	count++;
	//////	wifi.bfr_data[count]='#';
	//////	count++;
	//////	total=count;
	//////
	//////	i=j;
	//////	j=Find_And_Get_Next_Pos(i,",");
	//////	count= ((j-2)-(i+1));
	//////
	//////	if(count!=0)
	//////	{
	//////		Copyram2ram(&com.bfr[i+1],&wifi.bfr_data[total],count);
	//////	}
	//////	total+=count;
	//////
	//////	wifi.bfr_data[total]='>';
	//////	total++;
	//////	//////////////////////////
	//////	flash();
	//////	Fill_Buffer(&wifi.bfr_To_Send,0, esp_bfr_count);
	//////	strcpypgm2ram(&wifi.bfr_To_Send,"AT+CIPSEND=X,X");	//chanel, data <99.678>
	//////	wifi.bfr_To_Send[11]=wifi.channel;
	//////
	//////	if(total<=9)
	//////	ConvertInt2Ascii(total,&wifi.bfr_To_Send[13],1,0);
	//////	else ConvertInt2Ascii(total,&wifi.bfr_To_Send[13],2,0);
	//////
	//////	send_cmd(&wifi.bfr_To_Send);
	//////	sleep(40);
	//////	if(found_in_comm_bfr(">"))
	//////		{
	//////			send_cmd_Without_Linefeed(&wifi.bfr_data);
	//////			sleep(10000);
	//////			if(found_in_comm_bfr("SEND OK"))
	//////			{
	//////				flash();
	//////				return;
	//////			}
	//////		}
	//////	else
	//////		{
	//////			flash();
	//////		}
	//////}
	////////------------------------------------------------
	//////void Set_Wifi_Id_Password(void)
	//////{
	//////	unsigned char i,j,count,total;
	//////
	//////	// set time out
	//////	Fill_Buffer(&wifi.bfr_To_Send,0, esp_bfr_count);
	//////	strcpypgm2ram(&wifi.bfr_To_Send,"AT+CWSAP=");	//chanel, data <99.678>
	//////	wifi.bfr_To_Send[9]='"';
	//////
	//////	i=Find_And_Get_Position("#");					// 0x22= "(double quote)
	//////	j=Find_And_Get_Next_Pos(i,"#");
	//////	count= ((j-1)-i);
	//////	Copyram2ram(&com.bfr[i],&wifi.bfr_To_Send[10],count);
	//////
	//////	total=10+count;
	//////	wifi.bfr_To_Send[total]='"';
	//////	total++;
	//////	wifi.bfr_To_Send[total]=',';
	//////	total++;
	//////	wifi.bfr_To_Send[total]='"';
	//////	total++;
	//////
	//////	i=Find_And_Get_Next_Pos(i,">");					// 0x22= "(double quote)
	//////
	//////	count= ((i-1)-j);
	//////	Copyram2ram(&com.bfr[j],&wifi.bfr_To_Send[total],count);
	//////
	//////	total +=count;
	//////
	//////	wifi.bfr_To_Send[total]='"';
	//////	total++;
	//////
	//////	wifi.bfr_To_Send[total]=',';
	//////	total++;
	//////
	//////	wifi.bfr_To_Send[total]='1';//wifi.channel;
	//////	total++;
	//////
	//////	wifi.bfr_To_Send[total]=',';
	//////	total++;
	//////
	//////	wifi.bfr_To_Send[total]='3';
	//////	total++;
	//////
	//////	wifi.bfr_To_Send[total]=NULL;
	//////
	//////	flash();
	//////	send_cmd(&wifi.bfr_To_Send);
	//////	sleep(1000);
	//////	if(found_in_comm_bfr("OK"))
	//////		{
	//////			 Send_OK();
	//////		}
	//////}
	////////------------------------------------------------
	//////void set_default_SSID_Password(void)
	//////{
	//////	unsigned int i;
	////////	i=0;
	////////	Init_ESP8266();
	//////
	////////	flash();
	////////	Fill_Buffer(&wifi.bfr_To_Send,0, esp_bfr_count);
	////////	strcpypgm2ram(&wifi.bfr_To_Send,"AT+CWSAP?");	//chanel, data <99.678>
	////////	flash();
	////////	send_cmd(&wifi.bfr_To_Send);
	////////	sleep(10000);
	//////
	//////	i=0;
	//////	Fill_Buffer(&wifi.bfr_To_Send,0, esp_bfr_count);
	//////	strcpypgm2ram(&wifi.bfr_To_Send,"AT+CWSAP=#pces#,#pces@1234#,1,3");	//chanel, data <99.678>
	//////	Replace_Hash_To_Double_Quotation(&wifi.bfr_To_Send);
	//////
	//////	flash();
	//////	send_cmd(&wifi.bfr_To_Send);
	//////	sleep(10000);
	//////}
	////////------------------------------------------------
//
//
//
//
//
//
