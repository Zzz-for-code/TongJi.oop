/* ������ 2352847 �ž��� */
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

/*���ѡ��*/
/*���ɿ��*/
void output_kuang(int hang, int lie, char kuang[][4], int option)
{
	cct_cls();
	cct_setcursor(CURSOR_INVISIBLE);
	int cmd_hang, cmd_size;
	if (option == 4 || option == 6) {
		cmd_hang = hang + 6;
		cmd_size = 72 - 4 * hang;
	}
	else {
		cmd_hang = hang * 2 + 5;
		cmd_size = 68 - 4 * hang;
	}
	cct_setconsoleborder(40, cmd_hang, 40, cmd_hang);
	cct_setfontsize("������", cmd_size);
	cout << "��Ļ��" << cmd_hang << "��40��" << endl;
	print_line(1, lie, kuang[0], kuang[1], kuang[2], kuang[3]);
	for (int i = 1; i <= lie; i++) {
		print_line(1, lie, kuang[4], kuang[5], kuang[6], kuang[4]);
		if (option != 4 && option != 6 && i != lie) {
			print_line(1, lie, "�d ", "�T ", "�p ", "�g ");
		}
	}
	print_line(1, lie, kuang[7], kuang[8], kuang[9], kuang[10]);
}

/*��������ɫ*/
void output_ball(int hang, int lie, int ball_color[][length_max + 2], int option, int status[][length_max + 2])
{
	int i, j;
	for (i = 1; i <= hang; i++) {
		if (option == 4 || option == 6)
			cct_gotoxy(2, i + 1);
		else
			cct_gotoxy(2, 2 * i);
		for (j = 1; j <= lie; j++) {
			if (option != 4 && option != 6 && j != 1) {
				int a, b;
				cct_getxy(a, b);
				cct_gotoxy(a + 2, b);
				Sleep(10);
			}
			if (ball_color[i][j] == 9)
				cct_setcolor(5 + ball_color[i][j], COLOR_BLACK);
			else
				cct_setcolor(ball_color[i][j], COLOR_BLACK);
			if (status[i][j])
				cout << "��";
			else
				cout << "��";
		}
	}
	int x, y;
	cct_getxy(x, y);
	cct_gotoxy(0, y + 1);
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/*������������*/
void draw_able(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2])
{
	int i, j;
	for (i = 1; i <= hang; i++) {
		for (j = 1; j <= lie; j++) {
			if (status[i][j]) {
				cct_gotoxy(4 * j - 2, 2 * i);
				if (ball_color[i][j] == 9)
					cct_setcolor(5 + ball_color[i][j], COLOR_BLACK);
				else
					cct_setcolor(ball_color[i][j], COLOR_BLACK);
				cout << "��";
			}
		}
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/*������������*/
void clear_draw(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2])
{
	cct_setcursor(CURSOR_INVISIBLE);
	int i, j;
	for (i = 1; i <= hang; i++) {
		for (j = 1; j <= lie; j++) {
			if (status[i][j]) {
				if (ball_color[i][j] == 9)
					cct_setcolor(5 + ball_color[i][j], COLOR_BLACK);
				else
					cct_setcolor(ball_color[i][j], COLOR_BLACK);
				for (int m = 0; m < 5; m++) {
					cct_gotoxy(4 * j - 2, 2 * i);
					Sleep(50);
					cout << "  ";
					cct_gotoxy(4 * j - 2, 2 * i);
					cout << "��";
				}
				cct_gotoxy(4 * j - 2, 2 * i);
				cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
				cout << "  ";
			}
		}
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
}

/*����������*/
void fall_move(int hang, int lie, int ball_color[][length_max + 2])
{
	int blank[length_max + 2][length_max + 2] = { 0 };
	count_blank(hang, lie, ball_color, blank);
	cct_setcursor(CURSOR_INVISIBLE);
	int i, j, m;
	for (j = 1; j <= lie; j++) {
		for (i = hang; i >= 1; i--) {
			if (ball_color[i][j] != 0) {
				for (m = 0; m < blank[i][j]; m++) {
					cct_gotoxy(4 * j - 2, 2 * i + 2 * m);
					cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
					Sleep(50);
					cout << "  ";
					cct_gotoxy(4 * j - 2, 2 * i + 2 * m + 1);
					if (ball_color[i][j] == 9)
						cct_setcolor(5 + ball_color[i][j], COLOR_BLACK);
					else
						cct_setcolor(ball_color[i][j], COLOR_BLACK);
					Sleep(50);
					cout << "��";
					cct_gotoxy(4 * j - 2, 2 * i + 2 * m + 1);
					cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
					Sleep(50);
					cout << "�T ";
					cct_gotoxy(4 * j - 2, 2 * i + 2 * m + 2);
					if (ball_color[i][j] == 9)
						cct_setcolor(5 + ball_color[i][j], COLOR_BLACK);
					else
						cct_setcolor(ball_color[i][j], COLOR_BLACK);
					Sleep(50);
					cout << "��";
				}
			}
		}
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
}

/*���������ֵ*/
void fill_blank(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2])
{
	cct_setcursor(CURSOR_INVISIBLE);
	int i, j;
	for (i = 1; i <= hang; i++) {
		for (j = 1; j <= lie; j++) {
			if (ball_color[i][j] == 0) {
				ball_color[i][j] = rand() % 9 + 1;
				if (ball_color[i][j] == 9)
					cct_setcolor(5 + ball_color[i][j], COLOR_BLACK);
				else
					cct_setcolor(ball_color[i][j], COLOR_BLACK);
				cct_gotoxy(4 * j - 2, 2 * i);
				Sleep(100);
				cout << "��";
			}
		}
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
}

/*��ʾ����������ʾ*/
void output_remind(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2])
{
	remind_clear(hang, lie, ball_color, status);
	int i, j;
	for (i = 1; i <= hang; i++) {
		for (j = 1; j <= lie; j++) {
			if (status[i][j]) {
				cct_gotoxy(4 * j - 2, 2 * i);
				if (ball_color[i][j] == 9)
					cct_setcolor(5 + ball_color[i][j], COLOR_BLACK);
				else
					cct_setcolor(ball_color[i][j], COLOR_BLACK);
				cout << "��";
			}
		}
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/*������������ʾ����*/
void remind_to_zero(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2])
{
	cct_setcursor(CURSOR_INVISIBLE);
	int i, j;
	for (i = 1; i <= hang; i++) {
		for (j = 1; j <= lie; j++) {
			if (status[i][j] == 0) {
				if (ball_color[i][j] == 9)
					cct_setcolor(5 + ball_color[i][j], COLOR_BLACK);
				else
					cct_setcolor(ball_color[i][j], COLOR_BLACK);
				cct_gotoxy(4 * j - 2, 2 * i);
				cout << "��";
			}
		}
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
}

/*ѭ��*/
void cycle_2(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2], int option)
{
	find_clear(hang, lie, ball_color, status);
	if (judge(status)) {
		draw_able(hang, lie, ball_color, status);  //������������
		if (option == 7) {
			cct_gotoxy(0, 2 * hang + 2);
			cout << "���س������������������0����...";
			while (_getch() != '\r');
		}
		clear_draw(hang, lie, ball_color, status);   //������������
		zero(ball_color, status); //�����������
		fall_move(hang, lie, ball_color);   //����������
		if (option == 7) {
			cct_gotoxy(0, 2 * hang + 2);
			cout << setw(40) << " ";
			cct_gotoxy(0, 2 * hang + 2);
			cout << "���س���������ֵ���...";
			while (_getch() != '\r');
		}
		fall_un_zero(hang, lie, ball_color);
		fill_blank(hang, lie, ball_color, status);  //���׸������ֵ
		return cycle_2(hang, lie, ball_color, status, option);
	}
	else {
		if (option == 7) {
			cct_gotoxy(13, 0);
			cout << "(δ�ҵ���ʼ��������)";
			cct_gotoxy(0, 2 * hang + 2);
			cout << "���س�����ʾ������ʾ...";
			while (_getch() != '\r');
		}
		output_remind(hang, lie, ball_color, status);
		cct_gotoxy(0, 2 * hang + 1);
		return;
	}
}

/*���ڷ��������ѭ��*/
void calculate(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2], int* p_score)
{
	find_clear(hang, lie, ball_color, status);
	if (judge(status)) {
		draw_able(hang, lie, ball_color, status);  //������������
		clear_draw(hang, lie, ball_color, status);   //������������
		zero(ball_color, status); //�����������
		count_score(hang, lie, status, p_score);
		fall_move(hang, lie, ball_color);   //����������
		fall_un_zero(hang, lie, ball_color);
		fill_blank(hang, lie, ball_color, status);  //���׸������ֵ
		return calculate(hang, lie, ball_color, status, p_score);
	}
	else {
		output_remind(hang, lie, ball_color, status);
		cct_gotoxy(0, 2 * hang + 1);
		return;
	}
}

/*�жϹ��λ��*/
int find_place(int* x1, int* y1, int hang, int lie, int status[][length_max + 2], int option)
{
	cct_setcursor(CURSOR_INVISIBLE);
	int MX, MY, MAction, keycode1, keycode2;
	cct_enable_mouse();
	while (1) {
		cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
		int true_X = MX;
		int true_Y = MY;
		if ((true_X % 4 == 2 || true_X % 4 == 3) && true_X >= 2 && true_X <= (4 * lie - 1) && (true_Y % 2 == 0 && true_Y >= 2 && true_Y <= 2 * hang)) {
			*x1 = (true_X + 3) / 4;
			*y1 = true_Y / 2;
			cct_gotoxy(0, 2 * hang + 2);
			cout << setw(20) << " ";
			cct_gotoxy(0, 2 * hang + 2);
			cout << "[���λ��] ";
			cout << char(*y1 - 1 + 'A') << "��" << *x1 << "��";
			if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
				if (status[*y1][*x1]) {
					cct_gotoxy(0, 2 * hang + 2);
					cout << setw(20) << " ";
					cct_gotoxy(0, 2 * hang + 2);
					cout << "��ǰѡ��";
					cout << char(*y1 - 1 + 'A') << "��" << *x1 << "��";
					Sleep(300);
				}
				return 2;
			}
			if (MAction == MOUSE_LEFT_BUTTON_CLICK) {
				if (status[*y1][*x1] == 1 && option == 8)
					return 0;
				if (status[*y1][*x1] == 0) {
					cct_gotoxy(0, 2 * hang + 2);
					cout << setw(20) << " ";
					cct_gotoxy(0, 2 * hang + 2);
					cout << "����ѡ��" << char(*y1 - 1 + 'A') << "��" << *x1 << "��";
				}
				if (status[*y1][*x1] == 1 && option == 9)
					return 1;
			}
		}
		else {
			cct_gotoxy(0, 2 * hang + 2);
			cout << setw(20) << " ";
			cct_gotoxy(0, 2 * hang + 2);
			cout << "[���λ��] λ�÷Ƿ�";
		}
	}
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	return 0;
}

/*���н���*/
void move_change(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2], int score)
{
	int x1, y1, x2, y2;
	while (1) {
		if (able_to_end(hang, lie, status, score))
			return;
		int m1 = 0, m2 = 0;
		while (m1 == 0) {
			m1 = find_place(&x1, &y1, hang, lie, status, 9);
			if (m1 == 2)
				return;
		}
		if (ball_color[y1][x1] == 9)
			cct_setcolor(5 + ball_color[y1][x1], COLOR_HWHITE);
		else
			cct_setcolor(ball_color[y1][x1], COLOR_HWHITE);
		cct_gotoxy(4 * x1 - 2, 2 * y1);
		cout << "��";
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cct_gotoxy(0, 2 * hang + 2);
		cout << setw(20) << " ";
		cct_gotoxy(0, 2 * hang + 2);
		cout << "��ǰѡ��";
		cout << char(y1 - 1 + 'A') << "��" << x1 << "��";
		while (m2 == 0) {
			m2 = find_place(&x2, &y2, hang, lie, status, 9);
			if (m2 == 2)
				return;
		}
		if (ball_color[y1][x1] == 9)
			cct_setcolor(5 + ball_color[y1][x1], COLOR_BLACK);
		else
			cct_setcolor(ball_color[y1][x1], COLOR_BLACK);
		cct_gotoxy(4 * x1 - 2, 2 * y1);
		cout << "��";
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cct_gotoxy(0, 2 * hang + 2);
		cout << setw(20) << " ";
		cct_gotoxy(0, 2 * hang + 2);
		cout << "��ǰѡ��";
		cout << char(y2 - 1 + 'A') << "��" << x2 << "��";
		able_to_change(hang, lie, ball_color, status, x1, y1, x2, y2, &score);
	}
}

/*��Ϸ��*/
void autogame(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2], int option)
{
	int score = 0;
	cct_gotoxy(14, 0);
	cout << "(��ǰ������0)";
	cycle_2(hang, lie, ball_color, status, option);
	cct_gotoxy(14, 0);
	cout << "(��ǰ������" << score << " �Ҽ��˳�)";
	int x, y;
	if (option == 8)
		find_place(&x, &y, hang, lie, status, option);
	if (option == 9)
		move_change(hang, lie, ball_color, status, score);
	cct_gotoxy(0, 2 * hang + 1);
}
