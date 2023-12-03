/*
NokiaScr.C: GUI screens 
BENABADJI Noureddine - ORAN - May 26th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#include <c:\Program Files\Microchip\xc32\v1.43\pic32mx\include\xc.h>
//#include "SPI1.H"

#include <math.h>

#include "NokiaScr.h"
#include "Main.h"
#include "scd40.h"
#include "sgp30.h"
#include "BIT16_HEX4.h"

unsigned int ppmtriee[18], ppmQty[18] ;
unsigned int ppbtriee[18], ppbQty[18] ;
char affTVOC = 1 ;

//------------------------------------------------------------------------
void NokiaSplash1(void)
{
unsigned char splash[7] = "APOMOS" ;
short i, j ;

  j = 3 ;
  for (i = 0; i < 6; i++) 
  { LCD_PutCharZoom2( splash[i], 1, j ) ; j += 13 ;
      //OPTIONAL ANIMATION
    if (i < 5) Nokia_PositionXY (j, 2) ; LCD_PutChar (i+49) ; 
    delay1ms(700) ;
  }
  Nokia_PositionXY (79, 2) ; Nokia_SendString("6");
  delay1ms(500) ;
  Nokia_PositionXY (79, 2) ; Nokia_SendString("7");
  delay1ms(500) ;
  Nokia_PositionXY (79, 2) ; Nokia_SendString("8");
  Nokia_PositionXY (0, 0) ; LCD_DrawLine (0x0A, 84) ;  //Lin0 =====
  Nokia_PositionXY (0, 3) ; LCD_DrawLine (0x0A, 84) ;  //Lin3 =====
  Nokia_PositionXY (8, 4) ; Nokia_SendString("PIC32MX170F256") ;
  //Nokia_PositionXY (3, 5) ; Nokia_SendString(" Monitor System") ;
  Nokia_PositionXY (0, 5) ; Nokia_SendString("eCO2 Monitor syst") ;
}

//------------------------------------------------------------------------
void NokiaSysReport(void)
{
char Tperiod ;

  Nokia_Clear() ; PR1 = 32766 ;

  Nokia_PositionXY (6, 0) ; Nokia_SendString("SYSTEM  REPORT") ;
  Nokia_PositionXY (0, 1) ; LCD_DrawLine (0x0A, 84) ;  //Lin1 =====

  //----- NE SERT A RIEN POUR LE SCD40 !
  ///////Nokia_PositionXY (0, 1) ; Nokia_SendString("calibration :") ;
  ///////Nokia_PositionXY (67, 1) ; LCD_Write_Integer(calib, 3) ; 

  Nokia_PositionXY (0, 2) ; Nokia_SendString("Packets: ") ;
  val2txt(nPacketSaved, txt, 4) ; Nokia_SendString(txt) ;

  Nokia_PositionXY (0, 3) ; Nokia_SendString("Alarm 1: ") ;
  LCD_Write_Integer(alarm1, 4) ; 
  Nokia_PositionXY (67, 3) ; Nokia_SendString("ppm") ;

  Nokia_PositionXY (0, 4) ; Nokia_SendString("meas Cycle: ") ;
  Tperiod = Toff + 1 ; LCD_Write_Integer(Tperiod, 2) ; 
  Nokia_PositionXY (72, 4) ; LCD_PutChar('s') ;
  
  Nokia_PositionXY (0, 5) ; Nokia_SendString("Contrast Vop:") ;
  Nokia_PositionXY (67, 5) ; LCD_Write_Integer(Vop, 3) ;
  
  delay1ms(4000) ;
}

//------------------------------------------------------------------------
void NokiaSysCfgMenu(void)
{
char choix = 0, choice ; short s ;

  //Nokia_PositionXY (4, 0) ; Nokia_SendString("SYSTEM  CONFIG.") ;
  //Nokia_PositionXY (0, 1) ; LCD_DrawLine (0x0A, 84) ;  //Lin1 =====

  Nokia_PositionXY (8, 0) ; Nokia_SendString("SGP30 Infos...") ;
  Nokia_PositionXY (8, 1) ; Nokia_SendString("Erase EEPROM ?") ;
  Nokia_PositionXY (8, 2) ; Nokia_SendString("Alarm1 setting") ;
  Nokia_PositionXY (8, 3) ; Nokia_SendString("Measures cycle") ;
  Nokia_PositionXY (8, 4) ; Nokia_SendString("Contrast") ;
  Nokia_PositionXY (8, 5) ; Nokia_SendString("RTCC setting") ;

  PR1 = 22000 ;
  choice = ChosenOption(0, choix) ; if (choice == -1) return ;
  
    //blank lines 1 to 5
  //for (s=1; s<6; s++) { Nokia_PositionXY (0, s) ; LCD_DrawLine (0x00, 84) ; }
  Nokia_Clear() ;
  
  switch (choice)
  { case 0: NokiaSysCfg1() ; break ; //SCD40 Infos...
    case 1: NokiaSysCfg2() ; break ; //Erase EEPROM (Yes/No)
    case 2: NokiaSysCfg3() ; break ; //Alarm1 setting
    case 3: NokiaSysCfg4() ; break ; //measure period setting
    case 4: NokiaSysCfg5() ; break ; //Contrast setting
    case 5: NokiaSysCfg6() ; break ; //RTCC setting
  } 
}

//------------------------------------------------------------------------
void NokiaSysCfg1(void) //SCD40 Infos...
{
  Nokia_Clear() ;
  
  Nokia_PositionXY (12, 0) ; Nokia_SendString("SGP30  INFOS") ; 
  Nokia_PositionXY (0, 1) ; LCD_DrawLine (0x02, 84) ;  //Lin4 -----

  Nokia_PositionXY (0, 2) ; Nokia_SendString("Version: 0x") ;
  Int16_hex4dgt(sgp30Version) ; Nokia_SendString(hexStr) ; 
  
  Nokia_PositionXY (0, 3) ; Nokia_SendString("SelfTest: 0x") ;
  Int16_hex4dgt(sgp30SelfTest) ; Nokia_SendString(hexStr) ; 
  
  /* 
  Nokia_PositionXY (0, 4) ; Nokia_SendString("Altitude: ") ;
  val2txt(scd40Altitude, txt, 4) ; Nokia_SendString(txt) ; Nokia_SendString(" m") ;

  Nokia_PositionXY (0, 5) ; Nokia_SendString("Pressure:") ;
  val2txt(scd40Pressure, txt, 4) ; Nokia_SendString(txt) ; Nokia_SendString("hPa") ;
  */
  
  delay1ms(8000) ;
}
//------------------------------------------------------------------------
void NokiaSysCfg2(void) //Erase EEPROM (Yes/No)
{
int i ;

  calib = readEEP(ADDR_calib0) ; //retreive calib
  alarm1 = readEEP(ADDR_alarm1) ; //retreive alarm1

  Nokia_PositionXY (6, 2) ; Nokia_SendString("Erasing EEPROM") ;
  Nokia_PositionXY (6, 3) ; Nokia_SendString("...") ;    
  Nokia_PositionXY (0, 4) ; LCD_DrawLine (0x02, 84) ;  //Lin4 -----

  Erase_EEP () ; //EraseEEPROM() ; //delay1ms(5) ; 
  Nokia_PositionXY (30, 3) ; Nokia_SendString("DONE !") ; 
  nPacketSaved = 0 ;
  adrOfs = 0 ;
  
  i = ADDR_adrOfs ;
  writeEEP(i++, adrOfs) ; //store the last...
  writeEEP(i, adrOfs) ; //... adrOfs used
  writeEEP(ADDR_calib0, calib) ; //store again calib
  writeEEP(ADDR_alarm1, alarm1) ; //store again alarm1
}
//------------------------------------------------------------------------
void NokiaSysCfg3(void) //Alarm1 setting
{
char  choice, str[15] = "[  0 ...  63] " ; 
short extA, extB ;
short level = 0, i, incr[4] = {63, 15, 3, 0} ;
short ijkp[4] = {0, 0, 0, 0} ;
short s ;
char choix = 2 ; 

  Nokia_Clear() ;
  
  Nokia_PositionXY (0, 0) ; Nokia_SendString("ALARM/10 SETTING") ;
  Nokia_PositionXY (0, 1) ; LCD_DrawLine (0x0A, 84) ;  //Lin1 =====
  //Nokia_PositionXY (0, 1) ; LCD_DrawLine (0x02, 84) ;  //Lin1 -----
  
  do
  { extB = 64*ijkp[0] + 16*ijkp[1] + 4*ijkp[2] + ijkp[3] - 1 ;

    for (s=2; s<6; s++) //for lines 2 to 5
    { extA = extB + 1 ;
      extB = extA + incr[level] ;   
      val2txt(extA, txt, 3) ; for (i=1; i<4; i++) str[i] = txt[i-1] ;
      val2txt(extB, txt, 3) ; for (i=9; i<12; i++) str[i] = txt[i-9] ;
      //blank leading zero
      if (str[1] == '0') { str[1] = ' ' ; if (str[2] == '0') str[2] = ' ' ; }
      if (str[9] == '0') { str[9] = ' ' ; if (str[10] == '0') str[10] = ' ' ; }   
      //Nokia_PositionXY (6, 2) ; Nokia_SendString("[  0 ...  63]") ;
      Nokia_PositionXY (9, s) ; Nokia_SendString(str) ;
    }

    choice = ChosenOption(2, choix) ; if (choice == -1) return ;
  
    ijkp[level] = choice ; level++ ;
    
  }while (level < 4) ;

  Nokia_Clear() ;
  Nokia_PositionXY (5, 1) ; Nokia_SendString("Setting done !") ;

  extA = 64*ijkp[0] + 16*ijkp[1] + 4*ijkp[2] + ijkp[3] ;
  alarm1 = extA ; writeEEP(ADDR_alarm1, alarm1) ; //store alarm1
  alarm1 = alarm1*10 ; alarm2 = alarm1 + 500 ; alarm3 = alarm1 + 1000 ;
  
  Nokia_PositionXY (0, 3) ; Nokia_SendString("Alarm1 = ") ;
  val2txt(alarm1, txt, 4) ; Nokia_SendString(txt) ; Nokia_SendString(" ppm") ;
  Nokia_PositionXY (0, 4) ; Nokia_SendString("Alarm2 = ") ;
  val2txt(alarm2, txt, 4) ; Nokia_SendString(txt) ; Nokia_SendString(" ppm") ;
  Nokia_PositionXY (0, 5) ; Nokia_SendString("Alarm3 = ") ;
  val2txt(alarm3, txt, 4) ; Nokia_SendString(txt) ; Nokia_SendString(" ppm") ;
  delay1ms(3000) ;
}
//------------------------------------------------------------------------
void NokiaSysCfg4(void) //Measures cycle
{
char choix = 2, choice, Tperiod ;

  Nokia_Clear() ;
  
  Nokia_PositionXY (2, 0) ; Nokia_SendString("DATA ACQUISITION") ;
  Nokia_PositionXY (4, 1) ; Nokia_SendString("Cycle (s) : ") ;
  //Nokia_PositionXY (0, 1) ; LCD_DrawLine (0x0A, 84) ;  //Lin1 =====

  Nokia_PositionXY (21, 2) ; Nokia_SendString("Increment") ;
  Nokia_PositionXY (21, 3) ; Nokia_SendString("Decrement") ;
  Nokia_PositionXY (21, 4) ; Nokia_SendString("Accept") ;
  Nokia_PositionXY (21, 5) ; Nokia_SendString("Cancel") ;
    
  do
  { Tperiod = Toff + 1 ;
    Nokia_PositionXY (70, 1) ; LCD_Write_Integer(Tperiod, 2) ;
    choice = ChosenOption(2, choix) ; if (choice == -1) choice = 3 ; //timeout
    choix = choice + 2 ;
  
    switch (choice)
    { case 0: if (++Toff > 9) Toff = 0 ; break ; //increment Toff
      case 1: if (--Toff < 0) Toff = 9 ; break ; //decrement Toff
      case 2: if (Toff != ToffOld) { ToffOld = Toff; writeEEP(ADDR_Toff, Toff); } 
              break ; //Accept & save Toff to EEPROM
      case 3: Toff = ToffOld ; break ; //Cancel & Toff = ToffOld
    }
  }while((choice != 2) && (choice != 3)) ;   
}
//------------------------------------------------------------------------
void NokiaSysCfg5(void) //Contrast 0xB8 (=184, clair++) to 0xC2 (=194, foncé++)
{
char choix = 2, choice ;
unsigned char VopOLD ;

  VopOLD = Vop ;
 
  do
  { Nokia_Clear() ; Nokia_Init(Vop) ;
  
    Nokia_PositionXY (2, 0) ; Nokia_SendString("CONTRAST SETTING") ;
    Nokia_PositionXY (4, 1) ; Nokia_SendString("Op.Volt Vop:") ;
    //Nokia_PositionXY (0, 1) ; LCD_DrawLine (0x0A, 84) ;  //Lin1 =====

    Nokia_PositionXY (21, 2) ; Nokia_SendString("Darker") ; //("Increment")
    Nokia_PositionXY (21, 3) ; Nokia_SendString("Clearer") ;//("Decrement")
    Nokia_PositionXY (21, 4) ; Nokia_SendString("Accept") ;
    Nokia_PositionXY (21, 5) ; Nokia_SendString("Cancel") ;

    Nokia_PositionXY (66, 1) ; LCD_Write_Integer(Vop, 3) ;
    choice = ChosenOption(2, choix) ; if (choice == -1) choice = 3 ; //timeout
    choix = choice + 2 ;
  
    switch (choice)
    { case 0: if (++Vop > VopMAX) Vop = VopMIN ; break ; //Vop++
      case 1: if (--Vop < VopMIN) Vop = VopMAX ; break ; //Vop--
      case 2: if (Vop != VopOLD) writeEEP(ADDR_Vop, Vop) ; break ;//Accept & save
      case 3: Vop = VopOLD ; break ; //Cancel & Vop = VopOLD
    }
  }while((choice != 2) && (choice != 3)) ;
  
  if (choice == 3) { Nokia_Clear() ; Nokia_Init(Vop) ; }
}

