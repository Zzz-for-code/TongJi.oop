/* ������ 2352847 �ž��� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "../include/common_tools.h"
#include "../include/cmd_console_tools.h"
#include "../include/cmd_gmw_tools.h"
#include "90-01-b2-gmw-magic_ball.h"
using namespace std;

int main()
{
	srand((unsigned int)(time(0)));  //ȡϵͳʱ�䣬Ϊ�����������׼��
	cct_setcolor();
	cct_setfontsize("������", 16);
	cct_setconsoleborder(120, 30, 120, 200);
	cct_cls();
	//�������
	int hang = input_hang_lie(1, 9, 5, 9, 5);
	int lie = input_hang_lie(0, 9, 5, 9, 5);
	int status[length_max + 2][length_max + 2] = { 0 };
	int ball_color[length_max + 2][length_max + 2] = { 0 };
	creat_start(hang, lie, ball_color, 9);  //������

	cct_setcursor(CURSOR_INVISIBLE);
	CONSOLE_GRAPHICS_INFO MyCGI; //����һ��CGI����
	gmw_init(&MyCGI);  //��ʼ��
	gmw_set_rowcol(&MyCGI, hang, lie);					//��Ϸ����
	draw_game_kuang(&MyCGI);   //������Ϸ���
	output_ball(&MyCGI, ball_color, status);  //�����
	autogame(&MyCGI, ball_color, status);
	while (_getch() != '\r') {
		;
	}
	return 0;
}