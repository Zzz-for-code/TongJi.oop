/* ������ 2352847 �ž��� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include <Windows.h>
#include "../include/cmd_console_tools.h"
using namespace std;

//������
/*��������*/
void clear()
{
    cin.clear();
    cin.ignore(2048, '\n');
}

/*������ͣ*/
void wait_for_enter() 
{
    cout << "�밴���������...";
    char ch = _getch();
    cout << endl;
}

/*������/����*/
int input_hang_lie(int status, int hang_max, int hang_min, int lie_max, int lie_min)
{
    int n;
    if (status)    //status=1,�������У�status=0����������
        cout << "����������(" << hang_min << "-" << hang_max << ")" << endl;
    else
        cout << "����������(" << lie_min << "-" << lie_max << ")" << endl;
    cin >> n;
    while (cin.good() == 0 || n < hang_min || n>hang_max) {
        clear();
        if (status)    //status=1,�������У�status=0����������
            cout << "����������(" << hang_min << "-" << hang_max << ")" << endl;
        else
            cout << "����������(" << lie_min << "-" << lie_max << ")" << endl;
        cin >> n;
    }
    while (cin.good() == 1 && n >= hang_min && n <= hang_max) {
        clear();
        break;
    }
    return n;
}

/*�ж��Ƿ��п�������*/
int judge(int status[][11])
{
    int num = 0;
    int i, j;
    for (i = 0; i < 11; i++) {
        for (j = 0; j < 11; j++) {
            if (status[i][j] != 0)
                num++;
        }
    }
    return num;
}

/*�����������*/
void zero(int ball_color[][11], int status[][11])
{
    int i, j;
    for (i = 1; i <= 10; i++) {
        for (j = 1; j <= 10; j++)
            if (status[i][j] == 1)
                ball_color[i][j] = 0;
    }
}

/*����ֵ����*/
void fall_un_zero(int hang, int lie, int ball_color[][11])
{
    int i, j, m;
    for (i = 1; i <= lie; i++) {
        for (j = 1; j <= hang; j++) {
            for (m = 1; m <= hang - j; m++) {
                if (ball_color[m + 1][i] == 0) {
                    int t = ball_color[m][i];
                    ball_color[m][i] = ball_color[m + 1][i];
                    ball_color[m + 1][i] = t;
                }
            }
        }
    }
}

/*���¼�¼ɫ��λ��*/
void find_again(int hang, int lie, int a[][11], int b[][11])
{
    int i, j;
    for (i = 1; i <= hang; i++) {
        for (j = 1; j <= lie; j++) {
            if (a[i][j])
                b[i][j] = 0;
            else
                b[i][j] = 1;
        }
    }
}

/*С�����������ť*/
void end_game()
{
    cout << endl;
    cout << "��С�������������End����...";
    cct_setcursor(CURSOR_VISIBLE_NORMAL);
    int x1, y1;
    cct_getxy(x1, y1);
    char str[10] = { 0 };
    while (1) {
        cct_gotoxy(x1, y1);
        for (int i = 0; i < 8; i++) {
            str[i] = _getche();
            if (str[i] == '\r')
                break;
            if (str[i] == '\b') {
                int X, Y;
                cct_getxy(X, Y);
                cct_gotoxy(X + 1, Y);
                i -= 1;
            }
        }
        int m = 0;
        if (str[0] == 'E' || str[0] == 'e')
            m++;
        if (str[1] == 'N' || str[1] == 'n')
            m++;
        if (str[2] == 'D' || str[2] == 'd')
            m++;
        if (m == 3)
            break;
        else {
            cct_gotoxy(0, y1 + 1);
            cout << "�����������������";
            cct_gotoxy(x1, y1);
            cout << setw(10) << " ";
            cct_gotoxy(x1, y1);
        }
    }
}

/*����ÿ�����·������ո�*/
void count_blank(int hang, int lie, int ball_color[][11], int blank[][11])
{
    int i, j, m;
    for (i = 1; i <= hang; i++) {
        for (j = 1; j <= lie; j++) {
            blank[i][j] = 0;
        }
    }
    for (i = 1; i <= hang; i++) {
        for (j = 1; j <= lie; j++) {
            for (m = i + 1; m <= hang; m++) {
                if (ball_color[m][j] == 0)
                    blank[i][j]++;
            }
        }
    }
}

//�ڲ��������
/*���ɳ�ʼ����*/
void creat_start(int hang, int lie, int ball_color[][11],int max)
{
    int i, j;
    for (i = 0; i < 11; i++) {  //�ȳ�ʼ��
        for (j = 0; j < 11; j++)
            ball_color[i][j] = 0;
    }
    for (i = 1; i <= hang; i++) {
        for (j = 1; j <= lie; j++)
            ball_color[i][j] = rand() % max + 1;
    }
}

/*��ʼ��status*/
void start_status(int status[][11])
{
    int i, j;
    for (i = 0; i < 11; i++) {
        for (j = 0; j < 11; j++)
            status[i][j] = 0;
    }
}

/*��ӡ����*/
void print_start(int hang, int lie, int op, int star_color[][11], int status[][11],const char str[])
{
    cout << endl << str << endl;
    int i, j;
    cout << setw(3) << "|";
    for (i = 0; i < lie; i++)
        cout << setw(3) << i;
    cout << endl;
    cout << "--+";
    for (i = 1; i <= lie; i++)
        cout << "---";
    cout << endl;
    for (i = 1; i <= hang; i++) {
        cout << char(i - 1 + 'A') << setw(2) << "|";
        for (j = 1; j <= lie; j++) {
            if (op) {
                if (!status[i][j])
                    cout << setw(3) << status[i][j];
                else
                    cout << setw(3) << "*";
            }
            else {
                if (status[i][j]) {
                    cout << "  ";
                    cct_setcolor(COLOR_HYELLOW, COLOR_BLUE);
                    cout << star_color[i][j];
                    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                }
                else
                    cout << setw(3) << star_color[i][j];
            }
        }
        cout << endl;
    }
}


//αͼ�λ�����
/*��ܵ�ÿһ��*/
void print_line(int num,int length, const char start[], const char middle1[], const char middle2[], const char end[])
{
    cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
    cout << start;
    Sleep(1);
    for (int i = 0; i < length; i++) {
        if (i % num == 0 && i != 0)
            cout << middle2;
        cout << middle1;  //�����ո�
    }
    cout << end << endl;
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}