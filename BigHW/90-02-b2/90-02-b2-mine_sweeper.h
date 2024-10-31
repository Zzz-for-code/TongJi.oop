/* ������ 2352847 �ž��� */
#pragma once

/*�궨��*/
#define MAX_ROW 16
#define MAX_COL 30
#define VISITED 1
#define FLAGED -1
#define MINE 9
#define FLAG 10
const int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 }; // x�����ƫ����
const int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 }; // y�����ƫ����
//��ɫ��״̬
const BLOCK_DISPLAY_INFO bdi_normal[] = {
		{BDI_VALUE_BLANK, COLOR_YELLOW, COLOR_YELLOW, NULL},  //0����ʾ���ÿո���伴��
		{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
};
//���򿪺��
const BLOCK_DISPLAY_INFO bdi_open[] = {
		{BDI_VALUE_BLANK, COLOR_WHITE, COLOR_WHITE, NULL},
		{1, COLOR_WHITE, COLOR_BLUE, NULL},
		{2, COLOR_WHITE, COLOR_GREEN, NULL},
		{3, COLOR_WHITE, COLOR_CYAN, NULL},
		{4, COLOR_WHITE, COLOR_RED, NULL},
		{5, COLOR_WHITE, COLOR_PINK, NULL},
		{6, COLOR_WHITE, COLOR_YELLOW, NULL},
		{7, COLOR_WHITE, COLOR_HBLUE, NULL},
		{8, COLOR_WHITE, COLOR_HGREEN, NULL},
		{MINE, COLOR_WHITE, COLOR_BLACK, "*"},
		{FLAG, COLOR_RED, COLOR_HBLACK, "#"},
		{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
};

/*���ߺ���*/
int input_game_level();  //������Ϸ�Ѷ�
void ensure_size_mine(int level, int* size_hang, int* size_lie, int* mine);  //ȷ�������С������
int count_mine(char inner_mine[][MAX_COL + 2], int x, int y);  //����ÿ��λ�ø����˸�λ���м�����
void creat_mine(int size_hang, int size_lie, int mine, char inner_mine[][MAX_COL + 2]);  //�����ڲ�����/*�ж���Ϸ�Ƿ����*/
int judge_end(int size_hang, int size_lie, int status[][MAX_COL + 2]);  //�ж���Ϸ�Ƿ����

/*αͼ�ν������*/
void draw_kuang(CONSOLE_GRAPHICS_INFO* const pCGI, int level, char inner_mine[][MAX_COL + 2]);  //�������
void auto_game(CONSOLE_GRAPHICS_INFO* const pCGI, int mine, char inner_mine[][MAX_COL + 2]);  //��Ϸ�汾
int open_enable(CONSOLE_GRAPHICS_INFO* const pCGI, int x, int y, char inner_mine[][MAX_COL + 2], int status[][MAX_COL + 2]);  //������������