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

/*���ɿ��*/
void print_jia(CONSOLE_GRAPHICS_INFO* const pCGI)
{
	//��������
	gmw_set_font(pCGI, "������");
	//ɫ��
	gmw_set_frame_style(pCGI, 6, 3);
	gmw_set_block_border_switch(pCGI, true);
	//�������
	gmw_set_frame_default_linetype(pCGI, 2);   //ȫ����
	//��Ϸ������ɫ
	gmw_set_frame_color(pCGI, COLOR_HWHITE, COLOR_BLACK);
	//�кš��б�
	gmw_set_rowno_switch(pCGI, true);
	gmw_set_colno_switch(pCGI, true);

	gmw_draw_frame(pCGI);
	char temp[256];
	sprintf(temp, "��Ļ��ǰ����Ϊ��%d��%d��", pCGI->lines, pCGI->cols);
	gmw_status_line(pCGI, TOP_STATUS_LINE, temp);
}

/*����ȫ��������*/
void print_all_start(CONSOLE_GRAPHICS_INFO* const pCGI, int star_color[][length_max + 1], int status[][length_max + 1])
{
	int i, j;
	for (i = 1; i <= pCGI->row_num; i++) {
		for (j = 1; j <= pCGI->col_num; j++)
			gmw_draw_block(pCGI, i - 1, j - 1, star_color[i][j], bdi_normal);
	}
}

/*����������ͬ������*/
void same_star_print(CONSOLE_GRAPHICS_INFO* const pCGI, int star_color[][length_max + 1], int status[][length_max + 1], int color)
{
	int i, j;
	for (i = 1; i <= pCGI->row_num; i++) {
		for (j = 1; j <= pCGI->col_num; j++)
			if (status[i][j]) {
				if(color== COLOR_WHITE)
					gmw_draw_block(pCGI, i - 1, j - 1, star_color[i][j], bdi_related);   //����
				if(color== COLOR_BLACK)
					gmw_draw_block(pCGI, i - 1, j - 1, star_color[i][j], bdi_normal);    //ȡ������
			}
	}
}

/*����ѡ�е�����*/
void clear_choose_star(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 1])
{
	int i, j;
	for (i = 1; i <= pCGI->row_num; i++) {
		for (j = 1; j <= pCGI->col_num; j++)
			if (status[i][j])
				gmw_draw_block(pCGI, i - 1, j - 1, 0, bdi_normal);
	}
}

/*����ֵ���䶯��*/
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

/*��������*/
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

/*����÷�*/
void output_score(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 1], int* score)
{
	int score_this = score_count(pCGI->row_num, pCGI->col_num, status);  //����ôε÷�
	*score += score_this;
	char temp[256];
	sprintf(temp, "���ε÷֣�%d �ܵ÷֣�%d", score_this, *score);
	gmw_status_line(pCGI, TOP_STATUS_LINE, temp);
}

/*����һ�ص���Ϸ*/
void over_one_game(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 1], int star_color[][length_max + 1], int* score)
{
	int m = count_remain(pCGI->row_num, pCGI->col_num, star_color);
	char temp1[256];
	char temp2[256];
	sprintf(temp1, "ʣ��%d�����ǣ��޿���������ؽ�����", m);
	sprintf(temp2, "�س�������һ��");
	gmw_status_line(pCGI, LOWER_STATUS_LINE, temp2, temp1);
	mark_final(pCGI, m, score);
	while (_getch() != '\r') {
		;
	}
	cct_cls();
	creat_start(pCGI->row_num, pCGI->col_num, star_color, 5);  //�ٴ�����������
	print_jia(pCGI);
	print_all_start(pCGI, star_color, status);
}

