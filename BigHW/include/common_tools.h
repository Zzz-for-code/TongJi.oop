/* 大数据 2352847 张静敏 */
#pragma once

/*工具类*/
void clear();  //清理缓存区
void wait_for_enter();  //用于暂停
int input_hang_lie(int status, int hang_max, int hang_min, int lie_max, int lie_min);  //输入行、列数
int judge(int status[][11]);  //判断是否有可消除项
void find_again(int hang, int lie, int a[][11], int b[][11]);  //重新记录色块位置
void zero(int ball_color[][11], int status[][11]);  //可消除项归零
void end_game(); //小题结束继续按钮
void count_blank(int hang, int lie, int ball_color[][11], int blank[][11]); //计算每个球下方几个空格

/*内部数组相关*/
void creat_start(int hang, int lie, int ball_color[][11], int max); //生成初始数组
void start_status(int status[][11]);  //初始化status
void print_start(int hang, int lie, int op, int star_color[][11], int status[][11], const char str[]);  //打印数组
void fall_un_zero(int hang, int lie, int ball_color[][11]);  //非零值下落

/*伪图形界面*/
void print_line(int num, int length, const char start[], const char middle1[], const char middle2[], const char end[]);  //框架的每一行