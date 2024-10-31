/* 大数据 2352847 张静敏 */
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

/*数组循环*/
void cycle_for_arr(int hang, int lie, int status[][length_max + 1], int star_color[][length_max + 1], char op, int score)
{
	char x = 0;
	int y = 0;
	print_start(hang, lie, 0, star_color, status, "当前数组：");
	start_status(status);  //初始化statsu
	if (!ensure_to_end(hang, lie, star_color)) {
		cct_setcolor(COLOR_HYELLOW, COLOR_RED);
		cout << endl << "剩余" << count_remain(hang, lie, star_color) << "个不可消除项，本关结束！" << endl;
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		return;
	}
	add_to_input(hang, lie, status, star_color, &x, &y);
	print_start(hang, lie, 1, star_color, status, "查找结果数组：");
	print_start(hang, lie, 0, star_color, status, "当前数组(不同色标识)：");
	if (op == 'A')
		return;
	else {
		char ch = choose_YNQ(x, y);
		if (ch == 'Q')
			return;
		if (ch == 'Y') {
			zero(star_color, status);  //可消除项归零
			print_start(hang, lie, 0, star_color, status, "相同值归并后的数组(不同色标识)：");
			int score_this = score_count(hang, lie, status);  //计算该次得分
			score += score_this;
			cout << endl << "本次得分：" << score_this << " 总得分：" << score << endl;
			cout << endl << "按回车键进行数组下落操作...";
			while (_getch() != '\r')
				;
			fall_un_zero(hang, lie, star_color);   //非零值下落
			move_all_arr(hang, lie, star_color);   //列平移
			find_again(hang, lie, star_color, status);   //重新记录色块位置
			print_start(hang, lie, 0, star_color, status, "下落后的数组：");
			if (op == 'B')
				return;
			else {
				cout << endl << "本次消除结束，请按回车键进行下一次消除..." << endl;
				while (_getch() != '\r')
					;
				return cycle_for_arr(hang, lie, status, star_color, op, score);
			}
		}
		else {
			find_again(hang, lie, star_color, status);   //重新记录色块位置
			if (op == 'B') {
				return;
			}
			else
				return cycle_for_arr(hang, lie, status, star_color, op, score);
		}
	}
}

