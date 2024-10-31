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

/*Ѱ�ҿ�������*/
void find_clear(int hang, int lie, int a[length_max + 2][length_max + 2], int b[length_max + 2][length_max + 2])
{
    int i, j;
    start_status(b);
    for (i = 1; i <= hang; i++) {
        for (j = 1; j <= lie; j++) {
            if (a[i][j] == a[i][j + 1] && a[i][j] == a[i][j + 2]) {  //����ɨ
                for (int n = 0; n < 3; n++)
                    b[i][j + n] = 1;
            }
            if (a[i][j] == a[i + 1][j] && a[i][j] == a[i + 2][j]) {  //����ɨ
                for (int n = 0; n < 3; n++)
                    b[i + n][j] = 1;
            }
        }
    }
}

/*��ֵ���*/
void fill_zero(int hang, int lie, int ball_color[][length_max + 2])
{
    int i, j;
    for (i = 1; i <= hang; i++) {
        for (j = 1; j <= lie; j++)
            if (!ball_color[i][j])
                ball_color[i][j] = rand() % 9 + 1;
    }
}

/*��ʾѰ�ҿ�������*/
void remind_clear(int hang, int lie, int a[][length_max + 2], int b[][length_max + 2])
{
    start_status(b);   //�ȳ�ʼ��status
    int i, j;
    //����ɨ
    for (i = 1; i <= hang; i++) {
        for (j = 1; j <= lie; j++) {
            //0x0���
            if (a[i][j - 1] == a[i][j + 1]) {
                if (a[i - 1][j] == a[i][j - 1]) {   //0x0��
                    b[i][j] = 1;
                    b[i - 1][j] = 1;
                }
                if (a[i + 1][j] == a[i][j - 1]) {   //0x0��
                    b[i][j] = 1;
                    b[i + 1][j] = 1;
                }
            }
            //00x���
            if (a[i][j] == a[i][j + 1] && j <= (lie - 2)) {
                if (a[i - 1][j + 2] == a[i][j]) {   //00x��
                    b[i][j + 2] = 1;
                    b[i - 1][j + 2] = 1;
                }
                if (a[i + 1][j + 2] == a[i][j]) {       //00x��
                    b[i][j + 2] = 1;
                    b[i + 1][j + 2] = 1;
                }
                if (a[i][j] == a[i][j + 3]) {    //00x0
                    b[i][j + 2] = 1;
                    b[i][j + 3] = 1;
                }
            }
            //x00���
            if (a[i][j] == a[i][j + 1] && j > 1) {
                if (a[i - 1][j - 1] == a[i][j]) {   //x00��
                    b[i][j - 1] = 1;
                    b[i - 1][j - 1] = 1;
                }
                if (a[i + 1][j - 1] == a[i][j]) {       //x00��
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
    //����ɨ
    for (i = 1; i <= lie; i++) {
        for (j = 1; j <= hang; j++) {
            //���ŵ�0x0
            if (a[j - 1][i] == a[j + 1][i]) {
                if (a[j - 1][i] == a[j][i - 1]) {   //����0x0���
                    b[j][i - 1] = 1;
                    b[j][i] = 1;
                }
                if (a[j - 1][i] == a[j][i + 1]) {   //����0x0�ұ�
                    b[j][i + 1] = 1;
                    b[j][i] = 1;
                }
            }
            //����00x
            if (a[j][i] == a[j + 1][i] && j <= (hang - 2)) {
                if (a[j + 3][i] == a[j][i]) {  //����00x0
                    b[j + 3][i] = 1;
                    b[j + 2][i] = 1;
                }
                if (a[j][i] == a[j + 2][i - 1]) {  //����00x���
                    b[j + 2][i - 1] = 1;
                    b[j + 2][i] = 1;
                }
                if (a[j][i] == a[j + 2][i + 1]) {  //����00x�ұ�
                    b[j + 2][i + 1] = 1;
                    b[j + 2][i] = 1;
                }
            }
            //����x00
            if (a[j][i] == a[j + 1][i] && j > 1) {
                if (a[j - 2][i] == a[j][i]) {  //����0x00
                    b[j - 2][i] = 1;
                    b[j - 1][i] = 1;
                }
                if (a[j - 1][i - 1] == a[j][i]) {  //����x00���
                    b[j - 1][i - 1] = 1;
                    b[j - 1][i] = 1;
                }
                if (a[j - 1][i + 1] == a[j][i]) {  //����x00�ұ�
                    b[j - 1][i + 1] = 1;
                    b[j - 1][i] = 1;
                }
            }
        }
    }
}

/*����÷�*/
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
    sprintf(temp, "��ǰ����:%d �Ҽ��˳�", *p_score);
    gmw_status_line(pCGI, TOP_STATUS_LINE, temp);
    return *p_score;
}