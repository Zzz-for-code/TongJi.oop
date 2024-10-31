/* 大数据 2352847 张静敏 */
#pragma once

/* ------------------------------------------------------------------------------------------------------

	 本文件功能：
	1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp 能相互访问函数的函数声明
	2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量，个数不限
	3、可以参考 cmd_console_tools.h 的写法（认真阅读并体会）
   ------------------------------------------------------------------------------------------------------ */

   /*宏定义*/
#define length 120   //输出框的长度
#define width 40     //输出框的宽度
#define hang_4_heng 17   //菜单4横向输出的排数
#define hang_4_Y_tower 13   //菜单4纵向输出字母A的排数
#define lie_4_X_tower 11    //菜单4纵向输出字母A的列数
#define hang_Y_zhuzi  15    //第一个柱子图像的行数
#define lie_X_zhuzi  1     //第一个柱子图像的列数
#define lie_X_zhuzi_middle  12     //第一个柱子图像的中间的列数
#define distance 32  //柱子间差的列数
#define base_length 23//底座的长度
#define base_height 12//柱子的高度
#define diffirence 15  //4-8、9直接横向输出差的排数
#define Y_game 34   //游戏模式第一行输出的排数
#define X_game 60   //游戏模式输入参数的列数

/*与输入相关的函数*/
int input_n();
char input_src();
char input_dst(char src);
char input_tmp(char src, char dst);
int input_speed();
void input_all(int option, char& src, char& tmp, char& dst, int& n, int& speed);

/*递归函数Hanoi主体*/
void hanoi(int n, char src, char tmp, char dst, int option);   //递归主体
void output_realhanoi(int n, int num, char src, char tmp, char dst, int option);  //与不同输出有关

/*输出相关的函数*/
void output_8(int option, int n, int num, char src, char dst, int speed); //自动移动+横向+纵向
void output_7(int option, char src, char dst);  //第一次移动/盘子的移动
void output_6(int n, char src);  //在起始柱上画n个盘子
void output_5();   //画三个柱子
void output_4(int option, int status, int n, int num, char src, char dst, int speed);  //纵向+横向
void output_heng();  //横向输出
void output_start_shu(int status, int n, char src, char dst);  //纵向输出每个柱子盘子的编号

/*其他函数*/
void first(); //将全局变量归0
void start(int n, char src);  //初始化三个数组
void output_column(char ch);  //输出每个柱子的盘子编号
void move_top(char src, char dst);  //栈顶指针的变化
int time(int speed);  //延时参数
void clear(int status, char src);  //吃掉相应位置的数字
void print(int status, char src, char dst);  //在相应的位置打印相应的数字

/*与游戏模式相关的函数*/
void game(int n, char src, char dst);  // 游戏主要函数
void game_move(char src, char dst);  //游戏版的移动

