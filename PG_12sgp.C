/*
PG_12sgp.C: (= PG_12) + SGP30 
BENABADJI Noureddine - ORAN - Nov. 21st, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
PIC32MX170F256B Device ID Revision = A2
*/

//----------------------- INCLUDES ---------------------------
#include <c:\Program Files\Microchip\xc32\v1.43\pic32mx\include\xc.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <c:\Program Files\Microchip\xc32\v1.43\pic32mx\include\sys\attribs.h>
#include <c:\Program Files\Microchip\xc32\v1.43\pic32mx\include\ctype.h> // tolower

#include "CfgBits.H"
#include "delayPIC32MX.h"
#include "Main.h"
#include "uart1bn.h"
#include "hdc1080v2.h"
#include "DS3231v2.h"
#include "eeprom24.h"
#include "SPI1.H"
#include "NokiaDrv2.h"
#include "scd40.h"
#include "sgp30.h"

//--------------------------------- DEFINES -----------------------------------
//#define SYS_FREQ (32000000L)
//#define PERIOD  32767

#define  DELAY10s   30    //delay NOKIA on (if UART unplugged)
/*
//#define	 ADDR_Toff  4095  //24C32 last addr 0xFFF, to save Toff
#define	 ADDR_Toff  8191  //24LC64 last addr 0x1FFF, to save Toff
#define	 ADDR_adrOfs (ADDR_Toff-2) //to store last adrOfs used before PWR OFF
#define	 ADDR_calib0 (ADDR_Toff-3) //to store last auto zero calib
#define	 ADDR_alarm1 (ADDR_Toff-4) //to store last (alarm1/10) config  
*/

#define   QQ1     15 //15 minutes (period sample store)
//#define   QQ1    10 //10 minutes
//#define   QQ1    5   //5 minutes

#define   QQ2    4  // 4 x 15 minutes = 1h
//#define   QQ2   6   // 6 x 10 minutes = 1h
//#define   QQ2    12   // 12 x 5 minutes = 1h

#define  PIEZO  _LATA2  //drives the piezo

//#define  NOKIA_BL   _LATA3  //PROVISOIRE

#define    LOWBAT	  320	 // 3.20v low battery alarm (1 BipLo, each 5s)
#define    HALTBAT	  270	 // 2.70v stop device (endless sleep)

//--------------------------------- VAR.GLO -----------------------------------

extern unsigned int tempHDC, humHDC ; //dans hdc1080v2.h
//unsigned int tempHDC = 0, humHDC = 0 ;
extern unsigned char Vop, VopMIN, VopMAX ; //dans NokiaScr.h

extern unsigned short scd40co2, scd40tem, scd40hum ;
extern short scd40temAff ;
extern unsigned short scd40serial0, scd40serial1, scd40serial2 ;
extern unsigned short scd40Toffset, scd40Altitude, scd40Pressure ;

extern unsigned short sgp30Version, sgp30SelfTest ;
extern unsigned short sgp30eCO2, sgp30TVOC ;

int delay10s = 0, intT1done = 1, intRXdone = 0 ; 
char carRX = 'T' ;
short reglage = 0, runscroll = 0, BP1pushed = 0, modeScr = 0 ;

short i, j, k ;
short zz, hh = 18, mm = 24, ss = 0 ; // time elapsed (hours, minutes, sec.)
short jour = 9, mois = 6, annee = 23 ; //, bissextile = 0 ; 
short TabJmax[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } ;
short bit8, jourEEP, moisEEP, jmax = 31 ;
unsigned short hhmm ;

unsigned int adrOfs = 0, adrOfsMax, adrOfsMaximum, QteDaySaved, nDay = 1  ; 
unsigned int nPacketSaved ;

short firstime = 1, firstime2 = 1, p, ippmin, ippmax, ippbin, ippbax ;
char lin, col ;
unsigned int ppm, ppminterval[18] = { 0, 0, 0, 0, 0, 0, 0, 0, 0,
				      0, 0, 0, 0, 0, 0, 0, 0, 0 } ;
unsigned int ppb, ppbinterval[18] = { 0, 0, 0, 0, 0, 0, 0, 0, 0,
				      0, 0, 0, 0, 0, 0, 0, 0, 0 } ;
char BP1beforePWRON = 0 ; // 1 means BP1 pushed beforePWR ON
//char doEraseEEPROM = 0 ; // 1 means do erase EEPROM
unsigned char longPush = 0 ; //, BP1timeout = 0 ;

//unsigned int calib = 241 ; // 10-bit numerical count to be retreived (TGS5042ex1)
//unsigned int calib = 191 ; // 10-bit numerical count to be retreived (ME-2 CO)
//unsigned int calib = 131 ; // 10-bit numerical count to be retreived (TGS5141)
unsigned int calib = 150 ; // 10-bit numerical count to be retreived (TGS5042ex2)

char Toff = 3, ToffOld = 3 ;
unsigned int measTVOC = 0 ;
unsigned int meas_NH3 = 0, meas_NH3inV = 0, meas_NH3cn = 0 ;
unsigned int meas_NH3cumul = 0, meas_NH3qte = 0 ;
unsigned int measTVOCcumul = 0, measTVOCqte = 0 ;
unsigned int meas_Vbat = 0, meas_future = 0, val16 ;
//unsigned int val16 ;
unsigned short valEEP, valEEP2, dataSaved = 0 ; //top60 = 0, minute15 = 0 ;
//unsigned short valEEP_NH3, valEEP_Temp, valEEP_Hum ;
unsigned short valEEP_CO2, valEEP2_CO2, valEEP_Temp, valEEP_Hum ;
short valEEP_TempAff ;

char nokiaSleep, txt[60] ;

unsigned int alarm1 = 1000 ;	         // level 1 alarm (1 BipHi, each 20s)
unsigned int alarm2 ;// = alarm1 + 500 ; // level 2 alarm (2 BipHi, each 10s)
unsigned int alarm3 ;//= alarm1 + 1000 ; // level 3 alarm (3 BipHi, each 5s)

char tx_data[16] = {"PIC32MX170F256B\0"} ; //max. 32 bytes (1 page 24LC64)
//char tx_data[16] = {"ABCDEFGHIJKLMNO\0"} ;
//char tx_data[16] = {"123456789012345"} ;
//char *pWrite = (char *)tx_data ; //ptr to tx_data 
char rx_data[16] ; //max. 32 bytes (1 page 24LC64)
//char *pRead = (char *)rx_data ;  //ptr to rx_data

short TempPart1 = 0, TempPart2 = 0 ;
char presenceDS3231, repeated = 0 ;
char presenceMCP79411 ;

char hexStr[5] ; // 4 bytes in hexadecimal format, & hexStr[4] = '\0' ;

//-----------------------------------------------------------------------------
// test @ T=205µs => (F=4.8 kHz inaudible pour mini ceramic piezo diam:15.5mm) 
//do again T=410µs => F=2.44 kHz  
//-----------------------------------------------------------------------------
void BipHi() //alarm for NH3 alert (dure 12ms)
{
  for (i = 0; i < 30; i++) 
  { 
    PIEZO = 1 ; delay1us(200) ; // RB13 Hi => piezo on
    PIEZO = 0 ; delay1us(200) ; // RB13 Lo => piezo off
  }
}
//-----------------------------------------------------------------------------
void BipLo() //alarm for battery LOW (dure 12ms)
{
  for (i = 0; i < 15; i++) 
  { 
    PIEZO = 1 ; delay1us(400) ; // RB13 Hi => piezo on
    PIEZO = 0 ; delay1us(400) ; // RB13 Lo => piezo off
  }
}
/*
//-----------------------------------------------------------------------------
void clic() //BP1 clic (dure 8ms)
{
  for (i = 0; i < 10; i++) 
  { 
    PIEZO = 1 ; delay1us(400) ; // RB13 Hi => piezo on
    PIEZO = 0 ; delay1us(400) ; // RB13 Lo => piezo off
  }
}
*/
//-----------------------------------------------------------------------------
void clicweak() //BP1 clic (dure 8ms)
{
  for (i = 0; i < 10; i++) 
  { 
    PIEZO = 1 ; delay1us(8) ; // RB13 Hi => piezo on
    PIEZO = 0 ; delay1us(792) ; // RB13 Lo => piezo off
  }
}

