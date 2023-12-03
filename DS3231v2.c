/*
DS3231v2.c: RTCC chip (DS1307, DS3231 or DS1338=DS1307 avec Vdd=3v3)
BENABADJI Noureddine - ORAN - May 24th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#include <c:\Program Files\Microchip\xc32\v1.43\pic32mx\include\xc.h>
#include "DS3231v2.h"
#include "i2c1bn.h"

//unsigned char rd_ds3231[8] ;
//unsigned char *pRd3231 = (unsigned char *)rd_ds3231 ;

//-----------------------------------------------------------------------------
// convert BCD to decimal function
//-----------------------------------------------------------------------------
unsigned short bcd_to_decimal(unsigned short number) 
{
  unsigned short rtn = (number >> 4) * 10 + (number & 0x0F) ;
  return(rtn) ;
}
 
//-----------------------------------------------------------------------------
// convert decimal to BCD function
//-----------------------------------------------------------------------------
unsigned short decimal_to_bcd(unsigned short number) 
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
void writeDS3231_dis32kHz(void)
{
  //i2c1_write (DS3231_ADDR, "\xD0\x0F\x00", 3) ; //FAUX
  i2c1_write (DS3231_ADDR, "\x0F\x00", 2) ;
  //delay1ms(20) ;
}
//-----------------------------------------------------------------------------
// Write data to Status Register 0Fh ; set bit3 <EN32KHZ> to ...
// ...enable the 32KHZ output.
//-----------------------------------------------------------------------------
void writeDS3231_en32kHz(void)
{
  //i2c1_write (DS3231_ADDR, "\xD0\x0F\x08", 3) ; //FAUX
  i2c1_write (DS3231_ADDR, "\x0F\x08", 2) ;
  //delay1ms(20) ;
}
//-----------------------------------------------------------------------------
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
}

//-----------------------------------------------------------------------------
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
}

//-----------------------------------------------------------------------------
// Write data to DS1307 RTCC
//-----------------------------------------------------------------------------
void writeDS1307(void)
{ 
unsigned char buf[8] ;
  
  //enT3() ; //turn on mosfet T3 to enable module DS3231

    // convert decimal to BCD
  second = decimal_to_bcd(ss) ;    
  minute = decimal_to_bcd(mm) ;
  hour   = decimal_to_bcd(hh) ;
  m_day  = decimal_to_bcd(jour) ;
  month  = decimal_to_bcd(mois) ;
  year   = decimal_to_bcd(annee) ;
   
  buf[0] = 0x00 ; 
  buf[1] = second ; 
  buf[2] = minute ;
  buf[3] = hour ;
  buf[4] = zz ; // dummy
  buf[5] = m_day ;
  buf[6] = month ;
  buf[7] = year ;
    
  //i2c1_write (DS3231_ADDR, "\xD0\x00\x00\x15\x12\x01\x24\x05\x23", 9) ; //FAUX
  //i2c1_write (DS3231_ADDR, "\x00\x00\x15\x12\x01\x24\x05\x23", 8) ;  // OK !
  i2c1_write (DS3231_ADDR, buf, 8) ;
  //delay1ms(10) ;
  
  //disT3() ; //turn off mosfet T3 to disable module DS3231 (lower Icc)
}

//-----------------------------------------------------------------------------
// Read data to DS1307 RTCC
//-----------------------------------------------------------------------------
void readDS1307(void)
{
unsigned char buf[7] ;
int ret ;

  //enT3() ; //turn on mosfet T3 to enable module DS3231

  //i2c1_write (DS3231_ADDR | I2C_NOSTOP, "\xD0\x00", 2) ; //FAUX
  i2c1_write (DS3231_ADDR | I2C_NOSTOP, "\x00", 1) ;
  delay1ms(10) ;
  ret = i2c1_read (DS3231_ADDR | I2C_RESTART, buf, 7) ;
  
  if (ret == 7)
  { second = buf[0] ; 
    minute = buf[1] ;
    hour   = buf[2] ;
    zz     = buf[3] ; // read day from register 3 (not used)
    m_day  = buf[4] ;
    month  = buf[5] ;
    year   = buf[6] ;

      // convert data from BCD format to decimal format
    ss = bcd_to_decimal(second) ;
    mm = bcd_to_decimal(minute) ;
    hh   = bcd_to_decimal(hour) ;
    jour = bcd_to_decimal(m_day) ;
    mois = bcd_to_decimal(month) ;
    annee= bcd_to_decimal(year) ;
  }
  else { ss = 0 ; mm = 0 ; hh = 0 ; jour = 1 ; mois = 1 ; annee = 0 ; }
  
  //disT3() ; //turn off mosfet T3 to disable module DS3231 (lower Icc)
}

//-----------------------------------------------------------------------------
// test if module DS3231 present ?
//-----------------------------------------------------------------------------
char isDS3231present(void)
{
unsigned char buf[7] ;
int ret ;

  //enT3() ; //turn on mosfet T3 to enable module DS3231

  //i2c1_write (DS3231_ADDR | I2C_NOSTOP, "\xD0\x00", 2) ; //FAUX
  i2c1_write (DS3231_ADDR | I2C_NOSTOP, "\x00", 1) ;
  delay1ms(10) ;
  ret = i2c1_read (DS3231_ADDR | I2C_RESTART, buf, 7) ;
  
  if (ret == 7) return 1 ; else return 0 ;
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
