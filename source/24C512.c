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
	����������EEPROM24C512оƬ EEPROM24C512�Ķ�д
	������ļ�֧�֣�IIC.c
*////////////////////////////////////////////////////////////////////////////////////////
/*//////////////////�ⲿ����//////////////////////////////////
extern void EEPROM24C512_WriteString(uint8 addr,uint8 *dat,uint8 len,uint8 no);    //EEPROM24C512д�����������ݣ�addr����ַ��dat�����ݣ�len�����ݳ��ȣ�no�������ɱ�̵�ַ��
extern void EEPROM24C512_Write(uint8 addr,uint8 dat,uint8 no);   //EEPROM24C512д��һλ���ݣ�addr����ַ��dat�����ݣ�no�������ɱ�̵�ַ��
extern void EEPROM24C512_ReadString(uint8 addr,uint8 len,uint8 *dat,uint8 no);    //EEPROM24C512��ȡ���������ݣ�addr����ַ��dat���������ݵ����飬len��Ҫ��ȡ�ĳ��ȣ�no�������ɱ�̵�ַ��
extern uint8 EEPROM24C512_Read(uint8 addr,uint8 no);  //EEPROM24C512����һλ���ݣ�addr����ַ��no�������ɱ�̵�ַ�������أ�����������
////////////////////////////////////////////////////////////*/
#include"config.h"

extern void IIC_Start();
extern void IIC_Stop();
extern bit IIC_Write(uint8 dat);
extern uint8 IIC_Read(bit ACK);
uint8 EEPROM24C512_Read(uint8 addr,uint8 no)
{
	uint8 temp;
	IIC_Start();
	IIC_Write(0xA0|(no<<1));
	IIC_Write(addr);
	IIC_Start();
	IIC_Write(0xA0|(no<<1)|0x01);
	temp=IIC_Read(1);
	IIC_Stop();
	return temp;
}
void EEPROM24C512_ReadString(uint8 addr,uint8 len,uint8 *dat,uint8 no)
{
	IIC_Start();
	IIC_Write(0xA0|(no<<1));
	IIC_Write(addr);
	IIC_Start();
	IIC_Write(0xA0|(no<<1)|0x01);
	while(len>0)
	{
		*dat=IIC_Read(0);
		dat++;
		len--;
	}
	*dat=IIC_Read(1);
	IIC_Stop();
}
void EEPROM24C512_Write(uint8 addr,uint8 dat,uint8 no)
{
	bit temp;
	while(1)
	{
		IIC_Start();
		temp=IIC_Write(0xA0|(no<<1));
		if(temp)break;
		else IIC_Stop();
	}
	IIC_Write(addr);
	IIC_Write(dat);
	IIC_Stop();
}
void EEPROM24C512_WriteString(uint8 addr,uint8 *dat,uint8 len,uint8 no)
{
	bit temp;
	while(len>0)
	{
		while(1)
		{
			IIC_Start();
			temp=IIC_Write(0xA0|(no<<1));
			if(temp)break;
			else IIC_Stop();
		}
		IIC_Write(addr);
		while(len>0)
		{
			IIC_Write(*dat);
			len--;
			addr++;
			dat++;
			if((addr&0x07)==0)break;
		}
		IIC_Stop();
	}
}
