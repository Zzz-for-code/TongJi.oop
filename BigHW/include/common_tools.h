/* ������ 2352847 �ž��� */
#pragma once

/*������*/
void clear();  //��������
void wait_for_enter();  //������ͣ
int input_hang_lie(int status, int hang_max, int hang_min, int lie_max, int lie_min);  //�����С�����
int judge(int status[][11]);  //�ж��Ƿ��п�������
void find_again(int hang, int lie, int a[][11], int b[][11]);  //���¼�¼ɫ��λ��
void zero(int ball_color[][11], int status[][11]);  //�����������
void end_game(); //С�����������ť
void count_blank(int hang, int lie, int ball_color[][11], int blank[][11]); //����ÿ�����·������ո�

/*�ڲ��������*/
void creat_start(int hang, int lie, int ball_color[][11], int max); //���ɳ�ʼ����
void start_status(int status[][11]);  //��ʼ��status
void print_start(int hang, int lie, int op, int star_color[][11], int status[][11], const char str[]);  //��ӡ����
void fall_un_zero(int hang, int lie, int ball_color[][11]);  //����ֵ����

/*αͼ�ν���*/
void print_line(int num, int length, const char start[], const char middle1[], const char middle2[], const char end[]);  //��ܵ�ÿһ��