//------------------------------------------------------------------------
void NokiaSysCfg6(void) //RTCC setting
{
char choix = 2, choice, updRTCC = 0 ;

  do
  { Nokia_Clear() ;
  
    Nokia_PositionXY (0, 0) ; Nokia_SendString("R.T.C.C. SETTING") ;
    Nokia_PositionXY (0, 1) ; LCD_DrawLine (0x0A, 84) ;  //Lin1 =====
  //Nokia_PositionXY (0, 1) ; LCD_DrawLine (0x02, 84) ;  //Lin1 -----

    Nokia_PositionXY (21, 2) ;
    LCD_Write_Integer(hh, 2) ; LCD_PutChar(':') ;
    LCD_Write_Integer(mm, 2) ; LCD_PutChar(':') ;
    LCD_Write_Integer(ss, 2) ; 
    
    Nokia_PositionXY (21, 3) ; 
    LCD_Write_Integer(jour, 2) ; LCD_PutChar('/') ;
    LCD_Write_Integer(mois, 2) ; LCD_PutChar('/') ;
    LCD_Write_Integer(annee, 2) ; 

    Nokia_PositionXY (21, 4) ; Nokia_SendString("Accept") ;
    Nokia_PositionXY (21, 5) ; Nokia_SendString("Cancel") ;

    choice = ChosenOption(2, choix) ; if (choice == -1) choice = 3 ; //timeout
    choix = choice + 2 ;
  
    switch (choice)
    { case 0: updRTCC = ChosenOptionRTCC(2, choix) ; break ; 
      case 1: updRTCC = ChosenOptionRTCC(2, choix) ;break ; 
      case 2: if (presenceDS3231) writeDS1307() ; 
              else if (presenceMCP79411) writeMCP79411() ; 
              break ;//Accept & save
      case 3: if (presenceDS3231) readDS1307() ;
              else if (presenceMCP79411) readMCP79411() ; 
              break ; //Cancel & return
    }
    if (updRTCC == -1) choice = 3 ; //timeout inside function ChosenOptionRTCC()
    
  }while((choice != 2) && (choice != 3)) ; 
  
  if (updRTCC == -1)
  { if (presenceDS3231) readDS1307() ;
    else if (presenceMCP79411) readMCP79411() ;
  }
}

