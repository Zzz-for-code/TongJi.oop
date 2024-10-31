/* 大数据 2352847 张静敏 */
#pragma once

/*宏定义*/
#define length_max 10   //输入的行列数最大值
#define keyboard 1
#define mouse 2
#define right_left 1
#define up_down 2

/*循环相关*/
void cycle_for_arr(int hang, int lie, int status[][length_max + 1], int star_color[][length_max + 1], char op,int score);  //数组循环
void choose_star_to_game(int hang, int lie, int status[][length_max + 1], int star_color[][length_max + 1], char option, int score);  //处理键盘和鼠标信息并进行游戏
void over_one_game(int im_x, int im_y, int hang, int lie, int status[][length_max + 1], int star_color[][length_max + 1], char option, int score);  //结束一关的游戏

/*工具函数*/
void add_to_input(int hang, int lie, int status[][length_max + 1], int star_color[][length_max + 1], char* x, int* y); //输入坐标
void find_able_star(int hang, int lie, int x, int y, int star_color[][length_max + 1], int status[][length_max + 1]);  //查找目标位置可连续消除的星星
char choose_YNQ(char x, int y);  //选择是否消除选中的相同值
int score_count(int hang, int lie, int status[][length_max + 1]);  //分数计算
void exchange_two(int hang, int m1, int m2, int a[][length_max + 1]);  //交换数组的两列
int ensure_to_end(int hang, int lie, int a[][length_max + 1]);  //确认一关的结束
int count_remain(int hang, int lie, int a[][length_max + 1]);  //计算最后剩余的星星数量
void count_blank_lie(int hang, int lie, int a[][length_max + 1], int blank_lie[]);  //计算每一列左边的空列数
void move_all_arr(int hang, int lie, int a[][length_max + 1]);  //数组整体平移
void output_add(int high, int width, int star_x, int star_y, int add_y, int star_color[][length_max + 1], int flag, char option);  //输出坐标和反显
void keyboard_move(int* x, int* y, int keycode2, int hang, int lie, int star_color[][length_max + 1]);  //键盘变换
int decide_to_change(int hang, int lie, int option, int high, int width, int MX, int MY, int old_x, int old_y, int old_mark, int old_color);  //判断鼠标移动的范围是否超出单个星星范围
void no_same(int& MX, int& MY, int& MAction, int& keycode1, int& keycode2, int word_y, int star_x, int star_y, int star_color);  //无相同值对应的输出
void mark_final(int final_star, int* score);  //计算奖励得分

/*伪图形界面*/
void print_jia(int hang, int lie, char option, char kuang[][4]);  //生成框架
void out_a_star(int start_x, int start_y, int bg_color, int fg_color);  //输出一个星星的图案
void print_all_start(int hang, int lie, int star_color[][length_max + 1], char option, int status[][length_max + 1]); //画出全部的星星
void same_star_print(int hang, int lie, int star_color[][length_max + 1], int option, int status[][length_max + 1], int color);  //画出连续相同的星星
void clear_choose_star(int hang, int lie, int option, int status[][length_max + 1]);  //消除选中的星星
void one_star_move(int choose, int star_x, int star_y, int hang, int lie, int star_color, int option);  //单个星星的移动——一格
void fall_zero(int hang, int lie, int star_color[][length_max + 1], int status[][length_max + 1], int option);  //非零值下落动画
void translation_zero(int hang, int lie, int star_color[][length_max + 1], int status[][length_max + 1], int option);  //空列右移
void output_score(int hang, int lie, int status[][length_max + 1], int* score);  //输出得分