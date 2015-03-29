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
	���������������ַ���ͨ��
*////////////////////////////////////////////////////////////////////////////////////////
/*//////////////////�ⲿ����//////////////////////////////////
extern void UART_RxMonitor(uint8 ms)//UART�ַ������ս����жϡ��ڶ�ʱ���е��ã�ms����ʱ��ʱ�����ڣ�
extern void UART_Driver()//UARTͨ�ż�غ���������ѭ���е��á�������յ��ַ��������Զ��������б�д��UART_Action(uint8 *dat,uint8 len)
extern void UART_SendString(uint8 *dat,uint8 len)  //����ͨ�ţ�����һ���ַ�����dat��Ҫ���͵��ַ�����len���ַ������ȣ�
extern void UART_Conf(uint16 baud) //UART���ú�����buad�������õĲ����ʣ�
////////////////////////////////////////////////////////////*/
#include"config.h"

#define BUFFMAX 64

extern void UART_Action(uint8 *dat,uint8 len);  //�˺��������б�д��������
uint8 pdata UART_Buff[BUFFMAX];
uint8 UART_BuffIndex=0;
bit UART_SendFlag,UART_ResiveFlag,UART_ResiveStringEndFlag,UART_ResiveStringFlag;
void UART_Conf(uint16 baud) //UART���ú�����buad�������õĲ����ʣ�
{
	TL1=TH1=256-11059200/12/32/baud;
	EA=1;
	ES=1;
	TMOD&=0X0F;
	TMOD|=0X20;
	SCON=0X50;
	TR1=1;
}
void UART_SendString(uint8 *dat,uint8 len)  //����ͨ�ţ�����һ���ַ�����dat��Ҫ���͵��ַ�����len���ַ������ȣ�
{
	while(len)
	{
		len--;
		SBUF=*dat;
		dat++;
		while(!UART_SendFlag);
		UART_SendFlag=0;
	}
}
uint8 UART_Read(uint8 *to,uint8 len)    //UART��ȡ��������SBUF��ȡ�������ݴ�����
{
	uint8 i;
	if(UART_BuffIndex<len)len=UART_BuffIndex;
	for(i=0;i<len;i++)
		{
			*to=UART_Buff[i];
			to++;
		}
	UART_BuffIndex=0;
	return len;
}
void UART_Driver()//UARTͨ�ż�غ���������ѭ���е��á�������յ��ַ��������Զ��������б�д��UART_Action(uint8 *dat,uint8 len)
{
	uint8 pdata dat[64];
	uint8 len;
	if(UART_ResiveStringEndFlag)
		{
			UART_ResiveStringEndFlag=0;
			len=UART_Read(dat,64);
			UART_Action(dat,len);
		}
}
void UART_RxMonitor(uint8 ms)//UART�ַ������ս����жϡ��ڶ�ʱ���е��ã�ms����ʱ��ʱ�����ڣ�
{
	static uint8 ms30=0,UART_BuffIndex_Backup;
	ms30+=ms;
	if(!UART_ResiveStringFlag)return ;
	if(UART_BuffIndex_Backup!=UART_BuffIndex)
	{
		UART_BuffIndex_Backup=UART_BuffIndex;
		ms30=0;
	}
	if(ms30>30)
		{
			ms30=0;
			UART_ResiveStringEndFlag=1;
			UART_ResiveStringFlag=0;
		}

}
void interrupt_UART() interrupt 4   //�����жϺ���
{
	if(TI)
	{
		TI=0;
		UART_SendFlag=1;
	}
	if(RI)
	{
		RI=0;
		UART_ResiveFlag=1;
		UART_Buff[UART_BuffIndex]=SBUF;
		UART_ResiveStringFlag=1;
		UART_BuffIndex++;
	}
}