//------------------------------------------------------------------------
void AffDgt(char i, char p, char star, char inv)
{
char dgt ;

  if ((star == 2) || (star == 3)) 
  { switch(i)
    { case 0: if (star == 2) dgt = hh / 10 ; else dgt = jour / 10 ; break ;
      case 1: if (star == 2) dgt = hh % 10 ; else dgt = jour % 10 ; break ; 
      case 2: if (star == 2) dgt = mm / 10 ; else dgt = mois / 10 ; break ;
      case 3: if (star == 2) dgt = mm % 10 ; else dgt = mois % 10 ; break ;
      case 4: if (star == 2) dgt = ss / 10 ; else dgt = annee / 10 ; break ;
      case 5: if (star == 2) dgt = ss % 10 ; else dgt = annee % 10 ; break ;
    }
  }

  dgt += 48 ; Nokia_PositionXY (p, star) ; 
  //if (inv == 0) Nokia_SendData(dgt) ; else Nokia_SendDataINV(dgt) ;
  Nokia_SendData(dgt) ;
}

//------------------------------------------------------------------------
void hhmmssIncrement (char i)
{
  switch(i)
  { case 0 : hh += 10 ; if (hh >= 30) hh = 0 ; else if (hh >= 24) hh -= 20 ; 
             break ;
    case 1 : hh++ ; if (hh/10 == 2) { if (hh >= 24) hh = 20 ; }
                    else 
                      if (hh/10 == 1) { if (hh > 19) hh -= 10 ; }
                      else if (hh > 9) hh = 0 ;
            break ;
    case 2 : mm += 10 ; if (mm > 59) mm -= 60 ; break ;
    case 3 : mm++ ; if ((mm) && (mm % 10 == 0)) mm -= 10 ; break ;
    case 4 : ss += 10 ; if (ss > 59) ss -= 60 ; break ;
    case 5 : ss++ ; if ((ss) && (ss % 10 == 0)) ss -= 10 ; break ;
  }    
}

