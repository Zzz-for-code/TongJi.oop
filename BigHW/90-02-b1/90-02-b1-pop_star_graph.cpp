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

//{"┏","━","┓","┃","┗","━","┛"}{"┳","┣","╋","┫","┻"}
/*生成框架*/
void print_jia(int hang, int lie, char option,char kuang[][4])
{
	cct_cls();
	cct_setcursor(CURSOR_INVISIBLE);
	int cmd_hang, cmd_lie, cmd_size = 16;
	if (option == 'D' || option == 'F') {
		cmd_hang = hang*3 + 8;
		cmd_lie = lie * 6 + 7;
	}
	else {
		cmd_hang = hang * 4 + 7;
		cmd_lie = lie * 8 + 5;
	}
	cct_setconsoleborder(cmd_lie, cmd_hang, cmd_lie, cmd_hang);
	cct_setfontsize("新宋体", cmd_size);
	cout << "屏幕当前设置为：" << cmd_hang << "行" << cmd_lie << "列" << endl;
	int i;
	cout << setw(6) << " ";
	if (option == 'D' || option == 'F') {
		for (i = 0; i < lie; i++)
			cout << i <<  setw(5) << " ";
		cout << endl << "  ";
	}
	else {
		for (i = 0; i < lie; i++)
			cout << i << setw(7) << " ";
		cout << " ";
	}
	print_line(3, 3 * lie, kuang[0], kuang[1], kuang[2], kuang[3]);
	for (i = 0; i < hang; i++) {
		cout << "  ";
		print_line(3, 3 * lie, kuang[4], kuang[5], kuang[6], kuang[4]);
		cout << char(i + 'A') << " ";
		print_line(3, 3 * lie, kuang[4], kuang[5], kuang[6], kuang[4]);
		cout << "  ";
		print_line(3, 3 * lie, kuang[4], kuang[5], kuang[6], kuang[4]);
		if ((option == 'E' || option == 'G') && i < hang - 1) {
			cout << "  ";
			print_line(3, 3 * lie, "┣ ", "━ ", "╋ ", "┫ ");
		}
	}
	cout << "  ";
	print_line(3, 3 * lie, kuang[7], kuang[8], kuang[9], kuang[10]);
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
}

