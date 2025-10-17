
// #include <avr/io.h>
// #include <util/delay.h>
// #include <avr/wdt.h>
// #include <avr/pgmspace.h>

// namespace Tools
// {
// 	class helper
// {
// 	public:
// 		static void ConvertInt2Ascii(unsigned int val,unsigned char *destptr,unsigned char digitcount,unsigned char DecimalPlace);
// 		static unsigned int ConvertAscii2Decimal(unsigned char *srcptr,unsigned char count, unsigned char DecimalPlace);
// 		static unsigned int ConvertAscii2Decimal(unsigned char *srcptr,unsigned char count);
// 		static void Fill_Buffer(unsigned char *srcptr,unsigned char data, unsigned int count);
// 		static void pgm2ram(const char * str, unsigned char *bfr);
// 		static void ConvertBCD2Ascii(unsigned char val, unsigned char *destptr);
// 		static unsigned char ConvertAscii2BCD(unsigned char *srcptr);	
		
// 		static unsigned char Index_Of(unsigned char *bfr, unsigned char find_char, unsigned int bfr_count);
// 		static unsigned char Index_Of(unsigned char *bfr, unsigned char find_char, unsigned int bfr_count, unsigned char start_index);
// 		static unsigned char Index_Of(const char * str, unsigned char *bfr, unsigned int bfr_count, unsigned char StartIndex);	
		
// 		static void load_sample_string(unsigned char *bfr);
// 		static void Get_random_bfr(unsigned char *bfr, unsigned char count);
		
// 		static unsigned char String_found_in_bfr(const char * str, unsigned char *bfr, unsigned char bfr_count, unsigned char StartIndex);
// 		static unsigned char CompareRam2Ram_OK(unsigned char *cmpptr1, unsigned char *cpmptr2,unsigned char count);
// 		static unsigned char Get_length(unsigned char *bfr);
// 		static unsigned char Get_length(const char * str);
		
// 		static void Copyram2ram( unsigned char *src,unsigned char *dest, unsigned int count);
// 		static void Copyram2ram( unsigned char *src,unsigned char *dest);
// 	private:

// };
 

// //_____________________________________________________________________________________________________________________________
//  void helper::ConvertInt2Ascii(unsigned int val,unsigned char *destptr,unsigned char digitcount,unsigned char DecimalPlace)
// {
// 	unsigned int j;

// 	if(digitcount==5)
// 	{
// 		*destptr=(val/10000)|0x30;
// 		//*destptr=(val/10000);
// 		destptr++;
// 		digitcount--;
// 	}
	
// 	j=val%10000;

// 	if(digitcount==4)
// 	{
// 		*destptr=(j/1000)|0x30;
// 		//*destptr=(j/1000);
// 		destptr++;
// 		digitcount--;
// 	}

// 	j=j%1000;

// 	if(digitcount==3)
// 	{
// 		*destptr=(j/100)|0x30;
// 		//*destptr=(j/100);
// 		destptr++;
// 		digitcount--;
// 	}
// 	j=j%100;
	

// 	if(digitcount==2)
// 	{
// 		if(DecimalPlace==2)
// 		{
// 			*destptr='.';
// 			destptr++;
// 		}
// 		*destptr=(j/10)|0x30;
// 		//*destptr=(j/10);
// 		destptr++;
// 		digitcount--;
// 	}
	
// 	if(DecimalPlace==1)
// 	{
// 		*destptr='.';
// 		destptr++;
// 	}
	
// 	*destptr=(j%10)|0x30;
// 	//*destptr=(j%10);
// }
// ////------------------------------------------------------------------------------------------
// unsigned int helper::ConvertAscii2Decimal(unsigned char *srcptr,unsigned char count, unsigned char DecimalPlace)
// {
// 	unsigned int temp; 
// 	unsigned char k;
// 	unsigned int temp2;
// 	temp=0;

// 	if(count==5)
// 	{
// 		k=*srcptr;
// 		k=k&0x0f;
// 		temp=k*10000.0;
// 		srcptr++;
// 		count--;
// 	}

// 	if(count==4)
// 	{
// 		k=*srcptr;
// 		k=k&0x0f;
// 		temp=temp+(k*1000.0);
// 		srcptr++;
// 		count--;
// 	}

// 	if(count==3)
// 	{
// 		k=*srcptr;
// 		k=k&0x0f;
// 		temp2=k *100.0;
// 		temp=temp+temp2;
// 		srcptr++;
// 		count--;
// 	}

// 	if(count==2)
// 	{
// 		if(DecimalPlace==2)srcptr++;
// 		k=*srcptr;
// 		k=k&0x0f;
// 		temp2=k*10.0;
// 		temp=temp+temp2;
// 		srcptr++;
// 		count--;
// 	}
	
// 	if(DecimalPlace==1)	srcptr++;

// 	k=*srcptr;
// 	k=k&0x0f;
// 	temp=temp+k;

// 	return temp;
// }
// //__________________________________________________________________________________________________
// unsigned int helper::ConvertAscii2Decimal(unsigned char *srcptr,unsigned char count)
// {
// 	unsigned int temp;
// 	unsigned char k;
// 	unsigned int temp2;
// 	temp=0;

// 	if(count==5)
// 	{
// 		k=*srcptr;
// 		k=k&0x0f;
// 		temp=k*10000.0;
// 		srcptr++;
// 		count--;
// 	}

// 	if(count==4)
// 	{
// 		k=*srcptr;
// 		k=k&0x0f;
// 		temp=temp+(k*1000.0);
// 		srcptr++;
// 		count--;
// 	}

// 	if(count==3)
// 	{
// 		k=*srcptr;
// 		k=k&0x0f;
// 		temp2=k *100.0;
// 		temp=temp+temp2;
// 		srcptr++;
// 		count--;
// 	}

// 	if(count==2)
// 	{
// 		k=*srcptr;
// 		k=k&0x0f;
// 		temp2=k*10.0;
// 		temp=temp+temp2;
// 		srcptr++;
// 		count--;
// 	}

// 	k=*srcptr;
// 	k=k&0x0f;
// 	temp=temp+k;

