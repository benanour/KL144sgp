/*
MCP79411.c: RTCC chip (MCP79410, MCP79411, MCP79412)
BENABADJI Noureddine - ORAN - June 10th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#include <c:\Program Files\Microchip\xc32\v1.43\pic32mx\include\xc.h>
#include "mcp79411.h"
#include "i2c1bn.h"

//unsigned char rd_ds3231[8] ;
//unsigned char *pRd3231 = (unsigned char *)rd_ds3231 ;

//-----------------------------------------------------------------------------
// convert BCD to decimal function
//-----------------------------------------------------------------------------
unsigned short bcd2decimal(unsigned short number) 
{
  unsigned short rtn = (number >> 4) * 10 + (number & 0x0F) ;
  return(rtn) ;
}
 
//-----------------------------------------------------------------------------
// convert decimal to BCD function
//-----------------------------------------------------------------------------
unsigned short decimal2bcd(unsigned short number) 
{
  return(((number / 10) << 4) + (number % 10)) ;
}

//-----------------------------------------------------------------------------
// Write data to Control Register 0Eh ; reset bit 2 <INTCN> => output 1 Hz
//-----------------------------------------------------------------------------
/* ATTENTION, REDECLENCHER 32kHz ET NON PAS 1Hz !!!

void writeDS3231_0Eh(void)
{
  StartI2C1() ; IdleI2C1() ;//Send_I2C_StartBit() ;  // send start bit
  MasterWriteI2C1(0xD0) ; IdleI2C1() ;   // send byte via I2C  (RTCC @ + W)
  MasterWriteI2C1(0x0E) ; IdleI2C1() ;   // send register @ = 0Eh
  MasterWriteI2C1(0x18) ; IdleI2C1() ;   // reset bit2 <INTCN> = 0
  //MasterWriteI2C1(0x58) ; IdleI2C1() ; // <INTCN> = 0 ; <BBSQW> = 1
  StopI2C1() ; IdleI2C1() ;//Send_I2C_StopBit() ;   // stop I2C
}
*/

//-----------------------------------------------------------------------------
// Write data to Status Register 0Fh ; clear bit3 <EN32KHZ> to ...
// ...disable the 32KHZ output (high impedance).
//-----------------------------------------------------------------------------
void writeMCP79411_dis32kHz(void)
{
  //i2c1_write (DS3231_ADDR, "\xD0\x0F\x00", 3) ; //FAUX
  ///////i2c1_write (DS3231_ADDR, "\x0F\x00", 2) ;
  
  i2c1_write (MCP79411_ADDR_RTC, "\x07\x80", 2) ; //SQWEN=0 ALM0EN=0 ALM1EN=0
  //delay1ms(20) ;
}
//-----------------------------------------------------------------------------
// Write data to Status Register 0Fh ; set bit3 <EN32KHZ> to ...
// ...enable the 32KHZ output.
//-----------------------------------------------------------------------------
void writeMCP79411_en32kHz(void)
{
  //i2c1_write (DS3231_ADDR, "\xD0\x0F\x08", 3) ; //FAUX
  ///////i2c1_write (DS3231_ADDR, "\x0F\x08", 2) ;

  i2c1_write (MCP79411_ADDR_RTC, "\x07\xC3", 2) ; //SQWEN=1 no Alarms, MFP=32768Hz
  //delay1ms(20) ;
}
/*//-----------------------------------------------------------------------------
// Write data to Control Register 0Eh ; set bit5 <CONV> to force the...
// ...temperature sensor to convert the temperature into digital code and...
// ...execute the temperature compensate algo. to upd the osc. accuracy.
//-----------------------------------------------------------------------------
void writeDS3231_ConvTemp(void)
{
  //enT3() ; //turn on mosfet T3 to enable module DS3231

  //i2c1_write (DS3231_ADDR, "\xD0\x0E\x3C", 3) ; //FAUX
  i2c1_write (DS3231_ADDR, "\x0E\x3C", 2) ;
  //delay1ms(10) ;
  
  //disT3() ; //turn off mosfet T3 to disable module DS3231 (lower Icc)
}*/

