#include "p18F2520.h"
#include "setup.h"

#include "setting.h"	// Load Customized Source Code
#include "capture.h"				//header file for using library API for input capture

#define MODE 0			// 1 :enable senser
char rxBit = 0;

////////// INTERRUPT HANDLER /////////////
void high_ISR(void);
#pragma code high_vector=0x08
void high_interrupt(void){
	_asm GOTO high_ISR _endasm
}

#pragma code
#pragma interrupt high_ISR
void high_ISR(void){
//	if(PIR1bits.ADIF == 1)
//	{
//		//if(ReadADC() <200 )
//		//	LI_SIGN_LED = ~LI_SIGN_LED;
//		PIR1bits.ADIF = 0;
//	}
//	if(INTCON3bits.INT1IF == 1){
//		LI_SIGN_LED = ~LI_SIGN_LED;
//		INTCON3bits.INT1IF = 0;
//	}

//	if(PIR2bits.TMR3IF == 1) {
//		PIR2bits.TMR3IF = 0;
//		LI_SIGN_LED = ~LI_SIGN_LED;
//		TMR3H=0xFE;
//		TMR3L=0x0B;
//		//rxBit = 1;
//	}

}
/////////////////////////////////////
#pragma udata mydata
 unsigned char buffer1[6],buffer2[6];
 char astr[60]; 
#pragma

void main(void){
	int i = 0,adcResult;
	unsigned char error, checksum;
	value humi_val, temp_val;
	myfloat h_val , t_val;

	//OSCCON |= 0x70;
	//OSCTUNE = 0x40;

	UART_CTS_TRIS = OUT;	
	UART_TX_TRIS = OUT;		 //Tx
	UART_RX_TRIS = IN;		//Rx
	
	CUART_TX_TRIS = OUT;	//TX
	CUART_RX_TRIS = IN;		//RX

	LI_SIGN_LED_TRIS = OUT;

	SHT10_CONN_LED_TRIS = OUT;
	SHT10_SIGN_LED_TRIS = OUT;
	SHT10_CONN_LED = 0;
	SHT10_SIGN_LED = 0;

//	OpenADC(ADC_FOSC_8 & ADC_RIGHT_JUST , ADC_CH0 & ADC_INT_ON , 0);
//	OpenUSART(USART_TX_INT_OFF & USART_RX_INT_ON & USART_ASYNCH_MODE &
//			  USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_HIGH ,BAUD_RATE_GEN);
//	ADCON1 = 0x0d;			//All digital operation	for RA2 & RA0 pins being digital for SHT10 sensor
	RCONbits.IPEN = 1; 		//enable interrupt priority
//
//	IPR1bits.ADIP = 1;		// A/D high interrupt priority 
//	PIR1bits.ADIF = 0;		// A/D converter interrupt flag bit clear
//	PIE1bits.ADIE = 1;		// A/D interrupt enabled
//	
//	IPR1bits.RCIP = 1;		// UART receive interrupt high prority
//	PIR1bits.RCIF = 0;		// clear UART receive flag
//	PIE1bits.RCIE = 1;		// UART Reception interrupt Enable

	IPR1bits.TMR1IP = 1;	// set TMR1 interrupt to high priority	
	//IPR2bits.TMR3IP = 1;	// set TMR3 interrupt to high priority

	//OpenTimer3( TIMER_INT_ON & T3_16BIT_RW & T3_SOURCE_INT & T3_PS_1_1  &  T3_SYNC_EXT_OFF );
	//TMR3H=0xFE;
	//TMR3L=0x0B;

//	s_softreset();			//reset the SHT10 sensor
//	cUSART_tInit();

//	INTCONbits.RBIE = 1;	// enable PORTB change interrupt
//	INTCON2bits.INTEDG1 = 1;// INT1 interrupt on rising edge
//	INTCON3bits.INT1IP = 1;	// high priority
//	INTCON3bits.INT1IE = 1;	// enable INT1 interrupt
//	PIR2bits.TMR3IF = 0;
//	PIR1bits.TMR1IF = 0;
	//INTCONbits.GIEH = 1;	// enable all interrupts
	
//	SetTmrCCPSrc(T3_SOURCE_CCP);
//	OpenCapture1(CAP_EVERY_RISE_EDGE | CAPTURE_INT_OFF );
	while(1){		
		//for(i=0;i<10;i++)
		//	Delay10KTCYx(200);
		for(i=0;i<5;i++)
			DelayUs(200);
		LI_SIGN_LED = ~LI_SIGN_LED;
		
	}
}