// 	return temp;
// }
// //__________________________________________________________________________________________________
// void helper::Fill_Buffer(unsigned char *srcptr,unsigned char data, unsigned int count)
// {
// 	do{
// 		*srcptr=data;
// 		count--;
// 		srcptr++;
// 	}while(count!=0);
// }
// //_______________________________________________________________________________________________
// void helper::pgm2ram(const char * str, unsigned char *bfr)
// {
// 	while ((*bfr= pgm_read_byte(str++)))
// 	bfr++;
// }
// //_______________________________________________________________________________________________
// void helper::ConvertBCD2Ascii(unsigned char val, unsigned char *destptr)
// {
// 	*(destptr+1)=(val&0x0f)|0x30;
// 	val=val>>4;
// 	*destptr=(val&0x0f)|0x30;
// }
// //_______________________________________________________________________________________________
// unsigned char helper::ConvertAscii2BCD(unsigned char *srcptr)
// {
// register unsigned char i;
// i=*srcptr & 0x0f;
// i=i<<4;
// srcptr++;
// i=i|(*srcptr&0x0f);
// return i;
// }
// //________________________________________________________________________________________________
// unsigned char helper::Index_Of(unsigned char *bfr, unsigned char find_char, unsigned int bfr_count)
// {
// 	unsigned char bfr_str[50];
// 	unsigned char len;

// 	for(unsigned int i=0;i<bfr_count;i++)
// 	{
// 		if(*(bfr+i)==find_char)
// 		{			
// 			return i;
// 		}
// 	}
// 	return -1;
// }
// //________________________________________________________________________________________________________________________________
// unsigned char helper::Index_Of(unsigned char *bfr, unsigned char find_char, unsigned int bfr_count, unsigned char start_index)
// {
// 	unsigned char bfr_str[50];
// 	unsigned char len;

// 	for(unsigned int i=start_index;i<bfr_count;i++)
// 	{
// 		if(*(bfr+i)==find_char)
// 		{
// 			return i;
// 		}
// 	}
// 	return -1;
// }
// //________________________________________________________________________________________________________________________________
// unsigned char helper::Index_Of(const char * str, unsigned char *bfr, unsigned int bfr_count, unsigned char StartIndex)
// {
// 	unsigned char bfr_str[50];
// 	unsigned char len;
// //
// 	//Fill_Buffer(&bfr_str[0],0x00, 50);
// 	//pgm2ram(str,&bfr_str[0]);
// 	//len=Get_length(&bfr_str[0]);
// //
// 	//for(unsigned int i=StartIndex;i<=bfr_count-len;i++)
// 	//{
// 		//if(CompareRam2Ram_OK(&bfr_str[0], &bfr[i],len))
// 		//{
// 			//ret_val=i+len;
// 			//return i+len;
// 		//}
// 	//}
// 	//return -1;
// }
// //________________________________________________________________________________________________________________________________
// void helper::load_sample_string(unsigned char *bfr)
// {
// 	static const char sample_string[] PROGMEM = "<WELCOME TO EMBEDDED";
// 	pgm2ram(sample_string,bfr);	
// }
// //________________________________________________________________________________________________________________________________
// void helper::Get_random_bfr(unsigned char *bfr, unsigned char count)
// {
// 	unsigned char rand=0;
// 	for(int i=0;i<count;i++)
// 	{
// 		rand=(rand*109+89)%251;
// 		*bfr=rand;
// 		bfr++;
// 	}
// }
// //_________________________________________________________________________________________________________________________________
// unsigned char helper::String_found_in_bfr(const char * str, unsigned char *bfr, unsigned char bfr_count, unsigned char StartIndex)
// {
// 	unsigned char bfr_str[50];
// 	unsigned char len;

// 	Fill_Buffer(&bfr_str[0],0x00, 50);
// 	pgm2ram(str,&bfr_str[0]);
// 	len=Get_length(&bfr_str[0]);

// 	for(unsigned int i=StartIndex;i<=bfr_count-len;i++)
// 	{
// 		if(CompareRam2Ram_OK(&bfr_str[0], &bfr[i],len))
// 		{
// 			return true;
// 		}
// 	}
// 	return false;
// }
// //__________________________________________________________________________________________________________________________________________________________
// unsigned char helper::CompareRam2Ram_OK(unsigned char *cmpptr1, unsigned char *cpmptr2,unsigned char count)
// {
// register unsigned char j;
// j=0;
// do{
// if(*cmpptr1!=*cpmptr2)	//
// {
// return false;
// }
// cmpptr1++;
// cpmptr2++;
// j++;
// }while(j!=count);
// return true;
// }
// //____________________________________________________________________________________________________________________________________________
// unsigned char helper::Get_length(unsigned char *bfr)
// {
// unsigned char count=0;
// unsigned char exit=false;

// do{
// 	if(*bfr == 0x00)
// 	{
// 		exit=true;
// 	}
// 	else
// 	{
// 		count++;
// 		bfr++;
// 	}
// }while(exit==false);
// return count;
// }
// //____________________________________________________________________________________________________________________________________________
// unsigned char helper::Get_length(const char * str)
// {
// 	unsigned char val;
// 	unsigned char bfr[0xff];
// 	Fill_Buffer(&bfr[0],0,0xff);
	
// 	unsigned char i=0;

// 	while (bfr[i]= pgm_read_byte(str++))
// 	i++;
// 	val=Get_length(&bfr[0]);
// 	return val;
// }
// //____________________________________________________________________________________________________________________________________________
// void  helper::Copyram2ram( unsigned char *src,unsigned char *dest, unsigned int count)
// {
// 	unsigned int 	i;
// 	i=0;
// 	do
// 	{
// 		*dest=*src;
// 		dest++;
// 		src++;
// 		i++;
// 	}while(i<count);
// }
// //_____________________________________________________________________________________________________________________________________________
// void  helper::Copyram2ram( unsigned char *src,unsigned char *dest)
// {
// 	unsigned int 	i;
// 	i=0;
// 	do
// 	{
// 		*dest=*src;
// 		dest++;
// 		src++;
// 		i++;
// 	}while(*src !=0);
// }
// //_____________________________________________________________________________________________________________________________________________





