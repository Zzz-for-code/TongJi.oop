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

/*查找目标位置可连续消除的星星*/
void find_able_star(int hang, int lie, int x, int y, int star_color[][length_max + 1], int status[][length_max + 1])
{
	int color = star_color[x][y];
	int a[length_max + 2][length_max + 2] = { 0 };
	for (int i = 1; i < length_max + 1; i++)  //外扩
		for (int j = 1; j < length_max + 1; j++)
			a[i][j] = star_color[i][j];
	if (color == 0 || status[x][y] == 1) {
		return;  // 如果当前位置没有星星或已被访问过，则直接返回  
	}
	// 标记当前位置为已访问，并增加可消除星星的数量
	if (a[x - 1][y] == color || a[x + 1][y] == color || a[x][y - 1] == color || a[x][y + 1] == color)
		status[x][y] = 1;   //必须要周围有相同值才标记为1
	// 检查上下左右四个方向
	int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	for (int i = 0; i < 4; i++) {
		int nx = x + directions[i][0];
		int ny = y + directions[i][1];
		if (nx >= 0 && nx <= hang && ny >= 0 && ny <= lie && star_color[nx][ny] == color && status[nx][ny] != 1) {
			find_able_star(hang, lie, nx, ny, star_color, status);
		}
	}
}

/*分数计算*/
int score_count(int hang, int lie, int status[][length_max + 1])
{
	int score;
	int i, j, num = 0;;
	for (i = 1; i <= hang; i++) {
		for (j = 1; j <= lie; j++) {
			if (status[i][j])
				num++;
		}
	}
	score = num * num * 5;
	return score;
}

/*交换数组的两列*/
void exchange_two(int hang, int m1, int m2, int a[][length_max + 1])
{
	for (int i = 1; i <= hang; i++) {
		int t = a[i][m1];
		a[i][m1] = a[i][m2];
		a[i][m2] = t;
	}
}

/*确认一关的结束*/
int ensure_to_end(int hang, int lie, int a[][length_max + 1])
{
	int num = 0;   //用于记录
	for (int i = 1; i <= hang; i++) {
		for (int j = 1; j <= lie; j++) {
			if (a[i][j] == a[i][j - 1] && a[i][j])
				num++;
			if (a[i][j] == a[i - 1][j] && a[i][j])
				num++;
		}
	}
	return num;   //0代表可以结束
}

/*计算最后剩余的星星数量*/
int count_remain(int hang, int lie, int a[][length_max + 1])
{
	int num = 0;   //剩余星星总数
	for (int i = 1; i <= hang; i++) {
		for (int j = 1; j <= lie; j++) {
			if (a[i][j])
				num++;
		}
	}
	return num;
}

/*计算每一列左边的空列数*/
void count_blank_lie(int hang, int lie, int a[][length_max + 1], int blank_lie[])
{
	for (int i = 1; i <= lie; i++) {
		for (int j = 1; j < i; j++)
			if (a[hang][j] == 0)
				blank_lie[i] += 1;
	}
}

/*数组整体平移*/
void move_all_arr(int hang, int lie, int a[][length_max + 1])
{
	int blank_lie[length_max + 1] = { 0 };
	count_blank_lie(hang, lie, a, blank_lie);
	for (int i = 1; i <= lie; i++)
		exchange_two(hang, i, i - blank_lie[i], a);
}

/*计算奖励得分*/
void mark_final(CONSOLE_GRAPHICS_INFO* const pCGI,int final_star, int* score)
{
	int mark;
	if (final_star < 10)
		mark = (10 - final_star) * 180;
	else
		mark = 0;
	*score += mark;
	char temp[256];
	sprintf(temp, "奖励得分：%d 总得分：%d", mark, *score);
	gmw_status_line(pCGI, TOP_STATUS_LINE, temp);
}

/*键盘变换*/ //x-lie,y-hang
void keyboard_move(int* x, int* y, int keycode2, int hang, int lie, int star_color[][length_max + 1])
{
	if (keycode2 == KB_ARROW_UP) {
		do {
			if (*y != 1)
				(*y)--;
			else
				*y = hang;
		} while (star_color[*y][*x] == 0);
	}
	if (keycode2 == KB_ARROW_DOWN) {
		do {
			if (*y != hang)
				(*y)++;
			else
				*y = 1;
		} while (star_color[*y][*x] == 0);
	}
	if (keycode2 == KB_ARROW_LEFT) {
		do {
			if (*x != 1)
				(*x)--;
			else
				*x = lie;
		} while (star_color[*y][*x] == 0);
	}
	if (keycode2 == KB_ARROW_RIGHT) {
		do {
			if (*x != lie)
				(*x)++;
			else
				*x = 1;
		} while (star_color[*y][*x] == 0);
	}
}