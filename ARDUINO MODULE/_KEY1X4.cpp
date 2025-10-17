
// #include "\MEGA2560\IDE\MEGA2560.h"
// #include "KEY1X4.h"

// MEGA2560 b_key;
// //____________________________________________________________________________________________________________________________________________
// KEY1X4::KEY1X4()
// {
				
	
// }
// //____________________________________________________________________________________________________________________________________________
// void KEY1X4::setup(unsigned char inc,unsigned char dec,unsigned char cancel,unsigned char accept)
// {	
// 	this->key_inc=inc;
// 	this->key_dec=dec;
// 	this->key_accept=accept;
// 	this->key_cancel=cancel;	
	
// 	b_key.DI(this->key_inc);
// 	b_key.DI(this->key_inc);
// 	b_key.DI(this->key_cancel);
// 	b_key.DI(this->key_accept);	
// }
// //____________________________________________________________________________________________________________________________________________
// bool KEY1X4::pressed(void)
// {
// 	if(b_key.PIN(key_inc)==0)
// 	{
// 		this->key_val=KeyCode_INC;
// 		return true ;
// 	}
// 	//////////////////////////////
// 	if(b_key.PIN(key_dec)==0)
// 	{
// 		this->key_val=KeyCode_DEC;
// 		return true;
// 	}
// 	//////////////////////////////
// 	if(b_key.PIN(key_accept)==0) 
// 	{
// 		this->key_val=KeyCode_CANCEL;
// 		return true;
// 	}
// 	///////////////////////////////
// 	if(b_key.PIN(key_cancel)==0)
// 	{
// 		this->key_val=KeyCode_ACCEPT;
// 		return true;
// 	}	
// 	return 0;	
// }
// //____________________________________________________________________________________________________________________________________________
