/*��Ϸѭ��*/
void auto_game(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 1], int star_color[][length_max + 1], int score)
{
	int row = 0, col = 0;
	int x = col + 1;    //��
	int y = row + 1;    //��
	gmw_draw_block(pCGI, y - 1, x - 1, star_color[y][x], bdi_selected);   //A0�������ʼ����
	int MAction, keycode1, keycode2;
	int read = 1;
	while (1) {
		if (read)
			gmw_read_keyboard_and_mouse(pCGI, MAction, row, col, keycode1, keycode2);
		else
			read = 1;
		//������ͷ
		if (keycode1 == 0xE0) {
			gmw_draw_block(pCGI, y-1, x-1, star_color[y][x], bdi_normal);   //ȡ������
			x = col + 1;    //��
			y = row + 1;    //��
			keyboard_move(&x, &y, keycode2, pCGI->row_num, pCGI->col_num, star_color);
			col = x - 1;
			row = y - 1;
			gmw_draw_block(pCGI, y - 1, x - 1, star_color[y][x], bdi_selected);   //�������
			char temp[256];
			sprintf(temp, "[��ǰ����] %c��%d��", char(y + 'A' - 1), x - 1);
			gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
			MAction = MOUSE_NO_ACTION;
			continue;
		}

		//�����˳�
		else if (keycode1 == 'q' || keycode1 == 'Q') {
			x = col + 1;    //��
			y = row + 1;    //��
			char temp[256];
			sprintf(temp, "ѡ����%c��%d��", char(y + 'A' - 1), x - 1);
			gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
			Sleep(200);
			break;
		}

		//��������Ҽ�
		else if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
			x = col + 1;    //��
			y = row + 1;    //��
			//λ����Ч�����˳�
			if (x > 0 && x <= pCGI->col_num && y > 0 && y <= pCGI->row_num && star_color[y][x]) {
				char temp[256];
				sprintf(temp, "ѡ����%c��%d��", char(y + 'A' - 1), x - 1);
				gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
				Sleep(200);
				break;
			}
			//λ����Ч���������ȡ
			else {
				gmw_status_line(pCGI, LOWER_STATUS_LINE, "[��ǰ���] λ�÷Ƿ�", NULL);
				continue;
			}
		}

		//����ƶ�
		else if (MAction == MOUSE_ONLY_MOVED) {
			gmw_draw_block(pCGI, y - 1, x - 1, star_color[y][x], bdi_normal);   //ȡ������
			x = col + 1;    //��
			y = row + 1;    //��
			if (star_color[y][x])
				gmw_draw_block(pCGI, y - 1, x - 1, star_color[y][x], bdi_selected);   //�������
			else
				gmw_status_line(pCGI, LOWER_STATUS_LINE, "[��ǰ���] λ�÷Ƿ�", NULL);
			MAction = MOUSE_NO_ACTION, keycode1 = 0;   //��ԭ
		}

		//�������������߰��»س���
		else if (MAction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 0x0D) {
			x = col + 1;    //��
			y = row + 1;    //��
			//������ʱ���λ�÷Ƿ����ڿհ׸�������
			if (star_color[y][x] == 0 && MAction == MOUSE_LEFT_BUTTON_CLICK) {
				gmw_status_line(pCGI, LOWER_STATUS_LINE, "[��ǰ���] λ�÷Ƿ�", NULL);
				continue;
			}
			//λ�úϷ�
			else {
				start_status(status);   //��ʼ��
				find_able_star(pCGI->row_num, pCGI->col_num, y, x, star_color, status);   //Ѱ��Ŀ��λ����Χ�Ƿ�����ֵͬ
				if (status[y][x]) {   //����ֵͬ
					same_star_print(pCGI, star_color, status, COLOR_WHITE);  ////������ͬ��ɫ��ɫ�鷴��
					gmw_status_line(pCGI, LOWER_STATUS_LINE, "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�", NULL);
					//�ٴζ���
					while (1) {
						gmw_read_keyboard_and_mouse(pCGI, MAction, row, col, keycode1, keycode2);
						if (keycode1 == 'q' || keycode1 == 'Q' || keycode1 == 0x0D || MAction == MOUSE_LEFT_BUTTON_CLICK || MAction == MOUSE_RIGHT_BUTTON_CLICK || MAction == MOUSE_ONLY_MOVED || keycode1 == 0xe0)
							break;
					}
					//ȷ������
					if (keycode1 == 0x0D || MAction == MOUSE_LEFT_BUTTON_CLICK) {
						MAction = MOUSE_NO_ACTION, keycode1 = 0;   //��ԭ
						gmw_status_line(pCGI, LOWER_STATUS_LINE, "  ", NULL);
						clear_choose_star(pCGI, status);  //������ɫ
						zero(star_color, status);  //�����������
						output_score(pCGI, status, &score);
						fall_zero(pCGI, star_color, status);  //����ֵ���䶯��
						fall_un_zero(pCGI->row_num, pCGI->col_num, star_color);   //����ֵ����(���飩
						translation_zero(pCGI, star_color, status);  //��������
						move_all_arr(pCGI->row_num, pCGI->col_num, star_color);   //��ƽ��(���飩
						//������һ��
						if (!ensure_to_end(pCGI->row_num, pCGI->col_num, star_color))
							over_one_game(pCGI, status, star_color, &score);
						start_status(status);  //��ʼ��statsu
					}
					//��ͷ��/����ƶ�ȡ����ǰѡ������ѭ��			
					else {
						gmw_status_line(pCGI, LOWER_STATUS_LINE, "  ", NULL);
						same_star_print(pCGI, star_color, status, COLOR_BLACK);  //ȡ����ͬ��ɫ��ɫ�鷴��
						read = 0;  //�ٴν���while�����ٴζ���
						continue;
					}
				}
				else {  //����ֵͬ,����ѡ��
					gmw_status_line(pCGI, LOWER_STATUS_LINE, ",��ͷ��/����ƶ����س���/�������ѡ��Q/�����Ҽ�����", "��Χ����ֵͬ");
					continue;
				}
			}
		}

		else
			continue;
	}

	gmw_status_line(pCGI, LOWER_STATUS_LINE, "��Ϸ����,���س����˳�...");
}