/*//-----------------------------------------------------------------------------
// Read Temperature Registers 11h & 12h
//-----------------------------------------------------------------------------
void readDS3231_Temperature(void)
{
unsigned char buf[2] ;
int ret ;

  //enT3() ; //turn on mosfet T3 to enable module DS3231

  //i2c1_write (DS3231_ADDR, "\xD0\x11", 2) ; //FAUX
  i2c1_write (DS3231_ADDR | I2C_NOSTOP, "\x11", 1) ;
  delay1ms(10) ;
  ret = i2c1_read (DS3231_ADDR | I2C_RESTART, buf, 2) ;

  if (ret == 2)
  { TempPart1 = buf[0] ; // read Temperature integer part from vector pRd3231
    TempPart2 = buf[1] ; // read Temperature fractional part
  }
  else { TempPart1 = 0 ; TempPart2 = 0 ; }

  //disT3() ; //turn off mosfet T3 to disable module DS3231 (lower Icc)
}*/

//-----------------------------------------------------------------------------
// Write data to DS1307 RTCC
//-----------------------------------------------------------------------------
void writeMCP79411(void)
{ 
unsigned char buf[8] ;
  
  //enT3() ; //turn on mosfet T3 to enable module DS3231

    // convert decimal to BCD
  second = decimal2bcd(ss) ;    
  minute = decimal2bcd(mm) ;
  hour   = decimal2bcd(hh) ;
  zz = zz | 8 ; //to enable Vbat input
  m_day  = decimal2bcd(jour) ;
  month  = decimal2bcd(mois) ; if ((annee % 4) == 0) month |= 0x20 ;//set LeapYear
  year   = decimal2bcd(annee) ;
   
  buf[0] = 0x00 ; 
  buf[1] = second | 128 ; //+128 pour activer bit7=ST du registre RTCSEC 
  buf[2] = minute ;
  buf[3] = hour ;
  buf[4] = zz ; // dummy (week day)
  buf[5] = m_day ;
  buf[6] = month ;
  buf[7] = year ;
    
  //i2c1_write (DS3231_ADDR, "\xD0\x00\x00\x15\x12\x01\x24\x05\x23", 9) ; //FAUX
  //i2c1_write (DS3231_ADDR, "\x00\x00\x15\x12\x01\x24\x05\x23", 8) ;  // OK !
  ///////i2c1_write (DS3231_ADDR, buf, 8) ;

  i2c1_write (MCP79411_ADDR_RTC, buf, 8) ;
  //delay1ms(10) ;
  
  //disT3() ; //turn off mosfet T3 to disable module DS3231 (lower Icc)
}

//-----------------------------------------------------------------------------
// Read data to DS1307 RTCC
//-----------------------------------------------------------------------------
void readMCP79411(void)
{
unsigned char buf[7] ;
int ret ;

  //enT3() ; //turn on mosfet T3 to enable module DS3231

  //i2c1_write (DS3231_ADDR | I2C_NOSTOP, "\xD0\x00", 2) ; //FAUX
  ///////i2c1_write (DS3231_ADDR | I2C_NOSTOP, "\x00", 1) ;

  i2c1_write (MCP79411_ADDR_RTC | I2C_NOSTOP, "\x00", 1) ;
  delay1ms(10) ;
  ///////ret = i2c1_read (DS3231_ADDR | I2C_RESTART, buf, 7) ;
  
  ret = i2c1_read (MCP79411_ADDR_RTC | I2C_RESTART, buf, 7) ;
  if (ret == 7)
  { second = buf[0] & 127 ; //skip bit7=ST of register RTCSEC
    minute = buf[1] ;
    hour   = buf[2] ;
    zz     = buf[3] ; // read day from register 3 (not used)
    m_day  = buf[4] ;
    month  = buf[5] ; if (month & 0x20 == 0x20) month = month & (~0x20) ; //mask Leap year
    year   = buf[6] ;

      // convert data from BCD format to decimal format
    ss = bcd2decimal(second) ;
    mm = bcd2decimal(minute) ;
    hh   = bcd2decimal(hour) ;
    jour = bcd2decimal(m_day) ;
    mois = bcd2decimal(month) ;
    annee= bcd2decimal(year) ;
  }
  else { ss = 0 ; mm = 0 ; hh = 0 ; jour = 1 ; mois = 1 ; annee = 0 ; }
  
  //disT3() ; //turn off mosfet T3 to disable module DS3231 (lower Icc)
}

