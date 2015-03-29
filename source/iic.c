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
	����������IO��ģ��IICͨ��
*////////////////////////////////////////////////////////////////////////////////////////
/*//////////////////�ⲿ����//////////////////////////////////
extern void IIC_Start();    //����IICͨ����ʼ�ź�
extern void IIC_Stop();     //����IICͨ����ֹ�ź�
extern bit IIC_Write(uint8 dat);    //IICͨ��д��һ��uint8�͵����ݣ�dat��Ҫд������ݣ����أ�1���ɹ���0��ʧ��
extern uint8 IIC_Read(bit ACK);     //IICͨ�Ŷ���һ��uint8�͵����ݣ�ACK��0����ĩλ���ݣ�1��ĩλ���ݣ������ض���������
////////////////////////////////////////////////////////////*/
#include"config.h"
#define IICDelay() {nop_();nop_();nop_();nop_();}

void IIC_Start()
{
	IIC_SCL=0;
	IICDelay();
	IIC_SDA=1;
	IICDelay();
	IIC_SCL=1;
	IICDelay();
	IIC_SDA=0;
	IICDelay();
	IIC_SCL=0;
}
void IIC_Stop()
{
	IIC_SCL=0;
	IICDelay();
	IIC_SDA=0;
	IICDelay();
	IIC_SCL=1;
	IICDelay();
	IIC_SDA=1;
}
bit IIC_Write(uint8 dat)
{
	uint8 i,mask=0x80;
	bit a;
	for(i=0;i<8;i++)
		{
			if(dat&mask)IIC_SDA=1;
			else IIC_SDA=0;
			IICDelay();
			IIC_SCL=1;
			mask>>=1;
			IIC_SCL=0;
		}
	IICDelay();
	IIC_SDA=1;
	IICDelay();
	IIC_SCL=1;
	IICDelay();
	a=IIC_SDA;
	IIC_SCL=0;
	return (~a); //����1������
}
uint8 IIC_Read(bit ACK)
{
	uint8 i,mask=0x80,dat=0;
	IIC_SCL=0;
	IIC_SDA=1;
	for(i=0;i<8;i++)
		{
			IICDelay();
			IIC_SCL=1;
			IICDelay();
			if(IIC_SDA)dat|=mask;
			mask>>=1;
			IIC_SCL=0;
		}
	IICDelay();
	IIC_SDA=ACK;
	IICDelay();
	IIC_SCL=1;
	IICDelay();
	IIC_SCL=0;
	return dat;
}