// //
// //
// //
// //
// //
// //#include "Helper.h"
// //#include "avr/io.h"
// //#include "global.h"
// //#include "BIOS2560.h"
// //
// ////____________________________________________________________________________________________________________________________________________
//  //void ConvertInt2Ascii(unsigned int val,unsigned char *destptr,unsigned char digitcount,unsigned char DecimalPlace)
// //{
// 	//unsigned int j;
// //
// 	//if(digitcount==5)
// 	//{
// 		//*destptr=(val/10000)|0x30;
// 		////*destptr=(val/10000);
// 		//destptr++;
// 		//digitcount--;
// 	//}
// 	//
// 	//j=val%10000;
// //
// 	//if(digitcount==4)
// 	//{
// 		//if(DecimalPlace==4)
// 		//{
// 			//*destptr='.';
// 			//destptr++;
// 		//}
// 		//
// 		//*destptr=(j/1000)|0x30;
// 		////*destptr=(j/1000);
// 		//destptr++;
// 		//digitcount--;
// 	//}
// //
// 	//j=j%1000;
// //
// 	//if(digitcount==3)
// 	//{
// 		//if(DecimalPlace==3)
// 		//{
// 			//*destptr='.';
// 			//destptr++;
// 		//}
// 		//
// 		//*destptr=(j/100)|0x30;
// 		////*destptr=(j/100);
// 		//destptr++;
// 		//digitcount--;
// 	//}
// 	//j=j%100;
// 	//
// //
// 	//if(digitcount==2)
// 	//{
// 		//
// 		//if(DecimalPlace==2)
// 		//{
// 			//*destptr='.';
// 			//destptr++;
// 		//}
// 		//*destptr=(j/10)|0x30;
// 		////*destptr=(j/10);
// 		//destptr++;
// 		//digitcount--;
// 	//}
// 	//
// 	//if(DecimalPlace==1)
// 	//{
// 		//*destptr='.';
// 		//destptr++;
// 	//}
// 	//
// 	//*destptr=(j%10)|0x30;
// 	////*destptr=(j%10);
// //}
// ////__________________________________________________________________________________________________________________________________________
// //void Fill_Buffer(unsigned char *srcptr,unsigned char data, unsigned int count)
// //{
// 	//do{
// 		//*srcptr=data;
// 		//count--;
// 		//srcptr++;
// 	//}while(count!=0);
// //}
// ////__________________________________________________________________________________________________________________________________________
// //void ConvertByte2Ascii(unsigned char val,unsigned char *destptr,unsigned char digitcount,unsigned char DecimalPlace)
// //{
// 	//unsigned char j;
// //
// 	//if(digitcount==3)
// 	//{
// 		//*destptr=(val/100)|0x30;
// 		//destptr++;
// 		//digitcount--;
// 	//}
// 	//j=val%100;
// //
// 	//if(digitcount==2)
// 	//{
// 		//if(DecimalPlace==2)
// 		//{
// 			//*destptr='.';
// 			//destptr++;
// 		//}
// 		//*destptr=(j/10)|0x30;
// 		//destptr++;
// 		//digitcount--;
// 	//}
// //
// 	//if(DecimalPlace==1)
// 	//{
// 		//*destptr='.';
// 		//destptr++;
// 	//}
// 	//*destptr=(j%10)|0x30;
// //}
// ////_______________________________________________________________________________________________________________________________________________
// //unsigned int ConvertAscii2Decimal(unsigned char *srcptr,unsigned char count, unsigned char DecimalPlace)
// //{
// 	//unsigned int temp;
// 	//unsigned char k;
// 	//unsigned int temp2;
// 	//temp=0;
// //
// 	//if(count==5)
// 	//{
// 		//k=*srcptr;
// 		//k=k&0x0f;
// 		//temp=k*10000.0;
// 		//
// 		//if(DecimalPlace==4)	
// 		//{
// 			//srcptr++;
// 			//srcptr++;
// 		//}
// 		//else
// 		//{
// 			//srcptr++;		
// 		//}
// 		//count--;
// 	//}
// 	////////////////////////////////
// 	//
// 	//
// 	////////////////////////////////
// 	//if(count==4)
// 	//{
// 		//k=*srcptr;
// 		//k=k&0x0f;
// 		//temp=temp+(k*1000.0);
// 		//
// 		//if(DecimalPlace==3)
// 		//{
// 			//srcptr++;
// 			//srcptr++;
// 		//}
// 		//else	
// 		//{
// 			//srcptr++;
// 		//}			
// 		//count--;
// 	//}
// 	///////////////////////////////
// 	//
// 	//
// 	////////////////////////////////
// 	//if(count==3)
// 	//{
// 		//k=*srcptr;
// 		//k=k&0x0f;
// 		//temp2=k *100.0;
// 		//temp=temp+temp2;
// 		//
// 		//if(DecimalPlace==2)	
// 		//{
// 			//srcptr++;
// 			//srcptr++;
// 		//}
// 		//else
// 		//{
// 			//srcptr++;			
// 		//}
// 		//count--;
// 	//}
// 	///////////////////////////////
// 	//
// 	//if(count==2)
// 	//{
// 		//k=*srcptr;
// 		//k=k&0x0f;
// 		//temp2=k*10.0;
// 		//temp=temp+temp2;
// 		//
// 		//if(DecimalPlace==1)	
// 		//{
// 			//srcptr++;
// 			//srcptr++;
// 		//}
// 		//else
// 		//{
// 			//srcptr++;			
// 		//}
// 	//}
// 	//////////////////////	 
// //
// 	//k=*srcptr;
// 	//k=k&0x0f;
// 	//temp=temp+k;
// //
// 	//return temp;
// //}
// ////_______________________________________________________________________________________________________________________________________________

