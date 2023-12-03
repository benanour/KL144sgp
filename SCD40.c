/*
SCD40.c: CO2 sensor I2C functions
BENABADJI Noureddine - ORAN - Nov. 10th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#include <c:\Program Files\Microchip\xc32\v1.43\pic32mx\include\xc.h>
#include "scd40.h"
#include "i2c1bn.h"

//unsigned char rd_ds3231[8] ;
//unsigned char *pRd3231 = (unsigned char *)rd_ds3231 ;

//-----------------------------------------------------------------------------
//start periodic measurement mode. The signal update interval is 5 seconds
//-----------------------------------------------------------------------------
int scd40startPeriodicMeas(void)
{
int rtn ;

  rtn = i2c1_write (SCD40_ADDR, "\x21\xB1", 2) ; //send command 0x21B1
  delay1ms(1) ;
  return rtn ; 
}

//-----------------------------------------------------------------------------
//stop periodic measurement mode to change the sensor configuration or to save 
//power. Note that the sensor will only respond to other commands 500 ms after
//-----------------------------------------------------------------------------
int scd40stopPeriodicMeas(void)
{
int rtn ;

  rtn = i2c1_write (SCD40_ADDR, "\x3F\x86", 2) ; //send command 0x3F86
  delay1ms(500) ;
  return rtn ; 
}

//-----------------------------------------------------------------------------
//If no data is available in the buffer, the sensor returns a NACK. To avoid a 
//NACK response, the get_data_ready_status can be issued to check data status 
//-----------------------------------------------------------------------------
int scd40readMeas(void)
{
int rtn ; unsigned char buf[9] ;

  rtn = i2c1_write (SCD40_ADDR | I2C_NOSTOP, "\xEC\x05", 2) ; //send command 0xEC05
  delay1ms(10) ; //delay1ms(1) ;
  rtn = i2c1_read (SCD40_ADDR | I2C_RESTART, buf, 9) ;
  
  if (rtn == 9)
  { scd40co2 = 256*buf[0] + buf[1] ; //ppm
    scd40tem = 256*buf[3] + buf[4] ; scd40tem = 175L*(long)scd40tem/65535L ;   
    scd40temAff = scd40tem - 45 ;
    scd40hum = 256*buf[6] + buf[7] ; scd40hum = 100L*(long)scd40hum/65535L ;       
  }
  else { scd40co2 = 0 ; scd40tem = 0 ; scd40hum = 0 ; }

  return rtn ; 
}

//-----------------------------------------------------------------------------
//unique serial number with a length of 48 bits (big endian format).
//-----------------------------------------------------------------------------
int scd40Serial(void)
{
int rtn ; unsigned char buf[9] ;

  rtn = i2c1_write (SCD40_ADDR | I2C_NOSTOP, "\x36\x82", 2) ; //send command 0x3682
  delay1ms(10) ; //delay1ms(1) ;
  rtn = i2c1_read (SCD40_ADDR | I2C_RESTART, buf, 9) ;
  
  if (rtn == 9)
  { scd40serial0 = 256*buf[0] + buf[1] ; 
    scd40serial1 = 256*buf[3] + buf[4] ;      
    scd40serial2 = 256*buf[6] + buf[7] ;        
  }
  else { scd40serial0 = 0 ; scd40serial1 = 0 ; scd40serial2 = 0 ; }

  return rtn ; 
}

//-----------------------------------------------------------------------------
//read Temperature offset. (default = 4°C)
//-----------------------------------------------------------------------------
int scd40readToffset(void)
{
int rtn ; unsigned char buf[3] ;

  rtn = i2c1_write (SCD40_ADDR | I2C_NOSTOP, "\x23\x18", 2) ; //send command 0x2318
  delay1ms(10) ; //delay1ms(1) ;
  rtn = i2c1_read (SCD40_ADDR | I2C_RESTART, buf, 3) ;
  
  if (rtn == 3)
  { scd40Toffset = 256*buf[0] + buf[1] ;
    scd40Toffset = 175L*(long)scd40Toffset / 65535L ;   
  }
  else { scd40Toffset = 0 ; }

  return rtn ; 
}

//-----------------------------------------------------------------------------
//read sensor Altitude. (default = ??? m)
//-----------------------------------------------------------------------------
int scd40readAltitude(void)
{
int rtn ; unsigned char buf[3] ;

  rtn = i2c1_write (SCD40_ADDR | I2C_NOSTOP, "\x23\x22", 2) ; //send command 0x2322
  delay1ms(10) ; //delay1ms(1) ;
  rtn = i2c1_read (SCD40_ADDR | I2C_RESTART, buf, 3) ;
  
  if (rtn == 3)
  { scd40Altitude = 256*buf[0] + buf[1] ;
  }
  else { scd40Altitude = 0 ; }

  return rtn ; 
}

//-----------------------------------------------------------------------------
//read sensor Pressure. (default = ??? Pa)
//-----------------------------------------------------------------------------
int scd40readPressure(void)
{
int rtn ; unsigned char buf[3] ;

  rtn = i2c1_write (SCD40_ADDR | I2C_NOSTOP, "\xE0\x00", 2) ; //send command 0xE000
  delay1ms(10) ; //delay1ms(1) ;
  rtn = i2c1_read (SCD40_ADDR | I2C_RESTART, buf, 3) ;
  
  if (rtn == 3)
  { scd40Pressure = 256*buf[0] + buf[1] ;
  }
  else { scd40Pressure = 0 ; }

  return rtn ; 
}
