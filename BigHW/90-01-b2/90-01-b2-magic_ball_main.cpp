/* 大数据 2352847 张静敏 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "../include/common_tools.h"
#include "../include/cmd_console_tools.h"
#include "../include/common_menu.h"
#include "90-01-b2-magic_ball.h"
using namespace std;

int main()
{
	while (1) {
		cct_setfontsize("新宋体", 16);
		cct_setconsoleborder(120, 30, 120, 200);
		cct_cls();
		srand((unsigned int)(time(0)));  //取系统时间，为后续随机数做准备
		int option = (int)menu(1, 10) - '0';
		if (option == 0) {
			cct_gotoxy(0, 30 - 7);
			stop(option);
			break;
		}
		else {
			cct_cls();
			int hang = input_hang_lie(1, 9, 5, 9, 5);
			int lie = input_hang_lie(0,9, 5, 9, 5);
			int status[length_max + 2][length_max + 2] = { 0 };
			int ball_color[length_max + 2][length_max + 2] = { 0 };
			creat_start(hang, lie, ball_color,9);  //先生成
			if (option == 1 || option == 2 || option == 3) {
				print_start(hang, lie, 0, ball_color, status, "初始数组：");
				stop(1);
				cycle_1(hang, lie, ball_color, status, option, 0);
				if (option == 3)
					output_3(hang, lie, ball_color, status);
			}
			else {
				if (option == 4 || option == 5) {
					print_start(hang, lie, 0, ball_color, status, "初始数组：");
					stop(option);
				}
				if (option == 4 || option == 6) {
					char kuang[11][4] = { "╔ ","═ ","","╗ ","║ ","  ","","╚ ","═ ","","╝ " };
					output_kuang(hang, lie, kuang, option);
				}
				else {
					char kuang[11][4] = { "╔ ","═ ","╦ ","╗ ","║ ","  ","║ ","╚ ","═ ","╩ ","╝ " };
					cout << "jin ";
					output_kuang(hang, lie, kuang, option);
				}
				output_ball(hang, lie, ball_color, option, status);  //填充球
				if (option == 6) {
					find_clear(hang, lie, ball_color, status);   //判断是否有可消除项
					if (judge(status))
						output_ball(hang, lie, ball_color, option, status);
					else {
						cct_gotoxy(14, 0);
						cout << "(未找到初始可消除项)";
						cct_gotoxy(0, hang + 2);
					}
				}
				if (option == 7)
					cycle_2(hang, lie, ball_color, status, option);
				if (option == 8 || option == 9)
					autogame(hang, lie, ball_color, status, option);
			}
			end_game();
		}
	}
	return 0;
}
