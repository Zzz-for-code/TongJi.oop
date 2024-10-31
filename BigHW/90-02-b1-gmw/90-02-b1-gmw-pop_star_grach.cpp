/* 大数据 2352847 张静敏 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include "../include/cmd_gmw_tools.h"
#include "../include/common_tools.h"
#include "../include/cmd_console_tools.h"
#include "90-02-b1-gmw-pop_star.h"
using namespace std;

/*生成框架*/
void print_jia(CONSOLE_GRAPHICS_INFO* const pCGI)
{
	//设置字体
	gmw_set_font(pCGI, "新宋体");
	//色块
	gmw_set_frame_style(pCGI, 6, 3);
	gmw_set_block_border_switch(pCGI, true);
	//框架线形
	gmw_set_frame_default_linetype(pCGI, 2);   //全单线
	//游戏区域颜色
	gmw_set_frame_color(pCGI, COLOR_HWHITE, COLOR_BLACK);
	//行号、列标
	gmw_set_rowno_switch(pCGI, true);
	gmw_set_colno_switch(pCGI, true);

	gmw_draw_frame(pCGI);
	char temp[256];
	sprintf(temp, "屏幕当前设置为：%d行%d列", pCGI->lines, pCGI->cols);
	gmw_status_line(pCGI, TOP_STATUS_LINE, temp);
}

/*画出全部的星星*/
void print_all_start(CONSOLE_GRAPHICS_INFO* const pCGI, int star_color[][length_max + 1], int status[][length_max + 1])
{
	int i, j;
	for (i = 1; i <= pCGI->row_num; i++) {
		for (j = 1; j <= pCGI->col_num; j++)
			gmw_draw_block(pCGI, i - 1, j - 1, star_color[i][j], bdi_normal);
	}
}

/*画出连续相同的星星*/
void same_star_print(CONSOLE_GRAPHICS_INFO* const pCGI, int star_color[][length_max + 1], int status[][length_max + 1], int color)
{
	int i, j;
	for (i = 1; i <= pCGI->row_num; i++) {
		for (j = 1; j <= pCGI->col_num; j++)
			if (status[i][j]) {
				if(color== COLOR_WHITE)
					gmw_draw_block(pCGI, i - 1, j - 1, star_color[i][j], bdi_related);   //反显
				if(color== COLOR_BLACK)
					gmw_draw_block(pCGI, i - 1, j - 1, star_color[i][j], bdi_normal);    //取消反显
			}
	}
}

/*消除选中的星星*/
void clear_choose_star(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 1])
{
	int i, j;
	for (i = 1; i <= pCGI->row_num; i++) {
		for (j = 1; j <= pCGI->col_num; j++)
			if (status[i][j])
				gmw_draw_block(pCGI, i - 1, j - 1, 0, bdi_normal);
	}
}

/*非零值下落动画*/
void fall_zero(CONSOLE_GRAPHICS_INFO* const pCGI, int star_color[][length_max + 1], int status[][length_max + 1])
{
	int blank[length_max + 1][length_max + 1] = { 0 };
	count_blank(pCGI->row_num, pCGI->col_num, star_color, blank);
	int i, j;
	for (j = 1; j <= pCGI->col_num; j++) {
		for (i = pCGI->row_num; i >= 1; i--) {
			if (star_color[i][j] != 0)
				gmw_move_block(pCGI, i - 1, j - 1, star_color[i][j], 0, bdi_normal, UP_TO_DOWN, blank[i][j]);
		}
	}
}

/*空列左移*/
void translation_zero(CONSOLE_GRAPHICS_INFO* const pCGI, int star_color[][length_max + 1], int status[][length_max + 1])
{
	int blank_lie[length_max + 1] = { 0 };
	count_blank_lie(pCGI->row_num, pCGI->col_num, star_color, blank_lie);
	int i, j;
	for (j = 1; j <= pCGI->col_num; j++) {
		for (i = pCGI->row_num; i >= 1; i--) {
			if (star_color[i][j] != 0)
				gmw_move_block(pCGI, i - 1, j - 1, star_color[i][j], 0, bdi_normal, RIGHT_TO_LEFT, blank_lie[j]);
		}
	}
}

/*输出得分*/
void output_score(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 1], int* score)
{
	int score_this = score_count(pCGI->row_num, pCGI->col_num, status);  //计算该次得分
	*score += score_this;
	char temp[256];
	sprintf(temp, "本次得分：%d 总得分：%d", score_this, *score);
	gmw_status_line(pCGI, TOP_STATUS_LINE, temp);
}

/*结束一关的游戏*/
void over_one_game(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 1], int star_color[][length_max + 1], int* score)
{
	int m = count_remain(pCGI->row_num, pCGI->col_num, star_color);
	char temp1[256];
	char temp2[256];
	sprintf(temp1, "剩余%d个星星，无可消除项，本关结束！", m);
	sprintf(temp2, "回车进入下一关");
	gmw_status_line(pCGI, LOWER_STATUS_LINE, temp2, temp1);
	mark_final(pCGI, m, score);
	while (_getch() != '\r') {
		;
	}
	cct_cls();
	creat_start(pCGI->row_num, pCGI->col_num, star_color, 5);  //再次生成新数组
	print_jia(pCGI);
	print_all_start(pCGI, star_color, status);
}

