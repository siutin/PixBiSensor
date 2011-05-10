#include "p18F2520.h"
#include "setup.h"
#include "setting.h"	// Load Customized Source Code

////////// INTERRUPT HANDLER /////////////
void high_ISR(void);
#pragma code high_vector=0x08
void high_interrupt(void){
	_asm GOTO high_ISR _endasm
}

#pragma code
#pragma interrupt high_ISR
void high_ISR(void){
	if(PIR1bits.ADIF == 1)
	{
		if(ReadADC() <200 )
			LI_SIGN_LED = ~LI_SIGN_LED;
		PIR1bits.ADIF = 0;
	}
//	if(PIR1bits.TMR1IF == 1) {
//		PIR1bits.TMR1IF = 0;
//		//cnt=(cnt == 10)?0:cnt++;
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

	OpenADC(ADC_FOSC_8 & ADC_RIGHT_JUST , ADC_CH0 & ADC_INT_ON , 0);
	OpenUSART(USART_TX_INT_OFF & USART_RX_INT_ON & USART_ASYNCH_MODE &
			  USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_HIGH ,BAUD_RATE_GEN);

	s_softreset();			//reset the SHT10 sensor
	cUSART_tInit();

	ADCON1 = 0x0d;			//All digital operation	for RA2 & RA0 pins being digital for SHT10 sensor
	RCONbits.IPEN = 1; 		//enable interrupt priority
	IPR1bits.ADIP = 1;		// A/D high interrupt priority 
	PIR1bits.ADIF = 0;		// A/D converter interrupt flag bit clear
	PIE1bits.ADIE = 1;		// A/D interrupt enabled
	
	IPR1bits.TMR1IP = 1;	//set TMR1 interrupt to high priorit

	IPR1bits.RCIP = 1;		// receive interrupt high prority

	PIR1bits.RCIF = 0;		//PIR1bits.RCIF
	PIE1bits.RCIE = 1;		//Reception interrupt Enable
	INTCONbits.GIEH = 1;	//enable all interrupts
	
	while(1){

		error=0;
	    error+=s_measure((unsigned char*)&humi_val.i,&checksum,HUMI);  	//measure humidity
	    error+=s_measure((unsigned char*)&temp_val.i,&checksum,TEMP);  	//measure temperature

	    if(error!=0) {
			s_connectionreset();										//in case of an error: connection reset               {
	   		SHT10_CONN_LED = 1;
		}
		else
		{	
			SHT10_CONN_LED = 0;											//sht10 connection success

			ConvertADC();												//start ADC
			while(BusyADC());
			adcResult=ReadADC();

			//memset(dataout,0,60);										//clear array
	      	humi_val.f=(float)humi_val.i;								//converts integer to float
	      	temp_val.f=(float)temp_val.i;								//converts integer to float
			calc_sht1x(&humi_val.f,&temp_val.f);						//calculate humidity, temperature

			//-----------------------------
			
			ftoa(buffer1, temp_val.f);									//convert floating point to string in 1 dec place
			ftoa(buffer2, humi_val.f);									//convert floating point to string in 1 dec place
			sprintf(astr,(const far rom char*)"\rTemperature: %s C Relative Humidity: %s %% Light Intensity: %d \$\n",buffer1,buffer2,adcResult);
		
			//-----------------------------
		
			SHT10_SIGN_LED = ~SHT10_SIGN_LED;
			while(BusyUSART()&& !UART_CTS); 
			putsUSART(astr);
			uputs(astr);
	    }
	      //----------wait approx. 1s to avoid heating up SHTxx--------------          
		
//		if(BusyUSART()&& !UART_CTS){
//			input = getcUSART();
//			putcUSART(input);
//		}
//		uputs(to232);
//		putsUSART(toxbee);
		for(i=0;i<5;i++)
			DelayMs(200);
	}
}
