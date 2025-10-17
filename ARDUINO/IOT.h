#ifndef IOT_H_
#define IOT_H_

#include "\ArduinoEasy\SOFTWARE\COMMON\IOT\ThingSpeak.h"

namespace Tools
{
	class IOT:public ESP8266, public helper, public ThingSpeak
	{
		public:
		unsigned char serial_port_no=3;
		long baud_rate=115200;
		bool debug_enable=true;
		
		const char* ip_address;
		int socket_port=502;
		bool request_received=false;
		
		bool connected_with_server=false;
				
		IOT();
		void start(void);
		void start(unsigned char port_no);
		void start(unsigned char port_no, const char *ipaddress,int socket_port);
		void Update(unsigned char field_index, unsigned int val);
		//
		//unsigned char Update(unsigned char field_index,unsigned int val);
		//unsigned char Update_Field(const char *WriteKey, const char *field_name,unsigned char *bfr_val);
		
		private:
			
		protected:
	};// class IOT
	
	//______________________________________________________________________________________________________________________________
	IOT::IOT()
	{
				
	}
	//______________________________________________________________________________________________________________________________	
	void IOT::start(unsigned char port_no)
	{
		
		
	}
	//______________________________________________________________________________________________________________________________
	void IOT::start(void)
	{	
		if(connected_with_server==true) return;
		unsigned char bfr[0xff];	
		//static const char id[] PROGMEM="Sudip.embedded";
		//static const char id[] PROGMEM="Dr. Sudip's samsung Galaxy A30";
		static const char id[] PROGMEM="ArduinoEasy";
		static const char password[] PROGMEM="sudip123";
		start_client(id,password);
		if(connected_with_router)
		{
			sleep(50000);
			unsigned char con_str[0xff];
			Get_server_connection_string(&con_str[0]);
			debug(&con_str[0]);
			Not_Responseded(&con_str[0],1000,100);
			
			Fill_Buffer(&bfr[0],0,0xff);
			Get_rx_data(&bfr[0]);
			
			static const char OK[] PROGMEM="OK";
			if(String_found_in_bfr(OK,&bfr[0],0xff,0))
			{
				static const char connect_with_thingspeak[] PROGMEM="Connected With ThingSpeak Server...";
				debug(connect_with_thingspeak);
				connected_with_server=true;
				sleep(50000);
			}
			else
			{
				static const char Not_connect_with_thingspeak[] PROGMEM="ERROR:Unable to Connected With ThingSpeak Server";
				debug(Not_connect_with_thingspeak);	
				connected_with_server=false;		
			}		
		}		
	}
	//______________________________________________________________________________________________________________________________
	void IOT::Update(unsigned char field_index, unsigned int val)
	{
		if(!connected_with_server) start();
		
		
		if(connected_with_server==false)
		{
			static const char unable_to_send[] PROGMEM="ERROR: Unable to send. Not Connected with Server";
			debug(unable_to_send);
			return;
		}
		
		unsigned char bfr[0xff];		
		Get_Update_String(field_index,val, &bfr[0]);
		sleep(50000);

		debug(&bfr[0]);
		Not_Responseded(&bfr[0],1000,100);
		
		Fill_Buffer(&bfr[0],0,0xff);
		Get_rx_data(&bfr[0]);
		debug(&bfr[0]);
		
		static const char OK[] PROGMEM="OK";
		if(String_found_in_bfr(OK,&bfr[0],0xff,0))
		{
			static const char send_to_thingspeak_ok[] PROGMEM="Send Data to Thingspeak server successfully";
			debug(send_to_thingspeak_ok);
		}
		else
		{
			static const char Not_send_to_thingspeak[] PROGMEM="ERROR:Unable to Send Data to Thingspeak server";
			debug(Not_send_to_thingspeak);
			
		}		
	}
	//______________________________________________________________________________________________________________________________ 
	
}// namespace
	
	#endif