/* ������ 2352847 �ž��� */
#pragma once

/*�궨��*/
#define length_max 9   //��������������ֵ
/* ����1-9�������ú�����ʽ��ʾ�ڽ����ϣ�����״̬�� */
const BLOCK_DISPLAY_INFO bdi_normal[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},  //0����ʾ���ÿո���伴��
	{1, COLOR_HBLACK, -1, "��"},
	{2, COLOR_YELLOW, -1, "��"},
	{3, COLOR_HGREEN, -1, "��"},
	{4, COLOR_HCYAN, -1, "��"},
	{5, COLOR_HRED, -1, "��"},
	{6, COLOR_HPINK, -1, "��"},
	{7, COLOR_HYELLOW, -1, "��"},
	{8, COLOR_CYAN, -1, "��"},
	{9, COLOR_WHITE, -1, "��"},
	{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
};
/* ����1-9�������ú�����ʽ��ʾ�ڽ����ϣ�ѡ��״̬�� */
const BLOCK_DISPLAY_INFO bdi_selected[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},  //�հ�
	{1, COLOR_HBLACK, -1, "��"},
	{2, COLOR_YELLOW, -1, "��"},
	{3, COLOR_HGREEN, -1, "��"},
	{4, COLOR_HCYAN, -1, "��"},
	{5, COLOR_HRED, -1, "��"},
	{6, COLOR_HPINK, -1, "��"},
	{7, COLOR_HYELLOW, -1, "��"},
	{8, COLOR_CYAN, -1, "��"},
	{9, COLOR_WHITE, -1, "��"},
	{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
};
/* ����1-9�������ú�����ʽ��ʾ�ڽ����ϣ���������ʾ״̬�� */
const BLOCK_DISPLAY_INFO bdi_prompt[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},  //�հ�
	{1, COLOR_HBLACK, -1, "��"},
	{2, COLOR_YELLOW, -1, "��"},
	{3, COLOR_HGREEN, -1, "��"},
	{4, COLOR_HCYAN, -1, "��"},
	{5, COLOR_HRED, -1, "��"},
	{6, COLOR_HPINK, -1, "��"},
	{7, COLOR_HYELLOW, -1, "��"},
	{8, COLOR_CYAN, -1, "��"},
	{9, COLOR_WHITE, -1, "��"},
	{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
};
/* ����1-9�������ú�����ʽ��ʾ�ڽ����ϣ���ը/����״̬�� */
const BLOCK_DISPLAY_INFO bdi_exploded[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},  //�հ�
	{1, COLOR_HBLACK, -1, "��"},
	{2, COLOR_YELLOW, -1, "��"},
	{3, COLOR_HGREEN, -1, "��"},
	{4, COLOR_HCYAN, -1, "��"},
	{5, COLOR_HRED, -1, "��"},
	{6, COLOR_HPINK, -1, "��"},
	{7, COLOR_HYELLOW, -1, "��"},
	{8, COLOR_CYAN, -1, "��"},
	{9, COLOR_WHITE, -1, "��"},
	{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
};

/*���ߺ���*/
void find_clear(int hang, int lie, int a[length_max + 2][length_max + 2], int b[length_max + 2][length_max + 2]); //Ѱ�ҿ�������
void fill_zero(int hang, int lie, int ball_color[][length_max + 2]);  //��ֵ���
void remind_clear(int hang, int lie, int a[][length_max + 2], int b[][length_max + 2]);  //��ʾѰ�ҿ�������
int count_score(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 2], int* p_score); //����÷�

/*��αͼ�ν����йصĺ���*/
void draw_game_kuang(CONSOLE_GRAPHICS_INFO* const pCGI);  //������Ϸ����
void output_ball(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2]);  //��������ɫ
void draw_able(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2]);  //������������
void clear_draw(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2]);  //������������
void fall_move(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2]);  //����������
void fill_blank(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2]);  //���������ֵ
void output_remind(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2]);  //��ʾ����������ʾ
void remind_to_zero(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2]);  //������������ʾ����
void calculate(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2], int* p_score);  //���ڷ��������ѭ��
int find_place(CONSOLE_GRAPHICS_INFO* const pCGI,int* x1, int* y1, int status[][length_max + 2]);  //�жϹ��λ��
void move_change(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2], int score);  //���н���
void able_to_change(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2], int x1, int y1, int x2, int y2, int* p_score);  //�ж��Ƿ���Խ���
int able_to_end(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 2], int score);  //������Ϸ9����
void autogame(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2]);  //��Ϸ��
