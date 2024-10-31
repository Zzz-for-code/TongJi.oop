/* 大数据 2352847 张静敏 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "../include/common_tools.h"
#include "../include/cmd_console_tools.h"
#include "90-01-b2-magic_ball.h"
using namespace std;

/*满足各类暂停需要*/
void stop(int option)
{
    if (option == 0) {
        cout << "请按任意键继续...";
        char ch = _getch();
        cout << endl;
    }
    if (option == 1) {
        cout << endl;
        cout << "按回车键进行寻找初始可消除项的操作...";
        while (_getch() != '\r');
    }
    if (option == 4 || option == 5) {
        cout << endl;
        cout << "按回车键显示图形...";
        while (_getch() != '\r');
    }
}

/*寻找可消除项*/
void find_clear(int hang, int lie, int a[length_max + 2][length_max + 2], int b[length_max + 2][length_max + 2])
{
    int i, j;
    start_status(b);
    for (i = 1; i <= hang; i++) {
        for (j = 1; j <= lie; j++) {
            if (a[i][j] == a[i][j + 1] && a[i][j] == a[i][j + 2]) {  //横向扫
                for (int n = 0; n < 3; n++)
                    b[i][j + n] = 1;
            }
            if (a[i][j] == a[i + 1][j] && a[i][j] == a[i + 2][j]) {  //横向扫
                for (int n = 0; n < 3; n++)
                    b[i + n][j] = 1;
            }
        }
    }
}

/*新值填充*/
void fill_zero(int hang, int lie, int ball_color[][length_max + 2])
{
    int i, j;
    for (i = 1; i <= hang; i++) {
        for (j = 1; j <= lie; j++)
            if (!ball_color[i][j])
                ball_color[i][j] = rand() % 9 + 1;
    }
}

/*提示寻找可消除项*/
void remind_clear(int hang, int lie, int a[][length_max + 2], int b[][length_max + 2])
{
    start_status(b);   //先初始化status
    int i, j;
    //横向扫
    for (i = 1; i <= hang; i++) {
        for (j = 1; j <= lie; j++) {
            //0x0情况
            if (a[i][j - 1] == a[i][j + 1]) {
                if (a[i - 1][j] == a[i][j - 1]) {   //0x0上
                    b[i][j] = 1;
                    b[i - 1][j] = 1;
                }
                if (a[i + 1][j] == a[i][j - 1]) {   //0x0下
                    b[i][j] = 1;
                    b[i + 1][j] = 1;
                }
            }
            //00x情况
            if (a[i][j] == a[i][j + 1] && j <= (lie - 2)) {
                if (a[i - 1][j + 2] == a[i][j]) {   //00x上
                    b[i][j + 2] = 1;
                    b[i - 1][j + 2] = 1;
                }
                if (a[i + 1][j + 2] == a[i][j]) {       //00x下
                    b[i][j + 2] = 1;
                    b[i + 1][j + 2] = 1;
                }
                if (a[i][j] == a[i][j + 3]) {    //00x0
                    b[i][j + 2] = 1;
                    b[i][j + 3] = 1;
                }
            }
            //x00情况
            if (a[i][j] == a[i][j + 1] && j > 1) {
                if (a[i - 1][j - 1] == a[i][j]) {   //x00上
                    b[i][j - 1] = 1;
                    b[i - 1][j - 1] = 1;
                }
                if (a[i + 1][j - 1] == a[i][j]) {       //x00下
                    b[i][j - 1] = 1;
                    b[i + 1][j - 1] = 1;
                }
                if (a[i][j] == a[i][j - 2]) {    //0x00
                    b[i][j - 2] = 1;
                    b[i][j - 1] = 1;
                }
            }
        }
    }
    //纵向扫
    for (i = 1; i <= lie; i++) {
        for (j = 1; j <= hang; j++) {
            //竖着的0x0
            if (a[j - 1][i] == a[j + 1][i]) {
                if (a[j - 1][i] == a[j][i - 1]) {   //竖着0x0左边
                    b[j][i - 1] = 1;
                    b[j][i] = 1;
                }
                if (a[j - 1][i] == a[j][i + 1]) {   //竖着0x0右边
                    b[j][i + 1] = 1;
                    b[j][i] = 1;
                }
            }
            //竖着00x
            if (a[j][i] == a[j + 1][i] && j <= (hang - 2)) {
                if (a[j + 3][i] == a[j][i]) {  //竖着00x0
                    b[j + 3][i] = 1;
                    b[j + 2][i] = 1;
                }
                if (a[j][i] == a[j + 2][i - 1]) {  //竖着00x左边
                    b[j + 2][i - 1] = 1;
                    b[j + 2][i] = 1;
                }
                if (a[j][i] == a[j + 2][i + 1]) {  //竖着00x右边
                    b[j + 2][i + 1] = 1;
                    b[j + 2][i] = 1;
                }
            }
            //竖着x00
            if (a[j][i] == a[j + 1][i] && j > 1) {
                if (a[j - 2][i] == a[j][i]) {  //竖着0x00
                    b[j - 2][i] = 1;
                    b[j - 1][i] = 1;
                }
                if (a[j - 1][i - 1] == a[j][i]) {  //竖着x00左边
                    b[j - 1][i - 1] = 1;
                    b[j - 1][i] = 1;
                }
                if (a[j - 1][i + 1] == a[j][i]) {  //竖着x00右边
                    b[j - 1][i + 1] = 1;
                    b[j - 1][i] = 1;
                }
            }
        }
    }
}

