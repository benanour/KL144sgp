/* Nokia 5110 LCD interface
BENABADJI Noureddine - ORAN - May 26th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
 */

#include <c:\Program Files\Microchip\xc32\v1.43\pic32mx\include\xc.h>
#include "SPI1.H"
#include "NokiaDrv2.h"
#include "NokiaFont.h"

extern int meas_Vbat ;

char bytes[5], bytesZoom2 ; int ii, jj ;

//-----------------------------------------------------------------------------
void Nokia_SendCommand(char cmd)
{
  DC = 0 ;         // Data/Command pin, D/C=1 - Data, D/C = 0 - Command
  CS = 0 ;         // enable chip
  spi1Write(cmd) ; // write command to the Nokia 5110
  CS = 1 ;         // disable chip
}
//-----------------------------------------------------------------------------
void Nokia_SendData(char dat)
{
short i ;
 
  if (nokiaSleep) return ; //NOKIA is in sleep mode  

  DC = 1 ;         // Data/Command pin, D/C=1 - Data, D/C = 0 - Command
  CS = 0 ;         // enable chip 
  for (i=0; i<5; i++) spi1Write(font[dat - 32][i]) ; //write data to Nokia 
  CS = 1 ;         // disable chip 
}
//-----------------------------------------------------------------------------
void Nokia_SendDataINV(char dat)
{
short i ; unsigned char car ;
 
  if (nokiaSleep) return ; //NOKIA is in sleep mode  

  DC = 1 ;         // Data/Command pin, D/C=1 - Data, D/C = 0 - Command
  CS = 0 ;         // enable chip 
  for (i=0; i<5; i++) { car = font[dat-32][i]; car = 255 - car; spi1Write(car);}
  CS = 1 ;         // disable chip 
}

//-----------------------------------------------------------------------------
void Nokia_SendString(char *data)
{
  if (nokiaSleep) return ; //NOKIA is in sleep mode
  while ((*data) != 0)
  {   
    Nokia_SendData(*data) ;
    data++ ;
  }   
}
//-----------------------------------------------------------------------------
void Nokia_PositionXY(char X, char Y) // 0 <= X <= 83   0 <= Y <= 5
{
  if (nokiaSleep) return ; //NOKIA is in sleep mode

  Nokia_SendCommand(0x80 | X) ;    // set column pix X position
  Nokia_SendCommand(0x40 | Y) ;    // set line Y position  
}
//-----------------------------------------------------------------------------
void Nokia_Reset()
{
    //apply 100 ms reset(low to high) pulse
  //maximum time of 100 ms after Vdd goes HIGH (PCD8544 datasheet 15/32)
  //RES = 0 ; delay100ms() ; RES = 1 ;
  RES = 0 ; delay1ms(5) ; RES = 1 ; 
}
//-----------------------------------------------------------------------------
void Nokia_Init(unsigned char Vlcd)
{
  Nokia_Reset() ;

  Nokia_SendCommand(0x21) ;    // display extended commands

//ATTENTION: 0x12 pour KL139ex1 ; 0x13 pour KL139ex3 & breadboard
  //Nokia_SendCommand(0x13) ;  // foncé. Bias voltage: 0x10...0x17 p.14&15/32 PCD8544.PDF 
  //Nokia_SendCommand(0x15) ;  // trop foncé. Bias brightness: 0x10...0x17 p.14/32 PCD8544.PDF 
  Nokia_SendCommand(0x11) ;    // OK.  Bias voltage: 0x10...0x17 p.14&15/32 PCD8544.PDF 
  //Nokia_SendCommand(0x14) ;  // Bias voltage: 0x10...0x17 p.14&15/32 PCD8544.PDF 

  //Nokia_SendCommand(0x07) ;    // Temperature Coefficient
  Nokia_SendCommand(0x04) ;    // Temperature Coefficient

//ATTENTION: 0xB1 pour KL139ex1 ; 0xC1 pour KL139ex3 & breadboard
  //Nokia_SendCommand(0xC7) ;    //foncé++ Vop contrast: 0xC0...0xFF p.14/32 PCD8544.PDF   
  //Nokia_SendCommand(0xC0) ;    //foncé Vop contrast: 0xC0...0xFF p.14/32 PCD8544.PDF   
  ///////Nokia_SendCommand(0xC1) ;    //clair Vop contrast: 0xC0...0xFF p.14/32 PCD8544.PDF   
  Nokia_SendCommand(Vlcd) ;    //clair Vop contrast: 0xC0...0xFF p.14/32 PCD8544.PDF   
  //Nokia_SendCommand(0xBF) ;    //clair+ Vop contrast: 0xC0...0xFF p.14/32 PCD8544.PDF   
  ///////Nokia_SendCommand(0xB9) ;    //clair++ Vop contrast: 0xC0...0xFF p.14/32 PCD8544.PDF   
  //Nokia_SendCommand(0xB1) ;    //clair+++ Vop contrast: 0xC0...0xFF p.14/32 PCD8544.PDF   

  Nokia_SendCommand(0x20) ;    // display basic commands    
  Nokia_SendCommand(0x0C) ;    // set normal mode 
}
//-----------------------------------------------------------------------------
void Nokia_Sleep()
{
// A TESTER: activer Nokia_Clear() ; decrease Ipd davantage ?
 
  //Nokia_Clear() ; //zero's the whole RAM to lower Ipd
  Nokia_SendCommand(0x27) ;    // bit PD=1: chip is in Power-down mode
}
//-----------------------------------------------------------------------------
void Nokia_Wake()
{
  Nokia_SendCommand(0x20) ;    // bit PD=0: chip is active
}

