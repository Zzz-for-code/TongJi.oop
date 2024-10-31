/* 大数据 2352847 张静敏 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "../include/common_tools.h"
#include "../include/cmd_console_tools.h"
#include "90-02-b1-pop_star.h"
using namespace std;

/*输入坐标*/
void add_to_input(int hang, int lie, int status[][length_max + 1], int star_color[][length_max + 1], char* x, int* y)
{
	cout << endl;
	int x0, y0;
	cct_getxy(x0, y0);
	int x1, y1;
	while (1) {
		cct_gotoxy(x0, y0);
		cout << setw(50) << " ";
		cct_gotoxy(x0, y0);
		cout << "请以字母+数字形式[例：c2]输入矩阵坐标：";
		cct_getxy(x1, y1);
		cin >> *x >> *y;
		clear();
		if (*x >= 'a' && *x <= 'z')
			*x += 'A' - 'a';
		if (*x<'A' || *x>hang + 'A' - 1 || *y < 0 || *y >= lie) {
			cout << "输入错误，请重新输入." << endl;
			cct_gotoxy(x1, y1);
			cout << setw(5) << " ";
			cct_gotoxy(x1, y1);
		}
		else {
			cout << setw(30) << " ";
			cct_gotoxy(0, y1 + 1);
			cout << "输入为" << *x << "行" << *y << "列" << endl;
			if (star_color[*x - 'A' + 1][*y + 1] == 0) {
				cout << "输入的矩阵坐标位置为0（非法位置），请重新输入" << endl;
				cct_getxy(x0, y0);
				continue;
			}
			start_status(status);
			find_able_star(hang, lie, *x - 'A' + 1, *y + 1, star_color, status);
			if (status[*x - 'A' + 1][*y + 1] == 0) {
				cout << "输入的矩阵坐标位置处无连续相同值，请重新输入" << endl;
				cct_getxy(x0, y0);
			}
			else
				break;
		}
	}
}

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

/*选择是否消除选中的相同值*/
char choose_YNQ(char x, int y)
{
	cout << endl << "请确认是否把" << x << y << "及周围的相同值消除（Y/N/Q）：";
	int x1, y1;
	cct_getxy(x1, y1);
	char ch;
	while (1) {
		cct_gotoxy(x1, y1);
		ch = _getche();
		if (ch == '\r') {
			cct_gotoxy(x1, y1);
			continue;
		}
		if (ch >= 'a' && ch <= 'z')
			ch += 'A' - 'a';
		if (ch == 'Y' || ch == 'N' || ch == 'Q')
			break;
		else {
			cct_gotoxy(x1, y1);
			cout << ' ';
			cct_gotoxy(x1, y1);
			ch = _getche();
			if (ch == '\r') {
				cct_gotoxy(x1, y1);
				continue;
			}
			if (ch >= 'a' && ch <= 'z')
				ch += 'A' - 'a';
		}
	}
	cout << endl;
	return ch;
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

/*输出坐标和反显*/
void output_add(int high,int width,int star_x, int star_y, int add_y, int star_color[][length_max + 1],int flag,char option)
{
	int add_x = 0;
	out_a_star(4 + width * (star_x - 1), 3 + (star_y - 1) * high, star_color[star_y][star_x], COLOR_WHITE);
	if (option == 'E' || option == 'G')
		add_y--;
	cct_gotoxy(add_x, add_y);
	cout << setw(65) << " ";
	cct_gotoxy(add_x, add_y);
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
	if (flag == keyboard)
		cout << "[当前键盘] " << char(star_y + 'A' - 1) << "行" << star_x - 1 << "列";
	else if (flag == mouse)
		cout << "[当前鼠标] " << char(star_y + 'A' - 1) << "行" << star_x - 1 << "列  ";
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

//备用  /*判断鼠标移动的范围是否超出单个星星范围*/
int decide_to_change(int hang, int lie, int option, int high, int width, int MX, int MY, int old_x, int old_y, int old_mark, int old_color)
{
	bool condition = MX >= 4 && MX <= (lie * width + 3) && MY >= 3 && MY < (hang * high + 3);
	bool condition_else = 0;
	int new_x = (MX - 4) / width + 1;  //从1开始
	int new_y = (MY - 3) / high + 1; //从1开始
	if (option == 'E' || option == 'G')
		condition_else = MX % width == 2 || MX % width == 3 || MY % high == 2;
	if (condition && !condition_else && old_color) {
		if (new_x == old_x && new_y == old_y)
			return 1;
		else
			return 0;
	}
	else {
		if (old_mark == 0)
			return 1;
		else
			return 0;
	}
}

/*无相同值对应的输出*/
void no_same(int& MX, int& MY, int& MAction, int& keycode1, int& keycode2,int word_y,int star_x,int star_y,int star_color)
{
	cct_gotoxy(0, word_y);
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
	cout << setw(55) << " ";
	cct_gotoxy(0, word_y);
	cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
	cout << "周围无相同值";
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
	cout << ",箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束";
	if (MAction == MOUSE_LEFT_BUTTON_CLICK)
		cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);					
	cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);

	while (1) {
		if (MAction == MOUSE_ONLY_MOVED || keycode1 == 0xe0) {
			cct_gotoxy(0, word_y);
			cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
			cout << setw(60) << " ";
			out_a_star(star_x, star_y, star_color, COLOR_BLACK);//取消反显
			break;
		}
		else if (MAction == MOUSE_RIGHT_BUTTON_CLICK || keycode1 == 'Q' || keycode1 == 'q') {
			cct_gotoxy(0, word_y);
			cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
			cout << setw(60) << " ";
			break;
		}
		else
			cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
	}
}

/*计算奖励得分*/
void mark_final(int final_star, int* score)
{
	int mark;
	if (final_star < 10)
		mark = (10 - final_star) * 180;
	else
		mark = 0;
	*score += mark;
	cct_gotoxy(0, 0);
	cout << "奖励得分：" << mark << "  总得分：" << *score << "    " << endl;
}