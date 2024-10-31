/* ������ 2352847 �ž��� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "../include/common_tools.h"
#include "../include/cmd_console_tools.h"
#include "90-01-b2-magic_ball.h"
using namespace std;

/*ѡ��3�����*/
void output_3(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2])
{
	cout << endl ;
	remind_clear(hang, lie, ball_color, status);
	print_start(hang, lie, 0, ball_color, status,"��ѡ�����������ʾ���ò�ͬɫ���ʶ����");
}

/*ѭ�����0���������*/
void cycle_1(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2], int option, int num)
{
	find_clear(hang, lie, ball_color, status);
	if (judge(status))
		print_start(hang, lie, 0, ball_color, status, "��ʼ��������(��ͬɫ��ʶ):");
	else {
		if (num)
			cout << endl;
		cout << "��ʼ���޿�������";
		if (option == 2 && num == 0)
			cout << "����С���޷����ԣ����ٴ�����";
		return;
	}
	if (option == 2 || option == 3) {
		cout << endl << "���س����������������0����..." << endl;
		while (_getch() != '\r');
		zero(ball_color, status);
		fall_un_zero(hang, lie, ball_color);
		find_again(hang, lie, ball_color, status);   //��ɫ��λ�����¼�¼
		print_start(hang, lie, 0, ball_color, status, "�����0�������(��ͬɫ��ʶ):");

		cout << endl << "���س���������ֵ���..." << endl;
		while (_getch() != '\r');
		fill_zero(hang, lie, ball_color);
		print_start(hang, lie, 0, ball_color, status, "��ֵ���������(��ͬɫ��ʶ):");
		return cycle_1(hang, lie, ball_color, status, 2, 1);
	}
}
