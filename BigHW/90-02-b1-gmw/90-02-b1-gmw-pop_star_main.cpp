/* ������ 2352847 �ž��� */
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include "../include/cmd_gmw_tools.h"
#include "../include/common_tools.h"
#include "../include/cmd_console_tools.h"
#include "90-02-b1-gmw-pop_star.h"
using namespace std;

int main()
{

	srand((unsigned int)(time(0)));  //ȡϵͳʱ�䣬Ϊ�����������׼��
	cct_setcolor();
	cct_setfontsize("������", 16);
	cct_setconsoleborder(120, 30, 120, 200);
	cct_cls();
	int hang = input_hang_lie(1, 10, 8, 10, 8);
	int lie = input_hang_lie(0, 10, 8, 10, 8);
	int status[length_max + 1][length_max + 1] = { 0 };
	int star_color[length_max + 1][length_max + 1] = { 0 };
	creat_start(hang, lie, star_color, 5);  //������

	cct_setcursor(CURSOR_INVISIBLE);
	CONSOLE_GRAPHICS_INFO MyCGI; //����һ��CGI����
	gmw_init(&MyCGI);  //��ʼ��
	gmw_set_rowcol(&MyCGI, hang, lie);			//��Ϸ����
    print_jia(&MyCGI);
	print_all_start(&MyCGI, star_color, status);
	auto_game(&MyCGI, status, star_color, 0);
	while (_getch() != '\r') {
		;
	}
	return 0;
}
