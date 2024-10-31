/* ������ 2352847 �ž��� */
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

/*���ѡ��*/

/*������Ϸ����*/
void draw_game_kuang(CONSOLE_GRAPHICS_INFO* const pCGI)
{
	//��������
	gmw_set_font(pCGI, "������", 72 - 4 * pCGI->row_num);
	//������ʱ
	gmw_set_delay(pCGI, DELAY_OF_DRAW_FRAME, 3);
	gmw_set_delay(pCGI, DELAY_OF_DRAW_BLOCK, 10);
	//ɫ��
	gmw_set_frame_style(pCGI, 2, 1, false);
	//��Ϸ������ɫ
	gmw_set_frame_color(pCGI, COLOR_HWHITE, COLOR_BLACK);
	//��������
	gmw_set_ext_rowcol(pCGI, 0, 0, 1);				//���ö�������

	gmw_draw_frame(pCGI);

	char temp[256];
	sprintf(temp, "���ڴ�С��%d��%d��", pCGI->lines, pCGI->cols);
	gmw_status_line(pCGI, TOP_STATUS_LINE, temp);
}

/*��ʼ��������ɫ*/
void output_ball(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2])
{
	for (int i = 1; i <= pCGI->row_num; i++) {
		for (int j = 1; j <= pCGI->col_num; j++)
			gmw_draw_block(pCGI, i - 1, j - 1, ball_color[i][j], bdi_normal);
	}
}

/*������������*/
void draw_able(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2])
{
	int i, j;
	for (i = 1; i <= pCGI->row_num; i++) {
		for (j = 1; j <= pCGI->col_num; j++) {
			if (status[i][j])
				gmw_draw_block(pCGI, i - 1, j - 1, ball_color[i][j], bdi_prompt);
		}
	}
}

/*������������*/
void clear_draw(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2])
{
	int i, j;
	for (i = 1; i <= pCGI->row_num; i++) {
		for (j = 1; j <= pCGI->col_num; j++) {
			if (status[i][j]) {
				for (int k = 0; k < 5; k++) {
					gmw_draw_block(pCGI, i - 1, j - 1, ball_color[i][j], bdi_exploded);
					Sleep(50);
					gmw_draw_block(pCGI, i - 1, j - 1, 0, bdi_exploded); //0�ǿհ�
					Sleep(50);
				}
			}
		}
	}
}

/*����������*/
void fall_move(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2])
{
	int blank[length_max + 2][length_max + 2] = { 0 };
	count_blank(pCGI->row_num, pCGI->col_num, ball_color, blank);
	int i, j;
	for (j = 1; j <= pCGI->col_num; j++) {
		for (i = pCGI->row_num; i >= 1; i--) {
			if (ball_color[i][j] != 0)
				gmw_move_block(pCGI, i - 1, j - 1, ball_color[i][j], 0, bdi_normal, UP_TO_DOWN, blank[i][j]);
		}
	}
}

/*���������ֵ*/
void fill_blank(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2])
{
	int i, j;
	for (i = 1; i <= pCGI->row_num; i++) {
		for (j = 1; j <= pCGI->col_num; j++) {
			if (ball_color[i][j] == 0) {
				ball_color[i][j] = rand() % 9 + 1;
				gmw_draw_block(pCGI, i - 1, j - 1, ball_color[i][j], bdi_normal);
			}
		}
	}
}

/*��ʾ����������ʾ*/
void output_remind(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2])
{
	remind_clear(pCGI->row_num, pCGI->col_num, ball_color, status);
	int i, j;
	for (i = 1; i <= pCGI->row_num; i++) {
		for (j = 1; j <= pCGI->col_num; j++) {
			if (status[i][j]) 
				gmw_draw_block(pCGI, i - 1, j - 1, ball_color[i][j], bdi_prompt);
		}
	}
}

/*������������ʾ����*/
void remind_to_zero(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2])
{
	int i, j;
	for (i = 1; i <= pCGI->row_num; i++) {
		for (j = 1; j <= pCGI->col_num; j++) {
			if (status[i][j] == 0)
				gmw_draw_block(pCGI, i - 1, j - 1, ball_color[i][j], bdi_normal);
		}
	}
}

/*���ڷ��������ѭ��*/
void calculate(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2], int* p_score)
{
	find_clear(pCGI->row_num, pCGI->col_num, ball_color, status);
	if (judge(status)) {
		draw_able(pCGI, ball_color, status);  //������������
		clear_draw(pCGI, ball_color, status);   //������������
		zero(ball_color, status); //�����������
		count_score(pCGI, status, p_score);   //���㱾�η���
		fall_move(pCGI, ball_color);   //����������
		fall_un_zero(pCGI->row_num, pCGI->col_num, ball_color);
		fill_blank(pCGI, ball_color, status);  //���׸������ֵ
		return calculate(pCGI, ball_color, status, p_score);
	}
	else {
		output_remind(pCGI, ball_color, status);
		return;
	}
}