/*计算得分*/
int count_score(int hang, int lie, int status[][length_max + 2], int* p_score)
{
    int i, j;
    for (i = 1; i <= hang; i++) {
        for (j = 1; j <= lie; j++) {
            if (status[i][j])
                (*p_score)++;
        }
    }
    cct_gotoxy(25, 0);
    cout << *p_score << " 右键退出)";
    return *p_score;
}

/*判断是否可以交换*/
void able_to_change(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2], int x1, int y1, int x2, int y2, int* p_score)
{
    if ((fabs(x1 - x2) == 1 && y1 == y2) || (fabs(y1 - y2) == 1 && x1 == x2)) {
        int t = ball_color[y1][x1];
        ball_color[y1][x1] = ball_color[y2][x2];
        ball_color[y2][x2] = t;
        find_clear(hang, lie, ball_color, status);
        if (judge(status)) {
            if (ball_color[y1][x1] == 9)
                cct_setcolor(5 + ball_color[y1][x1], COLOR_BLACK);
            else
                cct_setcolor(ball_color[y1][x1], COLOR_BLACK);
            cct_gotoxy(4 * x1 - 2, 2 * y1);
            Sleep(50);
            cout << "○";
            if (ball_color[y2][x2] == 9)
                cct_setcolor(5 + ball_color[y2][x2], COLOR_BLACK);
            else
                cct_setcolor(ball_color[y2][x2], COLOR_BLACK);
            cct_gotoxy(4 * x2 - 2, 2 * y2);
            Sleep(50);
            cout << "○";
            cct_setcolor(COLOR_BLACK, COLOR_WHITE);
            remind_to_zero(hang, lie, ball_color, status);
            calculate(hang, lie, ball_color, status, p_score);

        }
        else {
            int t = ball_color[y1][x1];
            ball_color[y1][x1] = ball_color[y2][x2];
            ball_color[y2][x2] = t;
            remind_clear(hang, lie, ball_color, status);
        }
    }
}

/*宣布游戏9结束*/
int able_to_end(int hang, int lie, int status[][length_max + 2], int score)
{
    int num = 0;
    int i, j;
    for (i = 1; i <= hang; i++) {
        for (j = 1; j <= lie; j++) {
            if (status[i][j])
                num++;
        }
    }
    if (num)   //说明还有可移动项
        return 0;
    else {
        cct_gotoxy(0, 0);
        cout << setw(38) << " ";
        cct_gotoxy(0, 0);
        cout << "无可消除项，游戏结束！最终分数：" << score;
        return 1;
    }
}