//------------------------------------------------------------------------
void ddmmyyIncrement (char i)
{
  isLeapYear() ; majJmax() ;
  
  switch(i)
  { case 0 : jour += 10 ; 
             if (jour > jmax) { if (jour >= jmax+10) jour -= 40 ; else jour -= jmax ; } 
             break ;
    case 1 : if (jour/10 == 0) { if (++jour > 9) jour = 1 ; }
             if (jour/10 == 1) { if (++jour > 19) jour = 10 ; }
             if (jour/10 == 2) 
             { if (mois != 2) { if (++jour > 29) jour = 20 ; }
               else if (++jour > jmax) jour = 20 ; //case February (LEAPyear ?)
             }
             if ((jour/10 == 3) && (mois != 2)) { if (++jour > jmax) jour = 30 ; }
            break ;
    case 2 : mois += 10 ; if (mois >= 20) mois -= 20 ;
                          else if (mois > 12) mois -= 10 ; break ;     
    case 3 : mois++ ; if ((mois) && (mois % 10 == 0)) mois -= 9 ; 
                      if (mois == 13) mois -= 3 ; break ;
    case 4 : annee += 10 ; if (annee > 99) annee -= 100 ; break ;
    case 5 : annee++ ; if ((annee) && (annee % 10 == 0)) annee -= 10 ; break ;
  } 
  
  if (jour <= 0) jour = 1 ; if (mois <= 0) mois = 1 ; if (annee < 0) annee = 0 ;
  //if (mois == 2) { if (jour > jmax) jour = jmax ; } //case February (LEAPyear ?)
  isLeapYear() ; majJmax() ; //if (jour > jmax) jour = jmax ;
}

