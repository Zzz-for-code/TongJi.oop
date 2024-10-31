/* ������ 2352847 �ž��� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "../include/common_tools.h"
#include "../include/cmd_console_tools.h"
#include "90-02-b1-pop_star.h"
using namespace std;

/*����ѭ��*/
void cycle_for_arr(int hang, int lie, int status[][length_max + 1], int star_color[][length_max + 1], char op, int score)
{
	char x = 0;
	int y = 0;
	print_start(hang, lie, 0, star_color, status, "��ǰ���飺");
	start_status(status);  //��ʼ��statsu
	if (!ensure_to_end(hang, lie, star_color)) {
		cct_setcolor(COLOR_HYELLOW, COLOR_RED);
		cout << endl << "ʣ��" << count_remain(hang, lie, star_color) << "��������������ؽ�����" << endl;
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		return;
	}
	add_to_input(hang, lie, status, star_color, &x, &y);
	print_start(hang, lie, 1, star_color, status, "���ҽ�����飺");
	print_start(hang, lie, 0, star_color, status, "��ǰ����(��ͬɫ��ʶ)��");
	if (op == 'A')
		return;
	else {
		char ch = choose_YNQ(x, y);
		if (ch == 'Q')
			return;
		if (ch == 'Y') {
			zero(star_color, status);  //�����������
			print_start(hang, lie, 0, star_color, status, "��ֵͬ�鲢�������(��ͬɫ��ʶ)��");
			int score_this = score_count(hang, lie, status);  //����ôε÷�
			score += score_this;
			cout << endl << "���ε÷֣�" << score_this << " �ܵ÷֣�" << score << endl;
			cout << endl << "���س������������������...";
			while (_getch() != '\r')
				;
			fall_un_zero(hang, lie, star_color);   //����ֵ����
			move_all_arr(hang, lie, star_color);   //��ƽ��
			find_again(hang, lie, star_color, status);   //���¼�¼ɫ��λ��
			print_start(hang, lie, 0, star_color, status, "���������飺");
			if (op == 'B')
				return;
			else {
				cout << endl << "���������������밴�س���������һ������..." << endl;
				while (_getch() != '\r')
					;
				return cycle_for_arr(hang, lie, status, star_color, op, score);
			}
		}
		else {
			find_again(hang, lie, star_color, status);   //���¼�¼ɫ��λ��
			if (op == 'B') {
				return;
			}
			else
				return cycle_for_arr(hang, lie, status, star_color, op, score);
		}
	}
}

