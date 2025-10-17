// #include "\MEGA2560\MEGA2560\MEGA2560.h"
// #include "KEY4X4.h"
// MEGA2560 brd;

// unsigned char r1,r2,r3,r4,c1,c2,c3,c4;
// #define key_delay	5
// //__________________________________________________________________________________________________________________________________________
// KEY4X4::KEY4X4()
// {
	
// }
// //__________________________________________________________________________________________________________________________________________
// void KEY4X4::setup(unsigned char row_1,unsigned char row_2,unsigned char row_3,unsigned char row_4,unsigned char col_1,unsigned char col_2,unsigned char col_3,unsigned char col_4)
// {
// 	r1=row_1;
// 	r2=row_2;
// 	r3=row_3;
// 	r4=row_4;
	
// 	c1=col_1;
// 	c2=col_2;
// 	c3=col_3;
// 	c4=col_4;

// 	brd.DO(r1);
// 	brd.DO(r2);
// 	brd.DO(r3);
// 	brd.DO(r4);
	
// 	brd.DI(c1);
// 	brd.DI(c2);
// 	brd.DI(c3);
// 	brd.DI(c4);	
// }
// //__________________________________________________________________________________________________________________________________________
// unsigned char KEY4X4::pressed(void)
// {
// 	brd.PIN_Low(r1);
// 	brd.PIN_High(r2);
// 	brd.PIN_High(r3);
// 	brd.PIN_High(r4);
// 	if(brd.PIN(c1)==0) return '7';
// 	if(brd.PIN(c2)==0) return '8';
// 	if(brd.PIN(c3)==0) return '9';
// 	if(brd.PIN(c4)==0) return '/';
// 	///////////////////////////////
// 	brd.PIN_Low(r2);
// 	brd.PIN_High(r1);
// 	brd.PIN_High(r3);
// 	brd.PIN_High(r4);
// 	if(brd.PIN(c1)==0) return '4';
// 	if(brd.PIN(c2)==0) return '5';
// 	if(brd.PIN(c3)==0) return '6';
// 	if(brd.PIN(c4)==0) return '*';
// 	/////////////////////
// 	brd.PIN_Low(r3);
// 	brd.PIN_High(r1);
// 	brd.PIN_High(r2);
// 	brd.PIN_High(r4);
// 	if(brd.PIN(c1)==0) return '1';
// 	if(brd.PIN(c2)==0) return '2';
// 	if(brd.PIN(c3)==0) return '3';
// 	if(brd.PIN(c4)==0) return '-';
// 	///////////////////////////////
// 	brd.PIN_Low(r4);
// 	brd.PIN_High(r1);
// 	brd.PIN_High(r2);
// 	brd.PIN_High(r3);
// 	if(brd.PIN(c1)==0) return 'c';
// 	if(brd.PIN(c2)==0) return '0';
// 	if(brd.PIN(c3)==0) return '=';
// 	if(brd.PIN(c4)==0) return '+';

// 	brd.sleep(key_delay);	
// 	return 0;
// }
// //__________________________________________________________________________________________________________________________________________



