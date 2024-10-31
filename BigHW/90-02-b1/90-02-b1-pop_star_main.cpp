/* 大数据 2352847 张静敏 */
#include <iostream>
#include <Windows.h>
#include "../include/common_tools.h"
#include "../include/common_menu.h"
#include "../include/cmd_console_tools.h"
#include "90-02-b1-pop_star.h"
using namespace std;

int main()
{
	while (1) {
		cct_setfontsize("新宋体", 16);
		cct_setconsoleborder(120, 30, 120, 200);
		cct_cls();
		srand((unsigned int)(time(0)));  //取系统时间，为后续随机数做准备
		int option = menu(2, 10);
		if (option == 'Q') 
			break;
		else {
			cct_cls();
			int hang = input_hang_lie(1, 10, 8, 10, 8);
			int lie = input_hang_lie(0, 10, 8, 10, 8);
			int status[length_max + 1][length_max + 1] = { 0 };
			int star_color[length_max + 1][length_max + 1] = { 0 };
			creat_start(hang, lie, star_color, 5);  //先生成
			if (option == 'A' || option == 'B' || option == 'C')
				cycle_for_arr(hang, lie, status, star_color, option, 0);
			else {
				if (option == 'D' || option == 'F'){
					char kuang[11][4] = { "┏ ", "━ ", "", "┓ ", "┃ ","  ", "","┗ ", "━ ", "", "┛ " };
					print_jia(hang, lie, option, kuang);
				}
				else {
					char kuang[11][4] = { "┏ ", "━ ","┳ ", "┓ ", "┃ ","  ", "┃ ", "┗ ", "━ ","┻ ", "┛ " };
					print_jia(hang, lie, option, kuang);
				}
				print_all_start(hang, lie, star_color, option, status);
				choose_star_to_game(hang, lie, status, star_color, option, 0);
			}
			end_game();
		}
	}
	return 0;
}
