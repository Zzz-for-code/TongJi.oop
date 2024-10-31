/* 大数据 2352847 张静敏 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "../include/common_tools.h"
#include "../include/cmd_console_tools.h"
#include "90-01-b2-magic_ball.h"
using namespace std;

/*选项3的输出*/
void output_3(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2])
{
	cout << endl ;
	remind_clear(hang, lie, ball_color, status);
	print_start(hang, lie, 0, ball_color, status,"可选择的消除项提示（用不同色块标识）：");
}

/*循环填充0，下落过程*/
void cycle_1(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2], int option, int num)
{
	find_clear(hang, lie, ball_color, status);
	if (judge(status))
		print_start(hang, lie, 0, ball_color, status, "初始可消除项(不同色标识):");
	else {
		if (num)
			cout << endl;
		cout << "初始已无可消除项";
		if (option == 2 && num == 0)
			cout << "，本小题无法测试，请再次运行";
		return;
	}
	if (option == 2 || option == 3) {
		cout << endl << "按回车键进行数组下落除0操作..." << endl;
		while (_getch() != '\r');
		zero(ball_color, status);
		fall_un_zero(hang, lie, ball_color);
		find_again(hang, lie, ball_color, status);   //对色块位置重新记录
		print_start(hang, lie, 0, ball_color, status, "下落除0后的数组(不同色标识):");

		cout << endl << "按回车键进行新值填充..." << endl;
		while (_getch() != '\r');
		fill_zero(hang, lie, ball_color);
		print_start(hang, lie, 0, ball_color, status, "新值填充后的数组(不同色标识):");
		return cycle_1(hang, lie, ball_color, status, 2, 1);
	}
}
