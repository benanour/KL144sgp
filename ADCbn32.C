/*
ADCbn32.C: using ADC
BENABADJI Noureddine - ORAN - May 25th, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/
/*src: p.129/271
d:\...\PIC32\EmbeddedComputingWithPIC32.pdf
*/

#include <c:\Program Files\Microchip\xc32\v1.43\pic32mx\include\xc.h>
#include "ADCbn32.h"

//-----------------------------------------------------------------------------
/*
p11/40: Sect. 17 10-Bit AD Converter PIC24F 39705a.PDF

The SSRC, ASAM, BUFS SMPI, BUFM and ALTS bits, as well as the AD1CON3
and AD1CSSL registers, should not be written to while ADON = 1. Indeterminate
conversion data may result.
*/
//-----------------------------------------------------------------------------
//ATTENTION: AN0, AN1 selected by ANSELA see p.60/320 datasheet
		  // AN2 to AN5 selected by ANSELB see p.61/320
void ADCInit1() //avec 1 seule mesure (voir AD1CON2)!
{
  //ATTENTION: AD1PCFG n'existe pas. Utiliser ANSELA et ANSELB
  //AD1PCFG = 0xFFFF ; //use I/O, not AN
  
  _TRISA1 = 1 ; //RA1/AN1 cfg as input, to meas_Vbat
  ANSELAbits.ANSA1 = 1 ; // AN0, AN1 selected by ANSELA see p.61/320 datasheet
		//ATTENTION:   // AN2 to AN5 selected by ANSELB see p.62/320

  _TRISB3 = 1 ; //RB3/AN5 cfg as input, to meas_NH3
  ANSELBbits.ANSB3 = 1 ; // AN0, AN1 selected by ANSELA see p.61/320 datasheet
		//ATTENTION:   // AN2 to AN5 selected by ANSELB see p.62/320
							
  AD1CON1bits.ADON = 0 ; // Turn off the A/D converter

  //AD1CON1 = 0x00E4 ; //<15>ADON=0: turn off ; <9,8>FORM=00: integer value 
                     //<7-5>SSRC=111: auto-convert ; 
                     //<2>ASAM=1: auto sample

  AD1CON1 = 0x00E0 ; //<15>ADON=0: turn off ; <9,8>FORM=00: integer value 
                     //<7-5>SSRC=111: auto-convert ; 
                     //<2>ASAM=0: Sampling begins when SAMP bit is set

  //AD1CON2 = 0x6000 ; //<15-13>VCFG=011: Vref+, Vref- ; <0>ALTS=0: MUXA only
                       //<5-2>SMPI=0000: Int. at each conversion sample
  AD1CON2 = 0x0000 ; //<15-13>VCFG=000: AVDD, AVSS ; <0>ALTS=0: MUXA only
                     //<5-2>SMPI=0000: Int. at each conversion sample

//if 8 MHz
  //AD1CON3 = 0x1F05 ; //<12-8>SAMC=11111: auto-sample 31 Tad 
                      //<15>ADRC=0: AD from syst.clk ; <7-0>ADCS=0x05: Tad = 6*Tcy
//if 32 MHz-----------------
  //OK
  //AD1CON3 = 0x1F04 ; //<12-8>SAMC=11111: auto-sample 31 Tad 
                      //<15>ADRC=0: AD from syst.clk ; <7-0>ADCS=0x04: Tad = 5*Tcy
  //OK
  
//1//-------- OK sur MX230 --------
  AD1CON3 = 0x1F05 ; //<12-8>SAMC=11111: auto-sample 31 Tad 
                      //<15>ADRC=0: AD from syst.clk ; <7-0>ADCS=0x05: Tad = 6*Tcy
//2//
  AD1CON3bits.ADRC = 1 ; // A/D internal RC clock <--- DOUTEUX ---

/*----- selon Lucio, p.281/554 -----
AD1CON3 = 0x1F3F ; // Tsamp = 32*Tad; is the maximum self-timed sampling phase.
Notice also that: bit<15> ADRC=0
CE QUI SUIT A ETE TESTE: C'EST PLUS STABLE AVEC //1// ET //2// CI-DESSUS

  AD1CON3 = 0x1F3F ; //<12-8>SAMC=11111: auto-sample 31 Tad 
                      //<15>ADRC=0: AD from syst.clk ; <7-0>ADCS=0x3F: Tad = 32*Tcy
  AD1CON3bits.ADRC = 0 ; // A/D Clock derived from Peripheral Bus Clock (PBCLK)
*/  
  //NOT OK
  //AD1CON3 = 0x1F06 ; //<12-8>SAMC=11111: auto-sample 31 Tad 
                      //<15>ADRC=0: AD from syst.clk ; <7-0>ADCS=0x06: Tad = 7*Tcy
  //NOT OK
  //AD1CON3 = 0x0D13 ; //<12-8>SAMC=01101: auto-sample 13 Tad 
                      //<15>ADRC=0: AD from syst.clk ; <7-0>ADCS=0x13: Tad = 20*Tcy
//--------------------------

  AD1CSSL = 0 ;	 // no scanning required, selon Lucio, p.284/554
  
  ///ICI///AD1CON1bits.ADON = 1 ; // Turn on the A/D converter
}

