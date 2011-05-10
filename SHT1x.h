/*
***********************************************************************************************
*						SHT1x digital temperature and humidity sensor Driver
*										All Rights Reserved
* File name		: SHT1x.c
* Programmer 	: John Leung, TechToys Co. Hong Kong
* Web presence  : www.TechToys.com.hk
* Note			: 
* Language		: C18 complier version 2.40, MPLAB v7.41
* Hardware		: PIC18LF4550-STK1
* Date			: 11 Oct 2006			Version 1.0 

***********************************************************************************************
*										DESCRIPTION
*
* This module provides an interface to Sensirion SHT10 digital temperature & humidity sensor
*
* pinout function summarized as below
* ---SHT1x			MCU -----------------
* DATA - data		RA2
* SCK  - clock		RA0
***********************************************************************************************
*/

#ifndef SHT1X_H
#define SHT1X_H

/*
***********************************************************************************************
*										PORT DEFINITION
***********************************************************************************************
*/

#define DATA_WR		LATAbits.LATA2
#define	DATA_RD   	PORTAbits.RA2
#define	SCK   		LATAbits.LATA1
#define DATA_TRIS	TRISAbits.TRISA2
#define SCK_TRIS	TRISAbits.TRISA1

/*
***********************************************************************************************
*										GLOBAL CONSTANTS
***********************************************************************************************
*/

enum {TEMP,HUMI};	

/*
***********************************************************************************************
*									FUNCTION PROTOTYPES
***********************************************************************************************
*/
char s_softreset(void);
char s_measure(unsigned char *p_value, unsigned char *p_checksum, unsigned char mode);
char s_write_statusreg(unsigned char *p_value);
char s_read_statusreg(unsigned char *p_value, unsigned char *p_checksum);

/*
***********************************************************************************************
*									FUNCTION PROTOTYPES
*									 HARDWARE SPECIFIC
***********************************************************************************************
*/

void s_transstart(void);
void s_connectionreset(void);
char s_read_byte(unsigned char ack);
char s_write_byte(unsigned char value);
#endif

