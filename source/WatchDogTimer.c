/*//////////////////////////GPL��Դ���֤////////////////////////////////////////////////
    Copyright (C) <2015>  <Xianglong He>
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either verHC595_DATon 3 of the License, or
    (at your option) any later verHC595_DATon.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

	��Ȩ���У�C�� <2015>   <������>
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
	2015��2��6��
	����������STC12C5A60S2��Ƭ�����Ź�����
*////////////////////////////////////////////////////////////////////////////////////////
/*//////////////////�ⲿ����//////////////////////////////////
extern void WatchDogTimer_Init(uint8 ps);    //��ʼ�����Ź�����ps�����Ź�Ԥ��Ƶֵ���ã�
extern void WatchDogTimer_Feed();     //���Ź�ι����
extern WatchDogTimer_Hold();  //�رտ��Ź���
////////////////////////////////////////////////////////////*/
#include"config.h"

/*////////////////////////////////////////////////////////////////////////////////////////

	��������WatchDogTimer_Init
	�����ļ���watchdogtimer.c
	��;����ʼ�����Ź�
	�����б�
		������		��������	��������				��ע
		ps			uint8		���Ź�Ԥ��Ƶֵ����
	���ߣ�������
	���ڣ�2015��2��6��

*////////////////////////////////////////////////////////////////////////////////////////
void WatchDogTimer_Init(uint8 ps)
{
	WDT_CONTR =0x30|ps;	//�������Ź������¼���������Ԥ��Ƶ������ģʽ������
}
/*////////////////////////////////////////////////////////////////////////////////////////

	��������WatchDogTimer_Feed
	�����ļ���watchdogtimer.c
	��;�����Ź�ι��
	���ߣ�������
	���ڣ�2015��2��6��

*////////////////////////////////////////////////////////////////////////////////////////
void WatchDogTimer_Feed()
{
	WDT_CONTR |=0x10;
}
/*////////////////////////////////////////////////////////////////////////////////////////

	��������WatchDogTimer_Hold
	�����ļ���watchdogtimer.c
	��;���رտ��Ź�
	���ߣ�������
	���ڣ�2015��2��6��

*////////////////////////////////////////////////////////////////////////////////////////
void WatchDogTimer_Hold()
{
	WDT_CONTR &=0xDF;
}