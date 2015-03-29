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
	����������������ɨ��ʹ���
*////////////////////////////////////////////////////////////////////////////////////////
/*//////////////////�ⲿ����//////////////////////////////////
extern void KeyScan(uint8 ms);	//�ڶ�ʱ���ж��е��ã���ȡ������Ϣ��ms����ʱ����ʱʱ������
extern void KeyDriver();	//����ѭ���е��ã�������������
////////////////////////////////////////////////////////////*/

#include<reg51.h>
#define KEYTIMELIMIT 1000	//���°���������ʱ�佫�ᴥ������ģʽ����0��ʾ�رգ���λ��ms
#define KEYTIMEINC 200		//����ģʽ�У�ÿ��ʱ�䴥��һ�ΰ�����Ӧ����λ��ms

typedef unsigned char uint8;
typedef unsigned int uint16;

extern void KeyAction(uint8 keyc,uint8 statu);	//�˺�����Ҫ���ⲿ���壬���������������Զ����ã�keyc�������룬statu������״̬��0-�������£�1-��������2-����������

sbit KEYOUT1=P2^3; //����ʵ���������
sbit KEYOUT2=P2^2;
sbit KEYOUT3=P2^1;
sbit KEYOUT4=P2^0;
sbit KEYIN1=P2^4;
sbit KEYIN2=P2^5;
sbit KEYIN3=P2^6;
sbit KEYIN4=P2^7;

uint16 xdata keylimit[4][4]={
	{KEYTIMELIMIT,KEYTIMELIMIT,KEYTIMELIMIT,KEYTIMELIMIT},
	{KEYTIMELIMIT,KEYTIMELIMIT,KEYTIMELIMIT,KEYTIMELIMIT},
	{KEYTIMELIMIT,KEYTIMELIMIT,KEYTIMELIMIT,KEYTIMELIMIT},
	{KEYTIMELIMIT,KEYTIMELIMIT,KEYTIMELIMIT,KEYTIMELIMIT}
	};
uint16 xdata keytime[4][4]={
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
	};
uint8 xdata KeySatu[4][4]={
	{0xff,0xff,0xff,0xff},
	{0xff,0xff,0xff,0xff},
	{0xff,0xff,0xff,0xff},
	{0xff,0xff,0xff,0xff}
	};
uint8 xdata KeySatuBackup[4][4]={
	{0x01,0x01,0x01,0x01},
	{0x01,0x01,0x01,0x01},
	{0x01,0x01,0x01,0x01},
	{0x01,0x01,0x01,0x01}
	};
uint8 KeyScanArray[4][4]={
	{0xff,0xff,0xff,0xff},
	{0xff,0xff,0xff,0xff},
	{0xff,0xff,0xff,0xff},
	{0xff,0xff,0xff,0xff}
	};
uint8 code KeyCodeMap[4][4]={ //���󰴼���ŵ���׼���̼����ӳ���
	{ 0x31, 0x32, 0x33, 0x26 }, //���ּ�1�����ּ�2�����ּ�3�����ϼ�
    { 0x34, 0x35, 0x36, 0x25 }, //���ּ�4�����ּ�5�����ּ�6�������
    { 0x37, 0x38, 0x39, 0x28 },  //���ּ�7�����ּ�8�����ּ�9�����¼�
    { 0x30, 0x1B, 0x0D, 0x27 } //���ּ�0��ESC����  �س����� ���Ҽ�
	};
void KeyDriver()
{
	uint8 i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			{
				if(KeySatu[i][j]!=0xff)
					if(KeySatu[i][j]==0x00)
						{
							KeySatu[i][j]=0xff;
							KeyAction(KeyCodeMap[i][j],0);
						}
					else if(KeySatu[i][j]==0x01)
						{
							KeySatu[i][j]=0xff;
							KeyAction(KeyCodeMap[i][j],1);
						}
			}
	if(KEYTIMELIMIT!=0)
		for(i=0;i<4;i++)
			for(j=0;j<4;j++)
				{
					if(keytime[i][j]>=KEYTIMELIMIT)
						if(keytime[i][j]>=keylimit[i][j])
							{
								keylimit[i][j]+=KEYTIMEINC;
								KeyAction(KeyCodeMap[i][j],2);
							}
						else ;
					else keylimit[i][j]=KEYTIMELIMIT;
				}
}

void KeyScan(uint8 ms)
{
	static uint8 i=0;
	uint8 j=0;
	KeyScanArray[i][0]=(KeyScanArray[i][0]<<1)|KEYIN1;
	KeyScanArray[i][1]=(KeyScanArray[i][1]<<1)|KEYIN2;
	KeyScanArray[i][2]=(KeyScanArray[i][2]<<1)|KEYIN3;
	KeyScanArray[i][3]=(KeyScanArray[i][3]<<1)|KEYIN4;

	for(j=0;j<4;j++)
	{
		if((KeyScanArray[i][j]&0x0f)==0x0f)
			{
				if(KeySatuBackup[i][j]==0x00)
				{
					KeySatu[i][j]=0x01;
					keytime[i][j]=0;
				}
				KeySatuBackup[i][j]=0x01;
			}
		else if((KeyScanArray[i][j]&0x0f)==0x00)
			{
				if(KeySatuBackup[i][j]==0x01)
				{
					KeySatu[i][j]=0x00;
					keytime[i][j]=0;
				}
				else keytime[i][j]+=4*ms;
				KeySatuBackup[i][j]=0x00;
			}
	}
	i++;
	if(i>=4)i=0;
	switch(i)
	{
		case 0:KEYOUT4=1;KEYOUT1=0;break;
		case 1:KEYOUT1=1;KEYOUT2=0;break;
		case 2:KEYOUT2=1;KEYOUT3=0;break;
		case 3:KEYOUT3=1;KEYOUT4=0;break;
	}
}