//-----------------------------------------------------------------------------
void enT1() //turn on T1(BS250) & power leg R5,R6 to allow meas.Vbat
{
  _TRISB5 = 0 ; _LATB5 = 0 ; //RB5 cfg as output,then output low
  delay1us(10) ; //meas_Vbat OK, mais meas_Temp2 incorrect
  //delay1us(100) ; //meas_Vbat OK, mais meas_Temp2 incorrect
  //delay1ms(1) ;//ici seulement, meas_Temp2 correct
  ///////delay1ms(2) ;//ici seulement, meas_Temp2 correct
  //delay1us(250) ;  
}
//-----------------------------------------------------------------------------
void disT1() //turn off T1
{
  //delay1us(10) ;
  _TRISB5 = 1 ; //_LATB5 = 1 ;
  //delay1us(10) ;  
}

//-----------------------------------------------------------------------------
void enT2() //turn on T2(BS250) & power BlueTooth
{
/*  _TRISB5 = 0 ; _LATB5 = 0 ; //RB5 cfg as output,then output low
  //delay_us(10) ;//meas_Vbat OK, mais meas_Temp2 incorrect
  delay_ms(1) ;//ici seulement, meas_Temp2 correct 
*/  
}

//-----------------------------------------------------------------------------
void disT2() //turn off T2
{
/*  //delay_us(10) ;
  _TRISB5 = 1 ; _LATB5 = 1 ; //RB5 cfg as input (high Z, & 5.5V tolerant input)
  //delay_us(10) ;
*/  
}

//-----------------------------------------------------------------------------
void enT3() //turn on T3(BS250) & power I2C module
{
/*  _TRISB5 = 0 ; _LATB5 = 0 ; //RB5 cfg as output,then output low
  //delay_us(10) ;//meas_Vbat OK, mais meas_Temp2 incorrect
  delay_ms(1) ;//ici seulement, meas_Temp2 correct 
*/  
}

//-----------------------------------------------------------------------------
void disT3() //turn off T3
{
/*  //delay_us(10) ;
  _TRISB5 = 1 ; _LATB5 = 1 ; //RB5 cfg as input (high Z, & 5.5V tolerant input)
  //delay_us(10) ;
*/  
}

//-----------------------------------------------------------------------------
void InitIO()
{
  ANSELA = 0 ;  // AN0, AN1 as RA0, RA1
  ANSELB = 0 ;  // AN2 to AN5 as RB0 to RB3  ---and---  AN9 to AN11 as RB15 to RB13
  
  TRISA = 0 ;  	//all PORTA pins output (cas 28pins, PORTA 5-bit : RA0 to RA4)
  TRISB = 0 ;  	//all PORTB pins output (cas 28pins, PORTB 14-bit : RB0 to RB15)

enT1() ; //_TRISB5 = 0 ; _LATB5 = 0 ; //power leg R5,R6 to allow meas.Vbat

  _TRISA1 = 1 ; //RA1/AN1 cfg as input, to meas_Vbat
  _TRISB3 = 1 ; //RB3/AN5 cfg as input, to meas_NH3
  
  _TRISA4 = 1 ; //SOSCO output --- used for ...
  _TRISB4 = 1 ; //SOSCI input ---- ... Quartz 32768 Hz

  PORTA = 0xff ;
  
  _TRISB1 = 1 ; //input BP1 : short push => ... ; long push => ...
  CNPUBbits.CNPUB1 = 1 ; //Enable pull-up on input change for RB1
  
    //----setup I/O for SPI1
  _TRISB10 = 0 ;  //to RST (reset of NOKIA5110)
  _LATB10 = 1 ;  //RST = 1 ;   // disable reset of NOKIA5110
  _TRISB11 = 0 ;  //to DC (Data/Command of NOKIA5110)
  _LATB11 = 1 ; //DC = 1 ;
  _TRISB13 = 0 ; //to SDO1
  _LATB13 = 1 ; //idle SDO1 high 
  _TRISB14 = 0 ; //to CLK
  _LATB14 = 1 ; //idle CLK high
  _TRISB15 = 0 ; //SS1 to CE 
  _LATB15 = 1 ; //de-select NOKIA5110
  _TRISA3 = 0 ; //to NOKIA BL
  NOKIA_BL = 1 ; // turn on BL
}

//-----------------------------------------------------------------------------
void InitTIMER1() // ovf @ 1s (T1 with prescale 1:1)
{
  PR1 = 32766 ;  //
  //PR1 = 32765 ; // avance de 1s en 2h
  //PR1 = 32760 ; // avance de 1s en 2h
  //PR1 = 32767 ; // retard de 5s en 23h
  //PR1 = 32790 ; //  
  //PR1 = 32815 ; //  
  //PR1 = 33000 ; //  

  T1CONbits.TCS = 1 ;    //use external clock quartz 32768 Hz
  //T1CONbits.TSYNC = 1 ;   //PIC32 doesn't wake from sleep mode
  T1CONbits.TSYNC = 0 ;   //external clock input is not synchronized (*)
  T1CONbits.TCKPS = 0b00 ;  //prescaler value (1:1)

  IPC1bits.T1IP = 6 ;	// TIMER1 Interrupt priority.
  IPC1bits.T1IS = 0 ;	// TIMER1 Interrupt sub-priority.
  IFS0bits.T1IF = 0 ;	// clear the interrupt flag, before...
  IEC0bits.T1IE = 1 ;	// ...enabling the T1 interrupt source

  T1CONbits.TON = 1 ;  //Timer1 is activated

//(*) read p.128/613, last paragraphe, "EmbeddedComputingMechatronicsPIC32.PDF"
//Timer1 can only operate during Sleep when setup in Asynchronous Counter mode
}

//-----------------------------------------------------------------------------
void InitUART1()
{
    //U1RX = RA2 or RA4 or RB2 or RB6 or RB13 (p.134/350 datasheet)
  _TRISB2 = 1 ; U1RXRbits.U1RXR = 0x0004 ;	// RB2->UART1:U1RX
    //U1TX = RA0 or RB3 or RB4 or RB7 or RB15 (p.136/350 datasheet)
  _TRISB7 = 0 ; RPB7Rbits.RPB7R = 0x0001 ;	// RB7->UART1:U1TX

  UART1Init() ;	//Initiate UART1 to 115200 (MCU 32MHz) //OK!!!

  delay1ms(100) ; //wait 100ms to stabilize UART1
}