// ////____________________________________________________________________________________________________________________________________________
// //unsigned int Get_Uint16_From_Byte(unsigned char Hi_Byte, unsigned char Lo_Byte)
// //{
// 	//unsigned int result;
// 	//result=	Hi_Byte;
// 	//result=result<<8;
// 	//result |=Lo_Byte;
// 	//return result;
// //}
// ////____________________________________________________________________________________________________________________________________________
// //int Get_int16_From_Byte(unsigned char Hi_Byte, unsigned char Lo_Byte)
// //{
// 	//int result;
// 	//result=	Hi_Byte;
// 	//result=result<<8;
// 	//result |=Lo_Byte;
// 	//return result;
// //}
// ////_______________________________________________________________________________________________________________________________________________________
// //void Get_Bytes_From_Uint16(unsigned int val, unsigned char *bfr)
// //{
// 	//*(bfr+1)=val;
// 	//val=val>>8;
// 	//*bfr=val;	
// //}
// ////_______________________________________________________________________________________________________________________________________________________
// //void Get_Bytes_From_int16(int val, unsigned char *bfr)
// //{
// 	//*(bfr+1)=val;
// 	//val=val>>8;
// 	//*bfr=val;
// //}
// ////_______________________________________________________________________________________________________________________________________________________
// //unsigned char str_count(unsigned char *src_bfr, unsigned char bfr_count)
// //{
// //unsigned char 	i,char_count;
// //
// //char_count=0;
// //
// //for(i=0;i<=bfr_count;i++)
// //{
// 	//if(*(src_bfr+i)!=0x00)
// 	//{
// 		//char_count++;
// 	//}
// 	//else
// 	//{
// 		//return char_count;
// 	//}
// //}
// 	//return char_count;
// //}
// ////_______________________________________________________________________________________________________________________________________________________
// //void Replace_Hash_To_Double_Quotation(unsigned char *bfr)
// //{
// 	//do{
// 		//if(*bfr=='#')
// 		//{
// 			//*bfr='"';
// 		//}
// 		//bfr++;
// 	//}while(*bfr !=0);
// //}
// ////_______________________________________________________________________________________________________________________________________________________

// ////_______________________________________________________________________________________________________________________________________________________
// //unsigned char ConvertBCD2Decimal(unsigned char val)
// //{
// 	//unsigned char lsd,msd, result;
// 	//
// 	//lsd=val & 0x0f;
// 	//val=val>>4;
// 	//msd=val & 0x0f;
// 	//
// 	//result=(msd*10)+lsd;
// 	//
// 	//return result;
// //}
// ////_______________________________________________________________________________________________________________________________________________________
// //unsigned char Get_strIndex_in_bfr(const char * str, unsigned char *bfr, unsigned char bfr_count, unsigned char StartIndex)
// //{
// 	//unsigned char bfr_str[20];
// 	//unsigned char len;
// 	//
// 	//Fill_Buffer(bfr_str,0x00, 20);
// 	//pgm2ram(str,bfr_str);
// 	//len=Get_length(&bfr_str[0]);
// 	//
// 	//for(unsigned int i=StartIndex;i<=bfr_count-len;i++)
// 	//{
// 		//if(CompareRam2Ram_OK(&bfr_str[0], &bfr[i],len))
// 		//{
// 			//return i;
// 		//}
// 	//}
// 	//return -1;
// //}

