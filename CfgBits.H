/*
CfgBits.H: CONFIGURATION BIT SETTINGS
BENABADJI Noureddine - ORAN - May 20th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

//----------------------- CONFIGURATION BIT SETTINGS --------------------------
// DEVCFG3__________VU
// USERID = No Setting
//#pragma config FSRSSEL = PRIORITY_7     // Shadow Register Set Priority Select (SRS Priority 7)
#pragma config PMDL1WAY = ON            // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow only one reconfiguration)

// DEVCFG2_____reglage SYSCLK = 32 MHz <= (8MHz FRCPLL / FPLLIDIV * FPLLMUL / FPLLODIV)
#pragma config FPLLIDIV = DIV_2        // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_16        // PLL Multiplier (16x Multiplier)
#pragma config FPLLODIV = DIV_2        // Syst. PLL Output Clk Divider (PLL Divide /256)

// DEVCFG1__________VU
#pragma config FNOSC = FRCPLL         // Osc. Selection Bits (Fast RC Osc w/PLL)
#pragma config FSOSCEN = ON           // Secondary Oscillator (enabled)
#pragma config IESO = OFF             // Internal/External Switch Over (disabled)
#pragma config POSCMOD = OFF          // Primary Oscillator Configuration (disabled)
#pragma config OSCIOFNC = OFF         // CLKO Output Signal desactived on the OSCO Pin
#pragma config FPBDIV = DIV_1         // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)
/*
Meas:
OSCO(pin10)= 8MHz if FPBDIV = DIV_8 
OSCO(pin10)=64MHz if FPBDIV = DIV_1 
OSCO(pin10)=32MHz if FPBDIV = DIV_1 & FPLLODIV = DIV_2  
*/
#pragma config FCKSM = CSDCMD         // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576      // Watchdog Timer Postscaler (1:1048576)
#pragma config WINDIS = OFF           // Watchdog Timer Window Enable (Watchdog Timer is in Non-Window Mode)
#pragma config FWDTEN = OFF           // Watchdog Timer (WDT disabled)
#pragma config FWDTWINSZ = WINSZ_25    // Watchdog Timer Window Size (Window Size is 25%)

// DEVCFG0__________VU
#pragma config DEBUG = OFF            // Background Debugger Enable (disabled)
#pragma config JTAGEN = OFF           // JTAG Enable (JTAG Port disabled)
#pragma config ICESEL = ICS_PGx1      // ICE/ICD Comm Channel Select (Communicate on PGEC1/PGED1)
#pragma config PWP = OFF              // Program Flash Write Protect (disabled)
#pragma config BWP = OFF              // Boot Flash Write Protect bit (disabled)
#pragma config CP = OFF               // Code Protect (Protection disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