//-----------------------------------------------------------------------------
void InitSPI1()
{ 
  _TRISB10 = 0 ; //to RST
  _LATB10 = 1 ; //RES = 1 ;   // disable reset of NOKIA5110
  _TRISB11 = 0 ; //to DC
  
  //_TRISB12 = 1 ; //to SDI1
  _TRISB1 = 1 ; //to SDI1
  _TRISB13 = 0 ; //to SDO1
  _LATB13 = 1 ; //idle SDO1 high 
  _TRISB14 = 0 ; //to CLK
  _LATB14 = 1 ; //idle CLK high
  _TRISB15 = 0 ; //SS1 to CE 
  _LATB15 = 1 ; //de-select NOKIA5110
 
  				// SCK1->RB14 fixed
  //SDI1Rbits.SDI1R = 0x0003;	// SDI1->RB11
  SDI1Rbits.SDI1R = 0x0002 ;	// SDI1->RB1   //(p.134/350 datasheet)
  RPB13Rbits.RPB13R = 0x0003 ;	// SDO1->RB13  //(p.136/350 datasheet)
  RPB15Rbits.RPB15R = 0x0003 ;	//  SS1->RB15  //(p.136/350 datasheet)

  SPI1INTInit() ;
}

//-----------------test EEP with hardI2C---------------------------------------
//#define  ADDR0  0xB80 //24C32: 0x000 to 0xFFF
#define  ADDR0  0x0384 //24LC64: 0x0000 to 0x1FFF
void testEEPhard(void)
{
unsigned int addr ;
int size, NbrBytes ;

    //WRITE 1 BYTE TO addr
  UART1wrStr("\r \nwriting 184 into 24LC64\r \n") ;
  valEEP = 184 ; addr = ADDR0 ; writeEEP(addr, valEEP) ;
    //READ 1 BYTE FROM addr
  UART1wrStr("read 1 byte from 24LC64: ") ;
  addr = ADDR0 ;
  valEEP = readEEP(addr) ; val2txt(valEEP, txt, 3) ; UART1wrStr(txt) ;
  UART1wrStr("\r \n") ;

  //---------------------------------
  // ATTENTION, IL FAUT EFFACER AVANT RE-ECRIRE DANS LA MEME PAGE !!!
  //OK, CE BLOC FONCTIONNE CORRECTEMENT !!!
  //---------------------------------
  //WRITE 15 BYTES SEQUENTIAL TO addr
  UART1wrStr("write 15 bytes PIC32MX170F256B into 24LC64\r \n") ;
  //start = clock() ;
  size = 15 ; //size = sizeof(tx_data) - 1 ;
  addr = ADDR0 ; wr_pageEEP (addr, tx_data, size) ;
  //addr = ADDR0 ; wr_pageEEP (addr, pWrite, size) ;
  //stop = clock() ; duree = stop - start ; sprintf (txt, "%ld", duree) ;
  //UART1wrStr("duree wr. 10 bytes: ") ;UART1wrStr(txt) ; UART1wrStr(" \r \n") ;

  //READ 15 BYTES FROM addr
  UART1wrStr("read 15 bytes from 24LC64\r \n") ;
  //start = clock() 
  size = 15 ; //size = sizeof(rx_data)  - 1 ;
  addr = ADDR0 ; NbrBytes = rd_pageEEP (addr, rx_data, size) ;
  //stop = clock() ; duree = stop - start ; sprintf (txt, "%ld", duree) ;
  //UART1wrStr("duree rd. 10 bytes: ") ;UART1wrStr(txt) ; UART1wrStr(" \r \n") ;
  rx_data[size] = '\0' ; UART1wrStr(rx_data) ; UART1wrStr(" \r \n") ;
  UART1wrStr("ret = ") ;
  val2txt(NbrBytes, txt, 3) ; UART1wrStr(txt) ; UART1wrStr(" \r \n") ;
}
//-----------------------------------------------------------------------------
void calcul_adrOfsMax (void)
{
  //UARTWriteString("\r\nDUMP (91j)\r\n") ;
  //adrOfsMax = 7980 ; // = 7B * 60m * 19h (24LC64: 8KB)
  //adrOfsMax = 7920 ; // = 6B * 5 * 24h = 720B/j => 7920B = 11j (24LC64: 8KB)
  //adrOfsMax = 65520 ; // = 6B * 5 * 24h = 720B/j => 65520B = 91j (24LC512: 64KB)
  //adrOfsMax = 65088 ; // = 6B * 4 * 24h = 576B/j => 65088B = 113j (24LC512: 64KB)
  
  //adrOfsMaximum = 8 * QQ2 * 24 ; // 8B * 4 * 24h = 768B/j
  adrOfsMaximum = 7 * QQ2 * 24 ; // 7B * 4 * 24h = 672B/j
  //adrOfsMaximum = 6 * QQ2 * 24 ; // 6B * 4 * 24h = 576B/j

  //24LC64
  QteDaySaved = 8192 / adrOfsMaximum ; // 8192 / 672 = 12j (24LC64: 8KB)
  adrOfsMaximum = adrOfsMaximum * QteDaySaved ; // = 8064B en 12j (24LC64: 8KB) 
  //24C32
  //QteDaySaved = 4096 / adrOfsMaximum ; // 4096 / 768 = 5j (24C32: 4KB) module DS3231
  //QteDaySaved = 4096 / adrOfsMaximum ; // 4096 / 672 = 6j (24C32: 4KB) module DS3231
  //QteDaySaved = 4096 / adrOfsMaximum ; // 4096 / 576 = 7j (24C32: 4KB) module DS3231
  //adrOfsMaximum = adrOfsMaximum * QteDaySaved ; // = 4032B en 7j (24C32: 4KB) 
  
  adrOfsMax = adrOfsMaximum ;
}
//-----------------------------------------------------------------------------
void adrLRUnew(void)
{
unsigned int i, nPackets ;

  calcul_adrOfsMax () ;

  i = ADDR_adrOfs ;
  valEEP = readEEP(i++) ; valEEP2 = readEEP(i) ; 
  adrOfs = 256*valEEP + valEEP2 ;//is next to the last data saved before PWR OFF 
  
  if (adrOfs >= adrOfsMax) adrOfs = 0 ;
  
  UART1wrStr("\r \nNbr packets saved = ") ; nPackets = adrOfs / 7 ;
  nPacketSaved = nPackets ;
  val2txt(nPackets, txt, 4) ; UART1wrStr(txt) ; UART1wrStr(" \r \n") ;
  UART1wrStr("Next free addr = ") ;
  val2txt(adrOfs, txt, 5) ; UART1wrStr(txt) ; UART1wrStr(" \r \n") ;
}

//-----------------------------------------------------------------------------
void isLeapYear(void)
{
  //if (annee % 4) bissextile = 0 ; else bissextile = 1 ;
  if (annee % 4) TabJmax[1] = 28 ; else TabJmax[1] = 29 ;
}

//-----------------------------------------------------------------------------
void majJmax(void)
{
  jmax = TabJmax[mois-1] ; //if (mois == 2) jmax += bissextile ;
 
  if (jour > jmax) jour = jmax ;
}
//-----------------------------------------------------------------------------
void CalculnDay(void) // calcul numero du jour
{  
short z ;

  nDay = jour ; for (z=1; z<mois; z++) nDay += TabJmax[z-1] ;
  //if (mois > 2) nDay += bissextile ;
}

//-----------------------------------------------------------------------------
void entete (void)
{
  UART1wrStr("\r \nBat/Cy\t eCO2\tTVOC\tT[C]\tH[%]\tRTCC\r \n") ;  
}