/*游戏循环*/
void auto_game(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 1], int star_color[][length_max + 1], int score)
{
	int row = 0, col = 0;
	int x = col + 1;    //列
	int y = row + 1;    //行
	gmw_draw_block(pCGI, y - 1, x - 1, star_color[y][x], bdi_selected);   //A0处输出初始反显
	int MAction, keycode1, keycode2;
	int read = 1;
	while (1) {
		if (read)
			gmw_read_keyboard_and_mouse(pCGI, MAction, row, col, keycode1, keycode2);
		else
			read = 1;
		//读到箭头
		if (keycode1 == 0xE0) {
			gmw_draw_block(pCGI, y-1, x-1, star_color[y][x], bdi_normal);   //取消反显
			x = col + 1;    //列
			y = row + 1;    //行
			keyboard_move(&x, &y, keycode2, pCGI->row_num, pCGI->col_num, star_color);
			col = x - 1;
			row = y - 1;
			gmw_draw_block(pCGI, y - 1, x - 1, star_color[y][x], bdi_selected);   //输出反显
			char temp[256];
			sprintf(temp, "[当前键盘] %c行%d列", char(y + 'A' - 1), x - 1);
			gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
			MAction = MOUSE_NO_ACTION;
			continue;
		}

		//按键退出
		else if (keycode1 == 'q' || keycode1 == 'Q') {
			x = col + 1;    //列
			y = row + 1;    //行
			char temp[256];
			sprintf(temp, "选中了%c行%d列", char(y + 'A' - 1), x - 1);
			gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
			Sleep(200);
			break;
		}

		//单击鼠标右键
		else if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
			x = col + 1;    //列
			y = row + 1;    //行
			//位置有效，则退出
			if (x > 0 && x <= pCGI->col_num && y > 0 && y <= pCGI->row_num && star_color[y][x]) {
				char temp[256];
				sprintf(temp, "选中了%c行%d列", char(y + 'A' - 1), x - 1);
				gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
				Sleep(200);
				break;
			}
			//位置无效，则继续读取
			else {
				gmw_status_line(pCGI, LOWER_STATUS_LINE, "[当前光标] 位置非法", NULL);
				continue;
			}
		}

		//鼠标移动
		else if (MAction == MOUSE_ONLY_MOVED) {
			gmw_draw_block(pCGI, y - 1, x - 1, star_color[y][x], bdi_normal);   //取消反显
			x = col + 1;    //列
			y = row + 1;    //行
			if (star_color[y][x])
				gmw_draw_block(pCGI, y - 1, x - 1, star_color[y][x], bdi_selected);   //输出反显
			else
				gmw_status_line(pCGI, LOWER_STATUS_LINE, "[当前光标] 位置非法", NULL);
			MAction = MOUSE_NO_ACTION, keycode1 = 0;   //复原
		}

		//单击鼠标左键或者按下回车键
		else if (MAction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 0x0D) {
			x = col + 1;    //列
			y = row + 1;    //行
			//表明此时鼠标位置非法（在空白格子区域）
			if (star_color[y][x] == 0 && MAction == MOUSE_LEFT_BUTTON_CLICK) {
				gmw_status_line(pCGI, LOWER_STATUS_LINE, "[当前光标] 位置非法", NULL);
				continue;
			}
			//位置合法
			else {
				start_status(status);   //初始化
				find_able_star(pCGI->row_num, pCGI->col_num, y, x, star_color, status);   //寻找目标位置周围是否有相同值
				if (status[y][x]) {   //有相同值
					same_star_print(pCGI, star_color, status, COLOR_WHITE);  ////生成相同颜色的色块反显
					gmw_status_line(pCGI, LOWER_STATUS_LINE, "箭头键/鼠标移动取消当前选择，回车键/单击左键合成", NULL);
					//再次读键
					while (1) {
						gmw_read_keyboard_and_mouse(pCGI, MAction, row, col, keycode1, keycode2);
						if (keycode1 == 'q' || keycode1 == 'Q' || keycode1 == 0x0D || MAction == MOUSE_LEFT_BUTTON_CLICK || MAction == MOUSE_RIGHT_BUTTON_CLICK || MAction == MOUSE_ONLY_MOVED || keycode1 == 0xe0)
							break;
					}
					//确认消除
					if (keycode1 == 0x0D || MAction == MOUSE_LEFT_BUTTON_CLICK) {
						MAction = MOUSE_NO_ACTION, keycode1 = 0;   //复原
						gmw_status_line(pCGI, LOWER_STATUS_LINE, "  ", NULL);
						clear_choose_star(pCGI, status);  //消除颜色
						zero(star_color, status);  //可消除项归零
						output_score(pCGI, status, &score);
						fall_zero(pCGI, star_color, status);  //非零值下落动画
						fall_un_zero(pCGI->row_num, pCGI->col_num, star_color);   //非零值下落(数组）
						translation_zero(pCGI, star_color, status);  //空列右移
						move_all_arr(pCGI->row_num, pCGI->col_num, star_color);   //列平移(数组）
						//进入下一关
						if (!ensure_to_end(pCGI->row_num, pCGI->col_num, star_color))
							over_one_game(pCGI, status, star_color, &score);
						start_status(status);  //初始化statsu
					}
					//箭头键/鼠标移动取消当前选择，重新循环			
					else {
						gmw_status_line(pCGI, LOWER_STATUS_LINE, "  ", NULL);
						same_star_print(pCGI, star_color, status, COLOR_BLACK);  //取消相同颜色的色块反显
						read = 0;  //再次进入while无需再次读键
						continue;
					}
				}
				else {  //无相同值,重新选择
					gmw_status_line(pCGI, LOWER_STATUS_LINE, ",箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束", "周围无相同值");
					continue;
				}
			}
		}

		else
			continue;
	}

	gmw_status_line(pCGI, LOWER_STATUS_LINE, "游戏结束,按回车键退出...");
}