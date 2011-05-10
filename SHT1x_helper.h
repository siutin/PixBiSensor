
#ifndef SHT1X_HELPER_H
#define SHT1X_HELPER_H
	// SHT10 return type
	typedef union
	{
		unsigned int i;
		float f;
	} value;
	
	typedef union
	{
		unsigned int first;
		unsigned int second;
	} myfloat;
	
	void ftoa(unsigned char *buf, float f);
	void calc_sht1x(float *p_humidity ,float *p_temperature);
#endif