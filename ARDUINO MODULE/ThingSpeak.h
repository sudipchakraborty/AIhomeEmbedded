// #ifndef THINGSPEAK_H_
// #define THINGSPEAK_H_

// namespace Tools
// {
	
// class ThingSpeak: public helper,public SERIAL,public BOARD
// {
// 	public:
// 		ThingSpeak();
// 		void Get_server_connection_string(unsigned char *dst_ptr);
// 		void Get_Update_String(unsigned char field_index,unsigned int val, unsigned char *dst_bfr);
	
// 	private:
	
	
	
// 	protected:
	
		
	
	
// };// class ThingSpeak
// //__________________________________________________________________________________________________________________________________________________		
// ThingSpeak::ThingSpeak()
// {	
	
// }
// //________________________________________________________________________________________________________________
// void ThingSpeak::Get_server_connection_string(unsigned char *dst_ptr)
// 	{
// 		unsigned char bfr[0xff];
// 		Fill_Buffer(&bfr[0],0,0xff);

// 		static const char AT_plus_CIPSTART[] PROGMEM="AT+CIPSTART=";
	
// 		pgm2ram(AT_plus_CIPSTART,&bfr[0]);
// 		bfr[12]='"';
	
// 		bfr[13]='T'; bfr[14]='C'; bfr[15]='P'; bfr[16]='"'; bfr[17]=',';bfr[18]='"';
	
// 		static const char thinsspeak[] PROGMEM="api.thingspeak.com";	//;"184.106,153.149"
// 		pgm2ram(thinsspeak,&bfr[19]);
	
// 		bfr[37]='"'; bfr[38]=','; bfr[39]='8'; bfr[40]='0';	bfr[41]='\r';	bfr[42]='\n';	//api.thingspeak.com";
// 		//bfr[34]='"'; bfr[35]=','; bfr[36]='8'; bfr[37]='0';	bfr[38]='\r';	bfr[39]='\n';		// "184.106,153.149";	
// 		Copyram2ram(&bfr[0],dst_ptr,0xff);		
// 	}  
// //__________________________________________________________________________________________________________________________________________________
// 	void ThingSpeak::Get_Update_String(unsigned char field_index,unsigned int val, unsigned char *dst_bfr)
// 	{
// 		//GET/update?api_key=28MK9XLOC4YNIQDF&field1=0.3
		
// 		static const char WriteKey[] PROGMEM="28MK9XLOC4YNIQDF";
// 		static const char field[] PROGMEM="&field";
		
// 		unsigned char bfr[0xff];
// 		Fill_Buffer(&bfr[0],0,0xff);
		
// 		static const char preamble[] PROGMEM="GET/update?api_key=";
		
// 		pgm2ram(preamble,&bfr[0]);
// 		pgm2ram(WriteKey,&bfr[19]);
		
// 		int p=Get_length(WriteKey);		
// 		pgm2ram(field,&bfr[19+p]);
				
// 		int q=Get_length(field);
// 		int bfr_idx=19+p+q;
		
// 		if(field_index<10)
// 		{
// 			ConvertInt2Ascii(field_index,&bfr[bfr_idx],1,0);
// 			bfr_idx++;
// 		}
// 		else
// 		{
// 			ConvertInt2Ascii(field_index,&bfr[p+q+1],2,0);
// 			bfr_idx +=2;
// 		}
		
// 		bfr[bfr_idx]='=';
// 		bfr_idx++;
		
// 		ConvertInt2Ascii(val,&bfr[bfr_idx],3,0);	bfr_idx +=3;

// 		 bfr[bfr_idx]='\r';		bfr_idx++;
// 		 bfr[bfr_idx]='\n';		bfr_idx++;
// 		 bfr[bfr_idx]='\r';		bfr_idx++;
// 		 bfr[bfr_idx]='\n';
		 
// 		 Copyram2ram(&bfr[0], dst_bfr);
// 	}
// //_____________________________________________________________________________________________________________________________________________________
	
	
	
	  
	  
	  
	  
	  
	  
	  
	  
	
// }// namespace Tools

// #endif