//-----------------------------------------------------------------------------
void doDump (unsigned short opt)
{
  //enT3() ;
  calcul_adrOfsMax () ;	
  
  UART1wrStr("\r \n") ;
  if (opt == 0) // dump this session only
  { adrOfsMax = adrOfs ; UART1wrStr("\r \nDUMP (session)") ;
  }
  else UART1wrStr("\r \nDUMP (12j)") ; // full dump
  
  UART1wrStr("\r \nVbat\t eCO2\tT[C]\tH[%]\tRTCC\r \n") ;
  
  i = 0 ;
  while (i < adrOfsMax)
  {   //============ Vbat saved ============
    valEEP = readEEP(i++) ; //valEEP2 = readEEP(i++, Slave24C32) ; 
    //val16 = 256*valEEP + valEEP2 ;
    valEEP += 200 ;
    //val2txt(val16, txt, 3) ; UART1wrStr(txt) ; UART1wrCar('\t') ;
    val2txt(valEEP, txt, 3) ; UART1wrStr(txt) ; UART1wrCar('\t') ;

      //============ CO2, Temp, Hum saved ============
    valEEP_CO2 = readEEP(i++) ; //CO2 highbyte 
    valEEP2_CO2 = readEEP(i++) ; //CO2 lowbyte 
    val16 = 256*valEEP_CO2 + valEEP2_CO2 ;
    val2txt(val16, txt, 4) ; UART1wrStr(txt) ; UART1wrCar('\t') ;

    valEEP_Temp = readEEP(i++) ; valEEP_TempAff = valEEP_Temp - 45 ; //Temp (7bit)
    if (valEEP_TempAff < 0) { UART1wrCar('-') ; valEEP_TempAff = -valEEP_TempAff ; }
    val2txt(valEEP_TempAff, txt, 2) ; UART1wrStr(txt) ; UART1wrCar('\t') ;

    valEEP_Hum = readEEP(i++) ; //Hum (7bit)

    val2txt(valEEP_Hum, txt, 2) ; UART1wrStr(txt) ; UART1wrCar('\t') ;

      //============ Time saved ============
    hhmm = readEEP(i++) ; 
    bit8 = 0 ; if (hhmm >= 128) { bit8 = 1 ; hhmm -= 128 ; }//hhmm saved 7bit
    valEEP2 = hhmm / QQ2 ; //extract hh saved
    val2txt(valEEP2, txt, 2) ; UART1wrStr(txt) ; UART1wrCar(':') ;
    valEEP2 = QQ1 * (hhmm - valEEP2 * QQ2) ; //extract mm saved
    val2txt(valEEP2, txt, 2) ; UART1wrStr(txt) ; UART1wrCar(' ') ;

    //============ Date saved ============
    nDay = readEEP(i++) ; if (bit8) nDay += 256 ; //nDay saved 9bit
    jourEEP = 0 ; //moisEEP = 0 ;
    k = 0 ; while (nDay > jourEEP + TabJmax[k]) { jourEEP += TabJmax[k] ; k++ ; }

    jourEEP = nDay - jourEEP ; //if (k >= 2) jourEEP = jourEEP - bissextile ;
    moisEEP = k + 1 ; 

    val2txt(jourEEP, txt, 2) ; UART1wrStr(txt) ; UART1wrCar('/') ;
    val2txt(moisEEP, txt, 2) ; UART1wrStr(txt) ; //UART1wrCar(' ') ;
    UART1wrStr("\r \n") ;
    
      //key 'F' pushed again ? then stop FULLDUMP
   	if (i % 200 == 0) //sense keyboard, after each page of 25 lines
	{ if (intRXdone)
      { intRXdone = 0 ;
        //while (U1STAbits.URXDA == 0) ; //while RX buffer is empty, bloquante !
        //if (U1STAbits.URXDA == 1) LATA = U1RXREG ;  // 1 char received
        //LATA = U1RXREG ;  // 1 char received
        if (U1STAbits.OERR) U1STAbits.OERR = 0 ; //will reset the receiver buffer
        carRX = U1RXREG ;  // 1 char received
        if (carRX == 'f' || carRX == 'F') 
        { UART1wrStr("FULLDUMP stopped !") ;
          break ;
        }
      }
    }
  }  

  //disT3() ;
  
  entete () ; //UART1wrStr("\r \nBat/Cy\t eCO2\tTVOC\tT[C]\tH[%]\tRTCC\r \n") ;
}