/*������̺������Ϣ��������Ϸ*/
void choose_star_to_game(int hang, int lie, int status[][length_max + 1], int star_color[][length_max + 1], char option, int score)
{
	cct_setcursor(CURSOR_INVISIBLE);
	int x = 1, y = 1, * x1 = &x, * y1 = &y;
	int mark_status = 1, read = 1;  //mark_status���ڱ�ǰ���ʱ����Ƿ�λ����Чλ��,read��ʾ����ѭ���Ƿ��ٴζ���

	int high, width;   //���ǵĸ߶ȺͿ��
	if (option == 'D' || option == 'F') {
		high = 3;
		width = 6;
	}
	else {
		high = 4;
		width = 8;
	}
	int m = 0;
	if (option == 'E' || option == 'G')
		m = 1;
	int im_x = 0, im_y = high * hang + 4 - m;

	int MX, MY, MAction = MOUSE_NO_ACTION, keycode1 = 0, keycode2;
	cct_enable_mouse();
	out_a_star(4 + width * (*x1 - 1), 3 + (*y1 - 1) * high, star_color[*y1][*x1], COLOR_WHITE);   //A0�������ʼ����
	while (1) {
		if (read)
			cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
		else
			read = 1;
		//�����¼�
		if (keycode1 == 0xe0) {
			out_a_star(4 + width * (*x1 - 1), 3 + (*y1 - 1) * high, star_color[*y1][*x1], COLOR_BLACK);  //ȡ������
			keyboard_move(x1, y1, keycode2, hang, lie, star_color);
			output_add(high, width, *x1, *y1, high * hang + 4, star_color, keyboard, option);   //���λ����Ϣ�ͷ���
			MAction = MOUSE_NO_ACTION;
			continue;
		}

		//����¼�
		if (MAction == MOUSE_ONLY_MOVED || MAction == MOUSE_LEFT_BUTTON_CLICK || MAction == MOUSE_RIGHT_BUTTON_CLICK) {
			bool condition = MX >= 4 && MX <= (lie * width + 3) && MY >= 3 && MY < (hang * high + 3);
			bool condition_else = 0;
			out_a_star(4 + width * (*x1 - 1), 3 + (*y1 - 1) * high, star_color[*y1][*x1], COLOR_BLACK);  //ȡ������
			*x1 = (MX - 4) / width + 1;  //��1��ʼ
			*y1 = (MY - 3) / high + 1; //��1��ʼ
			if (option == 'E' || option == 'G')
				condition_else = MX % width == 2 || MX % width == 3 || MY % high == 2;
			mark_status = 0;
			if (condition && !condition_else && star_color[*y1][*x1]) {
				output_add(high, width, *x1, *y1, high * hang + 4, star_color, mouse, option);   ////���λ����Ϣ�ͷ���
				mark_status = 1;
			}
			else {
				int m = 0;
				if (option == 'E' || option == 'G')
					m = 1;
				cct_gotoxy(im_x, im_y);
				cout << setw(60) << " ";
				cct_gotoxy(im_x, im_y);
				cout << "[��ǰ���] λ�÷Ƿ�";
			}
		}

		//���������Ҵ�����Чλ�ã����߰��»س��Ҵ�����Чλ��
		if ((MAction == MOUSE_LEFT_BUTTON_CLICK && mark_status) || keycode1 == '\r') {
			//D��Eֱ���˳�
			if (option == 'D' || option == 'E') {
				cct_gotoxy(0, high * hang + 4);
				cout << setw(65) << " ";
				cct_gotoxy(0, high * hang + 4);
				cout << "ѡ����";
				cout << char(*y1 - 1 + 'A') << "��" << *x1 - 1 << "��";
				Sleep(200);
				break;
			}
			//F/G������һ����Ϸ
			else {
				start_status(status);   //��ʼ��
				find_able_star(hang, lie, *y1, *x1, star_color, status);   //Ѱ��Ŀ��λ����Χ�Ƿ�����ֵͬ
				if (status[*y1][*x1]) {   //����ֵͬ
					same_star_print(hang, lie, star_color, option, status, COLOR_WHITE);  ////������ͬ��ɫ��ɫ�鷴��
					cct_gotoxy(im_x, im_y);
					cout << setw(65) << " ";
					cct_gotoxy(im_x, im_y);
					cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
					cout << "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�";

					if (MAction == MOUSE_LEFT_BUTTON_CLICK)
						cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);//������������MAction���ȱ��2���ٱ��1���˾���Ϊ�ˡ��Ե���1	
					while (1) {
						cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
						if (keycode1 == '\r' || MAction == MOUSE_LEFT_BUTTON_CLICK || MAction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK || MAction == MOUSE_ONLY_MOVED || keycode1 == 0xe0)
							break;
					}

					//ȷ������,����˫���Ƿ�ֹ֮ǰһ�ε��̫��
					if (keycode1 == '\r' || MAction == MOUSE_LEFT_BUTTON_CLICK || MAction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK) {
						cct_gotoxy(im_x, im_y);
						cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
						cout << setw(65) << " ";
						cct_gotoxy(im_x, im_y);
						MAction = MOUSE_NO_ACTION, keycode1 = 0;   //��ԭ
						clear_choose_star(hang, lie, option, status);  //������ɫ
						zero(star_color, status);  //�����������
						output_score(hang, lie, status, &score);
						if (option == 'F') {
							cout << "�ϳ���ɣ��س���/�����������";
							while (1) {
								cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
								if (keycode1 == '\r' || MAction == MOUSE_LEFT_BUTTON_CLICK)
									break;
							}
							fall_zero(hang, lie, star_color, status, option);  //����ֵ���䶯��
							cct_gotoxy(im_x, im_y);
							cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
							cout << setw(65) << " ";
							cct_gotoxy(im_x, im_y);
							cout << "���κϳɽ�������C/�������������һ�κϳ�";
							MAction = MOUSE_NO_ACTION, keycode1 = 0;   //��ԭ
							while (1) {
								cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
								if (keycode1 == 'c' || keycode1 == 'C' || MAction == MOUSE_LEFT_BUTTON_CLICK)
									break;
							}
							cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
							break;
						}
						if (option == 'G') {
							fall_zero(hang, lie, star_color, status, option);  //����ֵ���䶯��
							fall_un_zero(hang, lie, star_color);   //����ֵ����(���飩
							translation_zero(hang, lie, star_color, status, option);  //��������
							move_all_arr(hang, lie, star_color);   //��ƽ��(���飩
							//������һ��
							if (!ensure_to_end(hang, lie, star_color))
								over_one_game(im_x, im_y, hang, lie, status, star_color, option, score);
							start_status(status);  //��ʼ��statsu
						}
					}

					//��ͷ��/����ƶ�ȡ����ǰѡ������ѭ��			
					else {
						MAction = MOUSE_NO_ACTION, keycode1 = 0;
						cct_gotoxy(im_x, im_y);
						cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
						cout << setw(65) << " ";
						same_star_print(hang, lie, star_color, option, status, COLOR_BLACK);  //ȡ����ͬ��ɫ��ɫ�鷴��
						read = 0;  //�ٴν���while�����ٴζ���
						continue;
					}
				}
				else {  //����ֵͬ,����ѡ��
					no_same(MX, MY, MAction, keycode1, keycode2, im_y, 4 + width * (*x1 - 1), 3 + (*y1 - 1) * high, star_color[*y1][*x1]);
					//only_one_star(MX, MY, MAction, keycode1, keycode2, info_x, info_y, p_x, p_y, matrix1, start_x, start_y);
					if (MAction == MOUSE_RIGHT_BUTTON_CLICK || keycode1 == 'Q' || keycode1 == 'q')
						break;
				}
			}
		}

		//������Ҽ��Ҵ�����Чλ�ã����߰���Q/q��
		if ((MAction == MOUSE_RIGHT_BUTTON_CLICK && mark_status) || keycode1 == 'q' || keycode1 == 'Q') {
			cct_gotoxy(im_x, im_y);
			cout << setw(65) << " ";
			cct_gotoxy(im_x, im_y);
			if (option == 'E' || option == 'D') {
				cout << "ѡ����";
				cout << char(*y1 - 1 + 'A') << "��" << *x1 - 1 << "��";
			}
			Sleep(200);
			break;
		}
	}
	cct_gotoxy(im_x, im_y);
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
	cout << setw(65) << " ";
	cct_gotoxy(im_x, im_y);
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
}

/*����һ�ص���Ϸ*/
void over_one_game(int im_x,int im_y,int hang, int lie, int status[][length_max + 1], int star_color[][length_max + 1], char option, int score)
{
	cct_gotoxy(im_x, im_y);
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
	cout << setw(65) << " ";
	cct_gotoxy(im_x, im_y);
	cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
	cout << "ʣ��" << count_remain(hang, lie, star_color) << "�����ǣ��޿���������ؽ�����";
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
	cout << "�س�������һ��";
	mark_final(count_remain(hang, lie, star_color), &score);
	while (_getch() != '\r') {
		;
	}
	cct_cls();
	creat_start(hang, lie, star_color, 5);  //�ٴ�����������
	if (option == 'D' || option == 'F') {
		char kuang[11][4] = { "�� ", "�� ", "", "�� ", "�� ","  ", "","�� ", "�� ", "", "�� " };
		print_jia(hang, lie, option, kuang);
	}
	else {
		char kuang[11][4] = { "�� ", "�� ","�� ", "�� ", "�� ","  ", "�� ", "�� ", "�� ","�� ", "�� " };
		print_jia(hang, lie, option, kuang);
	}
	print_all_start(hang, lie, star_color, option, status);
}