// ////__________________________________________________________________________________________________________________________________________________________
// //unsigned char Index_Of(const char * str, unsigned char *bfr, unsigned int bfr_count, unsigned char StartIndex)
// //{
// 	//unsigned char bfr_str[50];
// 	//unsigned char len;
// //
// 	//Fill_Buffer(&bfr_str[0],0x00, 50);
// 	//pgm2ram(str,&bfr_str[0]);
// 	//len=Get_length(&bfr_str[0]);
// //
// 	//for(unsigned int i=StartIndex;i<=bfr_count-len;i++)
// 	//{
// 		//if(CompareRam2Ram_OK(&bfr_str[0], &bfr[i],len))
// 		//{
// 			//ret_val=i+len;
// 			//return i+len;
// 		//}
// 	//}
// 	//return -1;
// //}
// ////__________________________________________________________________________________________________________________________________________________________
//  //
// //
// //
// //
// //
// //
// //
// //
// //unsigned char found_in_comm_bfr(unsigned char *str, unsigned char *bfr_src, unsigned char Compare_String_Length)
// //{
// 	////unsigned char i,count,char_count;
// 	////unsigned char bfr[Compare_String_Length];
// ////
// 	////// ready compare string buffer
// 	//////Utility::Fill_Buffer(&bfr,0x00,Compare_String_Length);
// //////	Utility::pgm2ram(str,&bfr[0]);
// 	////char_count=str_count(&bfr[0]);	
// 	////unsigned char BfrCount= str_count(&bfr_src[0]);
// 	////i=0;
// 	////while(true)
// 	////{
// 		////if(CompareRam2Ram(&(bfr_src+i),&bfr,char_count))
// 		////{
// 			////return true;
// 		////}
// 		////else
// 		////{
// 			////if(i<BfrCount-char_count)
// 			////{
// 				////i++;
// 			////}
// 			////else
// 			////{
// 				////break;
// 			////}
// 		////}
// 	////}
// 	//return false;
// //}
// ////----------------------------------------------- 
// ////unsigned char Find_And_Get_Position(unsigned char *str)
// ////{
// 	//////unsigned char i,count;
// 	//////unsigned char bfr_str[20];
// //////
// 	//////// ready compare string buffer
// 	//////ClearBuffer(&bfr_str,0x00,20);
// 	//////strcpypgm2ram(&bfr_str,str);
// 	//////count=str_count(&bfr_str);
// 	//////
// 	//////i=0;
// 	//////do
// 	//////{
// 		//////if(CompareRam2Ram_OK(&com.bfr[i],&bfr_str,count))
// 		//////{
// 			//////return i+count;
// 		//////}
// 		//////else
// 		//////{
// 			//////i++;
// 		//////}
// 	//////}while(i<esp_bfr_count-count);
// 	//////return -1;
// ////}
// //////________________________________________________________________________________________________________________________________________________________
// ////unsigned char Find_And_Get_Next_Pos(unsigned char pos,unsigned char *str)
// ////{
// 	////////unsigned char i,count;
// 	////////unsigned char bfr_str[20];
// ////////
// 	////////// ready compare string buffer
// 	////////ClearBuffer(&bfr_str,0x00,20);
// 	////////strcpypgm2ram(&bfr_str,str);
// 	////////count=str_count(&bfr_str);
// 	////////
// 	////////i=pos;
// 	////////do
// 	////////{
// 		////////if(CompareRam2Ram_OK(&com.bfr[i],&bfr_str,count))
// 		////////{
// 			////////return i+count;
// 		////////}
// 		////////else
// 		////////{
// 			////////i++;
// 		////////}
// 	////////}while(i<esp_bfr_count-count);
// 	////return -1;
// ////}
// //////////------------------------------------------------
// ////unsigned char Process_No_Of_Byte(unsigned char pos,unsigned char *bfr)
// ////{
// 	////////unsigned char b[5];
// 	////////unsigned char i,j;
// 	////////unsigned int k;
// 	////////
// 	////////j=pos;
// 	////////i=0;
// 	////////while(1)
// 	////////{
// 		////////k= com.bfr[pos];
// 		////////if(k==':')
// 		////////{
// 			////////break;
// 		////////}
// 		////////else
// 		////////{
// 			////////i++;
// 			////////pos++;
// 		////////}
// 	////////}
// 	////////k=ConvertAscii2Decimal(&com.bfr[j],i,0);
// 	////////*bfr=k;
// 	////return pos+1;	// skif ':'
// ////}
// //////------------------------------------------------
// ////unsigned char Get_cmd_length(unsigned char *bfr)
// ////{
// 	////unsigned char i;
// 	////i=0;
// 	////do{
// 		////i++;
// 		////bfr++;
// 	////}while(*bfr !='>');
// 	////i++;
// 	////return i;
// ////}
// //////________________________________________________________________________________________________________________________________________________________
// //
// //
// ////////------------------------------------------------
// //////unsigned char ConvertBCD2Decimal(unsigned char bcd_val)
// //////{
// 	//////register unsigned char i;
// 	//////i=bcd_val& 0xf0;
// 	//////i=i>>4;
// 	//////i=i*10;
// 	//////i=i+(bcd_val&0x0f);
// 	//////return i;
// //////}
// ////////------------------------------------------------
// //
// ////////------------------------------------------------
// //////unsigned char ConvertDecinal2BCD(unsigned char data)
// //////{
// //////register unsigned char i;
// //////i=data/10;
// //////i=i<<4;
// //////i=i|(data%10);
// //////return i;
// //////}
// ////////------------------------------------------------
// //////void Convertfloat2Ascii(float val,unsigned char *destptr, unsigned char *integercount, unsigned char *decimalplace)
// //////{
// //////float temp;
// //////unsigned int i,j;
// //////
// //////*destptr=(i/1000)|0x30;
// //////j=i%1000;
// //////
// //////destptr++;
// //////*destptr=(j/100)|0x30;
// //////j=j%100;
// //////
// //////destptr++;
// //////*destptr=(j/10)|0x30;
// //////
// //////destptr++;
// //////*destptr=(j%10)|0x30;
// //////
// //////destptr++;
// //////*destptr='.';
// //////destptr++;
// //////
// ////////temp = mms.kwh-i;
// ////////temp=temp*100;
// ////////i=temp;
// //////
// //////*destptr=(i/10)|0x30;
// //////destptr++;
// //////*destptr=(i%10)|0x30;
// //////}
// ////////================================================
// //////unsigned char  GetBin(unsigned int val,unsigned char *srcptr)
// //////{
//  ////////Convert 16 bit Data as binary Pattern
// ////////unsigned char i;
// ////////
// ////////for(i=0;i<=15;i++)
// ////////	{
// ////////	if((val &0x8000)==0x8000)
// ////////		{
// ////////	*srcptr='1';
// ////////		}
// ////////	else
// ////////		{
// ////////	*srcptr='0';
// ////////		}
// ////////	srcptr++;
// ////////	val = val<<1;
// ////////	}
// //////}
// ////////------------------------------------------------
// //////unsigned int ConvertAscii2Decimal(unsigned char *srcptr,unsigned char count, unsigned char DecimalPlace)
// //////{
// //////unsigned int i;
// //////unsigned int temp;
// //////unsigned char k;
// //////unsigned int temp2;
// //////temp=0;
// //////
// //////
// //////if(count==5)
// 	//////{
// 	//////k=*srcptr;
// 	//////k=k&0x0f;
// 	//////temp=k*10000.0;
// 	//////srcptr++;
// 	//////count--;
// 	//////}
// //////
// //////if(count==4)
// 	//////{
// 	//////k=*srcptr;
// 	//////k=k&0x0f;
// 	//////temp=temp+(k*1000.0);
// 	//////srcptr++;
// 	//////count--;
// 	//////}
// //////
// //////if(count==3)
// 	//////{
// 	//////k=*srcptr;
// 	//////k=k&0x0f;
// 	//////temp2=k *100.0;
// 	//////temp=temp+temp2;
// 	//////srcptr++;
// 	//////count--;
// 	//////}
// //////
// //////if(count==2)
// 	//////{
// 	//////if(DecimalPlace==2)srcptr++;
// 	//////k=*srcptr;
// 	//////k=k&0x0f;
// 	//////temp2=k*10.0;
// 	//////temp=temp+temp2;
// 	//////srcptr++;
// 	//////count--;
// 	//////}
// 	//////
// 	//////if(DecimalPlace==1)	srcptr++;
// //////
// 	//////k=*srcptr;
// 	//////k=k&0x0f;
// 	//////temp=temp+k;
// //////
// 	//////return temp;
// //////}
// ////////------------------------------------------------
// //////void Convert_Decimal2Hex(unsigned char data, unsigned char *destptr)
//  //////{
//   //////register unsigned char tmp;
//  	//////register unsigned char i;
// 	//////tmp=0;
// 	//////tmp=data &0x0f;
//  	//////*(destptr+1)=Convert_D2H(tmp);
//  	//////data=data>>4;
//  	//////tmp=data &0x0f;
//  	//////*destptr=Convert_D2H(tmp);
//  //////}
//  ////////-----------------------------------------------
// //////unsigned char Convert_D2H(unsigned char data)
// //////{
// ////////switch(data)
// ////////{
// ////////case 10:
// ////////return 'A';
// ////////break;
// //////////--------------
// ////////case 11:
// ////////return 'B';
// ////////break;
// //////////--------------
// ////////case 12:
// ////////return 'C';
// ////////break;
// //////////--------------
// ////////case 13:
// ////////return 'D';
// ////////break;
// //////////--------------
// ////////case 14:
// ////////return 'E';
// ////////break;
// //////////--------------
// ////////case 15:
// ////////return 'F';
// ////////break;
// //////////--------------
// ////////default:
// ////////return (data|0x30);
// ////////break;
// ////////}
// //////}
// ////////------------------------------------------------
// //////void Internal_Oscillator_tune_for_RS232(void)
// //////{
// ////////unsigned char i;
// ////////unsigned char tmp[4];
// ////////i=0;
// ////////while(i<=15)
// ////////{
// ////////	OSCTUNE=i;
// ////////	ConvertByte2Ascii(i,&tmp,3,0);
// ////////	tmp[3]='\r';
// ////////	PutsUSART(&tmp);
// ////////	PutUSART('\n');
// ////////	PutUSART('\r');
// ////////	DebugPrint("WELCOME TO EMBEDDED WORLD");
// ////////	i++;
// ////////	Delay(100);
// ////////}
// //////}
// ////////-----------------------------------------------
// //////void GetData_Between_Hash(unsigned int src,unsigned int HashCount, unsigned char *dest)
// //////{
// ////////	unsigned char i;
// ////////	unsigned int src_addr;
// ////////	
// ////////	src_addr=src;
// ////////	
// ////////	//---Find specific Hash------------------
// ////////	do{
// ////////	do{
// ////////		i=Read_One_Byte_Data_From_ROM(src_addr);
// ////////		if(i=='#') break;
// ////////		src_addr++;
// ////////	}while(i!=0x00);
// ////////	
// ////////	HashCount--;	
// ////////	}while(HashCount!=0);
// ////////	//---------------------------------------
// ////////	src_addr++;	// skif hash
// ////////	
// ////////	do{
// ////////		i=Read_One_Byte_Data_From_ROM(src_addr);
// ////////		*dest=i;
// ////////		dest++;
// ////////	}while(i !='#');
// ////////	//----------------------------------------
// //////}
// ////////================================================
// //////unsigned char Read_One_Byte_Data_From_ROM(unsigned int source)
// //////{
// //////// 		TBLPTRU = 0x00;				// Address Highest
// ////////		TBLPTRL =source;		// Address Lowest;
// ////////		source=source>>8;
// ////////		TBLPTRH	= source;		// Address Mid
// ////////	
// ////////		_asm    tblrdpostinc  _endasm
// //////// 		
// //////// 		return TABLAT;
// //////}
// ////////==================================================
// //////void Test_USART(void)	// send 5 digit incremented data
// //////{
// 	//////unsigned int i;
// 	//////unsigned char tmp[10];
// 	//////
// 	//////i=0;
// 		//////
// 	//////while(1)
// 		//////{	
// 			//////PutUSART('C');
// 			//////PutUSART('O');
// 			//////PutUSART('U');
// 			//////PutUSART('N');
// 			//////PutUSART('T');
// 			//////PutUSART('=');
// 			//////ConvertInt2Ascii(i,&tmp[0],5,0);
// //////
// 			//////PutUSART(tmp[0]);
// 			//////PutUSART(tmp[1]);
// 			//////PutUSART(tmp[2]);
// 			//////PutUSART(tmp[3]);
// 			//////PutUSART(tmp[4]);
// 			//////
// 			//////PutUSART('\n');
// 			//////PutUSART('\r');
// 			//////i++;
// 			//////delay(1000);
// 			//////
// 			//////SPBRG=i;
// //////
// 		//////}	
// //////}			
// ////////===================
// //////void delay(unsigned int val)
// //////{	unsigned int i,j;
// 	//////
//     //////for(i=0;i<val;i++)
//     //////{
// 	    //////for(j=0;j<=50;j++)
// 	    //////{
//         //////_asm clrwdt _endasm
//      	//////}   
//      //////
//     //////}
// //////}
// ////////=================================================
// //////void ClearBuffer(unsigned char *srcptr,unsigned char val, unsigned char count)
// //////{
// //////do{
// //////*srcptr=val;
// //////if(count!=0)count--;
// //////*srcptr++;
// //////}while(count!=0);
// //////}
// ////////==============================================================
// //////unsigned char CompareRam2Ram_OK(unsigned char *cmpptr1, unsigned char *cpmptr2,unsigned char count)
// //////{
//     //////unsigned char j;
// 	//////j=0;
// //////do{
// 	//////if(*cmpptr1!=*cpmptr2)	//
// 	//////{
// 		//////return 0;
// 	//////}
// 	//////cmpptr1++;
// 	//////cpmptr2++;
// 	//////j++;
//  //////}while(j!=count);
// //////return -1;
// //////}
// ////
// ////
// ////
// ////////______________________________________________________________________________________________________________________________________________________
// //////unsigned char Get_Next_Pos(const char * str, unsigned char *bfr)
// //////{
// //////unsigned char j=0;
// //////unsigned char bfr_str[20];
// //////unsigned char len;
// //////
// //////Fill_Buffer(bfr_str,0x00, 10);
// //////pgm2ram(str,bfr_str);
// //////len=Get_length(&bfr_str);
// //////
// //////for(unsigned int i=0;i<=Bfr_count_rx-len;i++)
// //////{
// //////if(CompareRam2Ram(&bfr_str, &bfr[i],len))
// //////{
// //////
// //////}
// //////else
// //////{
// //////return i+len;
// //////}
// //////}
// //////return false;
// //////}
// ////
// ////
// //
// //
// //
// ////void Utility::Set_All_Port_Input(void)
// ////{
// ////DDRA=0b00000000;
// ////DDRB=0b00000000;
// ////DDRC=0b00000000;
// ////DDRD=0b00000000;
// ////DDRE=0b00000000;
// ////DDRF=0b00000000;
// ////DDRG=0b00000000;
// ////DDRH=0b00000000;
// ////DDRJ=0b00000000;
// ////DDRK=0b00000000;
// ////DDRL=0b00000000;
// ////}
// //////_____________________________________________________________________________________________________________________________
// //unsigned int Get_Avj_val(unsigned int val, unsigned int *bfr,unsigned char bfr_count)
// //{
// 	//unsigned char i;
// 	//
// 	//unsigned long sum=0;
// 	//
// 	////---shift buffer---------
// 	//for(i=0;i<bfr_count-1;i++)
// 	//{
// 		//*(bfr+i)=*(bfr+i+1);
// 	//}
// 	////-------------------------
// 	//
// 	///// push data to buffer
// 	//*(bfr+bfr_count-1)=val;
// 	////--------------------------
// 	//sum=0;
// 	////---sum buffer ---------
// 	//for(i=0;i<bfr_count;i++)
// 	//{
// 		//sum=sum+*(bfr+i);
// 	//}
// 	////-------------------------
// 	//// get average value
// 	//sum=sum/bfr_count;
// 	////--------------------------
// 	//return  sum;
// //}
// ////__________________________________________________________________________________________________________________________________
// //void ConvertUnsignedLong2Ascii(unsigned long val, unsigned char *destptr)
// //{
// 	//*destptr=(val/1000000000)|0x30;
// 	//val=val%1000000000;
// 	//destptr++;
// //
// 	//*destptr=(val/100000000)|0x30;
// 	//val=val%100000000;
// 	//destptr++;
// //
// 	//*destptr=(val/10000000)|0x30;
// 	//val=val%10000000;
// 	//destptr++;
// //
// 	//*destptr=(val/1000000)|0x30;
// 	//val=val%1000000;
// 	//destptr++;
// //
// 	//*destptr=(val/100000)|0x30;
// 	//val=val%100000;
// 	//destptr++;
// //
// 	//*destptr=(val/10000)|0x30;
// 	//val=val%10000;
// 	//destptr++;
// //
// 	//*destptr=(val/1000)|0x30;
// 	//val=val%1000;
// 	//destptr++;
// //
// 	//*destptr=(val/100)|0x30;
// 	//val=val%100;
// 	//destptr++;
// //
// 	//*destptr=(val/10)|0x30;
// 	//val=val%10;
// 	//destptr++;
// //
// 	//*destptr=val|0x30;
// //}
// ////____________________________________________________________________________________________________________________________________
// //unsigned long Convert_Ascii_2_long(unsigned char *destptr, unsigned char digit_count)
// //{
// 	//unsigned long sum=0;
// 	//
// 	//switch(digit_count)
// 	//{
// 		//case 10:
// 			//sum += (*destptr &0x0f)* 1000000000; destptr++;
// 			//sum += (*destptr &0x0f)* 100000000; destptr++;
// 			//sum += (*destptr &0x0f)* 10000000; destptr++;
// 			//sum += (*destptr &0x0f)* 1000000; destptr++;
// 			//sum += (*destptr &0x0f)* 100000; destptr++;
// 			//sum += (*destptr &0x0f)* 10000; destptr++;
// 			//sum += (*destptr &0x0f)* 1000; destptr++;
// 			//sum += (*destptr &0x0f)* 100; destptr++;
// 			//sum += (*destptr &0x0f)* 10; destptr++;
// 			//sum += (*destptr &0x0f);
// 		//break;
// 		///////////////////////////////////
// 		//case 9:
// 			//sum += (*destptr &0x0f)* 100000000; destptr++;
// 			//sum += (*destptr &0x0f)* 10000000; destptr++;
// 			//sum += (*destptr &0x0f)* 1000000; destptr++;
// 			//sum += (*destptr &0x0f)* 100000; destptr++;
// 			//sum += (*destptr &0x0f)* 10000; destptr++;
// 			//sum += (*destptr &0x0f)* 1000; destptr++;
// 			//sum += (*destptr &0x0f)* 100; destptr++;
// 			//sum += (*destptr &0x0f)* 10; destptr++;
// 			//sum += (*destptr &0x0f);
// 		//break;
// 		///////////////////////////////////
// 		//case 8:
// 			//sum += (*destptr &0x0f)* 10000000; destptr++;
// 			//sum += (*destptr &0x0f)* 1000000; destptr++;
// 			//sum += (*destptr &0x0f)* 100000; destptr++;
// 			//sum += (*destptr &0x0f)* 10000; destptr++;
// 			//sum += (*destptr &0x0f)* 1000; destptr++;
// 			//sum += (*destptr &0x0f)* 100; destptr++;
// 			//sum += (*destptr &0x0f)* 10; destptr++;
// 			//sum += (*destptr &0x0f);	
// 		//break;
// 		////////////////////////////////
// 		//case 7:
// 			//sum += (*destptr &0x0f)* 1000000; destptr++;
// 			//sum += (*destptr &0x0f)* 100000; destptr++;
// 			//sum += (*destptr &0x0f)* 10000; destptr++;
// 			//sum += (*destptr &0x0f)* 1000; destptr++;
// 			//sum += (*destptr &0x0f)* 100; destptr++;
// 			//sum += (*destptr &0x0f)* 10; destptr++;
// 			//sum += (*destptr &0x0f);
// 		//break;
// 		////////////////////////////////
// 		//case 6:
// 			//sum += (*destptr &0x0f)* 100000; destptr++;
// 			//sum += (*destptr &0x0f)* 10000; destptr++;
// 			//sum += (*destptr &0x0f)* 1000; destptr++;
// 			//sum += (*destptr &0x0f)* 100; destptr++;
// 			//sum += (*destptr &0x0f)* 10; destptr++;
// 			//sum += (*destptr &0x0f);
// 		//break;
// 		//////////////////////////////////	
// 		//case 5:
// 			//sum += (*destptr &0x0f)* 10000; destptr++;
// 			//sum += (*destptr &0x0f)* 1000; destptr++;
// 			//sum += (*destptr &0x0f)* 100; destptr++;
// 			//sum += (*destptr &0x0f)* 10; destptr++;
// 			//sum += (*destptr &0x0f);
// 		//break;
// 		//////////////////////////////////
// 		//case 4:
// 		//sum += (*destptr &0x0f)* 1000; destptr++;
// 		//sum += (*destptr &0x0f)* 100; destptr++;
// 		//sum += (*destptr &0x0f)* 10; destptr++;
// 		//sum += (*destptr &0x0f);
// 		//break;
// 		//////////////////////////////////
// 		//case 3:
// 		//sum += (*destptr &0x0f)* 100; destptr++;
// 		//sum += (*destptr &0x0f)* 10; destptr++;
// 		//sum += (*destptr &0x0f);
// 		//break;
// 		//////////////////////////////////
// 		//case 2:
// 		//sum += (*destptr &0x0f)* 10; destptr++;
// 		//sum += (*destptr &0x0f);
// 		//break;
// 		//////////////////////////////////
// 		//case 1:
// 		//sum += (*destptr &0x0f);
// 		//break;
// 		//////////////////////////////////		
// 		//default:
// 		//sum=0;	
// 	//}
// 	//return sum;	 
// //}
// ////____________________________________________________________________________________________________________________________________
// //
// //
// //
// //
// //
// //////void ConvertUnsignedShortLong2Ascii(unsigned short long val, unsigned char *destptr,unsigned char digitcount, unsigned char DecimalPlace)
// //////{
// 	//////unsigned short long j;
// 			//////
// //////if(digitcount==8)
// 		//////{
// 		//////*destptr=(val/10000000)|0x30;
// 		//////destptr++;
// 		//////digitcount--;
// 		//////}
// ////////------------------------------	
// //////j=val%10000000;
// //////
// //////if(digitcount==7)	
// 		//////{
// 		//////*destptr=(j/1000000)|0x30;
// 		//////destptr++;
// 		//////digitcount--;
// 		//////}
// ////////-------------------------------
// //////j=j%1000000;
// //////
// //////if(digitcount==6)
// 	//////{
// 	//////*destptr=(j/100000)|0x30;
// 	//////destptr++;
// 	//////digitcount--;
// 	//////}
// ////////-------------------------------
// //////j=j%100000;	
// //////
// //////if(digitcount==5)
// 	//////{
// 		//////*destptr=(j/10000)|0x30;
// 		//////destptr++;
// 		//////digitcount--;
// 	//////}
// ////////------------------------------
// //////j=j%10000;	
// 	//////
// 	//////ConvertInt2Ascii(j,destptr,digitcount,DecimalPlace);
// //////}
// ////////================================================
// //////unsigned short long ConvertAscii2unsignedShortLong(unsigned char *srcptr,unsigned char count, unsigned char DecimalPlace)
// //////{
// //////unsigned int i;
// //////unsigned short long temp;
// //////unsigned char k;
// //////unsigned short long tmp2;
// //////temp=0;
// //////
// //////
// //////if(count==8)
// 	//////{
// 		//////k=*srcptr;
// 		//////k=k&0x0f;
// 		//////temp=k*10000000.0;
// 		//////srcptr++;
// 		//////count--;
// 	//////}
// //////
// //////if(count==7)
// 	//////{
// 		//////k=*srcptr;
// 		//////k=k&0x0f;
// 		//////temp +=(k*1000000.0);
// 		//////srcptr++;
// 		//////count--;
// 	//////}
// //////
// //////if(count==6)
// 	//////{
// 		//////k=*srcptr;
// 		//////k=k&0x0f;
// 		//////temp +=k *100000.0;	
// 		//////srcptr++;
// 		//////count--;
// 	//////}
// //////
// //////if(count==5)
// 	//////{
// 		//////k=*srcptr;
// 		//////k=k&0x0f;
// 		//////temp +=k*10000.0;
// 		//////srcptr++;
// 		//////count--;
// 	//////}
// 	//////
// //////if(count==4)
// 	//////{
// 		//////k=*srcptr;
// 		//////k=k&0x0f;
// 		//////temp +=k*1000.0;
// 		//////srcptr++;
// 		//////count--;
// 	//////}	
// 	//////
// //////if(count==3)
// 	//////{
// 		//////if(DecimalPlace==3)	srcptr++;
// 		//////k=*srcptr;
// 		//////k=k&0x0f;
// 		//////temp +=k*100.0;
// 		//////srcptr++;
// 		//////count--;
// 	//////}	
// 	//////
// //////if(count==2)
// 	//////{
// 		//////if(DecimalPlace==2)	srcptr++;
// 		//////k=*srcptr;
// 		//////k=k&0x0f;
// 		//////temp +=k*10;
// 		//////srcptr++;
// 		//////count--;
// 	//////}
// 		//////if(DecimalPlace==1)	srcptr++;
// 		//////k=*srcptr;
// 		//////k=k&0x0f;
// 		//////temp +=k*1;
// 	 //////
// 		//////return temp;
// //////}	
// ////______________________________________________________________________________________________________________________________
// //void convert_long_to_byte(long val, unsigned char *bfr)
// //{
// 	//*bfr=val; bfr++;
// 	//
// 	//val=val>>8;
// 	//*bfr=val; bfr++;
// 	//
// 	//val=val>>8;
// 	//*bfr=val; bfr++;
// 	//
// 	//val=val>>8;
// 	//*bfr=val;
// //}
// ////______________________________________________________________________________________________________________________________
// //long convert_byte_to_long(unsigned char *bfr)
// //{
// 	//long val;
// 	//val=0;
// 	//
// 	//val=*bfr;
// 	//val=val<<8;
// 	//
// 	//bfr++;	
// 	//val |=*bfr; 
// 	//val=val<<8;
// 	//
// 	//bfr++;	
// 	//val |=*bfr;
// 	//val=val<<8;
// 	//*bfr=val;	
// 	//
// 	//bfr++;
// 	//val |=*bfr;
// 	//
// 	//return val;	
// //}
// ////______________________________________________________________________________________________________________________________
// 	}