/*//------------------------------------------------------------------------
void EraseEEPROM(void) //PROVISOIRE, test fiabilité longPush BP1
{
  UART1wrStr(" executing fct EraseEEPROM") ;
  delay1ms(4000) ; // delay 4s
}
*/
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
int main()
{
  //__XC_UART = 1;
  CFGCONbits.JTAGEN = 0 ; //disable the JTAG port, to use RA0,RA1,RA4,RA5
  
  InitIO() ;
  if (BP1 == 0) BP1beforePWRON = 1 ; // BP1 pushed beforePWR ON
  
  BipLo() ; delay1ms(500) ; BipHi() ;  //SPLASH sonore
  
  InitTIMER1() ;

  InitUART1() ;
  //__XC_UART = 1;
  InitSPI1() ;
  
  i2c1_init() ; delay1ms(100) ; //wait 100ms to stabilize IEC1

  HDC1080_Init() ;
  
    // Enable the multi vector
  INTCONbits.MVEC = 1;
  // Enable Global Interrupts
  __builtin_mtc0(12,0,(__builtin_mfc0(12,0) | 0x0001));
  //__builtin_enable_interrupts();
  //asm("ei");   // Enable interrupts

    //ATTENTION: n'oubliez pas le BUG du CRLF "\r\n" : ecrire "\r \n"
  UART1wrStr("\r \n--------------------------------") ;
  UART1wrStr("\r \nPG12sgp @ 32MHz: PIC32MX170F256B") ;
  UART1wrStr("\r \n--------------------------------") ;
  UART1wrStr("\r \nChecking system ...\r \n") ;
  
    //HDC1080
  val16 = HDC1080_readID(0xFF) ; val2txt(val16, txt, 5) ; //read Device ID
  UART1wrStr("\r \nHDC1080 Device ID : ") ; UART1wrStr(txt) ; //0x1050 = 4176 OK!
  if (val16 == 0) UART1wrStr("not installed.\r \n") ;
  else
    { val16 = HDC1080_readID(0xFE) ; val2txt(val16, txt, 5) ; //Manufacturer ID
      UART1wrStr("\r \nHDC1080 Manufac.ID: "); UART1wrStr(txt); //0x5449 = 21577 OK!
      UART1wrStr(" \r \n") ;
    }       
 
  UART1wrStr("\r \nreading DS3231: ") ;
  presenceDS3231 = isDS3231present() ;
  if (presenceDS3231) { readDS1307() ; UART1wrStr("OK !\r \n") ; }
  else UART1wrStr("not installed.\r \n") ;

  UART1wrStr("\r \nreading MCP79411: ") ;
  presenceMCP79411 = isMCP79411present() ;
  if (presenceMCP79411) 
  { UART1wrStr("OK !\r \n") ;
  
    readMCP79411() ; //read MCP79411 RTCC at power ON
  
    val2txt(hh, txt, 2) ; UART1wrStr(txt) ; UART1wrCar(':') ;
    val2txt(mm, txt, 2) ; UART1wrStr(txt) ; UART1wrCar(':') ;
    val2txt(ss, txt, 2) ; UART1wrStr(txt) ; UART1wrCar(' ') ;
    val2txt(jour, txt, 2) ; UART1wrStr(txt) ; UART1wrCar('/') ;
    val2txt(mois, txt, 2) ; UART1wrStr(txt) ; UART1wrCar('/') ;
    val2txt(annee, txt, 2) ; UART1wrStr(txt) ; UART1wrStr(" \r \n") ;
          
    startMCP79411() ;
    
    UART1wrStr("MCP79411 EUI-48 = ") ;
    EUI48_MCP79411() ; // read EUI-48
    UART1wrStr(txt) ; UART1wrStr(" \r \n") ;
  }
  else UART1wrStr("not installed.\r \n") ;

  //testEEPhard() ;  //PROVISOIRE
  UART1wrStr("\r \nreading EEPROM:") ;
  adrLRUnew() ;
  
  if (BP1beforePWRON) //BP1 pushed beforePWR ON  
  { //BP1beforePWRON = 0 ; 
    UART1wrStr("\r \nBP1 pushed beforePWR ON\r \n") ;
    /*  //initialize datetime
    UART1wrStr("\r \nwriting DS3231\r \n") ;
    hh = 15 ; mm = 40 ; ss = 0 ; jour = 4, mois = 4, annee = 23 ; 
    writeDS1307() ; AckPoll (SlaveDS3231) ;
    delay1ms(100) ;
    */
  }
  
    // Initialize LCD
  Vop = readEEP(ADDR_Vop) ;  if (Vop < VopMIN || Vop > VopMAX) Vop = 0xC0 ;//default
  
  Nokia_Init(Vop) ; //Contrast setting: 0xB8 (clair++) to 0xC2 (foncé++)              
  Nokia_Clear() ;

  Toff = readEEP(ADDR_Toff) ; if (Toff < 0 || Toff > 9) Toff = 3 ; 
  ToffOld = Toff ;

/*  //SCD40 pseudo-init
  scd40stopPeriodicMeas() ; //dure 500 ms ! 
  scd40Serial() ; 
  scd40readToffset() ; scd40readAltitude() ; scd40readPressure() ; 
*/
  
    //SGP30 pseudo-init
  sgp30getVersion() ;
  sgp30MeasureTest() ;
  sgp30initIAQ() ;
  
  NOKIA_BL = 1 ; // turn on BL
  if (BP1beforePWRON) NokiaSysCfgMenu(); else { NokiaSplash1(); delay1ms(4000); }
  NOKIA_BL = 0 ; // turn off BL

  UART1wrStr("\r \nreading Alarms:\r \n") ;
  alarm1 = 10 * readEEP(ADDR_alarm1) ;
  alarm2 = alarm1 + 500 ; alarm3 = alarm1 + 1000 ; //VU dans NokiaSysCfg3() ;
  UART1wrStr("alarm1 = ") ;
  val2txt(alarm1, txt, 4) ; UART1wrStr(txt) ; UART1wrStr(" \r \n") ;
  UART1wrStr("alarm2 = ") ;
  val2txt(alarm2, txt, 4) ; UART1wrStr(txt) ; UART1wrStr(" \r \n") ;
  UART1wrStr("alarm3 = ") ;
  val2txt(alarm3, txt, 4) ; UART1wrStr(txt) ; UART1wrStr(" \r \n") ;

  calib = readEEP(ADDR_calib0) ;    //----- NE SERT A RIEN POUR LE SCD40 !
  ///////UART1wrStr("Auto Zero calib = ") ;
  ///////val2txt(calib, txt, 3) ; UART1wrStr(txt) ; UART1wrStr(" \r \n") ;

  //if (BP1beforePWRON) { BP1beforePWRON = 0 ; NokiaSysReport() ; }

  Toff = readEEP(ADDR_Toff) ; if (Toff < 0 || Toff > 9) Toff = 3 ; 
  ToffOld = Toff ;
  
/*  //SCD40
  UART1wrStr("\r \nreading SCD40 Serial (factory):\r \n \t") ; 
  val2txt(scd40serial0, txt, 5) ; UART1wrStr(txt); UART1wrStr(" ") ; //word[0]
  val2txt(scd40serial1, txt, 5) ; UART1wrStr(txt); UART1wrStr(" ") ; //word[1]
  val2txt(scd40serial2, txt, 5) ; UART1wrStr(txt) ; //word[2]
  UART1wrStr(" \r \n \t") ;

  Int16_hex4dgt(scd40serial0) ; UART1wrStr(hexStr); UART1wrStr("  ") ;
  Int16_hex4dgt(scd40serial1) ; UART1wrStr(hexStr); UART1wrStr("  ") ;
  Int16_hex4dgt(scd40serial2) ; UART1wrStr(hexStr);
  //UART1wrStr(" \r \n") ;
  
  UART1wrStr("\r \nSCD40 Temp. offset (default): ") ;
  val2txt(scd40Toffset, txt, 2) ; UART1wrStr(txt); UART1wrStr(" C") ;
  UART1wrStr("\r \nSCD40 sensor Altitude (user): ") ;
  val2txt(scd40Altitude, txt, 4) ; UART1wrStr(txt); UART1wrStr(" m") ;
  UART1wrStr("\r \nSCD40 sensor Pressure (user): ") ;
  val2txt(scd40Pressure, txt, 4) ; UART1wrStr(txt); UART1wrStr(" hPa \r \n") ;
  
  scd40startPeriodicMeas() ; //each 5s
  //delay1ms(100) ;
  //scd40readMeas () ;
*/
  //SGP30
  //sgp30getVersion() ;
  UART1wrStr("\r \nreading SGP30 Version : ") ; 
  val2txt(sgp30Version, txt, 5) ; UART1wrStr(txt) ; UART1wrStr(" (0x") ;
  Int16_hex4dgt(sgp30Version) ; UART1wrStr(hexStr) ; UART1wrCar(')') ; 

  UART1wrStr("\r \nreading SGP30 SelfTest: ") ; 
  val2txt(sgp30SelfTest, txt, 5) ; UART1wrStr(txt) ; UART1wrStr(" (0x") ;
  Int16_hex4dgt(sgp30SelfTest) ; UART1wrStr(hexStr) ; UART1wrStr(") \r \n") ;
  
  if (BP1beforePWRON) { BP1beforePWRON = 0 ; NokiaSysReport() ; }

  mainScr (0) ; delay1ms(1000) ; // delay 1s
  
  UART1wrStr("\r \nRun Stop Dump Fulldump Plus Minus Next") ;  
  entete () ; //UART1wrStr("\r \nBat/Cy\t eCO2\tTVOC\tT[C]\tH[%]\tRTCC\r \n") ;

    //====================== ENDLESS LOOP ======================
  while(1)
  {      
      //======================== sense BP1 ========================	   
    if (BP1 == 0) //BP1 pushed ?
    { delay10s = 0 ; NOKIA_BL = 1 ;
      if (nokiaSleep) 
      { nokiaSleep = 0 ; Nokia_Wake() ; 
        BP1pushed = -1 ; modeScr = 0 ; mainScr (0) ;
      } 
    }
    else
      { if (BP1pushed == 1) //shortpush
        { BP1pushed = 0 ; 
          if (modeScr == 0) 
          { if (++Toff > 9) Toff = 0 ;
            Nokia_PositionXY (52, 0) ; Nokia_SendData(Toff+48) ;
          }
        }
        if (BP1pushed == 2) //longpush
        { BP1pushed = 0 ; if (++modeScr > 3) modeScr = 0 ;
          if (modeScr == 0) mainScr (0) ;
          if (modeScr == 1) tablScr () ; 
          if (modeScr == 2) statScr () ;
          if (modeScr == 3) NokiaSysReport () ;
        }
      }
    
      //======================== each 1s ========================
    if (intT1done)
    { intT1done = 0 ;
    
      sgp30MeasureIAQ() ; //has to be sent in regular intervals of 1s 

      if (delay10s < DELAY10s) delay10s++ ;
      else 
        { NOKIA_BL = 0 ; // turn off BL
          if (Toff != ToffOld) 
          { ToffOld = Toff ; writeEEP(ADDR_Toff, Toff) ;
          }
        }
      //start = clock() ;
      if (BP1 == 0)
      { clicweak() ;
        if (++BP1pushed >= 2) BP1pushed = 2 ; //longpush
      }
        
	//----------------- maj time elapsed ----------------- 
      if (++ss >= 60)    //reach 60 seconds ?
      { //ss = 0 ;
        if (presenceDS3231) readDS1307() ;
        else 
          if (presenceMCP79411) readMCP79411() ;
          else
          { ss = 0 ;
            if (++mm >= 60)   //reach 60 minutes ? 
            { mm = 0 ; 
              if (++hh >= 24)   //reach 24 hours ?
              { hh = 0 ;
                if (++jour > jmax)
                { jour = 1 ;
                  if (++mois > 12)
                  { mois = 1 ;
                    if (++annee > 99) annee = 0 ;
                    isLeapYear() ; 
                  }
                  majJmax() ;
                }
              }
            }
          }
      }//ENDOF if (++ss >= 60)
    
        //---- alarm CO niveau 1, each 20s. TOTAL 1 BIP
      if (ss % 20 == 0)
      { if (meas_NH3 > alarm1) BipHi() ; 
      }
        //alarm CO niveau 2, each 10s. TOTAL 2 BIPs cumulés
      if (ss % 10 == 0) 
      { if (meas_NH3 > alarm2) BipHi() ; 
      }
        //alarm CO niveau 3, each 5s. TOTAL 3 BIPs cumulés
      if (ss % 5 == 0)
      { if (meas_NH3 > alarm3) BipHi() ; 
      }      
      //---- FIN alarm

     ///////////////////////////////////////////////
      //UART1 CAS3: à tester ...//ça marche mieux
      if (intRXdone)
      { intRXdone = 0 ;
        if (_RB2 == 1) delay10s = 0 ; //clear delay10s, only if serialink plugged
        //int n = uart1_read (txt, sizeof(txt)) ;
        //if (n) carRX = txt[0] ;
      }
      ///////////////////////////////////////////// 
    
      if (ss % 5 == 0) scd40readMeas () ;
         
      if (ss % (Toff+1) == 0) //each Toff = 0, 1, 2, ..., 9s
      { //--------------------------- meas.AN5 PPM ----------------------------  

        // meas_NH3cn = readADC_1meas(5) ; //read AN5  
        //meas_NH3cn = scd40co2 ;
        meas_NH3cn = sgp30eCO2 ;
        measTVOC = sgp30TVOC ;
                
        // meas_NH3inV = 33 * meas_NH3cn / 100 ; // meas_NH3inV, value in Volt
        meas_NH3inV =0 ;
              
        //  //2-step calibration   //----- NE SERT A RIEN POUR LE SCD40 !
         meas_NH3 = meas_NH3cn ;  
        // if (meas_NH3 > calib) meas_NH3 -= calib ; else meas_NH3 = 0 ; //cancel ofs.AOP   
        // meas_NH3 = (meas_NH3 * 21) / 10 ;
              
        if (meas_NH3 > 9999) meas_NH3 = 9999 ; //échelle mesurable 000 ... 9999
        if (measTVOC > 9999) measTVOC = 9999 ; //échelle mesurable 000 ... 9999

        
        meas_NH3cumul += meas_NH3 ; meas_NH3qte++ ;
        measTVOCcumul += measTVOC ; measTVOCqte++ ;
              
        if (Toff) disT1() ;
     
        if (nokiaSleep) clicweak() ; //BipHi() ; //dure 12ms
       
        if (firstime)
        { firstime = 0 ;
          ippmin = ippmax = 17 ; ppminterval[17] = meas_NH3 ;
          ippbin = ippbax = 17 ; ppbinterval[17] = measTVOC ;
        }
        else  //------------maj vect 18 derniers ppm------------
          { for (p=0; p<17; p++) 
            { ppminterval[p] = ppminterval[p+1] ; //shift left
              ppbinterval[p] = ppbinterval[p+1] ; //shift left
            }
            ppminterval[17] = meas_NH3 ; ppbinterval[17] = measTVOC ;
            
            ippmin-- ;  
            if (ippmin >= 0) { if (meas_NH3 < ppminterval[ippmin]) ippmin = 17 ; }     
            else //RechIndiceNewMinimum
              { ippmin = 0 ; for (p=1; p<17; p++) if (ppminterval[p] < ppminterval[ippmin]) ippmin = p ;
              } 
            ippbin-- ;
            if (ippbin >= 0) { if (measTVOC < ppbinterval[ippbin]) ippbin = 17 ; }     
            else //RechIndiceNewMinimum
              { ippbin = 0 ; for (p=1; p<17; p++) if (ppbinterval[p] < ppbinterval[ippbin]) ippbin = p ;
              } 

            ippmax-- ; 
            if (ippmax >= 0) { if (meas_NH3 > ppminterval[ippmax]) ippmax = 17 ; }
            else //RechIndiceNewMaximum
              { ippmax = 0 ; for (p=1; p<17; p++) if (ppminterval[p] > ppminterval[ippmax]) ippmax = p ;
              }            
            ippbax-- ; 
            if (ippbax >= 0) { if (measTVOC > ppbinterval[ippbax]) ippbax = 17 ; }
            else //RechIndiceNewMaximum
              { ippbax = 0 ; for (p=1; p<17; p++) if (ppbinterval[p] > ppbinterval[ippbax]) ippbax = p ;
              }
          }//FIN----------maj vect 1_ derniers ppm----------  
              
          //window2 ie AffZoom2 & "< ppm <" & GLOBA
        if (modeScr == 0) mainScr (2) ;
        if (modeScr == 1) tablScr () ;
        if (modeScr == 2) statScr () ; 
        if (modeScr == 3) NokiaSysReport () ;
      }
      else 
        if (ss % (Toff+1) == Toff) enT2() ; // A REVOIR, and where is disT2() ?
    
      if (Toff == 0) enT2() ;  // A REVOIR, and where is disT2() ?

        //--------------------------- meas. HDC1080 -------------------------
      if (ss % 2) //each 2s, HDC1080 meas.
      { //enT3() ; //turn on T3(BS250) & power leg R5,R6 + temperature sensor
	
        //INTCONbits.GIE = 0 ; //disable interrupts
        HDC1080_read() ;//fonction bloquante de 20ms, non interruptible.
        //INTCONbits.GIE = 1 ; //re-enable interrupts
        //disT3() ; //turn off T3(BS250)
        
        /*
        //if (scd40tem >= 0) tempHDC = scd40tem ; else tempHDC = -scd40tem ; 
        tempHDC = scd40tem ;
        humHDC = scd40hum ;
        */
        
          //window1 ie Aff. temprature & humidity
        if (modeScr == 0) mainScr (1) ;        
      }
    
      	//-------------------- meas.AN1 Vbat (durée 13µs ? ) ------------------

enT1() ; //turn on T3(BS250) & power leg R5,R6 + temperature sensor
      //meas_Vbat = ADC_1meas(1, 0xFFFD) ; //1 meas. ; mask to put PCFG1 = 0
      meas_Vbat = readADC_1meas(1) ; //read AN1 
disT1() ; //turn off T3(BS250)

      //meas_Vbat = (meas_Vbat * 6600L) / 1023 ; // converting CNum to mV
      //meas_Vbat = meas_Vbat / 10 ; //pour aff., ex: 367 means 3.67 V
      //le calc. approché induit 0.3% d'erreur 
      meas_Vbat = (meas_Vbat * 66L) / 103 ; // converting CNum to mVx10
                                            //pour aff., ex: 367 means 3.67 V

      if (meas_Vbat < LOWBAT)  //discharge 3v2 ... 2v7 in 1h30'
      { if (ss % 5 == 0) BipLo() ; //alarm battery LOW, each 5"
        UART1wrStr("\r \nBATTERY < 3.3V") ;  
        DispVbatLow () ;
      }  
      if ((meas_Vbat < HALTBAT) && (++repeated > 10))  //if Vbat 2v7, stop device
      { UART1wrStr("\r \nBAT.LOW, SYST.STOP") ;  
        DispVbatFlat () ;
        nokiaSleep = 1 ; //disT1() ; disT3() ; 
        asm( " di " ) ; //disable interrupts globally
        ///////PowerSaveSleep() ; // stops both Sys.Clock & Periph.Clock
        if (U1MODEbits.ON == 1) { U1MODEbits.ON = 0 ; _LATB7 = 0 ; }
        bitSLPEN(1) ; //set SLPEN bit, to prepare sleep mode
        __asm__ __volatile__ ("wait") ; //SLEEP as SLPEN = 1 ; //SLEEP FOREVER
      }
            //------------ each 15 minutes, save data acquisition ------------

      if (mm % QQ1 == 0) //each 15 minutes, save data acquisition
      { if (dataSaved == 0)
        {      
	  //enT3() ; 
          meas_NH3cumul /= meas_NH3qte ;
          
          if (adrOfs >= adrOfsMaximum) adrOfs = 0 ;  // cas 24C32: 4KB
          writeEEP(adrOfs++, meas_Vbat-200) ; 
          
          writeEEP(adrOfs++, meas_NH3cumul/256) ; //CO2 highbyte
          writeEEP(adrOfs++, meas_NH3cumul%256) ; //CO2 lowbyte

          val16 = tempHDC ; //if (meas_NH3cumul >= 256) val16 += 128 ;
          writeEEP(adrOfs++, val16) ;
          val16 = humHDC ; //if (meas_NH3cumul >= 512) val16 += 128 ;
          writeEEP(adrOfs++, val16) ;
                                           
          hhmm = hh*QQ2 + mm/QQ1; CalculnDay(); if (nDay >= 256) { hhmm += 128; nDay %= 256; }
          writeEEP(adrOfs++, hhmm) ; writeEEP(adrOfs++, nDay) ;
          
          i = ADDR_adrOfs ;
          valEEP = adrOfs / 256 ; writeEEP(i++, valEEP) ; //store this last...
          valEEP2 = adrOfs % 256 ; writeEEP(i, valEEP2) ; //... adrOfs used
          //disT3() ;
          
          dataSaved = 1 ; 
          meas_NH3cumul = 0 ; meas_NH3qte = 0 ;
          measTVOCcumul = 0 ; measTVOCqte = 0 ;
        }
      }
      else dataSaved = 0 ;

        //------------------- PLUGGED ? UNPLUGGED  ---------------------

      if (_RB2 == 0) //serialink UNPLUGGED, so do SLEEP mode 
      {
        if (U1MODEbits.ON == 1) 
        { U1MODEbits.ON = 0 ; _LATB7 = 0 ; 
          bitSLPEN(1) ; //set SLPEN bit, to prepare sleep mode
        }

        if (modeScr == 0) { Nokia_PositionXY (52, 1) ; Nokia_SendData('U') ; } 
        
        if (delay10s >= DELAY10s)  // RUN : curent Idd = 18.25 mA
	{			   //SLEEP: curent Idd = 43 µA ; OK !!!
          if (nokiaSleep == 0) 
          { //Nokia_Clear() ; nokiaSleep = 1 ; Nokia_Reset() ; // Ipd est ...
            Nokia_Clear() ; nokiaSleep = 1 ; Nokia_Sleep() ;  // ... le même !
            //writeDS3231_dis32kHz() ; //test to lower Icc of this module
										//OK. (0.56mA to 0.12mA)
          }
          //doSleep() ; lastmode = 1 ; //means last mode was SLEEP
          //doPowerSave (1) ; //do sleep mode
          __asm__ __volatile__ ("wait") ; //SLEEP as SLPEN = 1 ;
        }
      }
      else  //serialink PLUGGED, so process hotkeys & refresh puTTY 
	{   //(then IDLE after 10s if no keypress)
	    
          if (U1MODEbits.ON == 0) 
	  { //U1MODEbits.ON = 1 ; U1STAbits.UTXEN = 1 ;
	    ////UARTEnable(UART1, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
            UART1Init() ;
            bitSLPEN(0) ; //clear SLPEN bit, to prepare idle mode
	  }
            
          if (nokiaSleep) 
          { nokiaSleep = 0 ; Nokia_Wake() ; 
            //Nokia_PositionXY (0, 2) ; LCD_DrawLine (0x02, 84) ; //Lin2-----
            
            //BP1pushed = 0 ; modeScr = 0 ; mainScr (0) ;
            BP1pushed = -1 ; modeScr = 0 ; mainScr (0) ;
          }
          
          if (modeScr == 0) { Nokia_PositionXY (52, 1) ; Nokia_SendData('P') ; }

            //-------------------- hot keys ? --------------------
          carRX = tolower(carRX) ; 
          //if (carRX  == 'w') { writeDS1307() ; AckPoll (SlaveDS3231) ; } //ATTENTION: suivi par AckPoll
          if (carRX  == 'w') { if (presenceDS3231) writeDS1307() ; 
                               else if (presenceMCP79411) writeMCP79411() ;
                             }
          if (carRX  == 'x') { if (presenceDS3231) readDS1307() ;
                               else if (presenceMCP79411) readMCP79411() ;
                             }

          if (carRX == 'c') { if (++Toff > 9) Toff = 0 ; }

          if (carRX == 'r') runscroll = 1 ;
          if (carRX == 's') runscroll = 0 ;
          if (carRX == 'd') { doDump (0) ; //dump session  
                              if (presenceDS3231) readDS1307() ;
                              else if (presenceMCP79411) readMCP79411() ;
                            } 
          if (carRX == 'f') { doDump (1) ; //full dump 
                              if (presenceDS3231) readDS1307() ;
                              else if (presenceMCP79411) readMCP79411() ;          
                            }
          if (carRX == 'n') { runscroll = 0 ; if (++reglage >= 6)  reglage = 0 ; }
          if (carRX == 'p') 
          { // increment RTCC infos (hh:mm:ss jour/mois/annee)
            if (reglage == 0) { if (++hh > 23) hh = 0 ; }  
            if (reglage == 1) { if (++mm > 59) mm = 0 ; } 
            if (reglage == 2) { ss += 2; if (ss > 59) ss = 0 ; }
            if (reglage == 3) { if (++jour > jmax) jour = 1 ; }
            if (reglage == 4) { if (++mois > 12) mois = 1 ;
                                isLeapYear() ; majJmax() ; }
            if (reglage == 5) { if (++annee > 99) annee = 0 ;
                                isLeapYear() ; majJmax() ; }  
          }    
          if (carRX == 'm') 
          { // decrement RTCC infos (hh:mm:ss jour/mois/annee)
            if (reglage == 0) { if (--hh < 0) hh = 23 ; } 
            if (reglage == 1) { if (--mm < 0) mm = 59 ; }
            if (reglage == 2) { ss -= 2 ; if (ss < 0) ss = 59 ; }
            if (reglage == 3) { if (--jour <= 0) jour = jmax ; }
            if (reglage == 4) { if (--mois <= 0) mois = 12 ;
                                isLeapYear() ; majJmax() ; }
            if (reglage == 5) { if (--annee < 0) annee = 99 ;
                                isLeapYear() ; majJmax() ; }
          }

            //------------------- refresh puTTY ------------------
          
	      //ATTENTION, BUG (avec SLEEP): METTRE " \r \n" A CHAQUE DEBUT DE LIGNE
          UART1wrStr("\r ") ; if (runscroll) UART1wrStr("\n") ;    
                    
          val2txt(meas_Vbat, txt, 3) ; UART1wrStr(txt) ; UART1wrCar('/') ;
          val2txt(Toff, txt, 1) ; UART1wrStr(txt) ; UART1wrCar('\t') ;
          //UART1wrCar(carRX) ; UART1wrCar('\t') ;
          //val2txt(delay10s, txt, 2) ; UART1wrStr(txt) ; UART1wrCar('\t') ;
                   
          val2txt(sgp30eCO2, txt, 4) ; 
          UART1wrCar(' ') ; UART1wrStr(txt) ; UART1wrCar('\t') ;
          val2txt(sgp30TVOC, txt, 4) ; 
          UART1wrStr(txt) ; UART1wrCar('\t') ;
          
          /*
          scd40temAff = scd40tem - 45 ;
          if (scd40temAff < 0) { UART1wrCar('-') ; scd40temAff = -scd40temAff ; }
          else UART1wrCar(' ') ;
          val2txt(scd40temAff, txt, 2) ; UART1wrStr(txt) ; UART1wrCar('\t') ;
          
          val2txt(scd40hum, txt, 2) ; UART1wrStr(txt) ; UART1wrCar('\t') ;
          */
          
          val2txt(tempHDC, txt, 2) ; UART1wrStr(txt) ; UART1wrCar('\t') ;
          val2txt(humHDC, txt, 2) ; UART1wrStr(txt) ; UART1wrCar('\t') ;
          
            //RTCC
          val2txt(hh, txt, 2) ; UART1wrStr(txt) ; UART1wrCar(':') ;
          val2txt(mm, txt, 2) ; UART1wrStr(txt) ; UART1wrCar(':') ;
          val2txt(ss, txt, 2) ; UART1wrStr(txt) ; UART1wrCar(' ') ;
          val2txt(jour, txt, 2) ; UART1wrStr(txt) ; UART1wrCar('/') ;
          val2txt(mois, txt, 2) ; UART1wrStr(txt) ; UART1wrCar('/') ;
          val2txt(annee, txt, 2) ; UART1wrStr(txt) ; //UART1wrCar('\t') ;
        
            //do 17*backspace, if caret under hh
          k = 17 - (reglage * 3) ;
          for (j=0; j<k; j++) UART1wrCar('\b') ; // ASCII 8

            // ATTENTION: NOUS N'AVONS PLUS BESOIN DE carRX
          carRX = ' ' ;
          
          if (delay10s >= DELAY10s) 
          { /* //asm("pwrsav #1") ; //IDLE: disables CPU, but sys.clk still ON
		    PowerSaveIdle() ; //stops sys.clk but leaves Periph.Clk running
		    //OSCCONbits.SLPEN = 0 ; // enters idle (not sleep) when "wait"
            //__asm__ __volatile__ ("wait"); //IDLE
            */
            //doIdle(lastmode) ; lastmode = 0 ; //means last mode was IDLE
            //doPowerSave (0) ; //do idle mode
            __asm__ __volatile__ ("wait") ; //IDLE as SLPEN = 0 ;  
            //_wait() ; //testé, doing IDLE: Icc = 8.65mA
	  }

        }//ENDOF else of if (_RB2 == 0) //serialink unplugged 

      
      
      //PowerSaveSleep() ; // stops both Sys.Clock & Periph.Clock
      //asm("pwrsav #0") ; //sleep
      //Sleep() ;
      //asm("wait") ; //sleep ICI CA COMPILE
      
        //// enters sleep when "wait" , else idle
      /*  
      if ((minutes % 2) == 0) OSCCONbits.SLPEN = 1 ; else OSCCONbits.SLPEN = 0 ;
      __asm__ __volatile__ ("wait"); //SLEEP if SLPEN=1 ; IDLE if SLPEN=0
      Nop();
      */
      //OSCCONbits.SLPEN = 1 ; asm ("wait"); //SLEEP if SLPEN=1

    }//ENDOF if (intT1done)
    
  }//ENDOF while (1)
  
  return 0 ;
}

