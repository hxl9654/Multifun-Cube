/*//////////////////////////GPL��Դ���֤////////////////////////////////////////////////
    Copyright (C) <2014>  <Xianglong He>
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

	��Ȩ���У�C�� <2014>   <������>
	��һ����������������������������������������GNUͨ�ù������֤
	�������޸ĺ����·�����һ���������ʹ�����֤�ĵ����棬���ߣ�������
	��ѡ�����κθ��µİ汾��

	������һ�����Ŀ����ϣ�������ã���û���κε���������û���ʺ��ض�Ŀ��
	�������ĵ���������ϸ����������GNUͨ�ù������֤��

	��Ӧ���Ѿ��ͳ���һ���յ�һ��GNUͨ�ù������֤�ĸ����������û�У����
	��<http://www.gnu.org/licenses/>��
	���ߣ�������
	���䣺qwgg9654@gmail.com
		  568629794@qq.com
	2014��12��9��
	����������DS1302ʱ��оƬ��ʱ�����ü���ȡ
*////////////////////////////////////////////////////////////////////////////////////////
/*//////////////////�ⲿ����//////////////////////////////////
extern void DS1302_Init(uint8 *dat);  //DS1302��ʼ������������������ͷ���ã�dat�����õ�ʱ��
extern uint8 DS1302_SingleRead(uint8 addr); //DS1302���ֽڶ�ȡ��datΪ��ȡ���ݴ洢λ�ã�addrΪ�Ĵ�����ַ����������ֲ�
extern void DS1302_SingleWrite(uint8 addr,uint8 dat);   //DS1302���ֽ�д�룬datΪд�����ݣ�addrΪ�Ĵ�����ַ����������ֲ�
extern void DS1302_BrustWrite(uint8 *dat);  //DS1302Brustģʽд�룬datΪuint8�͵�ӵ��8��Ԫ�ص�����
extern void DS1302_BrustRead(uint8 *dat);   //DS1302Brustģʽ��ȡ��datΪuint8�͵�ӵ��8��Ԫ�ص�����
////////////////////////////////////////////////////////////*/
#include"config.h"

struct StructTime{
	uint8 sec;
	uint8 min;
	uint8 hour;
	uint8 day;
	uint8 month;
	uint8 week;
	uint8 year;
};

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}

void DS1302_ByteWrite(uint8 dat)
{
	uint8 mask;
	for(mask=0x01;mask!=0;mask<<=1)
		{
			if(mask&dat)DS1302_IO=1;
			else DS1302_IO=0;
			DS1302_CK=1;
			DS1302_CK=0;
		}
	DS1302_IO=1;
}

uint8 DS1302_ByteRead()
{
	uint8 mask,dat=0;
	DS1302_IO=1;
	for(mask=0x01;mask!=0;mask<<=1)
		{
			if(DS1302_IO)dat|=mask;
			DS1302_CK=1;
			DS1302_CK=0;
		}
	return dat;
}
uint8 DS1302_SingleRead(uint8 addr)		//DS1302���ֽڶ�ȡ��datΪ��ȡ���ݴ洢λ�ã�addrΪ�Ĵ�����ַ����������ֲ�
{
	uint8 dat;
	EA=0;
	DS1302_CE=1;
	DS1302_ByteWrite(0x81|(addr<<1));
	dat=DS1302_ByteRead();
	DS1302_CE=0;
	EA=1;
	return dat;
}
void DS1302_SingleWrite(uint8 addr,uint8 dat)	//DS1302���ֽ�д�룬datΪд�����ݣ�addrΪ�Ĵ�����ַ����������ֲ�
{
	EA=0;
	DS1302_CE=1;
	DS1302_ByteWrite(0x80|(addr<<1));
	DS1302_ByteWrite(dat);
	DS1302_CE=0;
	EA=1;
}
void DS1302_BrustWrite(uint8 *dat)	//DS1302Brustģʽд�룬datΪuint8�͵�ӵ��8��Ԫ�ص�����
{
	uint8 i;
	EA=0;
	DS1302_CE=1;
	DS1302_ByteWrite(0xBE);
	for(i=0;i<8;i++)
		{
			DS1302_ByteWrite(*dat);
			dat++;
		}
	DS1302_CE=0;
	EA=1;
}
void DS1302_BrustRead(uint8 *dat)	//DS1302Brustģʽ��ȡ��datΪuint8�͵�ӵ��8��Ԫ�ص�����
{
	uint8 i;
	EA=0;
	DS1302_CE=1;
	DS1302_ByteWrite(0xBF);
	for(i=0;i<8;i++)
		{
			*dat=DS1302_ByteRead();
			dat++;
			EA=1;
			Delay1ms();
			EA=0;
		}
	DS1302_IO=0;
	DS1302_CE=0;
	EA=1;
}
void DS1302_Init(uint8 *dat)	//DS1302��ʼ������������������ͷ���ã�dat�����õ�ʱ��
{
	DS1302_CE=0;
	DS1302_CK=0;
	DS1302_IO=1;
	DS1302_SingleWrite(7, 0x00);
    DS1302_BrustWrite(dat);
}
/*//////////////////ʾ������///////////////////////////////

void main()
{
	uint8 dat[8];
	uint8 dat[8]={0x00,0x15,0x91,0x09,0x12,0x02,0x14,0x00};	  //��ʼʱ��
	uint8 temp[16];
	uint8 backup=0xAA;
	LCD1602_Init();
	Timer0_Conf(1);
	DS1302_Init(dat);
	while(1)
	{
		if(Flag_200ms)
		{
			Flag_200ms=0;
			DS1302_BrustRead(dat);
			if(dat[0]==backup)continue;
			backup=dat[0];
			temp[0]='2';
			temp[1]='0';
			temp[2]=(dat[6]>>4)+'0';
			temp[3]=(dat[6]&0x0F)+'0';
			temp[4]='-';
			temp[5]=(dat[4]>>4)+'0';
			temp[6]=(dat[4]&0x0F)+'0';
			temp[7]='-';
			temp[8]=(dat[3]>>4)+'0';
			temp[9]=(dat[3]&0x0F)+'0';
			temp[10]=' ';
			temp[11]='w';
			temp[12]='e';
			temp[13]='e';
			temp[14]='k';
			temp[15]=dat[5]+'0';
			LCD1602_Show(0,0,temp,16);
			temp[0]=' ';
			temp[1]=' ';
			temp[2]=' ';
			temp[3]=' ';
			temp[4]=((dat[2]>>4)&0x07)+'0';
			temp[5]=(dat[2]&0x0F)+'0';
			temp[6]=':';
			temp[7]=(dat[1]>>4)+'0';
			temp[8]=(dat[1]&0x0F)+'0';
			temp[9]=':';
			temp[10]=((dat[0]>>4)&0x07)+'0';
			temp[11]=(dat[0]&0x0F)+'0';
			temp[12]=' ';
			temp[13]=' ';
			temp[14]=' ';
			temp[15]=' ';
			LCD1602_Show(0,1,temp,16);
		}
	}
}
void it0() interrupt 1
{
	static uint8 ms200=0;
	TH0=T0H;
	TL0=T0L;
	ms200++;
	if(ms200>=200)
		{
			ms200=0;
			Flag_200ms=1;
		}
}
/////////////////////////////////////////////////////////*/
