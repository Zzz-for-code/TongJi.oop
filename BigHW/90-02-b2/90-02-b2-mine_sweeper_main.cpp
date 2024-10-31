/* 大数据 2352847 张静敏 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include "../include/common_tools.h"
#include "../include/cmd_console_tools.h"
#include "../include/cmd_gmw_tools.h"
#include "90-02-b2-mine_sweeper.h"

int main()
{
	srand((unsigned int)(time(0)));  //取系统时间，为后续随机数做准备
	//初始窗口，用于输入初始参数
	while (1) {
		cct_setcolor();
		cct_setfontsize("新宋体", 16);
		cct_setconsoleborder(120, 30, 120, 200);
		cct_cls();
		//初始参数
		int level = input_game_level();
		int size_hang = 0, size_lie = 0, mine_num = 0;
		ensure_size_mine(level, &size_hang, &size_lie, &mine_num);   //根据难度确定对应的参数
		char inner_mine[MAX_ROW + 2][MAX_COL + 2] = { 0 };    //内部雷数组,扩展一圈
		creat_mine(size_hang, size_lie, mine_num, inner_mine);   //生成内部数组

		//伪图形界面
		cct_setcursor(CURSOR_INVISIBLE);
		CONSOLE_GRAPHICS_INFO MyCGI; //声明一个CGI变量
		gmw_init(&MyCGI);  //初始化
		gmw_set_rowcol(&MyCGI, size_hang, size_lie);					//游戏区域
		draw_kuang(&MyCGI, level, inner_mine);    //初始化图形界面
		auto_game(&MyCGI, mine_num, inner_mine);

		gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "请选择是重新进行下一次游戏(1)\\结束(0)", "本次游戏结束！");
		cout << endl;
		int op;
		cct_setcursor(CURSOR_VISIBLE_NORMAL);   //显示光标
		cout << "你的选择：";
		cin >> op;
		if (!op)
			break;
		cct_setcursor(CURSOR_INVISIBLE);   //光标不显示
	}
	return 0;
}