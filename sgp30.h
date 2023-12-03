/*
SGP30.h: eCO2 sensor I2C header file
BENABADJI Noureddine - ORAN - Nov. 22nd, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#ifndef   SGP30_HEADER_H
#define	  SGP30_HEADER_H

#define SGP30_ADDR  (0x58)  // (7-bit address)

//---------------------------  VAR.GLO -------------------------------

unsigned short sgp30Version = 0, sgp30SelfTest = 0 ;
unsigned short sgp30eCO2 = 0, sgp30TVOC = 0 ; 
/*
unsigned short scd40co2 = 0, scd40tem, scd40hum = 0 ;
short scd40temAff = 0 ;
unsigned short scd40serial0 = 0, scd40serial1 = 0, scd40serial2 = 0 ;
unsigned short scd40Toffset = 0, scd40Altitude = 0, scd40Pressure = 0 ;

//extern short zz, hh, mm, ss ; // time elapsed (hours, minutes, sec.)
//extern short jour, mois, annee ; //, bissextile = 0 ;
//extern short TempPart1, TempPart2 ;
//extern char txt[60] ;
*/
//------------------------ external FCT ------------------------------

extern void enT3() ;
extern void disT3() ;

//--------------------------------------------------------------------------

int sgp30getVersion(void) ;
int sgp30MeasureTest(void) ;
int sgp30initIAQ(void) ;
int sgp30MeasureIAQ(void) ;

/*
int scd40startPeriodicMeas(void) ;
int scd40stopPeriodicMeas(void) ;
int scd40readMeas(void) ;
int scd40Serial(void) ;

int scd40readToffset(void) ;
int scd40readAltitude(void) ;
int scd40readPressure(void) ;
*/

#endif	  //SGP30_HEADER_H
