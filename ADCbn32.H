/*
ADCbn32.H: prototypes
BENABADJI Noureddine - ORAN - May 25th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#ifndef   ADCbn32_HEADER_H
#define	  ADCbn32_HEADER_H

//-------------------external variables----------------------
//extern unsigned int voltage ;

//-------------------external ADC fct------------------------
extern void ADCInit1() ;
//extern void ADCInit16() ;
extern unsigned int ADC_1meas(unsigned int anIO, unsigned int maskIO) ;
//extern unsigned int ADC_16meas(unsigned int anIO, unsigned int maskIO) ;
//extern int ADCAvg(void) ;

#endif	//ADCbn32_HEADER_H