//------------------------------------------------------------------------
char ChosenOptionRTCC (char linTop, char choix)
{ //choix=2 : hhmmss  setting  ;  //choix=3 : ddmmyy  setting
#define  BP1_TIMEOUT   20  //approx.10s timeout (as PR1 modified...)
char i, dgt, star, xp[6] = {21, 26, 36, 41, 51, 56} ; 
unsigned char BP1timeout ;

  star = choix ; Nokia_PositionXY (0, star) ; LCD_PutChar('-') ;
  Nokia_PositionXY (xp[0], star) ; LCD_PutChar('*') ;

  i = 0 ; BP1timeout = 0 ;
  while (i < 6)
  { do
    { do
      { while ((BP1) && (intT1done == 0)) ; //waiting BP1push (timeout 9s)
        delay1ms(20) ; if (BP1 == 0) { TMR1 = 0 ; clicweak() ; }
        if (intT1done) 
        { intT1done = 0 ; if (++BP1timeout >= BP1_TIMEOUT) return -1 ;
        }
      }while (BP1) ;

      longPush = 1 ; BP1timeout = 0 ;
      do
      { while ((BP1 == 0) && (intT1done == 0)) ; //waiting releasing
        delay1ms(20) ;
        if (intT1done) { intT1done = 0 ; clicweak() ; } //clic() dure 8ms 
      }while ((BP1 == 0) && (longPush < 4)) ;
    
      if (longPush <= 2) 
      { longPush = 0 ; BP1timeout = 0 ;
        AffDgt(i, xp[i], star, 0) ; i++ ; if (i >= 6) break ;
        Nokia_PositionXY (xp[i], star) ; LCD_PutChar('*') ; 
        //Nokia_PositionXY (xp[i], star) ; AffDgt(i, xp[i], star, 1) ;      
      }
      else 
        { if (choix == 2) hhmmssIncrement (i) ;
          if (choix == 3) ddmmyyIncrement (i) ;
          AffDgt(i, xp[i], star, 1) ; 
        }
    
      while (intT1done == 0) ; //waiting tick 1s
      intT1done = 0 ;
    }while (longPush < 4) ;
  }//endof while (i < 6)
  
  Nokia_PositionXY (0, star) ; LCD_PutChar(' ') ;
  return (star - linTop) ;
}

