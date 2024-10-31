/* ������ 2352847 �ž��� */
#pragma once

/*�궨��*/
#define length_max 10   //��������������ֵ
#define keyboard 1
#define mouse 2
#define right_left 1
#define up_down 2
/* ����1-5�������ú�����ʽ��ʾ�ڽ����ϣ�����״̬�� */
const BLOCK_DISPLAY_INFO bdi_normal[] = {
	{0, -1, -1, "  "},  //0����ʾ���ÿո���伴��
	{1, COLOR_HBLUE, COLOR_BLACK, "��"},
	{2, COLOR_HGREEN, COLOR_BLACK, "��"},
	{3, COLOR_HCYAN, COLOR_BLACK, "��"},
	{4, COLOR_HRED, COLOR_BLACK, "��"},
	{5, COLOR_HPINK, COLOR_BLACK, "��"},
	{-999, -1, -1, NULL} //�жϽ�������Ϊ-999
};
/* ����1-5�������ú�����ʽ��ʾ�ڽ����ϣ���ǰѡ����״̬+ѡ�к������״̬�� */
const BLOCK_DISPLAY_INFO bdi_related[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},  //�հ�
	{1, COLOR_HBLUE, COLOR_WHITE, "��"},
	{2, COLOR_HGREEN, COLOR_WHITE, "��"},
	{3, COLOR_HCYAN, COLOR_WHITE, "��"},
	{4, COLOR_HRED, COLOR_WHITE, "��"},
	{5, COLOR_HPINK, COLOR_WHITE, "��"},
	{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
};
/* ����1-5�������ú�����ʽ��ʾ�ڽ����ϣ�ѡ��״̬�� */
const BLOCK_DISPLAY_INFO bdi_selected[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},  //�հ�
	{1, COLOR_HBLUE, COLOR_HWHITE, "��"},
	{2, COLOR_HGREEN, COLOR_HWHITE, "��"},
	{3, COLOR_HCYAN, COLOR_HWHITE, "��"},
	{4, COLOR_HRED, COLOR_HWHITE, "��"},
	{5, COLOR_HPINK, COLOR_HWHITE, "��"},
	{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
};

/*���ߺ���*/
void find_able_star(int hang, int lie, int x, int y, int star_color[][length_max + 1], int status[][length_max + 1]);  //����Ŀ��λ�ÿ���������������
int score_count(int hang, int lie, int status[][length_max + 1]);  //��������
void exchange_two(int hang, int m1, int m2, int a[][length_max + 1]);  //�������������
int ensure_to_end(int hang, int lie, int a[][length_max + 1]);  //ȷ��һ�صĽ���
int count_remain(int hang, int lie, int a[][length_max + 1]);  //�������ʣ�����������
void count_blank_lie(int hang, int lie, int a[][length_max + 1], int blank_lie[]);  //����ÿһ����ߵĿ�����
void move_all_arr(int hang, int lie, int a[][length_max + 1]);  //��������ƽ��
void mark_final(CONSOLE_GRAPHICS_INFO* const pCGI,int final_star, int* score);  //���㽱���÷�
void keyboard_move(int* x, int* y, int keycode2, int hang, int lie, int star_color[][length_max + 1]);  //���̱任
/*αͼ�ν���*/
void print_jia(CONSOLE_GRAPHICS_INFO* const pCGI);  //���ɿ��
void print_all_start(CONSOLE_GRAPHICS_INFO* const pCGI, int star_color[][length_max + 1], int status[][length_max + 1]); //����ȫ��������
void same_star_print(CONSOLE_GRAPHICS_INFO* const pCGI, int star_color[][length_max + 1], int status[][length_max + 1], int color);  //����������ͬ������
void clear_choose_star(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 1]);  //����ѡ�е�����
void fall_zero(CONSOLE_GRAPHICS_INFO* const pCGI, int star_color[][length_max + 1], int status[][length_max + 1]);  //����ֵ���䶯��
void translation_zero(CONSOLE_GRAPHICS_INFO* const pCGI, int star_color[][length_max + 1], int status[][length_max + 1]);  //��������
void output_score(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 1], int* score);  //����÷�
void over_one_game(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 1], int star_color[][length_max + 1], int score);  //����һ�ص���Ϸ
void auto_game(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 1], int star_color[][length_max + 1], int score);  //��Ϸѭ��
