/* 大数据 2352847 张静敏 */
#pragma once

/*宏定义*/
#define MAX_ROW 16
#define MAX_COL 30
#define VISITED 1
#define FLAGED -1
#define MINE 9
#define FLAG 10
const int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 }; // x方向的偏移量
const int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 }; // y方向的偏移量
//纯色块状态
const BLOCK_DISPLAY_INFO bdi_normal[] = {
		{BDI_VALUE_BLANK, COLOR_YELLOW, COLOR_YELLOW, NULL},  //0不显示，用空格填充即可
		{BDI_VALUE_END, -1, -1, NULL} //判断结束条件为-999
};
//被打开后的
const BLOCK_DISPLAY_INFO bdi_open[] = {
		{BDI_VALUE_BLANK, COLOR_WHITE, COLOR_WHITE, NULL},
		{1, COLOR_WHITE, COLOR_BLUE, NULL},
		{2, COLOR_WHITE, COLOR_GREEN, NULL},
		{3, COLOR_WHITE, COLOR_CYAN, NULL},
		{4, COLOR_WHITE, COLOR_RED, NULL},
		{5, COLOR_WHITE, COLOR_PINK, NULL},
		{6, COLOR_WHITE, COLOR_YELLOW, NULL},
		{7, COLOR_WHITE, COLOR_HBLUE, NULL},
		{8, COLOR_WHITE, COLOR_HGREEN, NULL},
		{MINE, COLOR_WHITE, COLOR_BLACK, "*"},
		{FLAG, COLOR_RED, COLOR_HBLACK, "#"},
		{BDI_VALUE_END, -1, -1, NULL} //判断结束条件为-999
};

/*工具函数*/
int input_game_level();  //输入游戏难度
void ensure_size_mine(int level, int* size_hang, int* size_lie, int* mine);  //确定区域大小和雷数
int count_mine(char inner_mine[][MAX_COL + 2], int x, int y);  //计算每个位置附近八个位置有几个雷
void creat_mine(int size_hang, int size_lie, int mine, char inner_mine[][MAX_COL + 2]);  //生成内部数组/*判断游戏是否结束*/
int judge_end(int size_hang, int size_lie, int status[][MAX_COL + 2]);  //判断游戏是否结束

/*伪图形界面相关*/
void draw_kuang(CONSOLE_GRAPHICS_INFO* const pCGI, int level, char inner_mine[][MAX_COL + 2]);  //画出框架
void auto_game(CONSOLE_GRAPHICS_INFO* const pCGI, int mine, char inner_mine[][MAX_COL + 2]);  //游戏版本
int open_enable(CONSOLE_GRAPHICS_INFO* const pCGI, int x, int y, char inner_mine[][MAX_COL + 2], int status[][MAX_COL + 2]);  //打开连续的区域