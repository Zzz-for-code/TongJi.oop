/* 大数据 2352847 张静敏 */
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "../include/common_tools.h"
#include "../include/cmd_console_tools.h"
#include "90-01-b1-hanoi.h"
using namespace std;
int num = 0;  //记录步数
int top[3] = { 0 };  //三个塔的栈顶指针
int tower[3][10] = { 0 };  //前者表示盘子，后者表示层数，值表示盘子编号
int speed;  //表示延时设定
/* ----------------------------------------------------------------------------------

     本文件功能：
    1、存放被 hanoi_main.cpp 中根据菜单返回值调用的各菜单项对应的执行函数

     本文件要求：
    1、不允许定义外部全局变量（const及#define不在限制范围内）
    2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
    3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
    4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------------------------------------------------- */

   /*输入n*/
int input_n()
{
    int n;
    cout << "请输入汉诺塔的层数(1-10)" << endl;
    cin >> n;
    while (cin.good() == 0 || n < 1 || n>10) {
        cin.clear();
        cin.ignore(2048, '\n');
        cout << "请输入汉诺塔的层数(1-10)" << endl;
        cin >> n;
    }
    while (cin.good() == 1 && n >= 1 && n <= 10) {
        cin.clear();
        cin.ignore(2048, '\n');
        break;
    }
    return n;
}

/*输入初始柱src*/
char input_src()
{
    char src;
    cout << "请输入起始柱(A-C)" << endl;
    cin >> src;
    if (src == 'a' || src == 'b' || src == 'c')
        src += 'A' - 'a';
    while (cin.good() == 0 || (src != 'A' && src != 'B' && src != 'C')) {
        cin.clear();
        cin.ignore(2048, '\n');
        cout << "请输入起始柱(A-C)" << endl;
        cin >> src;
        if (src == 'a' || src == 'b' || src == 'c')
            src += 'A' - 'a';
    }
    while (cin.good() == 1 && (src == 'A' || src == 'B' || src == 'C')) {
        cin.clear();
        cin.ignore(2048, '\n');
        break;
    }
    return src;
}

/*输入目标柱dst*/
char input_dst(char src)
{
    char dst;
    cout << "请输入目标柱(A-C)" << endl;
    cin >> dst;
    if (dst == 'a' || dst == 'b' || dst == 'c')
        dst += 'A' - 'a';
    while (cin.good() == 0 || (dst != 'A' && dst != 'B' && dst != 'C') || dst == src) {
        cin.clear();
        cin.ignore(2048, '\n');
        if (dst == src) {
            cout << "目标柱(" << dst << ")不能与起始柱(" << src << ")相同" << endl;
        }
        cout << "请输入目标柱(A-C)" << endl;
        cin >> dst;
        if (dst == 'a' || dst == 'b' || dst == 'c')
            dst += 'A' - 'a';
    }
    while (cin.good() == 1 && (dst == 'A' || dst == 'B' || dst == 'C') && dst != src && dst != (src - 'A' + 'a')) {
        cin.clear();
        cin.ignore(2048, '\n');
        break;
    }
    return dst;
}

/*判断中间柱tmp*/
char input_tmp(char src, char dst)
{
    char tmp = 0;
    if ((src == 'A') && (dst == 'B') || (src == 'B') && (dst == 'A'))
        tmp = char('C');
    if ((src == 'A') && (dst == 'C') || (src == 'C') && (dst == 'A'))
        tmp = char('B');
    if (((src == 'C') && (dst == 'B')) || ((src == 'B') && (dst == 'C')))
        tmp = char('A');
    return tmp;
}

/*速度参数输入*/
int input_speed()
{
    cout << "请输入移动速度(0-5：0-按回车单步演示 1-延时最长 5-延时最短)";
    cin >> speed;
    while (cin.good() == 0 || speed < 0 || speed>5) {
        cin.clear();
        cin.ignore(2048, '\n');
        cout << "请输入移动速度(0-5：0-按回车单步演示 1-延时最长 5-延时最短)";
        cin >> speed;
    }
    while (cin.good() == 1 && speed >= 0 && speed <= 5) {
        cin.clear();
        cin.ignore(2048, '\n');
        break;
    }
    return speed;
}

/*输入汇总*/
void input_all(int option, char& src, char& tmp, char& dst, int& n, int& speed)
{
    n = input_n();
    src = input_src();
    dst = input_dst(src);
    tmp = input_tmp(src, dst);
    if (option == 4 || option == 8)
        speed = input_speed();
}