/*处理键盘和鼠标信息并进行游戏*/
void choose_star_to_game(int hang, int lie, int status[][length_max + 1], int star_color[][length_max + 1], char option, int score)
{
	cct_setcursor(CURSOR_INVISIBLE);
	int x = 1, y = 1, * x1 = &x, * y1 = &y;
	int mark_status = 1, read = 1;  //mark_status用于标记按键时鼠标是否位于有效位置,read表示进入循环是否再次读键

	int high, width;   //星星的高度和宽度
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
	out_a_star(4 + width * (*x1 - 1), 3 + (*y1 - 1) * high, star_color[*y1][*x1], COLOR_WHITE);   //A0处输出初始反显
	while (1) {
		if (read)
			cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
		else
			read = 1;
		//键盘事件
		if (keycode1 == 0xe0) {
			out_a_star(4 + width * (*x1 - 1), 3 + (*y1 - 1) * high, star_color[*y1][*x1], COLOR_BLACK);  //取消反显
			keyboard_move(x1, y1, keycode2, hang, lie, star_color);
			output_add(high, width, *x1, *y1, high * hang + 4, star_color, keyboard, option);   //输出位置信息和反显
			MAction = MOUSE_NO_ACTION;
			continue;
		}

		//鼠标事件
		if (MAction == MOUSE_ONLY_MOVED || MAction == MOUSE_LEFT_BUTTON_CLICK || MAction == MOUSE_RIGHT_BUTTON_CLICK) {
			bool condition = MX >= 4 && MX <= (lie * width + 3) && MY >= 3 && MY < (hang * high + 3);
			bool condition_else = 0;
			out_a_star(4 + width * (*x1 - 1), 3 + (*y1 - 1) * high, star_color[*y1][*x1], COLOR_BLACK);  //取消反显
			*x1 = (MX - 4) / width + 1;  //从1开始
			*y1 = (MY - 3) / high + 1; //从1开始
			if (option == 'E' || option == 'G')
				condition_else = MX % width == 2 || MX % width == 3 || MY % high == 2;
			mark_status = 0;
			if (condition && !condition_else && star_color[*y1][*x1]) {
				output_add(high, width, *x1, *y1, high * hang + 4, star_color, mouse, option);   ////输出位置信息和反显
				mark_status = 1;
			}
			else {
				int m = 0;
				if (option == 'E' || option == 'G')
					m = 1;
				cct_gotoxy(im_x, im_y);
				cout << setw(60) << " ";
				cct_gotoxy(im_x, im_y);
				cout << "[当前鼠标] 位置非法";
			}
		}

		//鼠标点击左键且处于有效位置，或者按下回车且处于有效位置
		if ((MAction == MOUSE_LEFT_BUTTON_CLICK && mark_status) || keycode1 == '\r') {
			//D和E直接退出
			if (option == 'D' || option == 'E') {
				cct_gotoxy(0, high * hang + 4);
				cout << setw(65) << " ";
				cct_gotoxy(0, high * hang + 4);
				cout << "选中了";
				cout << char(*y1 - 1 + 'A') << "行" << *x1 - 1 << "列";
				Sleep(200);
				break;
			}
			//F/G进行下一步游戏
			else {
				start_status(status);   //初始化
				find_able_star(hang, lie, *y1, *x1, star_color, status);   //寻找目标位置周围是否有相同值
				if (status[*y1][*x1]) {   //有相同值
					same_star_print(hang, lie, star_color, option, status, COLOR_WHITE);  ////生成相同颜色的色块反显
					cct_gotoxy(im_x, im_y);
					cout << setw(65) << " ";
					cct_gotoxy(im_x, im_y);
					cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
					cout << "箭头键/鼠标移动取消当前选择，回车键/单击左键合成";

					if (MAction == MOUSE_LEFT_BUTTON_CLICK)
						cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);//按下鼠标左键，MAction会先变成2，再变成1，此句是为了“吃掉”1	
					while (1) {
						cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
						if (keycode1 == '\r' || MAction == MOUSE_LEFT_BUTTON_CLICK || MAction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK || MAction == MOUSE_ONLY_MOVED || keycode1 == 0xe0)
							break;
					}

					//确认消除,设置双击是防止之前一次点的太快
					if (keycode1 == '\r' || MAction == MOUSE_LEFT_BUTTON_CLICK || MAction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK) {
						cct_gotoxy(im_x, im_y);
						cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
						cout << setw(65) << " ";
						cct_gotoxy(im_x, im_y);
						MAction = MOUSE_NO_ACTION, keycode1 = 0;   //复原
						clear_choose_star(hang, lie, option, status);  //消除颜色
						zero(star_color, status);  //可消除项归零
						output_score(hang, lie, status, &score);
						if (option == 'F') {
							cout << "合成完成，回车键/单机左键下落";
							while (1) {
								cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
								if (keycode1 == '\r' || MAction == MOUSE_LEFT_BUTTON_CLICK)
									break;
							}
							fall_zero(hang, lie, star_color, status, option);  //非零值下落动画
							cct_gotoxy(im_x, im_y);
							cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
							cout << setw(65) << " ";
							cct_gotoxy(im_x, im_y);
							cout << "本次合成结束，按C/单机左键继续新一次合成";
							MAction = MOUSE_NO_ACTION, keycode1 = 0;   //复原
							while (1) {
								cct_read_keyboard_and_mouse(MX, MY, MAction, keycode1, keycode2);
								if (keycode1 == 'c' || keycode1 == 'C' || MAction == MOUSE_LEFT_BUTTON_CLICK)
									break;
							}
							cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
							break;
						}
						if (option == 'G') {
							fall_zero(hang, lie, star_color, status, option);  //非零值下落动画
							fall_un_zero(hang, lie, star_color);   //非零值下落(数组）
							translation_zero(hang, lie, star_color, status, option);  //空列右移
							move_all_arr(hang, lie, star_color);   //列平移(数组）
							//进入下一关
							if (!ensure_to_end(hang, lie, star_color))
								over_one_game(im_x, im_y, hang, lie, status, star_color, option, score);
							start_status(status);  //初始化statsu
						}
					}

					//箭头键/鼠标移动取消当前选择，重新循环			
					else {
						MAction = MOUSE_NO_ACTION, keycode1 = 0;
						cct_gotoxy(im_x, im_y);
						cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
						cout << setw(65) << " ";
						same_star_print(hang, lie, star_color, option, status, COLOR_BLACK);  //取消相同颜色的色块反显
						read = 0;  //再次进入while无需再次读键
						continue;
					}
				}
				else {  //无相同值,重新选择
					no_same(MX, MY, MAction, keycode1, keycode2, im_y, 4 + width * (*x1 - 1), 3 + (*y1 - 1) * high, star_color[*y1][*x1]);
					//only_one_star(MX, MY, MAction, keycode1, keycode2, info_x, info_y, p_x, p_y, matrix1, start_x, start_y);
					if (MAction == MOUSE_RIGHT_BUTTON_CLICK || keycode1 == 'Q' || keycode1 == 'q')
						break;
				}
			}
		}

		//鼠标点击右键且处于有效位置，或者按下Q/q键
		if ((MAction == MOUSE_RIGHT_BUTTON_CLICK && mark_status) || keycode1 == 'q' || keycode1 == 'Q') {
			cct_gotoxy(im_x, im_y);
			cout << setw(65) << " ";
			cct_gotoxy(im_x, im_y);
			if (option == 'E' || option == 'D') {
				cout << "选中了";
				cout << char(*y1 - 1 + 'A') << "行" << *x1 - 1 << "列";
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

/*结束一关的游戏*/
void over_one_game(int im_x,int im_y,int hang, int lie, int status[][length_max + 1], int star_color[][length_max + 1], char option, int score)
{
	cct_gotoxy(im_x, im_y);
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
	cout << setw(65) << " ";
	cct_gotoxy(im_x, im_y);
	cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
	cout << "剩余" << count_remain(hang, lie, star_color) << "个星星，无可消除项，本关结束！";
	cct_setcolor(COLOR_BLACK, COLOR_HWHITE);
	cout << "回车进入下一关";
	mark_final(count_remain(hang, lie, star_color), &score);
	while (_getch() != '\r') {
		;
	}
	cct_cls();
	creat_start(hang, lie, star_color, 5);  //再次生成新数组
	if (option == 'D' || option == 'F') {
		char kuang[11][4] = { "┏ ", "━ ", "", "┓ ", "┃ ","  ", "","┗ ", "━ ", "", "┛ " };
		print_jia(hang, lie, option, kuang);
	}
	else {
		char kuang[11][4] = { "┏ ", "━ ","┳ ", "┓ ", "┃ ","  ", "┃ ", "┗ ", "━ ","┻ ", "┛ " };
		print_jia(hang, lie, option, kuang);
	}
	print_all_start(hang, lie, star_color, option, status);
}