/*�жϹ��λ��*/
int find_place(CONSOLE_GRAPHICS_INFO* const pCGI,int* x1, int* y1, int status[][length_max + 2])
{
	int row = -1, col = -1;
	int MAction, keycode1, keycode2;
	while (1) {
		gmw_read_keyboard_and_mouse(pCGI, MAction, row, col, keycode1, keycode2);
		*x1 = col + 1;
		*y1 = row + 1;
		if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
			char temp[256];
			sprintf(temp, "��ǰѡ��%c��%d��", char(row + 'A'), col);
			gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
			return 2;
		}
		if (MAction == MOUSE_LEFT_BUTTON_CLICK) {
			if (status[*y1][*x1] == 1)
				return 1;
			if (status[*y1][*x1] == 0) {
				char temp[256];
				sprintf(temp, "����ѡ��%c��%d��", char(row + 'A'), col);
				gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
			}
		}
	}
	return 0;
}

/*���н���*/
void move_change(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2], int score)
{
	int x1, y1, x2, y2;
	while (1) {
		if (able_to_end(pCGI, status, score))
			return;
		int m1 = 0, m2 = 0;
		while (m1 == 0) {
			m1 = find_place(pCGI , &x1, &y1, status);
			if (m1 == 2)
				return;
		}
		gmw_draw_block(pCGI, y1 - 1, x1 - 1, ball_color[y1][x1], bdi_selected);
		char temp[256];
		sprintf(temp, "��ǰѡ��%c��%d��", char(y1 - 1 + 'A'), x1);
		gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
		while (m2 == 0) {
			m2 = find_place(pCGI, &x2, &y2, status);
			if (m2 == 2)
				return;
		}
		gmw_draw_block(pCGI, y2 - 1, x2 - 1, ball_color[y2][x2], bdi_selected);
		sprintf(temp, "��ǰѡ��%c��%d��", char(y2 - 1 + 'A'), x2);
		gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
		able_to_change(pCGI, ball_color, status, x1, y1, x2, y2, &score);
	}
}

/*�ж��Ƿ���Խ���*/
void able_to_change(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2], int x1, int y1, int x2, int y2, int* p_score)
{
	if ((fabs(x1 - x2) == 1 && y1 == y2) || (fabs(y1 - y2) == 1 && x1 == x2)) {
		int t = ball_color[y1][x1];
		ball_color[y1][x1] = ball_color[y2][x2];
		ball_color[y2][x2] = t;
		find_clear(pCGI->row_num, pCGI->col_num, ball_color, status);
		if (judge(status)) {
			gmw_draw_block(pCGI, y1 - 1, x1 - 1, ball_color[y1][x1], bdi_normal);
			gmw_draw_block(pCGI, y2 - 1, x2 - 1, ball_color[y2][x2], bdi_normal);
			remind_to_zero(pCGI, ball_color, status);
			calculate(pCGI, ball_color, status, p_score);
		}
		else {
			int t = ball_color[y1][x1];
			ball_color[y1][x1] = ball_color[y2][x2];
			ball_color[y2][x2] = t;
			gmw_draw_block(pCGI, y1 - 1, x1 - 1, ball_color[y1][x1], bdi_normal);
			gmw_draw_block(pCGI, y2 - 1, x2 - 1, ball_color[y2][x2], bdi_normal);
			remind_clear(pCGI->row_num, pCGI->col_num, ball_color, status);
		}
	}
	else {
		gmw_draw_block(pCGI, y1 - 1, x1 - 1, ball_color[y1][x1], bdi_normal);
		gmw_draw_block(pCGI, y2 - 1, x2 - 1, ball_color[y2][x2], bdi_normal);
	}
}

/*������Ϸ9����*/
int able_to_end(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 2], int score)
{
	int num = 0;
	int i, j;
	for (i = 1; i <= pCGI->row_num; i++) {
		for (j = 1; j <= pCGI->col_num; j++) {
			if (status[i][j])
				num++;
		}
	}
	if (num)   //˵�����п��ƶ���
		return 0;
	else {
		char temp[256];
		sprintf(temp, "���շ�����%d", score);
		gmw_status_line(pCGI, TOP_STATUS_LINE, temp);
		return 1;
	}
}

/*��Ϸ��*/
void autogame(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2])
{
	int score = 0;
	char temp[256];
	sprintf(temp, "��ǰ����:%d", score);
	gmw_status_line(pCGI, TOP_STATUS_LINE, temp);

	calculate(pCGI, ball_color, status, &score);

	sprintf(temp, "��ǰ����:%d �Ҽ��˳�", score);
	gmw_status_line(pCGI, TOP_STATUS_LINE, temp);
	move_change(pCGI, ball_color, status, score);
	gmw_status_line(pCGI, LOWER_STATUS_LINE, "��Ϸ����,���س����˳�.");
}
