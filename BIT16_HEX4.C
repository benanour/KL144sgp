/*
BIT16_HEX4.C: conv. a 16-bit unsigned integer in 4 hexadecimal digits
BENABADJI Noureddine - ORAN - Nov. 13th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#include <c:\Program Files\Microchip\xc32\v1.43\pic32mx\include\xc.h>
#include "BIT16_HEX4.h"

//extern char hexStr[5] ; // 4 bytes in hexadecimal digit, & hexStr[4] = '\0' ;

//----------------------------------------------------------------------------
// convert a single digit to hexadecimal character
//----------------------------------------------------------------------------
char hexChar(unsigned short digit)
{
  if (digit < 10) return '0' + digit ; else return 'A' + (digit - 10) ;
}

//----------------------------------------------------------------------------
// conv. a 16-bit unsigned integer in hexadecimal format
//----------------------------------------------------------------------------
void Int16_hex4dgt(unsigned short value)
{
//char hexStr[7] ; // hold the hexadecimal representation, including "0x" & null

  //hexStr[0] = '0' ;
  //hexStr[1] = 'x' ;
  hexStr[0] = hexChar((value >> 12) & 0xF) ;
  hexStr[1] = hexChar((value >> 8) & 0xF) ;
  hexStr[2] = hexChar((value >> 4) & 0xF) ;
  hexStr[3] = hexChar(value & 0xF) ;
  hexStr[4] = '\0' ;

  //// Output each character of the string
  //for (int i = 0; i < 6; ++i) putchar(hexStr[i]) ; 
    
  //putchar('\n'); // Newline at the end
}

/*
//----------------------------------------------------------------------------
int main()
{
uint16_t myValue = 0xABCD ;  // Example 16-bit value

  printHex16(myValue) ;      // Call the subroutine
  return 0 ;
}
*/
