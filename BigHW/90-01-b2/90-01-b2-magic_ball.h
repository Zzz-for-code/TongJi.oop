/* ������ 2352847 �ž��� */
#pragma once

/*�궨��*/
#define length_max 9   //��������������ֵ

/*���ߺ���*/
void stop(int option);  //���������ͣ��Ҫ
void find_clear(int hang, int lie, int a[length_max + 2][length_max + 2], int b[length_max + 2][length_max + 2]); //Ѱ�ҿ�������
void fill_zero(int hang, int lie, int ball_color[][length_max + 2]);  //��ֵ���
int count_score(int hang, int lie, int status[][length_max + 2], int* p_score); //����÷�
void able_to_change(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2], int x1, int y1, int x2, int y2, int* p_score);  //�ж��Ƿ���Խ���
int able_to_end(int hang, int lie, int status[][length_max + 2], int score);  //������Ϸ9����

/*���ڲ�������صĺ���*/
void cycle_1(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2], int option, int num);  //ѭ�����0���������
void remind_clear(int hang, int lie, int a[][length_max + 2], int b[][length_max + 2]);  //��ʾѰ�ҿ�������
void output_3(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2]); //ѡ��3�����

/*��αͼ�ν����йصĺ���*/
void output_kuang(int hang, int lie, char kuang[][4], int option);  //���ɿ��
void output_ball(int hang, int lie, int ball_color[][length_max + 2], int option, int status[][length_max + 2]);  //��������ɫ
void draw_able(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2]);  //������������
void clear_draw(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2]);  //������������
void fall_move(int hang, int lie, int ball_color[][length_max + 2]);  //����������
void fill_blank(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2]);  //���������ֵ
void output_remind(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2]);  //��ʾ����������ʾ
void remind_to_zero(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2]);  //������������ʾ����
void cycle_2(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2], int option);  //ѭ��
void calculate(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2], int* p_score);  //���ڷ��������ѭ��
int find_place(int* x1, int* y1, int hang, int lie, int status[][length_max + 2], int option);  //�жϹ��λ��
void move_change(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2], int score);  //���н���
void autogame(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2], int option);  //��Ϸ��