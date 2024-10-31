/* 大数据 2352847 张静敏 */
#pragma once

/*宏定义*/
#define length_max 9   //输入的行列数最大值
/* 定义1-9的数字用何种形式显示在界面上（正常状态） */
const BLOCK_DISPLAY_INFO bdi_normal[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},  //0不显示，用空格填充即可
	{1, COLOR_HBLACK, -1, "〇"},
	{2, COLOR_YELLOW, -1, "〇"},
	{3, COLOR_HGREEN, -1, "〇"},
	{4, COLOR_HCYAN, -1, "〇"},
	{5, COLOR_HRED, -1, "〇"},
	{6, COLOR_HPINK, -1, "〇"},
	{7, COLOR_HYELLOW, -1, "〇"},
	{8, COLOR_CYAN, -1, "〇"},
	{9, COLOR_WHITE, -1, "〇"},
	{BDI_VALUE_END, -1, -1, NULL} //判断结束条件为-999
};
/* 定义1-9的数字用何种形式显示在界面上（选中状态） */
const BLOCK_DISPLAY_INFO bdi_selected[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},  //空白
	{1, COLOR_HBLACK, -1, "●"},
	{2, COLOR_YELLOW, -1, "●"},
	{3, COLOR_HGREEN, -1, "●"},
	{4, COLOR_HCYAN, -1, "●"},
	{5, COLOR_HRED, -1, "●"},
	{6, COLOR_HPINK, -1, "●"},
	{7, COLOR_HYELLOW, -1, "●"},
	{8, COLOR_CYAN, -1, "●"},
	{9, COLOR_WHITE, -1, "●"},
	{BDI_VALUE_END, -1, -1, NULL} //判断结束条件为-999
};
/* 定义1-9的数字用何种形式显示在界面上（可消除提示状态） */
const BLOCK_DISPLAY_INFO bdi_prompt[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},  //空白
	{1, COLOR_HBLACK, -1, "◎"},
	{2, COLOR_YELLOW, -1, "◎"},
	{3, COLOR_HGREEN, -1, "◎"},
	{4, COLOR_HCYAN, -1, "◎"},
	{5, COLOR_HRED, -1, "◎"},
	{6, COLOR_HPINK, -1, "◎"},
	{7, COLOR_HYELLOW, -1, "◎"},
	{8, COLOR_CYAN, -1, "◎"},
	{9, COLOR_WHITE, -1, "◎"},
	{BDI_VALUE_END, -1, -1, NULL} //判断结束条件为-999
};
/* 定义1-9的数字用何种形式显示在界面上（爆炸/消除状态） */
const BLOCK_DISPLAY_INFO bdi_exploded[] = {
	{BDI_VALUE_BLANK, -1, -1, "  "},  //空白
	{1, COLOR_HBLACK, -1, "¤"},
	{2, COLOR_YELLOW, -1, "¤"},
	{3, COLOR_HGREEN, -1, "¤"},
	{4, COLOR_HCYAN, -1, "¤"},
	{5, COLOR_HRED, -1, "¤"},
	{6, COLOR_HPINK, -1, "¤"},
	{7, COLOR_HYELLOW, -1, "¤"},
	{8, COLOR_CYAN, -1, "¤"},
	{9, COLOR_WHITE, -1, "¤"},
	{BDI_VALUE_END, -1, -1, NULL} //判断结束条件为-999
};

/*工具函数*/
void find_clear(int hang, int lie, int a[length_max + 2][length_max + 2], int b[length_max + 2][length_max + 2]); //寻找可消除项
void fill_zero(int hang, int lie, int ball_color[][length_max + 2]);  //新值填充
void remind_clear(int hang, int lie, int a[][length_max + 2], int b[][length_max + 2]);  //提示寻找可消除项
int count_score(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 2], int* p_score); //计算得分

/*与伪图形界面有关的函数*/
void draw_game_kuang(CONSOLE_GRAPHICS_INFO* const pCGI);  //生成游戏区域
void output_ball(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2]);  //填充球的颜色
void draw_able(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2]);  //画出可消除项
void clear_draw(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2]);  //消除可消除项
void fall_move(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2]);  //非零项下落
void fill_blank(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2]);  //零项填充新值
void output_remind(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2]);  //显示可消除项提示
void remind_to_zero(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2]);  //将可消除项提示归零
void calculate(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2], int* p_score);  //用于分数计算的循环
int find_place(CONSOLE_GRAPHICS_INFO* const pCGI,int* x1, int* y1, int status[][length_max + 2]);  //判断光标位置
void move_change(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2], int score);  //进行交换
void able_to_change(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2], int x1, int y1, int x2, int y2, int* p_score);  //判断是否可以交换
int able_to_end(CONSOLE_GRAPHICS_INFO* const pCGI, int status[][length_max + 2], int score);  //宣布游戏9结束
void autogame(CONSOLE_GRAPHICS_INFO* const pCGI, int ball_color[][length_max + 2], int status[][length_max + 2]);  //游戏版
