#include <p18cxxx.h>
/*
***********************************************************************************************
*										Load Module
***********************************************************************************************
*/
#include "delay.h"
#include "SHT1x.h" 
#include "SHT1x_helper.h"
#include "cusart.h"
/*
***********************************************************************************************
*										PORT DEFINITION
***********************************************************************************************
*/


//SHT10 signal LED pins 
#define SHT10_CONN_LED PORTAbits.RA3
#define SHT10_SIGN_LED PORTAbits.RA4
#define SHT10_CONN_LED_TRIS TRISAbits.TRISA3
#define SHT10_SIGN_LED_TRIS TRISAbits.TRISA4

//build-in USART pins
#define UART_RTS	PORTCbits.RC2
#define UART_CTS	PORTCbits.RC3
#define UART_RTS_TRIS	TRISCbits.TRISC2
#define UART_CTS_TRIS	TRISCbits.TRISC3
#define UART_RX_TRIS TRISCbits.TRISC7
#define UART_TX_TRIS TRISCbits.TRISC6

/*
***********************************************************************************************
*										CUSTOM DEFINE
***********************************************************************************************
*/
#define IN 1
#define OUT 0

// BUILD-IN USART 
// Fosc = 20MHz, Baud Rate = 9600 bps 
#define BAUD_RATE_GEN 129    

#define ACCURACY 10
#define lightValue 150
            
