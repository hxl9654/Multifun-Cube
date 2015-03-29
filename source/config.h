#ifndef _CONFIG_H_
#define _CONFIG_H_

#include"STC12C5A.h"
#include<intrins.h>

typedef unsigned char uint8;
typedef unsigned int uint16;

#define SDAT P0

sbit IIC_SCL=P1^0;
sbit IIC_SDA=P1^1;
sbit RXD2=P1^2;
sbit TXD2=P1^3;
sbit KEY4=P1^3;
sbit DS18B20_IO=P1^4;
sbit LIGHT_CON=P1^5;
sbit MIC=P1^6;
sbit LIGHT=P1^7;

sbit HC138_A=P2^0;
sbit HC138_B=P2^1;
sbit HC138_C=P2^2;
sbit HC595_SHCP=P2^3;
sbit HC595_STCP=P2^4;
sbit HC595_DAT=P2^5;
sbit OE=P2^6;

sbit RXD=P3^0;
sbit TXD=P3^1;
sbit KEY1=P3^2;
sbit KEY2=P3^3;
sbit DS1302_CK=P3^4;
sbit DS1302_IO=P3^5;
sbit DS1302_CE=P3^6;
sbit BUZZ=P3^7;

sbit KEY3=P4^6;
sbit RST=P4^7;

#endif