// //unsigned char ESP8266::Update_Field(const char *WriteKey, const char *field_name,unsigned char *bfr_val)
// //{
// ////GET/update?api_key=28MK9XLOC4YNIQDF&field1=0.3
// //
// //unsigned char bfr[0xff];
// //Fill_Buffer(&bfr[0],0,0xff);
// //
// //static const char preamble[] PROGMEM="GET/update?api_key=";
// //
// //pgm2ram(preamble,&bfr[0]);
// //pgm2ram(WriteKey,&bfr[19]);
// //
// //int p=Get_length(WriteKey);
// //bfr[19+p]='&';
// //
// //pgm2ram(field_name,&bfr[19+p+1]);
// //int q=Get_length(field_name);
// //bfr[19+p+1+q]='=';
// //Copyram2ram(bfr_val, &bfr[19+p+1+q+1]);
// //
// //int r=Get_length(bfr_val);
// //bfr[19+p+1+q+1+r+0]='\r';
// //bfr[19+p+1+q+1+r+1]='\n';
// //bfr[19+p+1+q+1+r+2]='\r';
// //bfr[19+p+1+q+1+r+3]='\n';
// //
// //debug(&bfr[0]);
// //}
// ////_____________________________________________________________________________________________________________________________________________________
// //bool ESP8266::Not_Connected_With_Thingspeak_Webserver(void)
// //{
// //unsigned char bfr[0xff];
// //Fill_Buffer(&bfr[0],0,0xff);
// //flash();
// //static const char AT_plus_CIPSTART[] PROGMEM="AT+CIPSTART=";
// //
// //pgm2ram(AT_plus_CIPSTART,&bfr[0]);
// //bfr[12]='"';
// //
// //bfr[13]='T'; bfr[14]='C'; bfr[15]='P'; bfr[16]='"'; bfr[17]=',';bfr[18]='"';
// //
// //static const char thinsspeak[] PROGMEM="api.thingspeak.com";	//;"184.106,153.149"
// //pgm2ram(thinsspeak,&bfr[19]);
// //
// //bfr[37]='"'; bfr[38]=','; bfr[39]='8'; bfr[40]='0';	bfr[41]='\r';	bfr[42]='\n';	//api.thingspeak.com";
// ////bfr[34]='"'; bfr[35]=','; bfr[36]='8'; bfr[37]='0';	bfr[38]='\r';	bfr[39]='\n';		// "184.106,153.149";
// //
// //debug(&bfr[0]);
// //if(Not_Responseded(&bfr[0],10000,100)) return false;
// //////============  Conected with things speak server
// ////
// ////while(1)
// ////{
// ////Get_rx_data(&b[0]);
// ////debug(&b[0]);
// ////sleep(1000);
// ////}
// ////
// //////=====================================
// ////ERROR
// ////AT+CIPSTART="TCP","ap1.thingspeak.com",80
// ////DNS Fail
// ////
// ////ERROR
// ////AT+CIPSTART="TCP","184.106,153.149",80
// ////DNS Fail
// //
// ////WIFI CONNECTED
// ////WIFI GOT IP
// ////
// ////OK
// ////WIFI DISCONNECT
// ////+CWJAP:3
// ////
// ////
// ////OK
// ////
// ////OK
// ////WIFI DISCONNECT
// ////+CWJAP:3
// ////
// ////FAIL
// //}
// ////_________________________________________________________________________________________________________________________________________________
// //void ESP8266::Send_Request_To_ThingSpeak_Server(void)
// //{
// //////String getStr = "GET /update?api_key=";         // prepare GET string
// //////
// //////getStr += apiKey;
// //////
// //////getStr +="&field1=";
// //////
// //////getStr += String(state1);                       // Humidity Data
// //////
// //////getStr +="&field2=";
// //////
// //////getStr += String(state2);                       // Temperature Data
// //////
// //////getStr += "\r\n\r\n";
// //////
// //////cmd = "AT+CIPSEND=";
// //////
// //////cmd += String(getStr.length());                // Total Length of data
// //////
// //////ser.println(cmd);
// //////
// //////Serial.println(cmd);
// //////
// //////
// //////
// //////if(ser.find(">")){
// //////
// //////ser.print(getStr);
// //////
// //////Serial.print(getStr);
// //////
// //////}
// //////
// //////else{
// //////
// //////ser.println("AT+CIPCLOSE");                  // closing connection
// //////
// //////// alert user
// //////
// //////Serial.println("AT+CIPCLOSE");
// //////
// //////}
// //////
// //////delay(1000);                                  // Update after every 15 seconds
// //////
// //////}
// //////
// //////
// //////
// //}
// ////_________________________________________________________________________________________________________________________________________________
// //
// //
// //
// //
// //
// //
// //
// //
// //
// //
// //
// //
// //
// //
// //
// //
// //
// //
// //
// //
// //
// //
// //}// namespace Tools
// //#endif /* IOT_H_ */
// //
// //
// //
// //
// //
// //
// //
// ////
// ////
// ////
// ////// write Key 28MK9XLOC4YNIQDF
// ////// read key X3B6ZTK8GOMFTOMW
// ////// Channel ID: 635588
// ////// Temperature, Voltage, current
// ////
// //////Update a Channel Feed
// //////GET https://api.thingspeak.com/update?api_key=28MK9XLOC4YNIQDF&field1=0
// ////
// //////Get a Channel Feed
// //////GET https://api.thingspeak.com/channels/635588/feeds.json?results=2
// ////
// //////Get a Channel Field
// //////GET https://api.thingspeak.com/channels/635588/fields/1.json?results=2
// //////
// //////Get Channel Status Updates
// //////GET https://api.thingspeak.com/channels/635588/status.json
// ////
// ////
// ////
// ////void Init_IOT(void);
// //////______________________________________________________________________________________________________________________________________________________
// ////struct IOT
// ////{
// ////unsigned char val;
// ////};
// //////______________________________________________________________________________________________________________________________________________________
// ////
// ////
// ////
// //////
// //////
// //////
// //////w.connect("184.106.153.149", 80);
// //////if (!w.connected)
// //////{
// //////timer_live.Enabled = false;
// //////MessageBox.Show("Wifi Connection Error. Please Check the Connection...!!!!");
// //////return;
// //////}
// //////
// //////string temp = "";
// /////////////// read l.v> read voltage////////////////////
// ////////   System.Threading.Thread.Sleep(100);
// //////byte[] bfr;
// //////bfr = w.WriteSyncData_bfr_byte("GET /update?api_key=28MK9XLOC4YNIQDF&field1=1000\r\n\r\n");
// //////// trigger relay
// //////if (bfr != null)
// //////{
// //////temp = System.Text.Encoding.UTF8.GetString(bfr);
// //////Purse_Voltage_IC1(temp);
// //////populate_voltage();
// //////}
// ////
// ////
// ////
// ////
// ////
// ////
// ////
// ////
// ////
// ////
// ////
// //
// //
// //
// //
// //
// //
// ////#include <avr/io.h>
// ////#include "main.h"
// ////#include "BIOS2560.h"
// ////#include <avr/interrupt.h>
// ////#include "global.h"
// ////#include "Helper.h"
// ////#include "IOT.h"
// ////
// ////
// ////
// //////____________________________________________________________________________________________________________________________________________________________
// ////struct IOT			iot;
// ////
// ////
// ////
// //////____________________________________________________________________________________________________________________________________________________________
// ////void Init_IOT(void)
// ////{
// ////
// ////
// ////
// ////
// ////
// ////
// ////}
// //////____________________________________________________________________________________________________________________________________________________________
// ////
// ////
// //////
// //////
// //////#include "DHT.h"
// //////
// //////#include
// //////
// //////#define DHTPIN 5                       // Digital Pin 5
// //////
// //////#define DHTTYPE DHT11                  // We are Using DHT11
// //////
// //////String apiKey = "OX9T8Y9OL9HD0UBP";    // Edit this API key according to your Account
// //////
// //////String Host_Name = "Pantech";         // Edit Host_Name
// //////
// //////String Password = "pantech123";          // Edit Password
// //////
// //////SoftwareSerial ser(2, 3);              // RX, TX
// //////
// //////int i=1;
// //////
// //////DHT dht(DHTPIN, DHTTYPE);              // Initialising Pin and Type of DHT
// //////
// //////void setup() {
// //////
// //////Serial.begin(115200);                  // enable software serial
// //////
// //////ser.begin(115200);                     // reset ESP8266
// //////
// //////ser.println("AT+RST");               // Resetting ESP8266
// //////
// //////dht.begin();                        // Enabling DHT11
// //////
// //////char inv ='"';
// //////
// //////String cmd = "AT+CWJAP";
// //////
// //////cmd+= "=";
// //////
// //////cmd+= inv;
// //////
// //////cmd+= Host_Name;
// //////
// //////cmd+= inv;
// //////
// //////cmd+= ",";
// //////
// //////cmd+= inv;
// //////
// //////cmd+= Password;
// //////
// //////cmd+= inv;
// //////
// //////ser.println(cmd);                    // Connecting ESP8266 to your WiFi Router
// //////
// //////}
// //////
// //////// the loop
// //////
// //////void loop() {
// //////
// //////int humidity =  dht.readHumidity();             // Reading Humidity Value
// //////
// //////int temperature = dht.readTemperature();        // Reading Temperature Value
// //////
// //////String state1=String(humidity);                 // Converting them to string
// //////
// //////String state2=String(temperature);              // as to send it through URL
// //////
// //////
// //////
// //////String cmd = "AT+CIPSTART=\"TCP\",\"";          // Establishing TCP connection
// //////
// //////cmd += "184.106.153.149";                       // api.thingspeak.com
// //////
// //////cmd += "\",80";                                 // port 80
// //////
// //////ser.println(cmd);
// //////
// //////Serial.println(cmd);
// //////
// //////if(ser.find("Error")){
// //////
// //////Serial.println("AT+CIPSTART error");
// //////
// //////return;
// //////
// //////}
// //////
// //////String getStr = "GET /update?api_key=";         // prepare GET string
// //////
// //////getStr += apiKey;
// //////
// //////getStr +="&field1=";
// //////
// //////getStr += String(state1);                       // Humidity Data
// //////
// //////getStr +="&field2=";
// //////
// //////getStr += String(state2);                       // Temperature Data
// //////
// //////getStr += "\r\n\r\n";
// //////
// //////cmd = "AT+CIPSEND=";
// //////
// //////cmd += String(getStr.length());                // Total Length of data
// //////
// //////ser.println(cmd);
// //////
// //////Serial.println(cmd);
// //////
// //////
// //////
// //////if(ser.find(">")){
// //////
// //////ser.print(getStr);
// //////
// //////Serial.print(getStr);
// //////
// //////}
// //////
// //////else{
// //////
// //////ser.println("AT+CIPCLOSE");                  // closing connection
// //////
// //////// alert user
// //////
// //////Serial.println("AT+CIPCLOSE");
// //////
// //////}
// //////
// //////delay(1000);                                  // Update after every 15 seconds
// //////
// //////}
// //////
// //////
// //////
