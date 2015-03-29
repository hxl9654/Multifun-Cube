/*//////////////////////////GPL开源许可证////////////////////////////////////////////////
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

	版权所有（C） <2015>   <何相龙>
	这一程序是自由软件，你可以遵照自由软件基金会出版的GNU通用公共许可证
	条款来修改和重新发布这一程序。你可以使用许可证的第三版，或者（根据你
	的选择）用任何更新的版本。

	发布这一程序的目的是希望它有用，但没有任何担保。甚至没有适合特定目的
	的隐含的担保。更详细的情况请参阅GNU通用公共许可证。

	你应该已经和程序一起收到一份GNU通用公共许可证的副本。如果还没有，请访
	问<http://www.gnu.org/licenses/>。

	作者：何相龙
	邮箱：qwgg9654@gmail.com
		  568629794@qq.com
	2015年2月6日
	功能描述：STC12C5A60S2单片机看门狗程序
*////////////////////////////////////////////////////////////////////////////////////////
/*//////////////////外部声明//////////////////////////////////
extern void WatchDogTimer_Init(uint8 ps);    //初始化看门狗。（ps：看门狗预分频值设置）
extern void WatchDogTimer_Feed();     //看门狗喂狗。
extern WatchDogTimer_Hold();  //关闭看门狗。
////////////////////////////////////////////////////////////*/
#include"config.h"

/*////////////////////////////////////////////////////////////////////////////////////////

	函数名：WatchDogTimer_Init
	所在文件：watchdogtimer.c
	用途：初始化看门狗
	参数列表
		变量名		变量类型	变量描述				备注
		ps			uint8		看门狗预分频值设置
	作者：何相龙
	日期：2015年2月6日

*////////////////////////////////////////////////////////////////////////////////////////
void WatchDogTimer_Init(uint8 ps)
{
	WDT_CONTR =0x30|ps;	//启动看门狗并重新计数，设置预分频，空闲模式不计数
}
/*////////////////////////////////////////////////////////////////////////////////////////

	函数名：WatchDogTimer_Feed
	所在文件：watchdogtimer.c
	用途：看门狗喂狗
	作者：何相龙
	日期：2015年2月6日

*////////////////////////////////////////////////////////////////////////////////////////
void WatchDogTimer_Feed()
{
	WDT_CONTR |=0x10;
}
/*////////////////////////////////////////////////////////////////////////////////////////

	函数名：WatchDogTimer_Hold
	所在文件：watchdogtimer.c
	用途：关闭看门狗
	作者：何相龙
	日期：2015年2月6日

*////////////////////////////////////////////////////////////////////////////////////////
void WatchDogTimer_Hold()
{
	WDT_CONTR &=0xDF;
}