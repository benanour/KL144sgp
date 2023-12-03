/*
eeprom24.c: EEPROM 24LCxx
BENABADJI Noureddine - ORAN - May 24th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#include <c:\Program Files\Microchip\xc32\v1.43\pic32mx\include\xc.h>
#include "eeprom24.h"
#include "i2c1bn.h"

//----------------------------------------------------------------------------
void writeEEP (unsigned short addr, unsigned char value)
{
unsigned char buf[3] ;

  buf[0] = addr >> 8 ;  //eeprom HIGH address byte 
  buf[1] = addr & 0xFF ; //eeprom low address byte 
  buf[2] = value ;

  i2c1_write (EEP24LC64_ADDR, buf, 3) ;
  
    //Write Cycle Time Max. = 5 ms (24LC64 DS21189F.PDF p.3/24)
    //Write Cycle Time Max. = 10 ms (24C64 ATMEL  p.4/15)
  delay1ms(5) ; //OBLIGATOIRE, sinon, ça n'enregistre pas !
}
//----------------------------------------------------------------------------
//void wr_pageEEP (unsigned short addr, const void *buffer, int size)
void wr_pageEEP (unsigned short addr, char *buffer, int size)
{
int i ; //char buf[17] ; //ATTENTION: taille buf = size + 2
char buf[34] ; //2 bytes address + 32 bytes (1 page 24LC64)

  buf[0] = addr >> 8 ;  //eeprom HIGH address byte 
  buf[1] = addr & 0xFF ; //eeprom low address byte  
  for (i=0; i<size; i++) buf[i+2] = buffer[i] ;
  
  i2c1_write (EEP24LC64_ADDR, buf, size+2) ;
  
    //Write Cycle Time Max. = 5 ms (24LC64 DS21189F.PDF p.3/24)
    //Write Cycle Time Max. = 10 ms (24C64 ATMEL  p.4/15)
  delay1ms(6) ; //OBLIGATOIRE, sinon, ça n'enregistre pas !
}
//----------------------------------------------------------------------------
unsigned short readEEP (unsigned int addr)
{
unsigned char buf[2] ;
int ret ;

  //enT3() ;

  buf[0] = addr >> 8 ;  //eeprom HIGH address byte 
  buf[1] = addr & 0xFF ; //eeprom low address byte 

  i2c1_write (EEP24LC64_ADDR | I2C_NOSTOP, buf, 2) ;
  delay1ms(5) ;
  ret = i2c1_read (EEP24LC64_ADDR | I2C_RESTART, buf, 1) ;
   
  if (ret == 1) return (buf[0]) ; else return 0 ;

  //disT3() ; 
}
//----------------------------------------------------------------------------
int rd_pageEEP (unsigned short addr, char *buffer, int size)
{
char buf[2] ; int i, ret ;

  buf[0] = addr >> 8 ;  //eeprom HIGH address byte 
  buf[1] = addr & 0xFF ; //eeprom low address byte 

  i2c1_write (EEP24LC64_ADDR | I2C_NOSTOP, buf, 2) ;
  delay1ms(6) ;
  ret = i2c1_read (EEP24LC64_ADDR | I2C_RESTART, buffer, size) ;
 
  if (ret == size) return ret ; else { buffer[0] = '\0' ; return 0 ; }
  //return ret ;
}
//-----------------------------------------------------------------------------
void Erase_EEP (void)
{
unsigned int i, adr, adrMax = 8192 ; //cas 24LC64 ;
char buf[34] ; //2 bytes address + 32 bytes (1 page 24LC64)

  for (adr=0 ; adr < adrMax ; adr += 32) // 32 bytes per page
  {
    buf[0] = adr >> 8 ;  //eeprom HIGH address byte 
    buf[1] = adr & 0xFF ; //eeprom low address byte  
    //for (i=0; i<size; i++) buf[i+2] = buffer[i] ;
    for (i=0 ; i < 32 ; i++) buf[i] = 0xFF ; //for erasing
  
    i2c1_write (EEP24LC64_ADDR, buf, 34) ;
  
      //Write Cycle Time Max. = 5 ms (24LC64 DS21189F.PDF p.3/24)
      //Write Cycle Time Max. = 10 ms (24C64 ATMEL  p.4/15)
    delay1ms(6) ; //OBLIGATOIRE, sinon, ça n'enregistre pas !
  }
}
/*
char status ;
unsigned int i, adr, adrMax = 8192 ; //cas 24LC64

  for (i=0 ; i < 32 ; i++) tx_data32[i] = 0xFF ; //for erasing
  tx_data32[32] = 0x00 ; // '\0' ASCII 0
  
  for (adr=0 ; adr < adrMax ; adr += 32) // 32 bytes per page
  {
    wrEEP (adr, 0xFF, 3, SlaveAddress) ;

    // The data to be written should be end with '\0' if using 
    // char MasterputsI2C1(unsigned char *) library function. 
    status = MasterputsI2C1(pWrite32) ;
	
    //This function returns -3 if a write collision occurred
    if (status == -3) while (1) ; //ATTENTION, BLOQUANTE

    StopI2C1() ;	//Send the Stop condition
    IdleI2C1() ;	//Wait to complete

    AckPoll (SlaveAddress) ;
    delay10ms() ; //Write Cycle Time Max. = 10 ms
			      //OBLIGATOIRE, sinon, ça n'enregistre pas !
  }
}
*/
