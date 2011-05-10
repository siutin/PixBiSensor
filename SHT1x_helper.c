
/*
*********************************************************************************************************
*                         				CALCULATE RH AND TEMPERATURE
*
* Description :	This function returns temperature and relative humidity in floating point values
* Arguments   : float '*p_humidity'		pointer to humidity
*				float '* p_temperature' pointer to temperature
*				
* Returns     : none
* Notes		  : humidity in 12 bit raw data and temperature in 14 bit raw data passed to this
*				function, where at the same ram location, floating point values of temperature and
*				relative humidity value will be returned. 
*				Reference: an Keil C example for 8051 from Sensirion at www.sensirion.com
*********************************************************************************************************
*/	

void calc_sht1x(float *p_humidity ,float *p_temperature)
// calculates temperature [C] and humidity [%RH] 
// input :  humi [Ticks] (12 bit) 
//          temp [Ticks] (14 bit)
// output:  humi [%RH]
//          temp [deg Cel]
{ float rh=*p_humidity;             				// rh:      Humidity [Ticks] 12 Bit 
  float t=*p_temperature;           				// t:       Temperature [Ticks] 14 Bit
  float rh_lin;                     				// rh_lin:  Humidity linear
  float rh_true;                    				// rh_true: Temperature compensated humidity
  float t_C;                        				// t_C   :  Temperature [°C]

  t_C=t*0.01 - 40;                  				//calc. temperature from ticks to [deg Cel]	
  rh_lin=0.0405*rh - 0.0000028*rh*rh - 4.0;     	//calc. humidity from ticks to [%RH]
  rh_true=(t_C-25)*(0.01+0.00008*rh)+rh_lin;   		//calc. temperature compensated humidity [%RH]
  if(rh_true>100)rh_true=100;       				//cut if the value is outside of
  if(rh_true<0.1)rh_true=0.1;       				//the physical possible range

  *p_temperature=t_C;               				//return temperature [deg Cel]
  *p_humidity=rh_true;              				//return humidity[%RH]
}



/*
*********************************************************************************************************

*********************************************************************************************************
*/
void ftoa(unsigned char *buf, float f) {
	unsigned int rem;
	unsigned char *s,length=0;
	int i;

	i = (int)((float)f*10);

	s = buf;
	if (i == 0){ 		//print 0.0 with null termination here
		*s++ = '0';
		*s++ = '.';
		*s++ = '0'; 
		*s=0; 			//null terminate the string
	} else {	
		if (i < 0) {
			*buf++ = '-';
			s = buf;
			i = -i;
		}
		//while-loop to "decode" the long integer to ASCII by append '0', string in reverse manner
		//If it is an integer of 124 -> string = {'4', '2', '1'}
		while (i) {
			++length;
			rem = i % 10;
			*s++ = rem + '0';
			i /= 10;
		}
		//reverse the string in this for-loop, string became {'1', '2', '4'} after this for-loop
		for(rem=0; ((unsigned char)rem)<length/2; rem++) {
			*(buf+length) = *(buf+((unsigned char)rem));
			*(buf+((unsigned char)rem)) = *(buf+(length-((unsigned char)rem)-1));
			*(buf+(length-((unsigned char)rem)-1)) = *(buf+length);
		}

		/* Take care of the special case of 0.x if length ==1*/	
		if(length==1) {
			*(buf+2) = *buf;
			*buf = '0';
			*(buf+1) = '.';
			*(s+2)=0; 			//null terminate
		} else {
			*(buf+length) = *(buf+length-1);
			*(buf+length-1)='.';
			*(s+1)=0; 			//null terminate
		}
	}
}
