/* 大数据 2352847 张静敏 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "../include/common_tools.h"
#include "../include/cmd_console_tools.h"
#include "90-01-b1-hanoi.h"
#include "../include/common_menu.h"
using namespace std;

/* ----------------------------------------------------------------------------------

	 本文件功能：
	1、放main函数
	2、初始化屏幕
	3、调用菜单函数（hanoi_menu.cpp中）并返回选项
	4、根据选项调用菜单各项对应的执行函数（hanoi_multiple_solutions.cpp中）

	 本文件要求：
	1、不允许定义全局变量（含外部全局和静态全局，const及#define不在限制范围内）
	2、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	3、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */

int main()
{
	/* demo中首先执行此句，将cmd窗口设置为40行x120列（缓冲区宽度120列，行数9000行，即cmd窗口右侧带有垂直滚动杆）*/
	cct_setconsoleborder(120, 40, 120, 9000);
	cct_cls();
	int n, speed, option = 1;
	char src, tmp, dst;
	option = (int)menu(0, 10) - '0';
	cout << endl << endl;
	if (option == 0) {
		cct_gotoxy(0, width - 3);
		return 0;
	}
	else {
		if (option != 5) {
			first();
			input_all(option, src, tmp, dst, n, speed);
			start(n, src);
			if (option != 1 && option != 2 && option != 3)
				cct_cls();
			if (option == 4 || option == 8) {
				cout << "从 " << src << " 移动到 " << dst << ", 共 " << n << " 层，延时设置为 " << speed << endl;
				if (option == 4)
					output_start_shu(0, n, src, dst);  //初始状态
				if (option == 8) {
					output_start_shu(diffirence, n, src, dst);  //初始状态
					output_6(n, src);
				}
			}
			if (option == 6 || option == 7 || option == 9) {
				cout << "从 " << src << " 移动到 " << dst << ", 共 " << n << " 层" << endl;
				if (option == 6)
					output_6(n, src);
				if (option == 7) {
					output_6(n, src);
					output_7(option, src, dst);
				}
				if (option == 9) {
					output_start_shu(diffirence, n, src, dst);  //初始状态
					output_6(n, src);
					game(n, src, dst);
				}
			}
			hanoi(n, src, tmp, dst, option);
		}
		if (option == 5) {
			cct_cls();
			output_5();
		}
		if (option == 1 || option == 2 || option == 3)
			cout << endl;
		else
			cct_gotoxy(0, width - 2);
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
		cout << "按回车键继续";
		while (_getch() != '\r');
		main();
	}
}

