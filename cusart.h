/*
***********************************************************************************************
*									Custom PIC18 USART Driver 
*
*										All Rights Reserved
* File name		: cusart.c
* Programmer 	: Martin Chan, (TM)IVE. Hong Kong
* Note			: 
* Language		: C18 complier version 3.36, MPLAB v8.56
* Hardware		: PIC18F2520-I/P
* Date			: 08 May 2011			Version 1.0 
*
***********************************************************************************************
*/
#ifndef __CUSTOM_USART_H
#define __CUSTOM_USART_H
/*
***********************************************************************************************
*										PORT DEFINITION
***********************************************************************************************
*/
	#define	CUART_TX	PORTBbits.RB0 
	#define	CUART_RX	PORTBbits.RB1
	#define CUART_TX_TRIS	TRISBbits.TRISB0		//TX
	#define CUART_RX_TRIS	TRISBbits.TRISB1		//RX
/*
***********************************************************************************************
*										Timer Setting
***********************************************************************************************
*										DESCRIPTION
*
*	 Crystal : 20MHz , baudrate :9600Kbps
*	 9600bit/sec -> 104.2us/bit
*	 default value 65095 (around 94.2us)
*	 c statement latency (around 10 us)
*	 
***********************************************************************************************
*/
	
	//#define _1msec_16bit 65095
	#define _1msec_16bit 64793
	enum boolean{FALSE,TRUE};
	void cUSART_tInit(void);
	enum boolean get_cuUSART_status(void);
	void uputc(char data);
	void uputs(char *s);
#endif
