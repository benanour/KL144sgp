/*
HDC1080v2.h: header file, driver for HDC1080 sensor routines
BENABADJI Noureddine - ORAN - May 22nd, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#ifndef HDC1080v2_HEADER_H
#define	HDC1080v2_HEADER_H

//#define HDC1080_ADDR  (0x40 << 1)  // (7-bit address)
#define HDC1080_ADDR  (0x40)  // (7-bit address)

//---------------------------  VAR.GLO -------------------------------

unsigned int tempHDC = 0, humHDC = 0 ;

//============================= external fct ================================= 

extern void HDC1080_Init(void) ;
extern unsigned int HDC1080_readID(unsigned char c) ;
extern void HDC1080_read(void) ;

#endif //HDC1080v2_HEADER_H
