/*
UART1BN.C: UART1 functions
BENABADJI Noureddine - ORAN - May 21st, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#include <c:\Program Files\Microchip\xc32\v1.43\pic32mx\include\xc.h>
#include "uart1bn.h"

//----------------------------------------------------------------------------
void UART1Init(void)
{
  /*  //U1RX = RA2 or RA4 or RB2 or RB6 or RB13 (p.134/350 datasheet)
  _TRISB2 = 1 ; U1RXRbits.U1RXR = 0x0004 ;	// RB2->UART1:U1RX
    //U1TX = RA0 or RB3 or RB4 or RB7 or RB15 (p.136/350 datasheet)
  _TRISB7 = 0 ; RPB7Rbits.RPB7R = 0x0001 ;	// RB7->UART1:U1TX
  */
    
/*
     //Set up UART1
  U1BRG = BAUDRATEREG1 ; //set baud speed
  U1MODE = 0x8008 ;		 // enable, BREGH=1, 1 stop, no parity
  //U1MODE = 0x8080 ; //<15>=1 UARTEN + <7>=1 WAKEUP
  U1STA = 0x0400 ;		//<10>=1 UTXEN
  //U1STA = 0x8400 ; //<15,13>=1,0 set interrupts + <10>=1 UTXEN
 
  IFS1bits.U1TXIF = 0 ; //clear TX interrupt flag
  IEC1bits.U1TXIE = 1 ;	//enable TX interrupt
  IFS1bits.U1RXIF = 0 ; //clear RX interrupt flag
  IEC1bits.U1RXIE = 1 ;	//enable RX interrupt
 */

  U1MODE = 0x0008;
  U1STA = 0x0;
  uart1_set_baudrate (115200) ;

  // Enabling UART1
  U1STAbits.UTXEN = 1;	  // TX_enable
  U1STAbits.URXEN = 1;	  // RX_enable
  U1MODEbits.ON = 1;
    
  IFS1bits.U1TXIF = 0 ;   //clear TX interrupt flag
  IFS1bits.U1RXIF = 0 ;   //clear RX interrupt flag
  U1STAbits.URXISEL = 0x0;// RX interrupt when receive buffer not empty

  IPC8bits.U1IP = 1 ;	// UART1 Interrupt priority.
  IPC8bits.U1IS = 0 ;	// UART1 Interrupt sub-priority.
  
  //IEC1bits.U1TXIE = 1 ;	  //enable TX interrupt ; SINON ça bloque !!! 
  IEC1bits.U1RXIE = 1 ;	  //enable RX interrupt
}

//----------------------------------------------------------------------------
void uart1_set_baudrate (int baudrate)
{    
  unsigned int  brg_x16 = ((unsigned int )PBCLK << 2) / baudrate ;
  U1BRG = (brg_x16 >> 4) + ((brg_x16 & 0xf) >> 3) - 1 ;
}

//----------------------------------------------------------------------------
int uart1_write (const void *buffer, int size)
{
const unsigned char *p = (const unsigned char *)buffer ;
int n = size ;

  while (n > 0)
  { while (U1STAbits.UTXBF) { Nop() ; Nop() ; Nop() ; Nop() ; }
    U1TXREG = *p++ ;
    n-- ;
  }
  return size;
}

//----------------------------------------------------------------------------
int uart1_read (void *buffer, int size)
{
char *p = (char *)buffer ;
unsigned int sta = U1STA ;

  while (intT1done == 0)
  { sta = U1STA ;
    if (sta & (1 << _U1STA_OERR_POSITION)) U1STACLR = (1 << _U1STA_OERR_POSITION) ;

    if (sta & (1 << _U1STA_URXDA_POSITION))
    {
      *p++ = U1RXREG ; if (p - (char*)buffer >= size) break ;
    } 
    else 
      { if (p != buffer) break ;
        Nop() ; Nop() ; Nop() ; Nop() ;
      }
  }
  return p - (char*)buffer ;
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//UART transmit function, parameter Ch is the character to send
void UART1wrCar(char Ch) //p.229/554, Lucio:
{
  //transmit ONLY if TX buffer is empty
  while(U1STAbits.UTXBF == 1) ;
  U1TXREG = Ch ;
}

//-----------------------------------------------------------------------------
void UART1wrStr(char *str)
{
  while (*str != '\0') { UART1wrCar(*str) ; str++ ; }
}

/*-----------------------------------------------------------------------------
//UART receive function, returns the value received.
char UART1GetChar() //p.229/554, Lucio:
{
char Temp ;

  //wait for buffer to fill up, wait for interrupt
  while(IFS1bits.U1RXIF == 0) ;
  //selon Lucio: 
  //while ( !U1STAbits.URXDA); // wait for a new char to arrive
  Temp = U1RXREG ;

  //reset interrupt
  IFS1bits.U1RXIF = 0 ;

  //return my received byte
  return Temp ; 
}
*/
//----------------------------------------------------------------------------
void val2txt(unsigned int iVal, char *chx, char nbrDigits)
{
char t = 0 ;  
    
  if (nbrDigits > 4)  chx[t++] = (iVal / 10000) % 10 + 48 ; //ten thousands
  if (nbrDigits > 3)  chx[t++] = (iVal / 1000) % 10 + 48 ; //thousands
  if (nbrDigits > 2)  chx[t++] = (iVal / 100) % 10 + 48 ;  //hundreds
  if (nbrDigits > 1)  chx[t++] = (iVal / 10) % 10 + 48 ;   //tens
                      chx[t++] = iVal % 10 + 48 ;          //units
  chx[t] = 0 ;
}
