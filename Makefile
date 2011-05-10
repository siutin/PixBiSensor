# MPLAB IDE generated this makefile for use with GNU make.
# Project: proj.mcp
# Date: Tue May 10 14:56:49 2011

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

proj.cof : main.o SHT1x.o delay.o cusart.o SHT1x_helper.o
	$(LD) /l"C:\MCC18\lib" "18f2520_g.lkr" "main.o" "SHT1x.o" "delay.o" "cusart.o" "SHT1x_helper.o" /u_CRUNTIME /z__MPLAB_BUILD=1 /o"proj.cof" /M"proj.map" /W

main.o : main.c C:/MCC18/h/stdio.h C:/MCC18/h/stdlib.h C:/MCC18/h/timers.h C:/MCC18/h/string.h C:/MCC18/h/usart.h C:/MCC18/h/adc.h SHT1x.h SHT1x_helper.h cusart.h main.c C:/MCC18/h/p18F2520.h setup.h C:/MCC18/h/stdarg.h C:/MCC18/h/stddef.h C:/MCC18/h/pconfig.h C:/MCC18/h/p18cxxx.h C:/MCC18/h/p18f2520.h setting.h
	$(CC) -p=18F2520 "main.c" -fo="main.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

SHT1x.o : SHT1x.c SHT1x.h delay.h SHT1x.c C:/MCC18/h/p18cxxx.h C:/MCC18/h/p18f2520.h
	$(CC) -p=18F2520 "SHT1x.c" -fo="SHT1x.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

delay.o : delay.c delay.h delay.c C:/MCC18/h/p18cxxx.h C:/MCC18/h/p18f2520.h
	$(CC) -p=18F2520 "delay.c" -fo="delay.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

cusart.o : cusart.c cusart.h C:/MCC18/h/timers.h cusart.c C:/MCC18/h/pconfig.h C:/MCC18/h/p18cxxx.h C:/MCC18/h/p18f2520.h
	$(CC) -p=18F2520 "cusart.c" -fo="cusart.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

SHT1x_helper.o : SHT1x_helper.c
	$(CC) -p=18F2520 "SHT1x_helper.c" -fo="SHT1x_helper.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "main.o" "SHT1x.o" "delay.o" "cusart.o" "SHT1x_helper.o" "proj.cof" "proj.hex"

