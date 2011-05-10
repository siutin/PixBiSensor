/*
 *	Delay functions for C18 version 2.40
 *	See delay.h for details
 *
 *	Make sure this code is compiled with full optimization!!!
 *  Downloaded from www.microchipc.com - see site for more sample PIC C code
 */
#include <p18cxxx.h>
#include "delay.h"

void
DelayMs(unsigned char cnt)
{
#if	XTAL_FREQ <= 2MHZ
	do {
		DelayUs(996);
	} while(--cnt);
#endif

#if    XTAL_FREQ > 2MHZ	
	unsigned char	i;
	do {
		i = 4;
		do {
			DelayUs(250);
		} while(--i);
	} while(--cnt);
#endif
}
