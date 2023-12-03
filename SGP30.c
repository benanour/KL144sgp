/*
SGP30.c: eCO2 sensor I2C functions
BENABADJI Noureddine - ORAN - Nov. 22nd, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#include <c:\Program Files\Microchip\xc32\v1.43\pic32mx\include\xc.h>
#include "sgp30.h"
#include "i2c1bn.h"

//unsigned char rd_ds3231[8] ;
//unsigned char *pRd3231 = (unsigned char *)rd_ds3231 ;

//-----------------------------------------------------------------------------
//feature set version number. Should return 0x0020 or 0x0022 
//-----------------------------------------------------------------------------
int sgp30getVersion(void)
{
int rtn ; unsigned char buf[3] ;

  rtn = i2c1_write (SGP30_ADDR | I2C_NOSTOP, "\x20\x2F", 2) ; //send command 0x202F
  delay1ms(10) ;
  rtn = i2c1_read (SGP30_ADDR | I2C_RESTART, buf, 3) ;
  
  if (rtn == 3) sgp30Version = 256*buf[0] + buf[1] ; //version
  else sgp30Version = 0 ; 

  return rtn ; 
}

//-----------------------------------------------------------------------------
// runs an on-chip self-test. In case of a successful self-test, the sensor 
//returns the fixed data pattern 0xD400 (with correct CRC). 
//-----------------------------------------------------------------------------
int sgp30MeasureTest(void)
{
int rtn ; unsigned char buf[3] ;

  rtn = i2c1_write (SGP30_ADDR | I2C_NOSTOP, "\x20\x32", 2) ; //send command 0x2032
  delay1ms(220) ;
  rtn = i2c1_read (SGP30_ADDR | I2C_RESTART, buf, 3) ;
  
  if (rtn == 3) sgp30SelfTest = 256*buf[0] + buf[1] ; //version
  else sgp30SelfTest = 0 ; 

  return rtn ; 
}

//-----------------------------------------------------------------------------
// After the ?Init_air_quality? cmd, a ?Measure_air_quality? cmd has to be sent 
// in regular intervals of 1s to ensure proper operation of the dynamic baseline
// compensation algorithm. The sensor responds with 2 data bytes (MSB first) and
// 1 CRC byte for each of the 2 preprocessed air quality signals in the order :
// CO2eq (ppm) and TVOC (ppb). For the first 15s after the ?Init_air_quality? cmd
// the sensor is in an initialization phase during which a ?Measure_air_quality?
// command returns fixed values of 400 ppm CO 2 eq and 0 ppb TVOC. 
//-----------------------------------------------------------------------------
int sgp30initIAQ(void)
{
int rtn ;

  rtn = i2c1_write (SGP30_ADDR, "\x20\x03", 2) ; //send command 0x2003
  delay1ms(10) ;
  return rtn ; 
}
//-----------------------------------------------------------------------------
int sgp30MeasureIAQ(void)
{
int rtn ; unsigned char buf[6] ;

  rtn = i2c1_write (SGP30_ADDR | I2C_NOSTOP, "\x20\x08", 2) ; //send command 0x2008
  delay1ms(12) ;
  rtn = i2c1_read (SGP30_ADDR | I2C_RESTART, buf, 6) ;
  
  if (rtn == 6) 
  { sgp30eCO2 = 256*buf[0] + buf[1] ; sgp30TVOC = 256*buf[3] + buf[4] ;
  }
  else { sgp30eCO2 = 0 ; sgp30TVOC = 0 ; }

  return rtn ; 
}
