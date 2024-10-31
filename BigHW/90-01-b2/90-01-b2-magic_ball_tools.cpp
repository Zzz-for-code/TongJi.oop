/* ������ 2352847 �ž��� */
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

/*���������ͣ��Ҫ*/
void stop(int option)
{
    if (option == 0) {
        cout << "�밴���������...";
        char ch = _getch();
        cout << endl;
    }
    if (option == 1) {
        cout << endl;
        cout << "���س�������Ѱ�ҳ�ʼ��������Ĳ���...";
        while (_getch() != '\r');
    }
    if (option == 4 || option == 5) {
        cout << endl;
        cout << "���س�����ʾͼ��...";
        while (_getch() != '\r');
    }
}

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
    cout << *p_score << " �Ҽ��˳�)";
    return *p_score;
}

/*�ж��Ƿ���Խ���*/
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
            cout << "��";
            if (ball_color[y2][x2] == 9)
                cct_setcolor(5 + ball_color[y2][x2], COLOR_BLACK);
            else
                cct_setcolor(ball_color[y2][x2], COLOR_BLACK);
            cct_gotoxy(4 * x2 - 2, 2 * y2);
            Sleep(50);
            cout << "��";
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

/*������Ϸ9����*/
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
    if (num)   //˵�����п��ƶ���
        return 0;
    else {
        cct_gotoxy(0, 0);
        cout << setw(38) << " ";
        cct_gotoxy(0, 0);
        cout << "�޿��������Ϸ���������շ�����" << score;
        return 1;
    }
}
