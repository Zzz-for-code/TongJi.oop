/* ������ 2352847 �ž��� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "../include/common_tools.h"
#include "../include/cmd_console_tools.h"
#include "90-01-b1-hanoi.h"
#include "../include/common_menu.h"
using namespace std;

/* ----------------------------------------------------------------------------------

	 ���ļ����ܣ�
	1����main����
	2����ʼ����Ļ
	3�����ò˵�������hanoi_menu.cpp�У�������ѡ��
	4������ѡ����ò˵������Ӧ��ִ�к�����hanoi_multiple_solutions.cpp�У�

	 ���ļ�Ҫ��
	1����������ȫ�ֱ��������ⲿȫ�ֺ;�̬ȫ�֣�const��#define�������Ʒ�Χ�ڣ�
	2����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	3���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------------------------------------------------- */

int main()
{
	/* demo������ִ�д˾䣬��cmd��������Ϊ40��x120�У����������120�У�����9000�У���cmd�����Ҳ���д�ֱ�����ˣ�*/
	cct_setconsoleborder(120, 40, 120, 9000);
	cct_cls();
	int n, speed, option = 1;
	char src, tmp, dst;
	option = (int)menu(0, 10) - '0';
	cout << endl << endl;
	if (option == 0) {
		cct_gotoxy(0, width - 3);
		return 0;
	}
	else {
		if (option != 5) {
			first();
			input_all(option, src, tmp, dst, n, speed);
			start(n, src);
			if (option != 1 && option != 2 && option != 3)
				cct_cls();
			if (option == 4 || option == 8) {
				cout << "�� " << src << " �ƶ��� " << dst << ", �� " << n << " �㣬��ʱ����Ϊ " << speed << endl;
				if (option == 4)
					output_start_shu(0, n, src, dst);  //��ʼ״̬
				if (option == 8) {
					output_start_shu(diffirence, n, src, dst);  //��ʼ״̬
					output_6(n, src);
				}
			}
			if (option == 6 || option == 7 || option == 9) {
				cout << "�� " << src << " �ƶ��� " << dst << ", �� " << n << " ��" << endl;
				if (option == 6)
					output_6(n, src);
				if (option == 7) {
					output_6(n, src);
					output_7(option, src, dst);
				}
				if (option == 9) {
					output_start_shu(diffirence, n, src, dst);  //��ʼ״̬
					output_6(n, src);
					game(n, src, dst);
				}
			}
			hanoi(n, src, tmp, dst, option);
		}
		if (option == 5) {
			cct_cls();
			output_5();
		}
		if (option == 1 || option == 2 || option == 3)
			cout << endl;
		else
			cct_gotoxy(0, width - 2);
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
		cout << "���س�������";
		while (_getch() != '\r');
		main();
	}
}

