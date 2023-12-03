/*
SPI1.H: prototypes
BENABADJI Noureddine - ORAN - May 26th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#ifndef   SPI1_HEADER_H
#define	  SPI1_HEADER_H

/* DS39881E: p.147/278
<1:0>: PPRE: Primary Prescale bits (Master mode)
11 = Primary prescale 1:1
10 = Primary prescale 4:1
01 = Primary prescale 16:1
00 = Primary prescale 64:1

<4:2>: SPRE: Secondary Prescale bits (Master mode)
111 = Secondary prescale 1:1
110 = Secondary prescale 2:1
101 = Secondary prescale 3:1  ???
100 = Secondary prescale 4:1  ???
011 = Secondary prescale 5:1  ???
010 = Secondary prescale 6:1  ???
001 = Secondary prescale 7:1  ???
000 = Secondary prescale 8:1
*/

//<1:0>=00 Primary Prescale 64:1
//<4:2>=000 Secondary Prescale 8:1
//<5>=1 Master Mode Enable
//<8>=1 SPI1 Clock Edge

//for SPI1CON1: see TABLE 15-1 p.150/278
#define  SPI_MASTER_BN  0x0120  //00000: 64:1 & 8:1 => 31 kHz 
//#define  SPI_MASTER  0x0123  //00011: 1:1 & 8:1 => 2 MHz
//#define  SPI_MASTER_BN  0x013B    //11011: 1:1 & 2:1 => 8 MHz
//ATTENTION: SPIxCON<4:0> ignored in PIC32

//<15>=1 SPI1 Enable module
//#define  SPI_ENABLE_BN  0x8000 //for SPI1STAT

//#define SPI_BAUD 1 // SPI @ 8MHz = Fpb /(2*(1+1)) with Fpb = 32MHz 
#define SPI_BAUD 3 // SPI @ 4MHz = Fpb /(2*(3+1)) with Fpb = 32MHz 
//#define SPI_BAUD 7 // SPI @ 2MHz = Fpb /(2*(7+1)) with Fpb = 32MHz 
//#define SPI_BAUD 15 // SPI @ 1MHz = Fpb /(2*(15+1)) with Fpb = 32MHz 

//--------------------- external FCT -------------------------
void SPI1INTInit() ;
//unsigned char writeSPI1( unsigned char i ) ;
unsigned char spi1Write (unsigned char i) ;

#endif	  //SPI1_HEADER_H

