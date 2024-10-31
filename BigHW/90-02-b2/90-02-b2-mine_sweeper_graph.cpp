/* ������ 2352847 �ž��� */
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

/*�������*/
void draw_kuang(CONSOLE_GRAPHICS_INFO* const pCGI,int level, char inner_mine[][MAX_COL + 2])
{
	int word_size = 14;
	if (level == 1)
		word_size = 16;
	else
		word_size = 12;
	//��������
	gmw_set_font(pCGI, "������",word_size);
	//ɫ��
	gmw_set_frame_style(pCGI, 4, 2);
	//�������
	gmw_set_frame_default_linetype(pCGI, 2);   //ȫ����
	//��Ϸ������ɫ
	gmw_set_frame_color(pCGI, COLOR_HWHITE, COLOR_BLACK);
	//�кš��б�
	gmw_set_rowno_switch(pCGI, true);
	gmw_set_colno_switch(pCGI, true);

	gmw_draw_frame(pCGI);
	gmw_status_line(pCGI, TOP_STATUS_LINE, "�ո���ʾʱ��","Q\\q�˳���");
	//����ɫ��
	for (int i = 1; i <= pCGI->row_num; i++) {
		for (int j = 1; j <= pCGI->col_num; j++)
			gmw_draw_block(pCGI, i - 1, j - 1, BDI_VALUE_BLANK, bdi_normal);
	}
}

/*������������*/
int open_enable(CONSOLE_GRAPHICS_INFO* const pCGI, int x, int y, char inner_mine[][MAX_COL + 2], int status[][MAX_COL + 2])
{
	status[x][y] = VISITED;
	if (inner_mine[x][y] != '*')
		gmw_draw_block(pCGI, x - 1, y - 1, inner_mine[x][y] - '0', bdi_open);
	else
		gmw_draw_block(pCGI, x - 1, y - 1, MINE, bdi_open);
	if (inner_mine[x][y] == '*')
		return 1;
	else if (inner_mine[x][y] == '0') { // �����0����ݹ��������������
		for (int i = 0; i < 8; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx > 0 && nx <= pCGI->row_num && ny > 0 && ny <= pCGI->col_num && status[nx][ny] != VISITED && status[nx][ny] != FLAGED) {
				if (open_enable(pCGI, nx, ny, inner_mine, status))
					return 1;
			}
		}
	}
	return 0; // û�������ף�������Ϸ
}

/*��Ϸ�汾*/
void auto_game(CONSOLE_GRAPHICS_INFO* const pCGI, int mine,char inner_mine[][MAX_COL + 2])
{
	int status[MAX_ROW + 2][MAX_COL + 2] = { 0 };    //��¼ÿ��λ���Ƿ�̽����߱��
	int row = -1, col = -1;
	int MAction, keycode1, keycode2;
	//��ʱ��ʼ
	double dur;
	clock_t start, end;
	start = clock();
	while (1) {
		gmw_read_keyboard_and_mouse(pCGI, MAction, row, col, keycode1, keycode2);
		//�����˳�
		if (keycode1 == 'q' || keycode1 == 'Q') {
			//����ʱ����
			end = clock();
			dur = (double)(end - start);
			char temp1[256];
			sprintf(temp1, "ʣ��������%d,", mine);
			char temp2[256];
			sprintf(temp2, "������Ϸʱ�䣺%f��", (dur / CLOCKS_PER_SEC));
			gmw_status_line(pCGI, TOP_STATUS_LINE, temp2, temp1);
			break;
		}
		//���¿ո�,��ʾʱ��
		else if (keycode1 == ' ') {
			end = clock();
			dur = (double)(end - start);
			char temp[256];
			sprintf(temp, "��ǰʱ�䣺%f�� ", (dur / CLOCKS_PER_SEC));
			gmw_status_line(pCGI, TOP_STATUS_LINE, "�ո���ʾʱ��,Q\\q�˳�", temp);
		}
		//�������
		else if (MAction == MOUSE_LEFT_BUTTON_CLICK) {
			//����ǹ�
			if (status[row + 1][col + 1] == FLAGED) {
				gmw_status_line(pCGI, TOP_STATUS_LINE, "����ȡ������", "��λ���ѱ����Ϊ�ף�");
				continue;
			}
			//���򿪹�
			else if (status[row + 1][col + 1] == VISITED) {
				gmw_status_line(pCGI, LOWER_STATUS_LINE, "[λ�÷Ƿ�]!!!");
				continue;
			}
			else {
				int ret = open_enable(pCGI, row + 1, col + 1, inner_mine, status);  //�����ڲ�����
				//�㵽���ˣ���Ϸʧ��
				if (ret) {
					//����ʱ����
					end = clock();
					dur = (double)(end - start);
					char temp[256];
					sprintf(temp, "����ʱ��%f�� ", (dur / CLOCKS_PER_SEC));
					gmw_status_line(pCGI, LOWER_STATUS_LINE, "�����ˣ���Ϸʧ��,���س�����...", temp);
					while (_getch() != '\r') {
						;
					}
					break;
				}
			}
		}
		//�����Ҽ�
		else if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
			//�Ѿ�����ǹ���,ȡ�����
			if (status[row + 1][col + 1] == FLAGED) {
				gmw_draw_block(pCGI, row, col, BDI_VALUE_BLANK, bdi_normal);
				status[row + 1][col + 1] = 0;
				mine++;
				char temp1[256];
				sprintf(temp1, "ʣ��������%d,", mine);
				gmw_status_line(pCGI, TOP_STATUS_LINE, "�ո���ʾʱ��,Q\\q�˳���", temp1);
			}
			//δ����Ǻʹ򿪹��ģ����
			else if (status[row + 1][col + 1] == 0) {
				//�����ﵽ���޲�׼���
				if (mine == 0) {
					gmw_status_line(pCGI, TOP_STATUS_LINE, NULL, "��������Ѵ����ޣ������¿��ǣ�����");
					Sleep(800);
					char temp1[256];
					sprintf(temp1, "ʣ��������%d,", mine);
					gmw_status_line(pCGI, TOP_STATUS_LINE, "�ո���ʾʱ��,Q\\q�˳���", temp1);
					continue;
				}
				else {
					gmw_draw_block(pCGI, row, col, FLAG, bdi_open);
					status[row + 1][col + 1] = FLAGED;
					mine--;
					char temp1[256];
					sprintf(temp1, "ʣ��������%d,", mine);
					gmw_status_line(pCGI, TOP_STATUS_LINE, "�ո���ʾʱ��,Q\\q�˳���", temp1);
				}
			}
			else
				continue;
		}
		//�������Լ�����ƶ�
		else
			continue;
		//�ж���Ϸ�Ƿ����
		if (judge_end(pCGI->row_num, pCGI->col_num, status)==0) {
			//����ʱ����
			end = clock();
			dur = (double)(end - start);
			char temp[256];
			sprintf(temp, "��ϲ����Ϸ�ɹ�������ʱ��%f�� ", (dur / CLOCKS_PER_SEC));
			gmw_status_line(pCGI, LOWER_STATUS_LINE, "���س�����...", temp);
			while (_getch() != '\r') {
				;
			}
			break;
		}
	}
}