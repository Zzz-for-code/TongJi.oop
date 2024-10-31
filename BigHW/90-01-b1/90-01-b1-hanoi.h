/* ������ 2352847 �ž��� */
#pragma once

/* ------------------------------------------------------------------------------------------------------

	 ���ļ����ܣ�
	1��Ϊ�˱�֤ hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp ���໥���ʺ����ĺ�������
	2��һ�����ϵ�cpp���õ��ĺ궨�壨#define����ȫ��ֻ����const����������������
	3�����Բο� cmd_console_tools.h ��д���������Ķ�����ᣩ
   ------------------------------------------------------------------------------------------------------ */

   /*�궨��*/
#define length 120   //�����ĳ���
#define width 40     //�����Ŀ��
#define hang_4_heng 17   //�˵�4�������������
#define hang_4_Y_tower 13   //�˵�4���������ĸA������
#define lie_4_X_tower 11    //�˵�4���������ĸA������
#define hang_Y_zhuzi  15    //��һ������ͼ�������
#define lie_X_zhuzi  1     //��һ������ͼ�������
#define lie_X_zhuzi_middle  12     //��һ������ͼ����м������
#define distance 32  //���Ӽ�������
#define base_length 23//�����ĳ���
#define base_height 12//���ӵĸ߶�
#define diffirence 15  //4-8��9ֱ�Ӻ�������������
#define Y_game 34   //��Ϸģʽ��һ�����������
#define X_game 60   //��Ϸģʽ�������������

/*��������صĺ���*/
int input_n();
char input_src();
char input_dst(char src);
char input_tmp(char src, char dst);
int input_speed();
void input_all(int option, char& src, char& tmp, char& dst, int& n, int& speed);

/*�ݹ麯��Hanoi����*/
void hanoi(int n, char src, char tmp, char dst, int option);   //�ݹ�����
void output_realhanoi(int n, int num, char src, char tmp, char dst, int option);  //�벻ͬ����й�

/*�����صĺ���*/
void output_8(int option, int n, int num, char src, char dst, int speed); //�Զ��ƶ�+����+����
void output_7(int option, char src, char dst);  //��һ���ƶ�/���ӵ��ƶ�
void output_6(int n, char src);  //����ʼ���ϻ�n������
void output_5();   //����������
void output_4(int option, int status, int n, int num, char src, char dst, int speed);  //����+����
void output_heng();  //�������
void output_start_shu(int status, int n, char src, char dst);  //�������ÿ���������ӵı��

/*��������*/
void first(); //��ȫ�ֱ�����0
void start(int n, char src);  //��ʼ����������
void output_column(char ch);  //���ÿ�����ӵ����ӱ��
void move_top(char src, char dst);  //ջ��ָ��ı仯
int time(int speed);  //��ʱ����
void clear(int status, char src);  //�Ե���Ӧλ�õ�����
void print(int status, char src, char dst);  //����Ӧ��λ�ô�ӡ��Ӧ������

/*����Ϸģʽ��صĺ���*/
void game(int n, char src, char dst);  // ��Ϸ��Ҫ����
void game_move(char src, char dst);  //��Ϸ����ƶ�

