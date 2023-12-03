/*
delayPIC32MX.h: delays
BENABADJI Noureddine - ORAN - May 21st, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/
/*src: p.70/271
d:\...\PIC32\EmbeddedComputingWithPIC32.pdf
*/

#include <c:\Program Files\Microchip\xc32\v1.43\pic32mx\include\cp0defs.h>

#ifndef   delayPIC32MX_HEADER_H
#define	  delayPIC32MX_HEADER_H

#define SYS_FREQ (32000000L)

///////////////////////////////////////////////////////////////////////////////
//The Core timer count register is incremented every 2 ticks of SYSCLK.
//Fosc = 32 MHz ; Tosc = 0.03125 us or 31.25 ns ; so 62.5 ns for the Core timer
//as the core timer is 32 bits, it rolls over every 2<32> * 62.5 = 268,43 seconds
// 

//------------------------------------------------------------------
//#define DELAY1uS 16 // 16 core clock ticks, or 1 µs
#define  DELAY1uS  (SYS_FREQ/2000000) // 16 core clock ticks, or 1 µs
void delay1us(short d) 
{
unsigned int j = DELAY1uS * d ;	

  //WriteCoreTimer(0) ; while(ReadCoreTimer() < j) ;
  _CP0_SET_COUNT(0) ; while (_CP0_GET_COUNT() < j) ;
}

//------------------------------------------------------------------
//#define DELAY1mS 16000 // 16 000 core clock ticks, or 1 ms
#define  DELAY1mS  (SYS_FREQ/2000) // 16 000 core clock ticks, or 1 ms
void delay1ms(short d) 
{
unsigned int j = DELAY1mS * d ;	

  //WriteCoreTimer(0) ; while(ReadCoreTimer() < j) ;
  _CP0_SET_COUNT(0) ; while (_CP0_GET_COUNT() < j) ;
}

#endif	//delayPIC32MX_HEADER_H

//-----------------------------------------------------------------------------
/*The include file <cp0defs.h> contains 2 macros for accessing the core timer:
_CP0_GET_COUNT() and _CP0_SET_COUNT(val) ; 
The macro _CP0_GET_COUNT() returns the current core timer count
The macro _CP0_SET_COUNT(val) sets the count to val .

Code Example1:
	unsigned int elapsedticks, elapsedns ;
	_CP0_SET_COUNT(0) ; // set the core timer counter to 0
	... // some code you want to time
	elapsedticks = _CP0_GET_COUNT() ; // read the core timer
	elapsedns = elapsedticks * 62.5 ; // duration in ns, for 32 MHz SYSCLK

Code Example2:
	unsigned int elapsedticks, elapsedns ;
	WriteCoreTimer(0) ; // set the core timer counter to 0; in pic32-libs/peripheral/timer
	... // some code you want to time
	elapsedticks = ReadCoreTimer() ; // read the core timer
	elapsedns = elapsedticks * 62.5 ; // duration in ns, for 32 MHz SYSCLK

Code Example3: writing/readind the core timer to the bare minimum !
	unsigned int elapsed, start = 0 ;
	asm volatile("mtc0 %0, $9": "+r"(start)) ; // WriteCoreTimer(0);
	... // some code you want to time
	asm volatile("mfc0 %0, $9" : "=r"(elapsed)) ; // elapsed = ReadCoreTimer();

The asm command constructs a line of assembly code to be directly inserted by the compiler.
*/

//-----------------------------------------------------------------
/*
// clock-frequecy in Hz with suffix LL (64-bit-long), eg. 32000000LL for 32MHz
#define FOSC  32000000UL 

// clock-frequecy in Hz with suffix LL (64-bit-long), eg. 8000000LL for 8MHz
//#define FOSC  8000000UL 

#ifndef __DELAY_H

//ceci marche pour 32 MHz
#define  FCY       16000000UL  // MCU is running at FCY MIPS
#define  delay_us(x) __delay32(((x)*16UL))   // delays x us
#define  delay_ms(x) __delay32(((x)*16000UL))  // delays x ms

#define __DELAY_H  1
#endif
*/
