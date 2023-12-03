/* 
Main.h: header file
BENABADJI Noureddine - ORAN - May 26th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#ifndef  MAIN_HEADER_H
#define	 MAIN_HEADER_H

//#define	 ADDR_Toff  4095  //24C32 last addr 0xFFF, to save Toff
#define	 ADDR_Toff  8191  //24LC64 last addr 0x1FFF, to save Toff
#define	 ADDR_adrOfs (ADDR_Toff-2) //to store last adrOfs used before PWR OFF
#define	 ADDR_calib0 (ADDR_Toff-3) //to store last auto zero calib 
#define	 ADDR_alarm1 (ADDR_Toff-4) //to store last alarm1 setting 
#define	 ADDR_Vop    (ADDR_Toff-5) //to store last Vop setting 

#define  BP1  _RB1  //short push => ... ; long push => ... 

/*
#define  NOKIA_BL  _LATB4
#define  PIEZO     _LATA2      //drives the piezo |
#define  PIEZOb    _LATA3      //drives the piezo |=> in opposite level 

//----------------------
//user defined thresholds

#define    LOWBAT	  320	 // 3.20v low battery alarm (1 BipLo, each 5s)
#define    HALTBAT	  270	 // 2.70v stop device (endless sleep)
//----------------------

#define   QQ1     15 //15 minutes (period sample store)
//#define   QQ1    10 //10 minutes
//#define   QQ1    5   //5 minutes

#define   QQ2    4  // 4 x 15 minutes = 1h
//#define   QQ2   6   // 6 x 10 minutes = 1h
//#define   QQ2    12   // 12 x 5 minutes = 1h

//---------- VAR.GLO. définies dans HDC1080.H ------------------

//extern unsigned int tempHDC, humHDC ;
//unsigned int tempHDC = 0, humHDC = 0 ;

//---------- VAR.GLO. définies dans DS1307.H ------------------

short jour = 15, mois = 7, annee = 20 ; //, bissextile = 0 ;
short hh = 12, mm = 30, ss = 1 ; // time elapsed (hours, minutes, sec.)

//------------ VAR.GLO. définies dans PG14.C -------------------

char nokiaSleep = 0, txt[12] ; //, fulltxt[40] ; 
*/

#endif  //MAIN_HEADER_H
