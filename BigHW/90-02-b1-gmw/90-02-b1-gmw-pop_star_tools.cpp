/* ������ 2352847 �ž��� */
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

/*����Ŀ��λ�ÿ���������������*/
void find_able_star(int hang, int lie, int x, int y, int star_color[][length_max + 1], int status[][length_max + 1])
{
	int color = star_color[x][y];
	int a[length_max + 2][length_max + 2] = { 0 };
	for (int i = 1; i < length_max + 1; i++)  //����
		for (int j = 1; j < length_max + 1; j++)
			a[i][j] = star_color[i][j];
	if (color == 0 || status[x][y] == 1) {
		return;  // �����ǰλ��û�����ǻ��ѱ����ʹ�����ֱ�ӷ���  
	}
	// ��ǵ�ǰλ��Ϊ�ѷ��ʣ������ӿ��������ǵ�����
	if (a[x - 1][y] == color || a[x + 1][y] == color || a[x][y - 1] == color || a[x][y + 1] == color)
		status[x][y] = 1;   //����Ҫ��Χ����ֵͬ�ű��Ϊ1
	// ������������ĸ�����
	int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	for (int i = 0; i < 4; i++) {
		int nx = x + directions[i][0];
		int ny = y + directions[i][1];
		if (nx >= 0 && nx <= hang && ny >= 0 && ny <= lie && star_color[nx][ny] == color && status[nx][ny] != 1) {
			find_able_star(hang, lie, nx, ny, star_color, status);
		}
	}
}

/*��������*/
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

/*�������������*/
void exchange_two(int hang, int m1, int m2, int a[][length_max + 1])
{
	for (int i = 1; i <= hang; i++) {
		int t = a[i][m1];
		a[i][m1] = a[i][m2];
		a[i][m2] = t;
	}
}

/*ȷ��һ�صĽ���*/
int ensure_to_end(int hang, int lie, int a[][length_max + 1])
{
	int num = 0;   //���ڼ�¼
	for (int i = 1; i <= hang; i++) {
		for (int j = 1; j <= lie; j++) {
			if (a[i][j] == a[i][j - 1] && a[i][j])
				num++;
			if (a[i][j] == a[i - 1][j] && a[i][j])
				num++;
		}
	}
	return num;   //0������Խ���
}

/*�������ʣ�����������*/
int count_remain(int hang, int lie, int a[][length_max + 1])
{
	int num = 0;   //ʣ����������
	for (int i = 1; i <= hang; i++) {
		for (int j = 1; j <= lie; j++) {
			if (a[i][j])
				num++;
		}
	}
	return num;
}

/*����ÿһ����ߵĿ�����*/
void count_blank_lie(int hang, int lie, int a[][length_max + 1], int blank_lie[])
{
	for (int i = 1; i <= lie; i++) {
		for (int j = 1; j < i; j++)
			if (a[hang][j] == 0)
				blank_lie[i] += 1;
	}
}

/*��������ƽ��*/
void move_all_arr(int hang, int lie, int a[][length_max + 1])
{
	int blank_lie[length_max + 1] = { 0 };
	count_blank_lie(hang, lie, a, blank_lie);
	for (int i = 1; i <= lie; i++)
		exchange_two(hang, i, i - blank_lie[i], a);
}

/*���㽱���÷�*/
void mark_final(CONSOLE_GRAPHICS_INFO* const pCGI,int final_star, int* score)
{
	int mark;
	if (final_star < 10)
		mark = (10 - final_star) * 180;
	else
		mark = 0;
	*score += mark;
	char temp[256];
	sprintf(temp, "�����÷֣�%d �ܵ÷֣�%d", mark, *score);
	gmw_status_line(pCGI, TOP_STATUS_LINE, temp);
}

/*���̱任*/ //x-lie,y-hang
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