//-----------------------------------------------------------------------------
// test if module DS3231 present ?
//-----------------------------------------------------------------------------
char isMCP79411present(void)
{
unsigned char buf[7] ;
int ret ;

  //enT3() ; //turn on mosfet T3 to enable module DS3231

  //i2c1_write (DS3231_ADDR | I2C_NOSTOP, "\xD0\x00", 2) ; //FAUX

///////  i2c1_write (DS3231_ADDR | I2C_NOSTOP, "\x00", 1) ;
///////  delay1ms(10) ;
///////  ret = i2c1_read (DS3231_ADDR | I2C_RESTART, buf, 7) ;

  i2c1_write (MCP79411_ADDR_RTC | I2C_NOSTOP, "\x00", 1) ;
  delay1ms(10) ;
  ret = i2c1_read (MCP79411_ADDR_RTC | I2C_RESTART, buf, 7) ;
  
  if (ret == 7) return 1 ; else return 0 ;
}

//-----------------------------------------------------------------------------
// read EUI-48 (= 00 04 A3 12 34 56 ) of the MCP79411
//-----------------------------------------------------------------------------
void EUI48_MCP79411(void)
{
unsigned char buf[6] ;
int p, i, j, ret ;

  i2c1_write (MCP79411_ADDR_EEP | I2C_NOSTOP, "\xF2", 1) ;
  delay1ms(10) ;
  ret = i2c1_read (MCP79411_ADDR_EEP | I2C_RESTART, buf, 6) ;
  
  if (ret == 6)
  { i = 0 ;
    for (j=0; j<6; j++) 
    { p = buf[j] / 16 ; 
      if (p > 9) txt[i] = 'A' + p - 10 ; else txt[i] = '0' + p ;
    
      p = buf[j] % 16 ;
      i++ ;
      if (p > 9) txt[i] = 'A' + p - 10 ; else txt[i] = '0' + p ;
      i++ ;
    }
  }
  else for (i=0; i<12; i++) txt[i] = '0' ;
  
  txt[i] = '\0' ;
}

//-----------------------------------------------------------------------------
// initialize MCP79411 (start osc. bit RTCSEC<ST> = 1 ; set bit VBATEN)
//-----------------------------------------------------------------------------
void startMCP79411(void)
{
unsigned char buf[5] ;
int ret ;
  
    //d'abord, lire les secondes (pour voir bit ST)
  i2c1_write (MCP79411_ADDR_RTC | I2C_NOSTOP, "\x00", 1) ;
  delay1ms(10) ;
  ret = i2c1_read (MCP79411_ADDR_RTC | I2C_RESTART, buf, 4) ;
  if (ret != 4) return ;
  
  second = buf[0] ; //to know how is bit7=ST of register RTCSEC
  zz     = buf[3] ; //to know how is bit3=VBATEN of register RTCWKDAY
  //delay1ms(1) ;

      //activer bit VBATEN, sans altérer RTCWKDAY
  if ((zz & 8) == 0)
  { buf[0] = 0x03 ; //register RTCWKDAY 
    buf[1] = zz | 8 ; //+8 pour activer bit3=VBATEN
    i2c1_write (MCP79411_ADDR_RTC, buf, 2) ;
  }

  delay1ms(10) ;

      //activer bit ST, sans altérer les secondes
  if ((second & 128) == 0)
  { buf[0] = 0x00 ; //register RTCSEC 
    buf[1] = second | 128 ; //+128 pour activer bit7=ST
    i2c1_write (MCP79411_ADDR_RTC, buf, 2) ;
  }
}

//-----------------------------------------------------------------------------
/*
// display time and date function
void RTC_display()
{
  static char Time[] = "TIME: 00:00:00";
  static char Date[] = "DATE: 00/00/2000";
 
  // convert data from BCD format to decimal format
  second = bcd_to_decimal(second);
  minute = bcd_to_decimal(minute);
  hour   = bcd_to_decimal(hour);
  m_day  = bcd_to_decimal(m_day);
  month  = bcd_to_decimal(month);
  year   = bcd_to_decimal(year);
  // end conversion
 
  // update time
  Time[6]  = hour   / 10 + '0';
  Time[7]  = hour   % 10 + '0';
  Time[9]  = minute / 10 + '0';
  Time[10] = minute % 10 + '0';
  Time[12] = second / 10 + '0';
  Time[13] = second % 10 + '0';
  // update date
  Date[6]  = m_day  / 10 + '0';
  Date[7]  = m_day  % 10 + '0';
  Date[9]  = month  / 10 + '0';
  Date[10] = month  % 10 + '0';
  Date[14] = year   / 10 + '0';
  Date[15] = year   % 10 + '0';
 
  LCD_Goto(1, 1);    // go to column 1, row 1
  LCD_Print(Time);   // print time
  LCD_Goto(1, 2);    // go to column 1, row 2
  LCD_Print(Date);   // print date
}
*/
