/*
SPI1.c: fonctions SPI1INTInit() + writeSPI1()
BENABADJI Noureddine - ORAN - May 26th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#include <c:\Program Files\Microchip\xc32\v1.43\pic32mx\include\xc.h>
#include "SPI1.H"

//declare variables
//unsigned int prescale ;  // ?????

//-----------------------------------------------------------------------------
void SPI1INTInit()
{
  //IFS0bits.SPI1IF = 0 ;	   // clear interrupt flag
  //a PIC32 SPI interrupt can be due to TX, RX or fault error
  IFS1bits.SPI1TXIF = 0 ;
  IFS1bits.SPI1RXIF = 0 ;
  IFS1bits.SPI1EIF = 0 ;
  
/*  
  //ATTENTION CECI BLOQUE LE DEMARRAGE !
  IPC7bits.SPI1IP = 2 ;	// SPI1 Interrupt priority.
  IPC7bits.SPI1IS = 0 ;	// SPI1 Interrupt sub-priority.
*/ 
  //IEC0bits.SPI1IE = 1 ;	   // enable interrupt
  IEC1bits.SPI1TXIE = 1 ;
  IEC1bits.SPI1RXIE = 1 ;
  IEC1bits.SPI1EIE = 1 ;

  //SPI1CON1 = SPI_MASTER ;  // select mode
  SPI1CON = SPI_MASTER_BN ;  // select mode
  
  //sans effet dans PIC32
  //SPI1STAT = SPI_ENABLE ;  // enable the peripheral
  //SPI1STAT = SPI_ENABLE_BN ;  // enable the peripheral
  
  SPI1CONbits.ON = 1 ; // enable SPI1
  //p.50/320, PIC32MX230F064B.pdf datasheet DS61168D (2012)
  
  SPI1BRG = SPI_BAUD; // select clock speed
  //SPI2SPI2BRG = SPI_BAUD; // select clock speed
}

//-----------------------------------------------------------------------------
// send one byte of data and receive one back at the same time
//unsigned char writeSPI1( unsigned char i )
unsigned char spi1Write (unsigned char i)
{
    SPI1BUF = i;					// write to buffer for TX
    while(!SPI1STATbits.SPIRBF);	// wait for transfer to complete
    return SPI1BUF;    				// read the received value
}

//-----------------------------------------------------------------------------
/* METTRE CECI A LA FIN DU FICHIER PRINCIPAL MAIN.C 
void __attribute__((interrupt, no_auto_psv)) _SPI1Interrupt()
{
  // add code here
  IFS0bits.SPI1IF = 0 ;	
}
*/
