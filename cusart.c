#include "cusart.h"
#include "timers.h"

enum boolean cuUSART_STATUS;
enum boolean get_cuUSART_status(void){
	return cuUSART_STATUS;
}
void cUSART_tInit(void){
	OpenTimer1( TIMER_INT_OFF & T1_16BIT_RW & T1_SOURCE_INT &
				T1_PS_1_1 & T1_OSC1EN_OFF &	T1_SYNC_EXT_OFF
				);
}
void uputs(char *s){
	while(*s)
		uputc(*(s++));
}
void uputc(char data){
	char shift,i;
	cuUSART_STATUS = TRUE;
	INTCONbits.GIEH = 0;
	for(i=0;i<11;i++){
		switch(i){
			case 0:		break;
			case 1:		CUART_TX = 0;break;
			case 10:	CUART_TX = 1;break;
			default:	
						shift = (data >> (i-2));
						CUART_TX = 1 & 	shift;
			break;
		}
		WriteTimer1(_1msec_16bit);
		while(!PIR1bits.TMR1IF);
		PIR1bits.TMR1IF = 0;
	}
	INTCONbits.GIEH = 1;
	cuUSART_STATUS = FALSE;
}