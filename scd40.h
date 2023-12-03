/*
SCD40.h: CO2 sensor I2C header file
BENABADJI Noureddine - ORAN - Nov. 10th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#ifndef   SCD40_HEADER_H
#define	  SCD40_HEADER_H

#define SCD40_ADDR  (0x62)  // (7-bit address)

//---------------------------  VAR.GLO -------------------------------

unsigned short scd40co2 = 0, scd40tem, scd40hum = 0 ;
short scd40temAff = 0 ;
unsigned short scd40serial0 = 0, scd40serial1 = 0, scd40serial2 = 0 ;
unsigned short scd40Toffset = 0, scd40Altitude = 0, scd40Pressure = 0 ;

//extern short zz, hh, mm, ss ; // time elapsed (hours, minutes, sec.)
//extern short jour, mois, annee ; //, bissextile = 0 ;
//extern short TempPart1, TempPart2 ;
//extern char txt[60] ;

//------------------------ external FCT ------------------------------

extern void enT3() ;
extern void disT3() ;

//--------------------------------------------------------------------------
int scd40startPeriodicMeas(void) ;
int scd40stopPeriodicMeas(void) ;
int scd40readMeas(void) ;
int scd40Serial(void) ;

int scd40readToffset(void) ;
int scd40readAltitude(void) ;
int scd40readPressure(void) ;

#endif	  //SCD40_HEADER_H
