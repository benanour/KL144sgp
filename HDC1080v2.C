/*
HDC1080v2.C: HDC1080 sensor routines
BENABADJI Noureddine - ORAN - May 22nd, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#include <c:\Program Files\Microchip\xc32\v1.43\pic32mx\include\xc.h>
#include "hdc1080v2.h"
#include "i2c1bn.h"

//-----------------------------------------------------------------------------
void HDC1080_Init(void)
{
  //enT3() ;

  i2c1_write (HDC1080_ADDR, "\x02\x90\x00", 3) ; //cfg. Configuration Register (0x02))
  delay1ms(20) ;

  //disT3() ; 
}
//-----------------------------------------------------------------------------
unsigned int HDC1080_readID(unsigned char c)
{
unsigned char buf[2] ;
unsigned int value ;
int ret ;

  //enT3() ;

  if (c == 0xFF) i2c1_write (HDC1080_ADDR | I2C_NOSTOP, "\xff", 1) ;//Device ID
  if (c == 0xFE) i2c1_write (HDC1080_ADDR | I2C_NOSTOP, "\xfe", 1) ;//Manuf. ID
  delay1ms(7) ;
  ret = i2c1_read (HDC1080_ADDR | I2C_RESTART, buf, 2) ;
  
  //disT3() ;
  
  if (ret == 2) { value = 256*buf[0] + buf[1] ; return value ; }
  else return 0 ;
}

//-----------------------------------------------------------------------------
void HDC1080_read(void)
{
unsigned char buf[4] ;
//unsigned int value ; //, i ;
int ret ; //char status ;

  //enT3() ;

  i2c1_write (HDC1080_ADDR | I2C_NOSTOP, "\x00", 1) ;
  delay1ms(20) ; //delay1ms(20) ; //14-bit conversion needs 6.35ms(temp) + 6.5ms(hum) typical
  ret = i2c1_read (HDC1080_ADDR | I2C_RESTART, buf, 4) ;
   
  if (ret == 4) 
  { //tempHDC = (((unsigned int)buf[0] << 8 | buf[1])) ; //ça donne 0 fixe
    tempHDC = buf[0] *256 + buf[1] ;
    tempHDC = ((unsigned long)tempHDC * 165L)/65536L - 40 ;  //in °C

    //humHDC = (((unsigned int)buf[2] << 8 | buf[3])) ; //ça donne 0 fixe
    humHDC = buf[2] *256 + buf[3] ;
    humHDC = ((unsigned long)humHDC * 100L)/65536L ;  //in %  
  }
  else { tempHDC = 0 ; humHDC = 0 ; }

  //disT3() ; 
}
