/*
eeprom24.h: EEPROM 24LCxx chip header file
BENABADJI Noureddine - ORAN - May 24th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#ifndef   EEPROM24_HEADER_H
#define	  EEPROM24_HEADER_H

#define EEP24LC64_ADDR  (0x50)  //ADDRESS 7-bit, with A0A1A2=000

//unsigned short second, minute, hour, m_day, month, year ;

//extern short zz, hh, mm, ss ; // time elapsed (hours, minutes, sec.)
//extern short jour, mois, annee ; //, bissextile = 0 ;
//extern short TempPart1, TempPart2 ;
extern char txt[60] ;

//------------------------ external FCT ------------------------------
//extern void enT3() ;
//extern void disT3() ;

//--------------------------------------------------------------------------
void writeEEP (unsigned short addr, unsigned char value) ;
//void wr_pageEEP (unsigned short addr, const void *buffer, int size) ;
void wr_pageEEP (unsigned short addr, char *buffer, int size) ;

unsigned short readEEP (unsigned int addr) ;
int rd_pageEEP (unsigned short addr, char *buffer, int size) ;

void Erase_EEP (void) ;

#endif	  //EEPROM24_HEADER_H
