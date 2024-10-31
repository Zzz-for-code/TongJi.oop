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

/*������Ϸ�Ѷ�*/
int input_game_level()
{
	int level; 
    cout << "������ɨ�׵ĵȼ������֣�����\\һ��\\���ѣ�1\\2\\3��";
    cin >> level;
    while (cin.good() == 0 || level < 1 || level>3) {
        clear();
        cout << "������ɨ�׵ĵȼ������֣�����\\һ��\\���ѣ�1\\2\\3��";
        cin >> level;
    }
    clear();
    return level;
}

/*ȷ�������С������*/
void ensure_size_mine(int level,int* size_hang,int* size_lie,int* mine)
{
    if (level == 1) {
        *size_hang = 9;
        *size_lie = 9;
        *mine = 10;
    }
    if (level == 2) {
        *size_hang = 16;
        *size_lie = 16;
        *mine = 40;
    }
    if (level == 3) {
        *size_hang = 16;
        *size_lie = 30;
        *mine = 99;
    }
}

/*����ÿ��λ�ø����˸�λ���м�����*/
int count_mine(char inner_mine[][MAX_COL + 2], int x, int y)
{
    int num = 0;
    if (inner_mine[x - 1][y - 1] == '*')  //����
        num++;
    if (inner_mine[x - 1][y] == '*')  //����
        num++;
    if (inner_mine[x - 1][y + 1] == '*')  //����
        num++;
    if (inner_mine[x][y - 1] == '*')  //����
        num++;
    if (inner_mine[x][y + 1] == '*')  //����
        num++;
    if (inner_mine[x + 1][y - 1] == '*')  //����
        num++;
    if (inner_mine[x + 1][y] == '*')  //����
        num++;
    if (inner_mine[x + 1][y + 1] == '*')  //����
        num++;
    return num;
}

/*�����ڲ�����*/
void creat_mine(int size_hang, int size_lie, int mine,char inner_mine[][MAX_COL+2])
{
    int x, y;
    //������
    for (int i = 0; i < mine; i++) {
        x = rand() % size_hang + 1;
        y = rand() % size_lie + 1;
        if (i > 0 && inner_mine[x][y] == '*')
            i--;
        else
            inner_mine[x][y] = '*';
    }
    //�������з��׵�Ԫ�ؽ��и�ֵ
    for (int i = 1; i <= size_hang; i++) {
        for (int j = 1; j <= size_lie; j++) {
            if (inner_mine[i][j] != '*')
                inner_mine[i][j] = count_mine(inner_mine, i, j) + '0';
        }
    }
}

/*�ж���Ϸ�Ƿ����*/
int judge_end(int size_hang, int size_lie,int status[][MAX_COL + 2])
{
    int num = 0;
    for (int i = 1; i <= size_hang; i++) {
        for (int j = 1; j <= size_lie; j++) {
            if (status[i][j] == 0)   //��û�б��򿪣�Ҳû�б����
                num++;
        }
    }
    return num;  //����0˵�����еĸ���Ҫô����Ҫô�����
}