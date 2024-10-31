/* 大数据 2352847 张静敏 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "../include/common_tools.h"
#include "../include/cmd_console_tools.h"
#include "../include/cmd_gmw_tools.h"
#include "90-01-b2-gmw-magic_ball.h"
using namespace std;

int main()
{
	srand((unsigned int)(time(0)));  //取系统时间，为后续随机数做准备
	cct_setcolor();
	cct_setfontsize("新宋体", 16);
	cct_setconsoleborder(120, 30, 120, 200);
	cct_cls();
	//输入参数
	int hang = input_hang_lie(1, 9, 5, 9, 5);
	int lie = input_hang_lie(0, 9, 5, 9, 5);
	int status[length_max + 2][length_max + 2] = { 0 };
	int ball_color[length_max + 2][length_max + 2] = { 0 };
	creat_start(hang, lie, ball_color, 9);  //先生成

	cct_setcursor(CURSOR_INVISIBLE);
	CONSOLE_GRAPHICS_INFO MyCGI; //声明一个CGI变量
	gmw_init(&MyCGI);  //初始化
	gmw_set_rowcol(&MyCGI, hang, lie);					//游戏区域
	draw_game_kuang(&MyCGI);   //画出游戏框架
	output_ball(&MyCGI, ball_color, status);  //填充球
	autogame(&MyCGI, ball_color, status);
	while (_getch() != '\r') {
		;
	}
	return 0;
}