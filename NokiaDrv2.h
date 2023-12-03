/* 
NokiaDrv2.h: NOKIA 5110 Driver Header File 
BENABADJI Noureddine - ORAN - May 26th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef NOKIADRV2_HEADER_H
#define	NOKIADRV2_HEADER_H

#define  RES   _LATB10  
#define  DC    _LATB11      
#define  CS    _LATB15 //_LATB13
#define  NOKIA_BL   _LATA3

extern char nokiaSleep, txt[60] ; //, fulltxt[40] ; 

//--------------------------------------------------------------------------
void Nokia_Reset() ;
void Nokia_Init(unsigned char Vlcd) ;
void Nokia_Clear() ;
void Nokia_Sleep() ;
void Nokia_Wake() ;
void Nokia_SendCommand(char) ;
void Nokia_SendData(char) ;
void Nokia_SendDataINV(char dat) ;
void Nokia_SendString(char *) ;
//void MSdelay(unsigned int) ;
void Nokia_PositionXY(char, char) ;

void LCD_DrawBat() ;
void LCD_PutChar (char ch) ;
void AffZoom2 (unsigned int val, unsigned char row, unsigned char colpix) ;
void LCD_PutCharZoom2 (char ch, unsigned char Row, unsigned char ColumnPix) ;
void LCD_PutCharX2sendSPI2 (char ch, unsigned char lin, unsigned char colpix, unsigned char qbits) ;
void LCD_DrawLine (unsigned char motif8bit, unsigned char nbrColpix) ;
void LCD_Write_Integer (unsigned int val, int nbrDigits) ;

#endif	// NOKIADRV2_HEADER_H

