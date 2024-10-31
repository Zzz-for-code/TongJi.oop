/* ������ 2352847 �ž��� */
#pragma once

/*�궨��*/
#define length_max 10   //��������������ֵ
#define keyboard 1
#define mouse 2
#define right_left 1
#define up_down 2

/*ѭ�����*/
void cycle_for_arr(int hang, int lie, int status[][length_max + 1], int star_color[][length_max + 1], char op,int score);  //����ѭ��
void choose_star_to_game(int hang, int lie, int status[][length_max + 1], int star_color[][length_max + 1], char option, int score);  //������̺������Ϣ��������Ϸ
void over_one_game(int im_x, int im_y, int hang, int lie, int status[][length_max + 1], int star_color[][length_max + 1], char option, int score);  //����һ�ص���Ϸ

/*���ߺ���*/
void add_to_input(int hang, int lie, int status[][length_max + 1], int star_color[][length_max + 1], char* x, int* y); //��������
void find_able_star(int hang, int lie, int x, int y, int star_color[][length_max + 1], int status[][length_max + 1]);  //����Ŀ��λ�ÿ���������������
char choose_YNQ(char x, int y);  //ѡ���Ƿ�����ѡ�е���ֵͬ
int score_count(int hang, int lie, int status[][length_max + 1]);  //��������
void exchange_two(int hang, int m1, int m2, int a[][length_max + 1]);  //�������������
int ensure_to_end(int hang, int lie, int a[][length_max + 1]);  //ȷ��һ�صĽ���
int count_remain(int hang, int lie, int a[][length_max + 1]);  //�������ʣ�����������
void count_blank_lie(int hang, int lie, int a[][length_max + 1], int blank_lie[]);  //����ÿһ����ߵĿ�����
void move_all_arr(int hang, int lie, int a[][length_max + 1]);  //��������ƽ��
void output_add(int high, int width, int star_x, int star_y, int add_y, int star_color[][length_max + 1], int flag, char option);  //�������ͷ���
void keyboard_move(int* x, int* y, int keycode2, int hang, int lie, int star_color[][length_max + 1]);  //���̱任
int decide_to_change(int hang, int lie, int option, int high, int width, int MX, int MY, int old_x, int old_y, int old_mark, int old_color);  //�ж�����ƶ��ķ�Χ�Ƿ񳬳��������Ƿ�Χ
void no_same(int& MX, int& MY, int& MAction, int& keycode1, int& keycode2, int word_y, int star_x, int star_y, int star_color);  //����ֵͬ��Ӧ�����
void mark_final(int final_star, int* score);  //���㽱���÷�

/*αͼ�ν���*/
void print_jia(int hang, int lie, char option, char kuang[][4]);  //���ɿ��
void out_a_star(int start_x, int start_y, int bg_color, int fg_color);  //���һ�����ǵ�ͼ��
void print_all_start(int hang, int lie, int star_color[][length_max + 1], char option, int status[][length_max + 1]); //����ȫ��������
void same_star_print(int hang, int lie, int star_color[][length_max + 1], int option, int status[][length_max + 1], int color);  //����������ͬ������
void clear_choose_star(int hang, int lie, int option, int status[][length_max + 1]);  //����ѡ�е�����
void one_star_move(int choose, int star_x, int star_y, int hang, int lie, int star_color, int option);  //�������ǵ��ƶ�����һ��
void fall_zero(int hang, int lie, int star_color[][length_max + 1], int status[][length_max + 1], int option);  //����ֵ���䶯��
void translation_zero(int hang, int lie, int star_color[][length_max + 1], int status[][length_max + 1], int option);  //��������
void output_score(int hang, int lie, int status[][length_max + 1], int* score);  //����÷