void lighting(enum lightingType _lightingtype){

	switch (_lightingtype){
		case LITEON:
				PORTB = 0b00000001;break;
		case FULLON:
				PORTB = 0b00001111;break;
		case CROSS:
				PORTB = 0b00001010;break;
		case OFF:
				PORTB = 0b00000000;break;
		case SIGN:
				PORTB = 0b00001100;
		default:
				break;	 
	}
}

void sleep(int time){
	int i;
	for(i=0;i<time;i++)Delay10KTCYx(400);
}
void sleepms(unsigned char time){
	while(time--)Delay10KTCYx(50);
}
void XBeeSend(unsigned char data[]){
	int k;
	for(k=0;k<data[k];k++){
		while(BusyUSART());
		putcUSART(data[k]);
	}
}
void clearRx(){	Rx='\0';}
