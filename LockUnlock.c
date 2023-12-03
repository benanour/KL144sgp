/*
LockUnlock.c: Lock and Unlock functions
BENABADJI Noureddine - ORAN - May 23rd, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#include <c:\Program Files\Microchip\xc32\v1.43\pic32mx\include\xc.h>
#include "LockUnlock.h"

//----------------------------------------------------------------------------
void  bitSLPEN(char mode) //mode=0: IDLE ; mode=1: SLEEP
{
    __builtin_disable_interrupts();
  
    SYSKEY = 0x33333333 ; // write invalid key to force lock
    SYSKEY = 0xAA996655 ; // write key1 to SYSKEY
    SYSKEY = 0x556699AA ; // write key2 to SYSKEY
  
    OSCCONbits.SLPEN = mode ;
  
    SYSKEY = 0x0 ;  //lock again

    __builtin_enable_interrupts();
    Nop() ;   
}

/*//----------------------------------------------------------------------------
void  doPowerSave(char mode) //mode=0: IDLE ; mode=1: SLEEP
{
    __builtin_disable_interrupts();
  
    SYSKEY = 0x33333333 ; // write invalid key to force lock
    SYSKEY = 0xAA996655 ; // write key1 to SYSKEY
    SYSKEY = 0x556699AA ; // write key2 to SYSKEY
  
    OSCCONbits.SLPEN = mode ;
  
    SYSKEY = 0x0 ;  //lock again

    __builtin_enable_interrupts();
    Nop() ;   
  
  __asm__ __volatile__ ("wait"); //IDLE if SLPEN == 0 ;
  Nop() ;
}*/

/*
//----------------------------------------------------------------------------
void system_register_lock(void)
{
  SYSKEY = 0x0 ;
}

//----------------------------------------------------------------------------
void system_register_unlock(void)
{
unsigned int status ;

    // Suspend or Disable all Interrupts
  asm volatile ("di %0" : "=r" (status)) ;
  //__builtin_disable_interrupts();  

    // starting critical sequence
  SYSKEY = 0x33333333 ; // write invalid key to force lock
  SYSKEY = 0xAA996655 ; // write key1 to SYSKEY
  SYSKEY = 0x556699AA ; // write key2 to SYSKEY

    // Restore Interrupts
  if (status & 0x00000001) { asm volatile ("ei"); } else { asm volatile ("di"); }
  //__builtin_enable_interrupts();  
}

//----------------------------------------------------------------------------
void system_reset(void) //software reset	DS60001118H
{
  system_register_unlock() ;

  RSWRSTSET = 1 ;

  // read RSWRST register to trigger reset
  unsigned int dummy = RSWRST ;
  (void)dummy ;

  while (1) ;
}
*/