//------------------------------------------------------------------------
char ChosenOption (char linTop, char choix)
{
#define  BP1_TIMEOUT   20  //approx.10s timeout (as PR1 modified...)
char star ; short s ; unsigned char BP1timeout ;

  //star = linTop ; Nokia_PositionXY (0, star) ; LCD_PutChar('*') ;
  star = choix ; Nokia_PositionXY (0, star) ; LCD_PutChar('*') ;

  BP1timeout = 0 ;
  do
  { do
    { while ((BP1) && (intT1done == 0)) ; //waiting BP1push (timeout 9s)
      delay1ms(20) ; if (BP1 == 0) { TMR1 = 0 ; clicweak() ; }
      if (intT1done) 
      { intT1done = 0 ; if (++BP1timeout >= BP1_TIMEOUT) return -1 ;
      }
    }while (BP1) ;

    //longPush = 0 ; BP1timeout = 0 ;
    longPush = 1 ; BP1timeout = 0 ;
    do
    { while ((BP1 == 0) && (intT1done == 0)) ; //waiting releasing
      delay1ms(20) ;
      if (intT1done) { intT1done = 0 ; clicweak() ; } //clic() dure 8ms 
    }while ((BP1 == 0) && (longPush < 4)) ;
    
    if (longPush <= 2) 
    { longPush = 0 ; BP1timeout = 0 ;
      Nokia_PositionXY (0, star) ; LCD_PutChar(' ') ;
      if (star < 5) star++ ; else star = linTop ;
      Nokia_PositionXY (0, star) ; LCD_PutChar('*') ;      
    }
    else { Nokia_PositionXY (0, star) ; LCD_PutChar('-') ; }
    
    while (intT1done == 0) ; //waiting tick 1s
    intT1done = 0 ;
  }while (longPush < 4) ;

  Nokia_PositionXY (0, star) ; LCD_PutChar(' ') ;
  return (star - linTop) ;
}

