
#include "avr/io.h"

namespace hardware

{
	

class fnd:public BOARD, public helper
{
	public:
	fnd();
	void update(unsigned int val);

	
	unsigned data=D2,clock=D3,strobe=D4;
	private:
	void ConvertAscii2FND(unsigned char *srcptr, unsigned char No_Of_FND);
	void strobe_trigger(void);
	void puts(unsigned char *bfr,unsigned char fnd_count);
	void put(unsigned char val);
	
	unsigned char fnd_count=5;
	unsigned char fnd_type='c';
	
	protected:
	

};// class fnd
	
//_______________________________________________________________________________________________________________________	
fnd::fnd()
{
	DO(data);
	DO(clock);
	DO(strobe);
}
//_______________________________________________________________________________________________________________________
void fnd::update(unsigned int val)
{
	unsigned char bfr[5];
	ConvertInt2Ascii(val,&bfr[0],5,0);	
	ConvertAscii2FND(&bfr[0],5);
	puts(&bfr[0],5);
}
//___________________________________________________________________________________________________________________



//______________________________________________________________________________________________________________________________________
void fnd::ConvertAscii2FND(unsigned char *srcptr, unsigned char No_Of_FND)
{
	unsigned char i;
	
	for(i=0;i<No_Of_FND;i++)
	{
		switch(*srcptr)
		{
			case 0x30:	*srcptr=0x3F;	break;
			case 0x31:	*srcptr=0x06;	break;
			case 0x32:	*srcptr=0x5B;	break;
			case 0x33:	*srcptr=0x4F;	break;
			case 0x34:	*srcptr=0x66;	break;
			case 0x35:	*srcptr=0x6D;	break;
			case 0x36:	*srcptr=0x7D;	break;
			case 0x37:	*srcptr=0x07;	break;
			case 0x38:	*srcptr=0x7F;	break;
			case 0x39:	*srcptr=0x6F;	break;
			case 0x3A:	*srcptr=0x00;	break;
			case '-':	*srcptr= 0x40;	break;
			
			case 'A':	case 'a':	*srcptr=0x77;	break;
			case 'B':	case 'b':	*srcptr=0x7C;	break;
			
			case 'C':	*srcptr=0x39;	break;
			case 'c':	*srcptr=0x58;	break;

			case 'D':
			case 'd':
			*srcptr=0x5E;
			break;
			
			case 'E':
			case 'e':
			*srcptr=0x79;
			break;
			
			case 'F':
			case 'f':
			*srcptr=0x71;
			break;
			
			case 'G':
			case 'g':
			*srcptr=0x6F;
			break;
			
			case 'H':
			*srcptr=0x76;
			break;
			
			case 'h':
			*srcptr=0x74;
			break;
			
			case 'i':
			case 'I':
			*srcptr=0x04;
			break;
			
			case 'L':
			case 'l':
			*srcptr=0x38;
			break;
			
			case 'N':
			case 'n':
			*srcptr=0x54;
			break;

			case 'O':
			*srcptr=0x3F;
			break;
			
			case 'o':
			*srcptr=0x5C;
			break;
			
			case 'P':
			case 'p':
			*srcptr=0x73;
			break;
			
			case 'Q':
			case 'q':
			*srcptr=0x67;
			break;
			
			case 'R':
			case 'r':
			*srcptr=0x50;
			break;
			
			case 'S':
			case 's':
			*srcptr=0x6D;
			break;
			
			case 'T':
			case 't':
			*srcptr=0x78;
			break;
			
			case 'U':
			*srcptr=0x3E;
			break;
			
			case 'u':
			*srcptr=0x1C;
			break;
			
			case 'V':
			case 'v':
			*srcptr=0x1C;
			break;
			
			case 'Y':
			case 'y':
			*srcptr=0x6E;
			break;
			
			default:
			*srcptr=0x00;
			break;
		}
		srcptr++;
	}
}
//___________________________________________________________________________________________________________________________	
void fnd::puts(unsigned char *bfr,unsigned char fnd_count)
{
	for(int i=0;i<fnd_count;i++)
	{
		put(*bfr);
		bfr++;	
	}
	strobe_trigger();
}
//___________________________________________________________________________________________________________________________
void fnd::put(unsigned char val)
	{
		register unsigned char j,k;
		
		for(j=0;j<=7;j++)
		{
			k = val & 128;
			switch (k)
			{
				case 0:			PIN_Low(this->data);	break;
				default:		PIN_High(this->data);	break;
			}
			PIN_High(clock);
			PIN_Low(clock);
			val =val <<1;
		}
	}
//__________________________________________________________________________________________________________________
void fnd::strobe_trigger(void)
{
	PIN_High(strobe);
	PIN_Low(strobe);	
}
//___________________________________________________________________________________________________________________

	
	
}// namespace



