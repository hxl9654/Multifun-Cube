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

	�ļ�����74hc573.c
	���ߣ�������
	���䣺qwgg9654@gmail.com
		  568629794@qq.com
	2015��3��28��
	����������74HC573оƬ�Ŀ���
*////////////////////////////////////////////////////////////////////////////////////////
/*//////////////////�ⲿ����//////////////////////////////////


////////////////////////////////////////////////////////////*/
#include"config.h"
/*////////////////////////////////////////////////////////////////////////////////////////

	��������HC573_Init
	�����ļ���74hc573.c
	��;����������ʼ��
	���ߣ�������
	���ڣ�2015��3��28��

*////////////////////////////////////////////////////////////////////////////////////////
void HC573_Init()
{
	OE=0;
	SDAT=0xFF;
	//LE=1;
	//LE=0;
}

