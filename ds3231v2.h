/*
DS3231v2.h: RTCC chip header file
BENABADJI Noureddine - ORAN - May 24th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#ifndef   DS3231v2_HEADER_H
#define	  DS3231v2_HEADER_H

#define DS3231_ADDR  (0x68)  // (7-bit address)


unsigned short second, minute, hour, m_day, month, year ;

extern short zz, hh, mm, ss ; // time elapsed (hours, minutes, sec.)
extern short jour, mois, annee ; //, bissextile = 0 ;
extern short TempPart1, TempPart2 ;
//extern char presenceDS3231 ;

//------------------------ external FCT ------------------------------
//extern void enRTCC() ;
//extern void disRTCC() ;
extern void enT3() ;
extern void disT3() ;
//extern void i2c_wait(unsigned int cnt) ;

//extern unsigned short bcd_to_decimal(unsigned short number) ;
//extern unsigned short decimal_to_bcd(unsigned short number) ;

//--------------------------------------------------------------------------
unsigned short bcd_to_decimal(unsigned short number) ;
unsigned short decimal_to_bcd(unsigned short number) ;
//void writeDS3231_0Eh(void) ;
void writeDS3231_dis32kHz(void) ;
void writeDS3231_en32kHz(void) ;
void writeDS3231_ConvTemp(void) ;
void readDS3231_Temperature(void) ;
void writeDS1307(void) ;
void readDS1307(void) ;
char isDS3231present(void) ;

#endif	  //DS3231v2_HEADER_H
