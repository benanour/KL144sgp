/*
UART1BN.H: UART1 header file
BENABADJI Noureddine - ORAN - May 21st, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#ifndef UART1BN_HEADER_H
#define	UART1BN_HEADER_H

//-------------------------------- DEFINES -----------------------------------
#if !defined(SYS_FREQ)
#define SYS_FREQ (32000000L)
#endif 

#if !defined(PBCLK)
#define PBCLK (SYS_FREQ / 1)  // because: #pragma config FPBDIV = DIV_1
#endif 

extern int intT1done ; 

//----------------------------------------------------------------------------
void UART1Init(void) ;
void uart1_set_baudrate (int baudrate) ;
int uart1_write (const void *buffer, int size) ;
int uart1_read (void *buffer, int size) ;

void UART1wrCar(char Ch) ;
void UART1wrStr(char *str) ;
//char UART1GetChar() ;
void val2txt(unsigned int iVal, char *chx, char nbrDigits) ;

#endif	// UART1BN_HEADER_H
