/*
mcp7941.h: RTCC chip header file
BENABADJI Noureddine - ORAN - June 10th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#ifndef   MCP79411_HEADER_H
#define	  MCP79411_HEADER_H

#define MCP79411_ADDR_RTC  (0x6F)  // (7-bit address)
#define MCP79411_ADDR_EEP  (0x57)  // (7-bit address)

unsigned short second, minute, hour, m_day, month, year ;

extern short zz, hh, mm, ss ; // time elapsed (hours, minutes, sec.)
extern short jour, mois, annee ; //, bissextile = 0 ;
extern short TempPart1, TempPart2 ;
extern char txt[60] ;

//------------------------ external FCT ------------------------------
//extern void enRTCC() ;
//extern void disRTCC() ;
extern void enT3() ;
extern void disT3() ;
//extern void i2c_wait(unsigned int cnt) ;

//extern unsigned short bcd_to_decimal(unsigned short number) ;
//extern unsigned short decimal_to_bcd(unsigned short number) ;

//--------------------------------------------------------------------------
unsigned short bcd2decimal(unsigned short number) ;
unsigned short decimal2bcd(unsigned short number) ;
//void writeDS3231_0Eh(void) ;
void writeMCP79411_dis32kHz(void) ;
void writeMCP79411_en32kHz(void) ;
//void writeDS3231_ConvTemp(void) ;
//void readDS3231_Temperature(void) ;
void writeMCP79411(void) ;
void readMCP79411(void) ;
char isMCP79411present(void) ;
void EUI48_MCP79411(void) ;
void startMCP79411(void) ;

#endif	  //MCP79411_HEADER_H
