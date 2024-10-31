/* 大数据 2352847 张静敏 */
#pragma once

/*宏定义*/
#define length_max 9   //输入的行列数最大值

/*工具函数*/
void stop(int option);  //满足各类暂停需要
void find_clear(int hang, int lie, int a[length_max + 2][length_max + 2], int b[length_max + 2][length_max + 2]); //寻找可消除项
void fill_zero(int hang, int lie, int ball_color[][length_max + 2]);  //新值填充
int count_score(int hang, int lie, int status[][length_max + 2], int* p_score); //计算得分
void able_to_change(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2], int x1, int y1, int x2, int y2, int* p_score);  //判断是否可以交换
int able_to_end(int hang, int lie, int status[][length_max + 2], int score);  //宣布游戏9结束

/*与内部数组相关的函数*/
void cycle_1(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2], int option, int num);  //循环填充0，下落过程
void remind_clear(int hang, int lie, int a[][length_max + 2], int b[][length_max + 2]);  //提示寻找可消除项
void output_3(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2]); //选项3的输出

/*与伪图形界面有关的函数*/
void output_kuang(int hang, int lie, char kuang[][4], int option);  //生成框架
void output_ball(int hang, int lie, int ball_color[][length_max + 2], int option, int status[][length_max + 2]);  //填充球的颜色
void draw_able(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2]);  //画出可消除项
void clear_draw(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2]);  //消除可消除项
void fall_move(int hang, int lie, int ball_color[][length_max + 2]);  //非零项下落
void fill_blank(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2]);  //零项填充新值
void output_remind(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2]);  //显示可消除项提示
void remind_to_zero(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2]);  //将可消除项提示归零
void cycle_2(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2], int option);  //循环
void calculate(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2], int* p_score);  //用于分数计算的循环
int find_place(int* x1, int* y1, int hang, int lie, int status[][length_max + 2], int option);  //判断光标位置
void move_change(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2], int score);  //进行交换
void autogame(int hang, int lie, int ball_color[][length_max + 2], int status[][length_max + 2], int option);  //游戏版