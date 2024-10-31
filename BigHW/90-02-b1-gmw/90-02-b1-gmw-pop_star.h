/* 大数据 2352847 张静敏 */
#pragma once

/*宏定义*/
#define length_max 10   //输入的行列数最大值
#define keyboard 1
#define mouse 2
#define right_left 1
#define up_down 2
/* 定义1-5的数字用何种形式显示在界面上（正常状态） */
const BLOCK_DISPLAY_INFO bdi_normal[] = {
	{0, -1, -1, "  "},  //0不显示，用空格填充即可
	{1, COLOR_HBLUE, COLOR_BLACK, "★"},
	{2, COLOR_HGREEN, COLOR_BLACK, "★"},
	{3, COLOR_HCYAN, COLOR_BLACK, "★"},
	{4, COLOR_HRED, COLOR_BLACK, "★"},
	{5, COLOR_HPINK, COLOR_BLACK, "★"},
	{-999, -1, -1, NULL} //判断结束条件为-999
};
/* 定义1-5的数字用何种形式显示在界面上（当前选择项状态+选中后关联项状态） */
const BLOCK_DISPLAY_INFO bdi_related[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},  //空白
	{1, COLOR_HBLUE, COLOR_WHITE, "★"},
	{2, COLOR_HGREEN, COLOR_WHITE, "★"},
	{3, COLOR_HCYAN, COLOR_WHITE, "★"},
	{4, COLOR_HRED, COLOR_WHITE, "★"},
	{5, COLOR_HPINK, COLOR_WHITE, "★"},
	{BDI_VALUE_END, -1, -1, NULL} //判断结束条件为-999
};
/* 定义1-5的数字用何种形式显示在界面上（选中状态） */
const BLOCK_DISPLAY_INFO bdi_selected[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},  //空白
	{1, COLOR_HBLUE, COLOR_HWHITE, "★"},
	{2, COLOR_HGREEN, COLOR_HWHITE, "★"},
	{3, COLOR_HCYAN, COLOR_HWHITE, "★"},
	{4, COLOR_HRED, COLOR_HWHITE, "★"},
	{5, COLOR_HPINK, COLOR_HWHITE, "★"},
	{BDI_VALUE_END, -1, -1, NULL} //判断结束条件为-999
};

/*工具函数*/
void find_able_star(int hang, int lie, int x, int y, int star_color[][length_max + 1], int status[][length_max + 1]);  //查找目标位置可连续消除的星星
int score_count(int hang, int lie, int status[][length_max + 1]);  //分数计算
void exchange_two(int hang, int m1, int m2, int a[][length_max + 1]);  //交换数组的两列
int ensure_to_end(int hang, int lie, int a[][length_max + 1]);  //确认一关的结束
int count_remain(int hang, int lie, int a[][length_max + 1]);  //计算最后剩余的星星数量
void count_blank_lie(int hang, int lie, int a[][length_max + 1], int blank_lie[]);  //计算每一列左边的空列数
void move_all_arr(int hang, int lie, int a[][length_max + 1]);  //数组整体平移
void mark_final(CONSOLE_GRAPHICS_INFO* const pCGI,int final_star, int* score);  //计算奖励得分
void keyboard_move(int* x, int* y, int keycode2, int hang, int lie, int star_color[][length_max + 1]);  //键盘变换
/*伪图形界面*/
void print_jia(CONSOLE_GRAPHICS_INFO* const pCGI);  //生成框架
void print_all_start(CONSOLE_GRAPHICS_INFO* const pCGI, int star_color[][length_max + 1], int status[][length_max + 1]); //画出全部的星星
void same_star_print(CONSOLE_GRAPHICS_INFO* const pCGI, int star_color[][length_max + 1], int status[][length_max + 1], int color);  //画出连续相同的星星
void clear_choose_star(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 1]);  //消除选中的星星
void fall_zero(CONSOLE_GRAPHICS_INFO* const pCGI, int star_color[][length_max + 1], int status[][length_max + 1]);  //非零值下落动画
void translation_zero(CONSOLE_GRAPHICS_INFO* const pCGI, int star_color[][length_max + 1], int status[][length_max + 1]);  //空列右移
void output_score(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 1], int* score);  //输出得分
void over_one_game(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 1], int star_color[][length_max + 1], int score);  //结束一关的游戏
void auto_game(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 1], int star_color[][length_max + 1], int score);  //游戏循环
