/* 大数据 2352847 张静敏 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include "../include/common_tools.h"
#include "../include/cmd_console_tools.h"
#include "../include/cmd_gmw_tools.h"
#include "90-02-b2-mine_sweeper.h"

/*输入游戏难度*/
int input_game_level()
{
	int level; 
    cout << "请输入扫雷的等级（数字），简单\\一般\\困难（1\\2\\3）";
    cin >> level;
    while (cin.good() == 0 || level < 1 || level>3) {
        clear();
        cout << "请输入扫雷的等级（数字），简单\\一般\\困难（1\\2\\3）";
        cin >> level;
    }
    clear();
    return level;
}

/*确定区域大小和雷数*/
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

/*计算每个位置附近八个位置有几个雷*/
int count_mine(char inner_mine[][MAX_COL + 2], int x, int y)
{
    int num = 0;
    if (inner_mine[x - 1][y - 1] == '*')  //左上
        num++;
    if (inner_mine[x - 1][y] == '*')  //正上
        num++;
    if (inner_mine[x - 1][y + 1] == '*')  //右上
        num++;
    if (inner_mine[x][y - 1] == '*')  //正左
        num++;
    if (inner_mine[x][y + 1] == '*')  //正右
        num++;
    if (inner_mine[x + 1][y - 1] == '*')  //左下
        num++;
    if (inner_mine[x + 1][y] == '*')  //正下
        num++;
    if (inner_mine[x + 1][y + 1] == '*')  //右下
        num++;
    return num;
}

/*生成内部数组*/
void creat_mine(int size_hang, int size_lie, int mine,char inner_mine[][MAX_COL+2])
{
    int x, y;
    //生成雷
    for (int i = 0; i < mine; i++) {
        x = rand() % size_hang + 1;
        y = rand() % size_lie + 1;
        if (i > 0 && inner_mine[x][y] == '*')
            i--;
        else
            inner_mine[x][y] = '*';
    }
    //对数组中非雷的元素进行赋值
    for (int i = 1; i <= size_hang; i++) {
        for (int j = 1; j <= size_lie; j++) {
            if (inner_mine[i][j] != '*')
                inner_mine[i][j] = count_mine(inner_mine, i, j) + '0';
        }
    }
}

/*判断游戏是否结束*/
int judge_end(int size_hang, int size_lie,int status[][MAX_COL + 2])
{
    int num = 0;
    for (int i = 1; i <= size_hang; i++) {
        for (int j = 1; j <= size_lie; j++) {
            if (status[i][j] == 0)   //既没有被打开，也没有被标记
                num++;
        }
    }
    return num;  //返回0说明所有的格子要么被打开要么被标记
}