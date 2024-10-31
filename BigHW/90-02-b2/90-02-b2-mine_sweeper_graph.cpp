/* 大数据 2352847 张静敏 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "../include/common_tools.h"
#include "../include/cmd_console_tools.h"
#include "../include/cmd_gmw_tools.h"
#include "90-02-b2-mine_sweeper.h"

/*画出框架*/
void draw_kuang(CONSOLE_GRAPHICS_INFO* const pCGI,int level, char inner_mine[][MAX_COL + 2])
{
	int word_size = 14;
	if (level == 1)
		word_size = 16;
	else
		word_size = 12;
	//设置字体
	gmw_set_font(pCGI, "新宋体",word_size);
	//色块
	gmw_set_frame_style(pCGI, 4, 2);
	//框架线形
	gmw_set_frame_default_linetype(pCGI, 2);   //全单线
	//游戏区域颜色
	gmw_set_frame_color(pCGI, COLOR_HWHITE, COLOR_BLACK);
	//行号、列标
	gmw_set_rowno_switch(pCGI, true);
	gmw_set_colno_switch(pCGI, true);

	gmw_draw_frame(pCGI);
	gmw_status_line(pCGI, TOP_STATUS_LINE, "空格显示时间","Q\\q退出，");
	//画出色块
	for (int i = 1; i <= pCGI->row_num; i++) {
		for (int j = 1; j <= pCGI->col_num; j++)
			gmw_draw_block(pCGI, i - 1, j - 1, BDI_VALUE_BLANK, bdi_normal);
	}
}

/*打开连续的区域*/
int open_enable(CONSOLE_GRAPHICS_INFO* const pCGI, int x, int y, char inner_mine[][MAX_COL + 2], int status[][MAX_COL + 2])
{
	status[x][y] = VISITED;
	if (inner_mine[x][y] != '*')
		gmw_draw_block(pCGI, x - 1, y - 1, inner_mine[x][y] - '0', bdi_open);
	else
		gmw_draw_block(pCGI, x - 1, y - 1, MINE, bdi_open);
	if (inner_mine[x][y] == '*')
		return 1;
	else if (inner_mine[x][y] == '0') { // 如果是0，则递归打开所有相邻区域
		for (int i = 0; i < 8; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx > 0 && nx <= pCGI->row_num && ny > 0 && ny <= pCGI->col_num && status[nx][ny] != VISITED && status[nx][ny] != FLAGED) {
				if (open_enable(pCGI, nx, ny, inner_mine, status))
					return 1;
			}
		}
	}
	return 0; // 没有遇到雷，继续游戏
}

/*游戏版本*/
void auto_game(CONSOLE_GRAPHICS_INFO* const pCGI, int mine,char inner_mine[][MAX_COL + 2])
{
	int status[MAX_ROW + 2][MAX_COL + 2] = { 0 };    //记录每个位置是否被探查或者标记
	int row = -1, col = -1;
	int MAction, keycode1, keycode2;
	//计时开始
	double dur;
	clock_t start, end;
	start = clock();
	while (1) {
		gmw_read_keyboard_and_mouse(pCGI, MAction, row, col, keycode1, keycode2);
		//按键退出
		if (keycode1 == 'q' || keycode1 == 'Q') {
			//计算时间间隔
			end = clock();
			dur = (double)(end - start);
			char temp1[256];
			sprintf(temp1, "剩余雷数：%d,", mine);
			char temp2[256];
			sprintf(temp2, "本次游戏时间：%f秒", (dur / CLOCKS_PER_SEC));
			gmw_status_line(pCGI, TOP_STATUS_LINE, temp2, temp1);
			break;
		}
		//按下空格,显示时间
		else if (keycode1 == ' ') {
			end = clock();
			dur = (double)(end - start);
			char temp[256];
			sprintf(temp, "当前时间：%f秒 ", (dur / CLOCKS_PER_SEC));
			gmw_status_line(pCGI, TOP_STATUS_LINE, "空格显示时间,Q\\q退出", temp);
		}
		//按下左键
		else if (MAction == MOUSE_LEFT_BUTTON_CLICK) {
			//被标记过
			if (status[row + 1][col + 1] == FLAGED) {
				gmw_status_line(pCGI, TOP_STATUS_LINE, "请先取消其标记", "该位置已被标记为雷！");
				continue;
			}
			//被打开过
			else if (status[row + 1][col + 1] == VISITED) {
				gmw_status_line(pCGI, LOWER_STATUS_LINE, "[位置非法]!!!");
				continue;
			}
			else {
				int ret = open_enable(pCGI, row + 1, col + 1, inner_mine, status);  //处理内部数组
				//点到雷了，游戏失败
				if (ret) {
					//计算时间间隔
					end = clock();
					dur = (double)(end - start);
					char temp[256];
					sprintf(temp, "共用时：%f秒 ", (dur / CLOCKS_PER_SEC));
					gmw_status_line(pCGI, LOWER_STATUS_LINE, "你输了，游戏失败,按回车继续...", temp);
					while (_getch() != '\r') {
						;
					}
					break;
				}
			}
		}
		//按下右键
		else if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
			//已经被标记过的,取消标记
			if (status[row + 1][col + 1] == FLAGED) {
				gmw_draw_block(pCGI, row, col, BDI_VALUE_BLANK, bdi_normal);
				status[row + 1][col + 1] = 0;
				mine++;
				char temp1[256];
				sprintf(temp1, "剩余雷数：%d,", mine);
				gmw_status_line(pCGI, TOP_STATUS_LINE, "空格显示时间,Q\\q退出，", temp1);
			}
			//未被标记和打开过的，标记
			else if (status[row + 1][col + 1] == 0) {
				//雷数达到上限不准标记
				if (mine == 0) {
					gmw_status_line(pCGI, TOP_STATUS_LINE, NULL, "标记雷数已达上限，请重新考虑！！！");
					Sleep(800);
					char temp1[256];
					sprintf(temp1, "剩余雷数：%d,", mine);
					gmw_status_line(pCGI, TOP_STATUS_LINE, "空格显示时间,Q\\q退出，", temp1);
					continue;
				}
				else {
					gmw_draw_block(pCGI, row, col, FLAG, bdi_open);
					status[row + 1][col + 1] = FLAGED;
					mine--;
					char temp1[256];
					sprintf(temp1, "剩余雷数：%d,", mine);
					gmw_status_line(pCGI, TOP_STATUS_LINE, "空格显示时间,Q\\q退出，", temp1);
				}
			}
			else
				continue;
		}
		//其他键以及鼠标移动
		else
			continue;
		//判断游戏是否结束
		if (judge_end(pCGI->row_num, pCGI->col_num, status)==0) {
			//计算时间间隔
			end = clock();
			dur = (double)(end - start);
			char temp[256];
			sprintf(temp, "恭喜您游戏成功！共用时：%f秒 ", (dur / CLOCKS_PER_SEC));
			gmw_status_line(pCGI, LOWER_STATUS_LINE, "按回车继续...", temp);
			while (_getch() != '\r') {
				;
			}
			break;
		}
	}
}