//-----------------------------------------------------------------------------
//meas_Vbat = ADC_1meas(1, 0xFFFD) ; //1 meas. ; mask to put PCFG1 = 0 
//unsigned int ADC_1meas(unsigned int anIO, unsigned int maskIO)

//meas_Vbat = readADC_1meas(1) ; //read AN1
unsigned int readADC_1meas(unsigned int anIO)
{
unsigned int adc1buffer ;

  ADCInit1() ; // INUTILE SI SLEEP NON UTILISé
  //AD1CON1bits.ADON = 1 ; // Turn on the A/D converter

  //AD1CHS = anIO ;
  AD1CHSbits.CH0SA = anIO ; // connect pin of anIO to MUXA for sampling
  
  //AD1PCFGbits.PCFG4 = 0 ; //Disable digital input RB2/AN4
  //AD1PCFG = AD1PCFG & 0xFFEF ; //put PCFG4 = 0 to enable analog AN4 (RB2)

  //AD1PCFG = AD1PCFG & maskIO ; //put PCFG4 = 0 to enable analog AN4 (RB2)
/*
  AD1PCFG = maskIO ; //put PCFG4 = 0 to enable analog AN4 (RB2): meas_Temp2
                   //or put PCFG1 = 0 to enable analog AN1 (RA1): meas_Vbat
                   //or put PCFG5 = 0 to enable analog AN5 (RB3): meas_Hum
*/                   
AD1CON1bits.ADON = 1 ; // Turn on the A/D converter

  AD1CON1bits.SAMP = 1 ; //re-activer, si auto sample bit<2>ASAM=0 
///////  //delay_us(1) ; //takes 1 clk to clear previous DONE flag
///////  delay250ns() ; //min. sampling time = 200ns when using AVss & AVdd as Vref-/+
  //delay1us(1) ;
///////  AD1CON1bits.SAMP = 0; // stop sampling and start converting
/* selon Lucio, p.282/554:
Notice how making the conversion-start, triggered automatically by the completion of the self-timed sampling phase, gives us two advantages:
- Proper timing of the sampling phase is guaranteed without requiring us to use any
timed delay loop and/or other resource.
- One command (start of the sample phase) suffices to complete the entire sampling
and conversion sequence.
*/  
  
  while (!AD1CON1bits.DONE) ;  // wait for the conversion process to finish

  adc1buffer = ADC1BUF0 ;//ADC1BUFn do not retain their values after ADON = 0.

  AD1CON1bits.ADON = 0 ; // Turn off the A/D converter
  return adc1buffer ;
}
