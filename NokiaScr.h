/* 
NokiaScr.h: Header File 
BENABADJI Noureddine - ORAN - May 26th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef NOKIASCR_HEADER_H
#define	NOKIASCR_HEADER_H
/*
#define  RES   _LATB10  
#define  DC    _LATB11      
#define  CS    _LATB15 //_LATB13
#define  NOKIA_BL   _LATA3
*/
extern char nokiaSleep, txt[60] ; //, fulltxt[40] ; 
extern short hh, mm, ss ; // time elapsed (hours, minutes, sec.)
extern short jour, mois, annee, jmax ; //, bissextile = 0 ;
//extern int intT1done, meas_Vbat, meas_NH3, meas_NH3inV, meas_NH3cn ;
extern int intT1done, meas_Vbat, meas_NH3, measTVOC ;
extern unsigned int calib, ppminterval[18], ppmtriee[18] ;
extern short ippmin, ippmax ;

extern unsigned int ppbinterval[18], ppbtriee[18] ;
extern short ippbin, ippbax ;

extern char Toff, ToffOld ;

extern unsigned int nPacketSaved, adrOfs ;
extern unsigned char longPush, BP1timeout ;
extern unsigned int alarm1, alarm2, alarm3 ;

extern char presenceDS3231, presenceMCP79411 ;

extern unsigned char Slave24LC64 ;

extern unsigned int tempHDC, humHDC ; //dans HDC1080.h
extern short scd40temAff ;
extern unsigned short scd40hum ;

unsigned char Vop = 0xBD ; //Contrast setting: 0xB8 (clair++) to 0xC2 (foncé++)
unsigned char VopMIN = 184, VopMAX = 194 ;

//--------------------------------------------------------------------------
void NokiaSplash1(void) ;
void NokiaSysReport(void) ;
void NokiaSysCfgMenu(void) ;
void NokiaSysCfg1(void) ;
void NokiaSysCfg2(void) ;
void NokiaSysCfg3(void) ;
void NokiaSysCfg4(void) ;
void NokiaSysCfg5(void) ;
void NokiaSysCfg6(void) ;
void AffDgt(char i, char p, char star, char inv) ;
void hhmmssIncrement (char i) ;
void ddmmyyIncrement (char i) ;
char ChosenOptionRTCC (char linTop, char choix) ;
char ChosenOption (char linTop, char choix) ;
void mainScr (char zone) ;
void tablScr (void) ;
void statScr (void) ;
void DispVbatLow  (void) ;
void DispVbatFlat  (void) ;

#endif	// NOKIASCR_HEADER_H