//-----------------------------------------------------------------------------
void Nokia_Clear()
{
char i, j ;

  if (nokiaSleep) return ; //NOKIA is in sleep mode

  CS = 0 ;
  DC = 1 ;
  for (i=0; i<6; i++)
    for (j=0; j<84; j++) spi1Write(0) ;       /*write 0 to clear display */
        
  CS = 1 ;  
}

//-----------------------------------------------------------------------------
// void LCD_DrawBat(int pourcent)
// returns nothing
// Displays battery with percentage
//-----------------------------------------------------------------------------
void LCD_DrawBat()
{   
  if (nokiaSleep) return ; //NOKIA is in sleep mode

  Nokia_PositionXY (1, 5) ; Nokia_SendString(txt);

  Nokia_PositionXY (18, 5) ; LCD_PutChar('V') ;
  Nokia_PositionXY (5, 5) ; LCD_DrawLine (0x80, 1) ; //decimal point
    
  int z = meas_Vbat / 100 ;
  Nokia_PositionXY (0, 5) ; LCD_PutChar(48+z) ;
}
//-----------------------------------------------------------------------------
// void OLED_PutChar(char ch)
// returns nothing
// Displays character ch into OLED
//-----------------------------------------------------------------------------
void LCD_PutChar (char ch)
{
short i ;

  if (nokiaSleep) return ; //NOKIA is in sleep mode

  //if ( (ch < 32) || (ch > 127) ) { ch = ' ' ; }
  if (ch < 32) ch = ' ' ;
  
  for (i=0; i<5; i++) bytes[i] = font[ch - 32][i] ;  
 
  for (i=0; i<5; i++) 
  { DC = 1 ;         // Data/Command pin, D/C=1 - Data, D/C = 0 - Command
    CS = 0 ;         // enable chip
    spi1Write(bytes[i]) ;   
    CS = 1 ;         // disable chip 
  }
}

//-----------------------------------------------------------------------------
void AffZoom2 (unsigned int val, unsigned char row, unsigned char colpix)
{
unsigned char ch ;
short i ;
 
  if (nokiaSleep) return ; //NOKIA is in sleep mode
     
  for (i=1; i<=4; i++)    
  { ch = val % 10 + 48 ; val /= 10 ; 
    LCD_PutCharZoom2( ch, row, colpix) ; colpix -= 13 ; 
  }   
}

//-----------------------------------------------------------------------------
// void LCD_PutCharZoom2 (char ch, unsigned char Row, unsigned char ColumnPix)
// returns nothing
// Displays character ch, zoomed x2, @ Row, ColumnPix
//-----------------------------------------------------------------------------
void LCD_PutCharZoom2 (char ch, unsigned char Row, unsigned char ColumnPix)
{
  if (nokiaSleep) return ; //NOKIA is in sleep mode

  //if ( (ch < 32) || (ch > 127) ) { ch = ' ' ; }
  if (ch < 32) ch = ' ' ;
   
  LCD_PutCharX2sendSPI2 (ch, Row, ColumnPix, 0) ;
  LCD_PutCharX2sendSPI2 (ch, Row+1, ColumnPix, 4) ;
}

///////////// INTERNAL FUNCTION: CALLED ONLY BY LCD_PutCharZoom2 
void LCD_PutCharX2sendSPI2 (char ch, unsigned char lin, unsigned char colpix, unsigned char qbits)
{
  for (ii=0; ii<5; ii++) bytes[ii] = font[ch - 32][ii] ;  

  Nokia_PositionXY (colpix, lin) ;
  
  for (ii = 0; ii < 5; ii++) 
  { jj = (bytes[ii] >> qbits) & 0x0F ; bytesZoom2 = lutZoom2[jj] ;
    
    DC = 1 ;         // Data/Command pin, D/C=1 - Data, D/C = 0 - Command
    CS = 0 ;         // enable chip
    spi1Write(bytesZoom2) ; spi1Write(bytesZoom2) ;  
    CS = 1 ;         // disable chip 
  }
}

//-----------------------------------------------------------------------------
// void LCD_DrawLine (uint8_t motif8bit, unsigned char nbrColpix)
// returns nothing
// Displays a horiz. line (according to byte motif8bit) with Length = nbrColpix
//-----------------------------------------------------------------------------
void LCD_DrawLine (unsigned char motif8bit, unsigned char nbrColpix)
{
  if (nokiaSleep) return ; //NOKIA is in sleep mode

  DC = 1 ;         // Data/Command pin, D/C=1 - Data, D/C = 0 - Command
  CS = 0 ;         // enable chip
  for (ii = 0; ii < nbrColpix; ii++) spi1Write(motif8bit) ;
  //Send_I2C_StopBit();    
  CS = 1 ;// send stop bit
}
//OPTIMISATION-----------------------------------------------------------------
// void OLED_Write_Integer (unsigned int iVal, uint8_t nbrDigits)
// returns nothing
// Displays integer iVal into OLED, with nbrDigits places
//-----------------------------------------------------------------------------
void LCD_Write_Integer (unsigned int val, int nbrDigits)
{
char str[5] = {0,0,0,0,0} ;

  if (nokiaSleep) return ; //NOKIA is in sleep mode

  ii = 4 ;
  while(val) { str[ii] = val % 10 ; val /= 10 ; ii-- ; }
  jj = 5 - nbrDigits ;
  //if (val < 0) LCDData('-') ;
  for (ii=jj; ii<5; ii++) LCD_PutChar(48+str[ii]) ;
}