/*输出一个星星的图案*/
void out_a_star(int start_x, int start_y, int bg_color, int fg_color)
{
	if (bg_color != 0) {
		cct_gotoxy(start_x, start_y);
		cct_setcolor(bg_color, fg_color);
		cout << "╔ ═ ╗ ";
		cct_gotoxy(start_x, start_y + 1);
		cout << "║ ★║ ";
		cct_gotoxy(start_x, start_y + 2);
		cout << "╚ ═ ╝ ";
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/*画出全部的星星*/
void print_all_start(int hang, int lie, int star_color[][length_max + 1], char option, int status[][length_max + 1])
{
	int i, j;
	int high, width;
	if (option == 'D' || option == 'F') {
		high = 3;
		width = 6;
	}
	else{
		high = 4;
		width = 8;
	}
	for (i = 1; i <= hang; i++) {
		for (j = 1; j <= lie; j++)
			out_a_star(4 + width * (j-1), 3 + (i - 1) * high, star_color[i][j], COLOR_BLACK);
	}
	cct_gotoxy(0, 3 + hang * high);
}

/*画出连续相同的星星*/
void same_star_print(int hang, int lie, int star_color[][length_max + 1], int option, int status[][length_max + 1],int color)
{
	int i, j;
	int high, width;
	if (option == 'F') {
		high = 3;
		width = 6;
	}
	else {
		high = 4;
		width = 8;
	}
	for (i = 1; i <= hang; i++) {
		for (j = 1; j <= lie; j++)
			if (status[i][j])
				out_a_star(4 + width * (j - 1), 3 + (i - 1) * high, star_color[i][j], color);
	}
}

/*消除选中的星星*/
void clear_choose_star(int hang, int lie, int option, int status[][length_max + 1])
{
	int i, j;
	int high, width;
	if (option == 'F') {
		high = 3;
		width = 6;
	}
	else {
		high = 4;
		width = 8;
	}
	for (i = 1; i <= hang; i++) {
		for (j = 1; j <= lie; j++)
			if (status[i][j]) {
				int blank_x = 4 + width * (j - 1), blank_y = 3 + (i - 1) * high;
				cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
				cct_gotoxy(blank_x, blank_y);
				cout << setw(6) << " ";
				cct_gotoxy(blank_x, blank_y + 1);
				cout << setw(6) << " ";
				cct_gotoxy(blank_x, blank_y + 2);
				cout << setw(6) << " ";
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			}
	}
}

/*单个星星的移动——一格*/
void one_star_move(int choose,int star_x,int star_y,int hang, int lie, int star_color, int option)
{
	int i;
	int high, width;
	if (option == 'F') {
		high = 3;
		width = 6;
	}
	else {
		high = 4;
		width = 8;
	}
	if (choose == right_left) {
		for (i = 0; i < width/2; i++) {
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cct_gotoxy(star_x + 4 - 2 * i, star_y);
			cout << "  ";
			cct_gotoxy(star_x + 4 - 2 * i, star_y + 1);
			cout << "  ";
			cct_gotoxy(star_x + 4 - 2 * i, star_y + 2);
			cout << "  ";
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			out_a_star(star_x - 2 * i - 2, star_y, star_color, COLOR_BLACK);
		}
		if (option == 'G') {
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cct_gotoxy(star_x - 2, star_y);
			cout << "┃ ";
			cct_gotoxy(star_x - 2, star_y + 1);
			cout << "┃ ";
			cct_gotoxy(star_x - 2, star_y + 2);
			cout << "┃ ";
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		}
	}
	if (choose == up_down) {
		for (i = 0; i < high; i++) {
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cct_gotoxy(star_x, star_y + i);
			cout << setw(6) << " ";
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
			out_a_star(star_x, star_y + i + 1, star_color, COLOR_BLACK);
		}
		if (option == 'G') {
			cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			cct_gotoxy(star_x, star_y + 3);
			cout << "━ ━ ━ ";
			cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		}
	}
	Sleep(50);
}

/*非零值下落动画*/
void fall_zero(int hang, int lie, int star_color[][length_max + 1], int status[][length_max + 1], int option)
{
	int blank[length_max + 1][length_max + 1] = { 0 };
	count_blank(hang, lie, star_color, blank);
	cct_setcursor(CURSOR_INVISIBLE);
	int i, j, m;
	int high, width;
	if (option == 'F') {
		high = 3;
		width = 6;
	}
	else {
		high = 4;
		width = 8;
	}
	for (j = 1; j <= lie; j++) {
		for (i = hang; i >= 1; i--) {
			if (star_color[i][j] != 0) {
				for (m = 0; m < blank[i][j]; m++) {
					one_star_move(up_down, 4 + width * (j - 1), 3 + (i - 1) * high + m * high, hang, lie, star_color[i][j], option);
				}
			}
		}
	}
}

/*空列右移*/
void translation_zero(int hang, int lie, int star_color[][length_max + 1], int status[][length_max + 1], int option)
{
	int blank_lie[length_max + 1] = { 0 };
	count_blank_lie(hang, lie, star_color, blank_lie);
	int i, j, m;
	int high, width;
	if (option == 'F') {
		high = 3;
		width = 6;
	}
	else {
		high = 4;
		width = 8;
	}
	for (j = 1; j <= lie; j++) {
		for (i = hang; i >= 1; i--) {
			if (star_color[i][j] != 0) {
				for (m = 0; m < blank_lie[j]; m++) {
					one_star_move(right_left, 4 + width * (j - 1) - m * width, 3 + (i - 1) * high, hang, lie, star_color[i][j], option);
				}
			}
		}
	}
}

/*输出得分*/
void output_score(int hang, int lie, int status[][length_max + 1],int* score)
{
	int score_this = score_count(hang, lie, status);  //计算该次得分
	*score += score_this;
	cct_gotoxy(0, 0);
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
	cout << setw(40) << " ";
	cct_gotoxy(0, 0);
	cout << "本次得分：" << score_this << " 总得分：" << *score << endl;
}