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
	2015��1��8��
	����������74HC595�ļ�Ӧ��
*////////////////////////////////////////////////////////////////////////////////////////
/*//////////////////�ⲿ����//////////////////////////////////
extern void _74HC595_WriteData(uint8 dat);	//��74HC595дһ���ֽڵ����ݣ�dat�����ݣ����������ݷ�����������_74HC595_Change();����
extern void _74HC595_Change();				//��74HC595���͸������ָ��
////////////////////////////////////////////////////////////*/
#include"config.h"

void _74HC595_Change()
{
	HC595_STCP=0;
	_nop_();_nop_();_nop_();_nop_();
	HC595_STCP=1;
	_nop_();_nop_();_nop_();_nop_();
	HC595_STCP=0;
}
void _74HC595_WriteData(uint8 dat)
{
	uint8 mask;
	HC595_STCP=0;
	for(mask=0x80;mask!=0;mask>>=1)
	{
		HC595_SHCP=0;
		HC595_DAT=dat&mask;
		HC595_SHCP=1;
	}
	HC595_SHCP=0;		
}