//-----------------------------------------------------------------------------
void mainScr (char zone)
{
//short s, seuil[4] = {200, 350, 500, 750} ; // seuils NH3 alert
short z, s, seuil[4] = {1000, 1350, 1700, 2000} ; // seuils CO2 alert
char dgt, xp ;
//unsigned int temper, humid ;

  seuil[0] = alarm1 ; seuil[1] = alarm2 ; 
  seuil[2] = alarm3 ; seuil[3] = alarm3 + 50 ;

  //Nokia_PositionXY (40, 0) ; Nokia_SendString("mainScr");
  if (zone == 0)
  { Nokia_Clear() ;
    Nokia_PositionXY (0, 2) ; LCD_DrawLine (0x08, 84) ;  //Lin2 -----
    //Nokia_PositionXY (0, 2) ; LCD_DrawLine (0x24, 84) ;  //Lin2 =====
  }

  Nokia_PositionXY (0, 0) ; 
  LCD_Write_Integer(hh, 2) ; LCD_PutChar(':') ;
  LCD_Write_Integer(mm, 2) ; LCD_PutChar(':') ;
  LCD_Write_Integer(ss, 2) ; 
  Nokia_PositionXY (0, 1) ;
  LCD_Write_Integer(jour, 2) ; LCD_PutChar('/') ;
  LCD_Write_Integer(mois, 2) ; LCD_PutChar('/') ;
  LCD_Write_Integer(annee, 2) ; 

  if ((zone == 0) || (zone == 1))
  { /*
    Nokia_PositionXY (61, 0) ;
    if (scd40temAff >= 0) { Nokia_SendData('+') ; temper = scd40temAff ; } 
    else { Nokia_SendData('-') ; temper = -scd40temAff ; }
    */
    Nokia_PositionXY (67, 0) ;
    dgt = tempHDC / 10 ; dgt += 48 ; Nokia_SendData(dgt) ; 
    dgt = tempHDC % 10 ; dgt += 48 ; Nokia_SendData(dgt) ; Nokia_SendData('C') ;
    
    ///////humid = scd40hum ;
    Nokia_PositionXY (67, 1) ;
    dgt = humHDC / 10 ; dgt += 48 ; Nokia_SendData(dgt) ; 
    dgt = humHDC % 10 ; dgt += 48 ; Nokia_SendData(dgt) ; Nokia_SendData('%') ; 
  }
       
  Nokia_PositionXY (52, 0) ; Nokia_SendData(Toff+48) ;
  
  val2txt(meas_Vbat, txt, 3) ; LCD_DrawBat() ;

  if ((zone == 0) || (zone == 2))
  {  affTVOC = 1 -  affTVOC ;
    if (affTVOC)
    { AffZoom2 (measTVOC, 3, 42) ;
    
      Nokia_PositionXY (32, 2) ; Nokia_SendString("TVOC") ;
      Nokia_PositionXY (62, 3) ; LCD_Write_Integer(ppbinterval[ippmax], 4) ;
      Nokia_PositionXY (62, 4) ; LCD_Write_Integer(ppbinterval[ippmin], 4) ;  
      Nokia_PositionXY (65, 5) ; Nokia_SendString("ppb") ;
    }
    else
      { AffZoom2 (meas_NH3, 3, 42) ;
      
        Nokia_PositionXY (32, 2) ; Nokia_SendString("eCO2") ;
        Nokia_PositionXY (62, 3) ; LCD_Write_Integer(ppminterval[ippmax], 4) ;
        Nokia_PositionXY (62, 4) ; LCD_Write_Integer(ppminterval[ippmin], 4) ;  
        Nokia_PositionXY (65, 5) ; Nokia_SendString("ppm") ;
      }
      //GLOBA: CE BLOC1 OCCUPE MOINS D'ESPACE ROM  
    xp = 33 ; //xp = 0 ;
    for (s=0; s<4; s++)  
    { if (meas_NH3 < seuil[s]) dgt = 126 ; else dgt = 127 ; 
      Nokia_PositionXY (xp, 5) ; Nokia_SendData(dgt) ;
      xp += 6 ;
    }
        
  }
}
//-----------------------------------------------------------------------------
void tablScr (void)
{
char lin, col ;
short p ;
unsigned int ppm ;

  Nokia_Clear() ;
  //Nokia_PositionXY (40, 0) ; Nokia_SendString("tablScr");
  p = 0 ;
  for (lin=0; lin<6; lin++)
    for (col=6; col<80; col+=28)
    { ppm = ppminterval[p] ;
      Nokia_PositionXY (col, lin) ; LCD_Write_Integer(ppm, 4) ;
      if (p == ippmax) { Nokia_PositionXY (col-6, lin) ; LCD_PutChar ('<') ; }
      if (p == ippmin) { Nokia_PositionXY (col-6, lin) ; LCD_PutChar ('>') ; }
      p++ ;
    }  
}
//-----------------------------------------------------------------------------
void BubbleSort (int n)
{
int f=0, i=0, j ;
unsigned int t ;

  while (i < n-1)
  { if (ppmtriee[i] > ppmtriee[i+1])
    { t = ppmtriee[i+1] ; ppmtriee[i+1] = ppmtriee[i] ; ppmtriee[i] = t ;
      if (f == 0) { j = i ; f = 1 ; }
      i-- ;
      if (i < 0) i = j ;
    }
    else
      { if (f == 1) { i = j ; f = 0 ; }
	    i++ ;
      }
  }
}
//-----------------------------------------------------------------------------
void statScr (void)
{
unsigned int p, q, ppmMoy, ppmMed, ppmMod ;
unsigned int ppmQtyMax, ndxppmQtyMax ;
int ppmDif, ppmDev ;

  Nokia_Clear() ;
  //Nokia_PositionXY (40, 0) ; Nokia_SendString("statScr");
  Nokia_PositionXY (18, 0) ; Nokia_SendString("min. = ") ;
  LCD_Write_Integer(ppminterval[ippmin], 4) ;
  
  Nokia_PositionXY (18, 1) ; Nokia_SendString("max. = ") ;
  LCD_Write_Integer(ppminterval[ippmax], 4) ;
  
  ppmMoy = 0 ; 
  for (p=0;  p<18; p++) ppmMoy += ppminterval[p] ; ppmMoy /= 18 ;
  Nokia_PositionXY (18, 2) ; Nokia_SendString("mean = ") ;
  LCD_Write_Integer(ppmMoy, 4) ;
  
  //ppmMed = 0 ; 
  for (p=0; p<18; p++) ppmtriee[p] = ppminterval[p] ; 
  BubbleSort (18) ;
  ppmMed = (ppmtriee[8] + ppmtriee[9]) / 2 ; 
  Nokia_PositionXY (8, 3) ; Nokia_SendString("median = ") ;
  LCD_Write_Integer(ppmMed, 4) ;

  //ppmMod = 0 ; 
  for (p=0; p<18; p++) ppmQty[p] = 1 ; 
  p = 0;  
  while (p<17)
  { q = p+1 ; while ((ppmtriee[p] == ppmtriee[q]) && (q < 18))
              { ppmQty[p]++ ; ppmQty[q]++ ; q++ ;
              }
    if (q == 18) break ;else p = q ;           
  }
  ppmQtyMax = 0 ; ndxppmQtyMax = 0 ;
  for (p=0; p<18; p++) 
  { if (ppmQtyMax < ppmQty[p]) { ppmQtyMax = ppmQty[p] ; ndxppmQtyMax = p ; } 
  }
  ppmMod = ppmtriee[ndxppmQtyMax] ;
  Nokia_PositionXY (18, 4) ; Nokia_SendString("mode = ") ;
  LCD_Write_Integer(ppmMod, 4) ;

  ppmDev = 0 ; 
  for (p=0; p<18; p++) { ppmDif = ppminterval[p] - ppmMoy ; ppmDev += ppmDif * ppmDif ; } 
  ppmDev /= 18 ; ppmDev = sqrt(ppmDev) ;
  Nokia_PositionXY (13, 5) ; Nokia_SendString("stDev = ") ;
  LCD_Write_Integer(ppmDev, 4) ;
}
//-----------------------------------------------------------------------------
void DispVbatLow  (void)
{
  Nokia_PositionXY (15, 2) ; Nokia_SendString("Bat < 3v3") ;
}
//-----------------------------------------------------------------------------
void DispVbatFlat  (void)
{
  Nokia_PositionXY (0, 2) ; Nokia_SendString("Bat<2v7 SYSTOP") ;
}