/*将全局变量归0*/
void first()
{
    int i, j;
    num = 0;
    speed = 0;
    for (i = 0; i < 3; i++)
        top[i] = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 10; j++)
            tower[i][j] = 0;
    }
}

/*hanoi递归函数主体*/
void hanoi(int n, char src, char tmp, char dst, int option)
{
    if (n == 1) {
        num++;
        output_realhanoi(n, num, src, tmp, dst, option);
        return;
    }
    if (n > 1) {
        hanoi(n - 1, src, dst, tmp, option);
        num++;
        output_realhanoi(n, num, src, tmp, dst, option);
        hanoi(n - 1, tmp, src, dst, option);
    }
}

/*输出hanoi*/
void output_realhanoi(int n, int num, char src, char tmp, char dst, int option)
{
    if (option == 1)
        cout << n << "# " << src << "---->" << dst << endl;
    if (option == 2)
        cout << "第" << setw(4) << num << " 步(" << setw(2) << n << "#: " << src << "-->" << dst << ")" << endl;
    if (option == 3) {
        cout << "第" << setw(4) << num << " 步(" << setw(2) << n << "#: " << src << "-->" << dst << ") ";
        move_top(src, dst);
        output_heng();
    }
    if (option == 4)
        output_4(4, 0, n, num, src, dst, speed);
    if (option == 8)
        output_8(option, n, num, src, dst, speed);
}

/*自动移动+横向+纵向*/
void output_8(int option, int n, int num, char src, char dst, int speed)
{
    if (speed == 0)
        while (_getch() != '\r');
    output_7(option, src, dst);
    output_4(8, diffirence, n, num, src, dst, speed);
}

