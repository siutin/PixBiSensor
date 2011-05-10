#define USE_OR_MASKS
#include <p18F2520.h>
#include "setup.h"
#include "delays.h"
#include "stdlib.h"
#include <usart.h>

#pragma config OSC = INTIO7, FCMEN = OFF, IESO = OFF, PWRT = OFF, BOREN = OFF, WDT = OFF
#pragma config MCLRE = ON, PBADEN = OFF, STVREN = ON, LVP = OFF, XINST = OFF, DEBUG = ON

unsigned char Rxdata[16];
unsigned char Txdata[]="1234";
unsigned char newLine[] = {'\015','\012'};
unsigned int  i,counter = 0;
unsigned char c;
#define BAUD_RATE_GEN 50                 // Fosc = 20MHz, Baud Rate = 9600 bps

enum lightingType{LITEON,FULLON,CROSS,OFF};
void clear_data();
void rx_handler(void);
void XBeeSend(unsigned char data[]);
void sleep(int time);
void sleepms(unsigned char time);


#pragma code rx_interrupt=0x08
void rx_int(void){
	_asm GOTO rx_handler _endasm
}
#pragma code
#pragma interrupt rx_handler
void rx_handler(void){
//-----------USART Reception ----------------------------------

	if(PIR1bits.RCIF) {

		while(BusyUSART());
		c = getcUSART();
		if (c == '\015'){ 	//Enter
			for(i=0;i<newLine[i];i++){
				while(BusyUSART());
				putcUSART(newLine[i]);
			}	
		}else{
			Rxdata[counter] = (unsigned char)c;
			while(BusyUSART());
			putcUSART(c);
		}
	}
	PIR1bits.RCIF = 0;
}
void clear_data(){
	int j;
	for(j=0;j<16;j++){
		Rxdata[j]='\0';
	}
}
void sleepms(unsigned char time){
	while(time--){
		Delay10KTCYx(50);
	}
}
void XBeeSend(unsigned char data[]){
	int k;
	for(k=0;k<data[k];k++){
		while(BusyUSART());
		putcUSART(data[k]);
	}
}

void sleep(int time){
	int i;
	for(i=0;i<time;i++)
			Delay10KTCYx(400);
}
void lighting(enum lightingType);
void main(void){
	int i = 0;
	enum lightingType lightingtype;
	OSCCON = 0x70;
	//OSCTUNE = 0x40;
	TRISB = 0x00;
	TRISC = 0xFD;
	PORTB = 0x00;
	PORTC = 0x00;
	
	
	//------------USART Setting --------
	TRISCbits.TRISC6 = OUT; //Tx
	TRISCbits.TRISC7 = IN;	//Rx
	
 	OpenUSART(USART_TX_INT_ON & USART_RX_INT_ON & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_HIGH, BAUD_RATE_GEN);
  	baudUSART(BAUD_8_BIT_RATE | BAUD_AUTO_OFF);
	
	//INTCONbits.GIEH = 0;	// disable interrupts
	
	TXSTAbits.SYNC = 0;		// asynchronous mode
	TXSTAbits.BRGH = 1;		// high speed 
	TXSTAbits.TXEN = 1;		// transmit enabled	

	RCSTAbits.SPEN = 1;		// Serial port enabled
	RCSTAbits.CREN = 1;		// Enable reciver

	RCONbits.IPEN = 1; 		//enable interrupt priority
	IPR1bits.RCIP = 1;		// receive interrupt high prority

	PIR1bits.RCIF = 0;		//PIR1bits.RCIF
	PIE1bits.RCIE = 1;		//Reception interrupt Enable
	INTCONbits.GIEH = 1;	//enable all interrupts
	INTCONbits.GIEL = 1;	//enable low-priority interrupts		
	while(1){
		
//		lighting(LITEON);
//		sleep(3);
//		//lighting(CROSS);
//		//sleep(3);
//		lighting(FULLON);
//		sleep(3);
//		lighting(OFF);
//		sleep(4);
		
//		for(i = 0 ; i<16; i++){
//			PORTB = Rxdata[i];
//			sleep(1);
//		}
		if(	Rxdata[0] != '\0'){
			
			if(Rxdata[0] == 'A')
				lighting(OFF);
			else if (Rxdata[0] == 'B')
				lighting(LITEON);
			else if (Rxdata[0] == 'C')
				lighting(FULLON);
			else if (Rxdata[0] == 'D')
				lighting(CROSS);
		}

		
//		if(PORTCbits.RC0 == 0 && PORTCbits.RC2 == 0)
//			lighting(OFF);
//		else if(PORTCbits.RC0 == 0 && PORTCbits.RC2 == 1)
//			lighting(LITEON);
//		else if(PORTCbits.RC0 == 1 && PORTCbits.RC2 == 0)
//			lighting(FULLON);
//		else if(PORTCbits.RC0 == 1 && PORTCbits.RC2 == 1)
//			lighting(CROSS);
//		else lighting(OFF);

	}
}
void lighting(enum lightingType _lightingtype){
	switch (_lightingtype){
		case LITEON:
			PORTB = 0b00000001;
			break;
		case FULLON:
			PORTB = 0b00001111;
			break;
		case CROSS:
			PORTB = 0b00001010;
			break;
		case OFF:
			PORTB = 0b00000000;
			break;
		default:
			break;	 
	}
}
