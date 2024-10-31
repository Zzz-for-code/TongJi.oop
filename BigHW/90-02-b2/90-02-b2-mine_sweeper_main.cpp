/* ������ 2352847 �ž��� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include "../include/common_tools.h"
#include "../include/cmd_console_tools.h"
#include "../include/cmd_gmw_tools.h"
#include "90-02-b2-mine_sweeper.h"

int main()
{
	srand((unsigned int)(time(0)));  //ȡϵͳʱ�䣬Ϊ�����������׼��
	//��ʼ���ڣ����������ʼ����
	while (1) {
		cct_setcolor();
		cct_setfontsize("������", 16);
		cct_setconsoleborder(120, 30, 120, 200);
		cct_cls();
		//��ʼ����
		int level = input_game_level();
		int size_hang = 0, size_lie = 0, mine_num = 0;
		ensure_size_mine(level, &size_hang, &size_lie, &mine_num);   //�����Ѷ�ȷ����Ӧ�Ĳ���
		char inner_mine[MAX_ROW + 2][MAX_COL + 2] = { 0 };    //�ڲ�������,��չһȦ
		creat_mine(size_hang, size_lie, mine_num, inner_mine);   //�����ڲ�����

		//αͼ�ν���
		cct_setcursor(CURSOR_INVISIBLE);
		CONSOLE_GRAPHICS_INFO MyCGI; //����һ��CGI����
		gmw_init(&MyCGI);  //��ʼ��
		gmw_set_rowcol(&MyCGI, size_hang, size_lie);					//��Ϸ����
		draw_kuang(&MyCGI, level, inner_mine);    //��ʼ��ͼ�ν���
		auto_game(&MyCGI, mine_num, inner_mine);

		gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "��ѡ�������½�����һ����Ϸ(1)\\����(0)", "������Ϸ������");
		cout << endl;
		int op;
		cct_setcursor(CURSOR_VISIBLE_NORMAL);   //��ʾ���
		cout << "���ѡ��";
		cin >> op;
		if (!op)
			break;
		cct_setcursor(CURSOR_INVISIBLE);   //��겻��ʾ
	}
	return 0;
}