/*第一次移动/盘子的移动*/
void output_7(int option, char src, char dst)
{
    int i;
    int x = top[src - 'A'];
    int y = top[dst - 'A'];
    int m = (int)(dst - src);
    //上移
    for (i = 0; i < base_height + 2 - x; i++) {
        if (option == 8 && speed != 0)
            time(speed);
        else
            Sleep(20);
        cct_showch(lie_X_zhuzi_middle + (src - 'A') * distance - tower[src - 'A'][x - 1], hang_Y_zhuzi - x - i, ' ', COLOR_BLACK, COLOR_BLACK, 2 * tower[src - 'A'][x - 1] + 1);  //清理
        if (i != base_height + 1 - x)
            cct_showch(lie_X_zhuzi_middle + (src - 'A') * distance, hang_Y_zhuzi - x - i, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);  //柱子重新填充黄色
        cct_showch(lie_X_zhuzi_middle + (src - 'A') * distance - tower[src - 'A'][x - 1], hang_Y_zhuzi - x - 1 - i, ' ', tower[src - 'A'][x - 1], tower[src - 'A'][x - 1], 2 * tower[src - 'A'][x - 1] + 1); //填充颜色
    }
    //平移
    for (i = 0; i < fabs(dst - src) * distance; i++) {
        if (option == 8 && speed != 0)
            time(speed);
        else
            Sleep(20);
        if (m > 0) {    //右移
            cct_showch(lie_X_zhuzi_middle + (src - 'A') * distance - tower[src - 'A'][x - 1] + i, 1, ' ', COLOR_BLACK, COLOR_BLACK, 1);  //清理
            cct_showch(lie_X_zhuzi_middle + (src - 'A') * distance - tower[src - 'A'][x - 1] + i + (2 * tower[src - 'A'][x - 1] + 1), 1, ' ', tower[src - 'A'][x - 1], tower[src - 'A'][x - 1], 1);  //填充颜色
        }
        else {          //左移
            cct_showch(lie_X_zhuzi_middle + (src - 'A') * distance + tower[src - 'A'][x - 1] - i, 1, ' ', COLOR_BLACK, COLOR_BLACK, 1);  //清理
            cct_showch(lie_X_zhuzi_middle + (src - 'A') * distance + tower[src - 'A'][x - 1] - i - (2 * tower[src - 'A'][x - 1] + 1), 1, ' ', tower[src - 'A'][x - 1], tower[src - 'A'][x - 1], 1);  //填充颜色
        }
    }
    //下移
    for (i = 0; i < base_height + 1 - y; i++) {
        if (option == 8 && speed != 0)
            time(speed);
        else
            Sleep(20);
        cct_showch(lie_X_zhuzi_middle + (dst - 'A') * distance - tower[src - 'A'][x - 1], 1 + i, ' ', COLOR_BLACK, COLOR_BLACK, 2 * tower[src - 'A'][x - 1] + 1);  //清理
        if (i > 1 && i < base_height + 1 - y)
            cct_showch(lie_X_zhuzi_middle + (dst - 'A') * distance, 1 + i, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);  //柱子重新填充黄色
        cct_showch(lie_X_zhuzi_middle + (dst - 'A') * distance - tower[src - 'A'][x - 1], 2 + i, ' ', tower[src - 'A'][x - 1], tower[src - 'A'][x - 1], 2 * tower[src - 'A'][x - 1] + 1); //填充颜色
    }
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/*在起始柱上画n个盘子*/
void output_6(int n, char src)
{
    output_5();
    int i;
    for (i = 0; i < top[src - 'A']; i++) {
        Sleep(30);
        cct_showch(lie_X_zhuzi_middle + (src - 'A') * distance - tower[src - 'A'][i], hang_Y_zhuzi - 1 - i, ' ', tower[src - 'A'][i], tower[src - 'A'][i], 2 * tower[src - 'A'][i] + 1);
    }
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/*画柱子*/
void output_5()
{
    cct_setcursor(CURSOR_INVISIBLE);
    int i, j;
    for (i = 0; i <= 2 * distance; i += distance)
        cct_showch(lie_X_zhuzi + i, hang_Y_zhuzi, ' ', COLOR_HYELLOW, COLOR_HYELLOW, base_length);
    for (j = 0; j < base_height; j++) {
        Sleep(30);
        cct_setcursor(CURSOR_INVISIBLE);
        cct_showch(lie_X_zhuzi_middle, hang_Y_zhuzi - 1 - j, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
        cct_showch(lie_X_zhuzi_middle + distance, hang_Y_zhuzi - 1 - j, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
        cct_showch(lie_X_zhuzi_middle + 2 * distance, hang_Y_zhuzi - 1 - j, ' ', COLOR_HYELLOW, COLOR_HYELLOW, 1);
    }
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/*纵向+横向*/
void output_4(int option, int status, int n, int num, char src, char dst, int speed)
{
    int ms;
    ms = time(speed);
    if (speed == 0 && option != 8)
        while (_getch() != '\r');  //回车单步演示
    if (speed != 0)
        Sleep(ms);
    cct_setcursor(CURSOR_INVISIBLE);
    clear(status, src);
    print(status, src, dst);
    move_top(src, dst);
    cct_gotoxy(0, hang_4_heng + status);
    cout << "第" << setw(4) << num << " 步(" << setw(2) << n << "#: " << src << "-->" << dst << ") ";
    output_heng();
}

/*横向输出*/
void output_heng()
{
    cout << " A:";
    output_column('A');
    cout << "B:";
    output_column('B');
    cout << "C:";
    output_column('C');
    cout << endl;
}

/*初始化三个数组*/
void start(int n, char src)
{
    int i;
    top[src - 'A'] = n;
    for (i = 0; i < n; i++)
        tower[src - 'A'][i] = n - i;
}

/*输出每个柱子的盘子编号*/
void output_column(char ch)
{
    int i, j = 21;
    for (i = 0; i < top[ch - 'A']; i++) {
        cout << setw(2) << tower[ch - 'A'][i];
        j -= 2;
    }
    for (i = 0; i < j; i++)
        cout << " ";
}

/*纵向输出初始状态每个柱子盘子的编号*/
void output_start_shu(int status, int n, char src, char dst)
{
    int i;
    cct_gotoxy(lie_4_X_tower - 2, hang_4_Y_tower - 1 + status);
    cout << "=========================";
    cct_gotoxy(lie_4_X_tower, hang_4_Y_tower + status);
    cout << "A         B         C" << endl;
    for (i = 0; i < top[src - 'A']; i++) {
        cct_gotoxy(lie_4_X_tower - 1 + 10 * (src - 'A'), hang_4_Y_tower - 2 - i + status);
        cout << setw(2) << tower[src - 'A'][i];
    }
    cct_gotoxy(0, hang_4_heng + status);
    cout << "初始: ";
    output_heng();
}

/*吃掉相应位置的数字*/
void clear(int status, char src)
{
    int x = (int)src - 'A';
    cct_gotoxy(lie_4_X_tower - 1 + 10 * x, hang_4_Y_tower - 1 - top[x] + status);
    cout << "  ";   //两个空格
}

/*在相应的位置打印相应的数字*/
void print(int status, char src, char dst)
{
    int x = (int)dst - 'A';
    cct_gotoxy(lie_4_X_tower - 1 + 10 * x, hang_4_Y_tower - 2 - top[x] + status);
    cout << setw(2) << tower[src - 'A'][top[src - 'A'] - 1];
}

/*栈顶指针与栈顶的变化*/
void move_top(char src, char dst)
{
    int x = tower[src - 'A'][--top[src - 'A']];
    tower[src - 'A'][top[src - 'A']] = 0; //src顶端置0
    tower[dst - 'A'][top[dst - 'A']++] = x; //dst顶端为src顶端
}

/*延时参数*/
int time(int speed)
{
    int time;
    time = 25 * (5 - speed);
    return time;
}

/*游戏模式*/
void game(int n, char src, char dst)
{
    cct_gotoxy(0, Y_game);
    cout << "请输入移动的柱号(命令形式：AC=A顶端的盘子移动到C，Q=退出) ：";
    while (1) {
        cct_setcursor(CURSOR_VISIBLE_NORMAL);
        char src1 = 'A', dst1 = 'A', input[20];
        int i = 1;
        while (1) {
            for (i = 0; i < 20; i++) {
                input[i] = _getche();
                if (input[i] == '\r')
                    break;
                if (input[i] == '\b') {
                    int X, Y;
                    cct_getxy(X, Y);
                    cct_gotoxy(X + 1, Y);
                    i -= 1;
                }
            }
            if (input[0] == 'a' || input[0] == 'b' || input[0] == 'c')
                input[0] += 'A' - 'a';
            if (input[1] == 'a' || input[1] == 'b' || input[1] == 'c')
                input[1] += 'A' - 'a';
            if (i == 2 && (input[0] == 'A' || input[0] == 'B' || input[0] == 'C') && (input[1] == 'A' || input[1] == 'B' || input[1] == 'C') && input[0] != input[1]) {
                src1 = input[0];
                dst1 = input[1];
                cct_setcursor(CURSOR_INVISIBLE);
                game_move(src1, dst1);
                break;
            }
            if (i == 1 && (input[0] == 'Q' || input[0] == 'q')) {
                src1 = 'Q';
                break;
            }
            else {
                cct_gotoxy(X_game, Y_game);
                cout << setw(i + 1) << " ";
                cct_gotoxy(X_game, Y_game);
            }
        }
        if (src1 == 'Q' || top[dst - 'A'] == n) {
            cct_gotoxy(0, Y_game + 1);
            cout << "游戏中止!!!!!" << endl;
            return;
        }
    }
}

/*游戏版的移动*/
void game_move(char src, char dst)
{
    if (top[src - 'A'] == 0) {
        cct_gotoxy(0, Y_game + 1);
        cout << "源柱为空！";
        Sleep(1000);
        cct_gotoxy(0, Y_game + 1);
        cout << setw(10) << " ";
        cct_gotoxy(X_game, Y_game);
        cout << setw(20) << " ";
        cct_gotoxy(X_game, Y_game);
    }
    else {
        int k;
        if (top[dst - 'A'] == 0)
            k = 11;          //若目标柱什么也没有，则任何盘子均可压上去
        else
            k = tower[dst - 'A'][top[dst - 'A'] - 1];
        if (tower[src - 'A'][top[src - 'A'] - 1] < k) {
            num++;
            output_7(0, src, dst);
            output_4(9, diffirence, tower[src - 'A'][top[src - 'A'] - 1], num, src, dst, 3);
            cct_gotoxy(X_game, Y_game);
            cout << setw(20) << " ";
            cct_gotoxy(X_game, Y_game);
        }
        else {
            cct_gotoxy(0, Y_game + 1);
            cout << "大盘压小盘，非法移动！";
            Sleep(1000);
            cct_gotoxy(0, Y_game + 1);
            cout << setw(22) << " ";
            cct_gotoxy(X_game, Y_game);
            cout << setw(20) << " ";
            cct_gotoxy(X_game, Y_game);
        }
    }
}
