#include "p18F2520.h"
#include "setup.h"
#include "setting.h"	// Load Customized Source Code


#pragma udata mydata
 enum boolean{FALSE,TRUE};
 enum boolean ADCfirst = FALSE;
 unsigned char buffer1[6],buffer2[6];
 unsigned char Rx;
 int adcResult;
 char to232[]="to RS232 ";
 char toxbee[]="to xBee";
 char astr[60]; 
#pragma

////////// INTERRUPT HANDLER /////////////
void high_ISR(void);
#pragma code high_vector=0x08
void high_interrupt(void){
	_asm GOTO high_ISR _endasm
}

#pragma code
#pragma interrupt high_ISR
void high_ISR(void){
//-----------USART handler Start --------------

	if(PIR1bits.RCIF) {	
		//if(!BusyUSART() && !UART_xBee_RTS){
		//while(BusyUSART());
			Rx = getcUSART();
		//while(BusyUSART());
			putcUSART(Rx);
		//}
		//}
		PIR1bits.RCIF = 0;
	}
	
//-----------USART handler End --------------

	if(PIR1bits.ADIF)
	{
		if(ADCfirst){
			PIE1bits.ADIE = 0;
			ADCfirst = FALSE;
		}else {
			if(adcResult <200 ){
				ADCfirst = TRUE;
				LI_SIGN_LED = ~LI_SIGN_LED;
			}
		}
		PIR1bits.ADIF = 0;
	}

//	if(PIR1bits.TMR1IF == 1) {
//		PIR1bits.TMR1IF = 0;
//		//cnt=(cnt == 10)?0:cnt++;
//	}
}
/////////////////////////////////////


void main(void){
	enum xEvent{MEASURE,CHECK,ERROR,MLIGHT,CONVCALC,TOSTRING,PRINT,SLEEP};
	enum xEvent e = MEASURE;
	int i = 0,cnt =0;
	unsigned char error, checksum;
	value humi_val, temp_val;
	myfloat h_val , t_val;

	OSCCON |= 0x70;
	OSCTUNE = 0x40;

	UART_xBee_RTS_TRIS = OUT;	
	UART_xBee_CTS_TRIS = IN;
	
	UART_TX_TRIS = OUT;		 //Tx
	UART_RX_TRIS = IN;		//Rx
	UART_xBee_RTS = 1;

	CUART_TX_TRIS = OUT;	//TX
	CUART_RX_TRIS = IN;		//RX

	LI_SIGN_LED_TRIS = OUT;

	SHT10_CONN_LED_TRIS = OUT;
	SHT10_SIGN_LED_TRIS = OUT;
	SHT10_CONN_LED = 0;
	SHT10_SIGN_LED = 0;

	RCONbits.IPEN = 1; 		//enable interrupt priority

	OpenADC(ADC_FOSC_8 & ADC_RIGHT_JUST , ADC_CH0 & ADC_INT_ON , 0);

	ADCON1 = 0x0d;			//All digital operation	for RA2 & RA0 pins being digital for SHT10 sensor
	IPR1bits.ADIP = 1;		// A/D high interrupt priority 
	PIR1bits.ADIF = 0;		// A/D converter interrupt flag bit clear
	PIE1bits.ADIE = 1;		// A/D interrupt enabled

	OpenUSART(USART_TX_INT_OFF & USART_RX_INT_ON & USART_ASYNCH_MODE &
			  USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_HIGH ,BAUD_RATE_GEN);

	IPR1bits.RCIP = 1;		// UART receive interrupt high prority
	PIR1bits.RCIF = 0;		// clear UART receive flag
	PIE1bits.RCIE = 1;		// UART Reception interrupt Enable
	IPR1bits.TMR1IP = 1;	//set TMR1 interrupt to high priorit

	INTCONbits.GIEH = 1;	//enable all interrupts

	s_softreset();			//reset the SHT10 sensor
	cUSART_tInit();

	while(1){
		switch(e){
			case MEASURE:
							error=0;
				   			error+=s_measure((unsigned char*)&humi_val.i,&checksum,HUMI);  	//measure humidity
				   			error+=s_measure((unsigned char*)&temp_val.i,&checksum,TEMP);  	//measure temperature
							e = CHECK;
							break;
			case CHECK:
							if(error!=0)
								e = ERROR;	
							else
								e = MLIGHT;
							break;
			case ERROR:
							s_connectionreset();			//in case of an error: connection reset               {
	   						SHT10_CONN_LED = 1;
							e = MEASURE;
							break;
			case MLIGHT:
							SHT10_CONN_LED = 0;											//sht10 connection success

							ConvertADC();												//start ADC
							while(BusyADC());
							adcResult=ReadADC();
							e = CONVCALC;
							break;
			case CONVCALC: 
							//memset(dataout,0,60);										//clear array
					      	humi_val.f=(float)humi_val.i;								//converts integer to float
					      	temp_val.f=(float)temp_val.i;								//converts integer to float
							calc_sht1x(&humi_val.f,&temp_val.f);						//calculate humidity, temperature
							e = TOSTRING;
			case TOSTRING:
							//-----------------------------
							ftoa(buffer1, temp_val.f);									//convert floating point to string in 1 dec place
							ftoa(buffer2, humi_val.f);									//convert floating point to string in 1 dec place
							//sprintf(astr,(const far rom char*)"\rTemperature: %s C Relative Humidity: %s %% Light Intensity: %d \$\n",buffer1,buffer2,adcResult);						
							sprintf(astr,(const far rom char*)"T: %s RH: %s LI: %d \$",buffer1,buffer2,adcResult);						
							//-----------------------------
							e = PRINT;
							break;
			case PRINT:	
							SHT10_SIGN_LED = ~SHT10_SIGN_LED;
							while(BusyUSART()&& !UART_xBee_RTS); 
							putsUSART(astr);
							uputs(astr);
							e = SLEEP;
							//PIE1bits.ADIE = 1;
							break;
			case SLEEP:
								//DelayMs(200);
							Delay10KTCYx(100);
							if(cnt==8){
								e = MEASURE;
								cnt=0;
							}else
								cnt++;
							break;
		}

	    //putcUSART('.');
	      //----------wait approx. 1s to avoid heating up SHTxx--------------          
		
	}
}
