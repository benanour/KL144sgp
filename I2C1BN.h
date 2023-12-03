/*
I2C1BN.H: I2C1 header file
BENABADJI Noureddine - ORAN - May 22nd, 2023
compiler: XC32 v1.43 (2017) under MPLABX v4.15 (2018)
pic32mx170f256b used : Device ID Revision = A2
*/

#ifndef I2C1BN_HEADER_H
#define	I2C1BN_HEADER_H

//#include <stdint.h>

enum {
  I2C_RESTART = 0x1000,
  I2C_NOSTART = 0x2000,
  I2C_NOSTOP  = 0x4000,
};

//----------------------------------------------------------------------------
int i2c1_init(void);
int i2c1_start(void);
int i2c1_restart(void);
int i2c1_stop(void);
int i2c1_write1(unsigned char data);
int i2c1_read1(int ack_nack);
int i2c1_write(int i2c_adrs_7, const void *buffer, int size);
int i2c1_read(int i2c_adrs_7, void *buffer, int size);
int i2c1_trans(int i2c_adrs_7, const void *wbuf, int wsize, void *rbuf, int rsize);

#endif	// I2C1BN_HEADER_H
