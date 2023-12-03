/*
LockUnlock.h: header file
BENABADJI Noureddine - ORAN - May 23rd, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#ifndef LockUnlock_HEADER_H
#define	LockUnlock_HEADER_H

//----------------------------------------------------------------------------
//void  doIdle(char lastmode) ;
//void  doSleep(char lastmode) ;
void  bitSLPEN(char mode) ; //mode=0: IDLE ; mode=1: SLEEP
//void  doPowerSave(char mode) ;

//void system_register_lock (void)  ;
//void system_register_unlock (void) ;
//void system_reset (void) ;

#endif //LockUnlock_HEADER_H
