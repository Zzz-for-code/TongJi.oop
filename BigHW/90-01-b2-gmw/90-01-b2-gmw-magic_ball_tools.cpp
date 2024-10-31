/* 大数据 2352847 张静敏 */
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
int count_score(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 2], int* p_score)
{
    int i, j;
    for (i = 1; i <= pCGI->row_num; i++) {
        for (j = 1; j <= pCGI->col_num; j++) {
            if (status[i][j])
                (*p_score)++;
        }
    }
    char temp[256]; 
    sprintf(temp, "当前分数:%d 右键退出", *p_score);
    gmw_status_line(pCGI, TOP_STATUS_LINE, temp);
    return *p_score;
}