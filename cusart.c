#include "cusart.h"
#include "timers.h"
#include "usart.h"
#include "delays.h"

int CUART_IDX = 0;
void cUSART_tInit(void){
	OpenTimer1( TIMER_INT_ON & T1_16BIT_RW & T1_SOURCE_INT &
				T1_PS_1_1 & T1_OSC1EN_OFF &	T1_SYNC_EXT_OFF
				);
	//T1CONbits.TMR1CS = 0;
	//WriteTimer1(_1msec_16bit);
	//WriteTimer1();
		TMR1H = 0xFE;
		TMR1L = 0x72;
}
void uputs(char *s){
	while(*s)
		uputc(*(s++));
}
int ugetIdx(void){
	return CUART_IDX;
}
void uSetIdx(int d){
	CUART_IDX = d;
}
int uAddIdx(void){
	return CUART_IDX=(CUART_IDX < 10)? CUART_IDX++:0;
}
void uprintc(char data){
	putcUSART('*');
	CUART_IDX = 0;
	uputc(data);
}

void uputc(char data){
	//while(CUART_IDX < 11){
	//if(CUART_IDX == 0) putcUSART('*');
	switch(CUART_IDX){
		case 0:		Delay10TCYx(5); break;
		case 1:		CUART_TX = 0;Delay10TCYx(5); break;
		case 10:	CUART_TX = 1;Delay10TCYx(5); break;
		default:	CUART_TX = 1 & (data >> (CUART_IDX-2));
		break;
	}
	//}
	CUART_IDX=(CUART_IDX < 10)? CUART_IDX++:0;
}


//void uputc(char data){
//	char shift,i;
//	for(i=0;i<11;i++){
//		switch(i){
//			case 0:		break;
//			case 1:		CUART_TX = 0;break;
//			case 10:	CUART_TX = 1;break;
//			default:	
//						shift = (data >> (i-2));
//						CUART_TX = 1 & 	shift;
//			break;
//		}
//		WriteTimer1(_1msec_16bit);
//		while(!PIR1bits.TMR1IF);
//		PIR1bits.TMR1IF = 0;
//	}
//}