///////////////////////////////////////////////////////////////////////////////
//----------------------- INTERRUPT --------------------------
////void _ISR _T1Interrupt (void) 
//#pragma interrupt InterruptHandler ipl1 vector 0   // p.117/554, Lucio
//void InterruptHandler (void) //T1 int every 0.1s
void __ISR(_TIMER_1_VECTOR, IPL6AUTO) timer1_isr(void)
//void __ISR(_TIMER_1_VECTOR, IPL1AUTO) _T1Interrupt()
//void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{    
  ////IFS0bits.T1IF = 0 ; //clear interrupt flag
  //mT1ClearIntFlag() ;
  IFS0CLR = (1 << _IFS0_T1IF_POSITION) ; //clear interrupt flag
  //IFS0CLR = 0x00008000; // clear interrupt flag (DS60001108H, p21/30)
  
  intT1done = 1 ; longPush++ ; //BP1timeout++ ;
  
  //_SLEEP = 0 ; //clear SLEEP flag
  ///////RCONbits.SLEEP = 0 ;

//read p.132/613, A 5Hz Timer1 ISR, "EmbeddedComputingMechatronicsPIC32.PDF"
//using Timer without external quartz.
  
}// Interrupt Handler

//-----------------------------------------------------------------------------
//void __ISR(_UART1_VECTOR, IPL1AUTO) uart1_isr(void)
//void __ISR(_UART1_VECTOR, IPL2SOFT) uart1_isr(void)
void __ISR(_UART_1_VECTOR, IPL1SOFT) IntUart1Handler(void)
{//EmbeddedComputingMechatr...PDF, p.167/613 Code Sample 11.2
	// re-enable interrupts immediately (nesting)
  //asm( " ei " );

  if (IFS1bits.U1RXIF) // Is this an RX interrupt ?
  {   
    //if (U1STAbits.OERR) U1STAbits.OERR = 0 ; //will reset the receiver buffer
    carRX = U1RXREG ;  // 1 char received
    //if (U1STAbits.OERR) U1STAbits.OERR = 0 ; //will reset the receiver buffer
    
    intRXdone = 1 ;
    //if (_RB2 == 1) delay10s = 0 ; //clear delay10s, only if serialink plugged
    IFS1bits.U1RXIF = 0 ; //clear RX interrupt flag
  }
  
  //if (IFS1bits.U1TXIF) //We don't care about TX interrupt
  //{
  //  IFS1bits.U1TXIF = 0 ; //clear TX interrupt flag
  //}
}

//-----------------------------------------------------------------------------
//void __attribute__((interrupt, no_auto_psv)) _SPI1Interrupt()
void __ISR(_SPI1_VECTOR, IPL2SOFT) IntSpi1Handler(void)
{
		// re-enable interrupts immediately (nesting)
  asm( " ei " );

  // add code here
  //IFS0bits.SPI1IF = 0 ;
  IFS1bits.SPI1TXIF = 0 ;
  IFS1bits.SPI1RXIF = 0 ;
  IFS1bits.SPI1EIF = 0 ;
}
