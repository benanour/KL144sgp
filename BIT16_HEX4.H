/*
BIT16_HEX4.H: Header File
BENABADJI Noureddine - ORAN - Nov. 13th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#ifndef BIT16_HEX4_HEADER_H
#define	BIT16_HEX4_HEADER_H

extern char hexStr[5] ; // 4 bytes in hexadecimal digit, & hexStr[4] = '\0' ;

//----------------------------------------------------------------------------

char hexChar(unsigned short digit) ;
void Int16_hex4dgt(unsigned short value) ;

#endif	// BIT16_HEX4_HEADER_H
