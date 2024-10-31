/* 2352847 张静敏 大数据 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <conio.h>
#include <string>
#include <Windows.h>
#include "../include/cmd_console_tools.h"
#include "../include/cmd_gmw_tools.h"
using namespace std;

/* --------------------------------------------------
		此处可以给出需要的静态全局变量（尽可能少，最好没有）、静态全局只读变量/宏定义（个数不限）等
   -------------------------------------------------- */

   /* --------------------------------------------------
		   此处可以给出需要的内部辅助工具函数
		   1、函数名不限，建议为 gmw_inner_*
		   2、个数不限
		   3、必须是static函数，确保只在本源文件中使用
	  -------------------------------------------------- */
/*处理输入中文制表符的错误*/
static void gmw_inner_deal_Chinese_character(char* target,const char* str)
{
	if (str[2] != '\0') {
		char s[3] = { str[0],str[1],'\0' };
		strcpy(target, s);
	}
	else if (str == NULL) {
		char s[3] = "  ";
		strcpy(target, s);
	}
	else if (str[1] == '\0') {
		char s[3] = { str[0],' ','\0' };
		strcpy(target, s);
	}
	else {
		char s[3] = { str[0],str[1],'\0' };
		strcpy(target, s);
	}
}

/*打印框架的一行*/
static void gmw_inner_print_every_line_of_kuang(const CONSOLE_GRAPHICS_INFO* const pCGI, const char* left, const char* right, const char* normal, const char* separator)
{
	int x, y;
	cct_getxy(x, y);
	if (y == pCGI->start_y)
		cct_showstr(x, y, left, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	else
		cct_showstr(x + pCGI->start_x, y, left, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	cct_getxy(x, y);
	for (int i = 1; i <= pCGI->col_num; i++) {
		for (int j = 1; j <= pCGI->CFI.block_width / 2; j++) {
			cct_showstr(x, y, normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			cct_getxy(x, y);
		}
		if (pCGI->CFI.separator && i != pCGI->col_num) {
			Sleep(pCGI->delay_of_draw_frame);
			cct_showstr(x, y, separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			cct_getxy(x, y);
		}
	}
	Sleep(pCGI->delay_of_draw_frame);
	cct_showstr(x, y, right, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);
	cout << endl;
}

/*打印整个框架*/
static void gmw_inner_print_all_kuang(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	//画列标
	if (pCGI->draw_frame_with_col_no) {
		for (int i = 0; i < pCGI->col_num; i++) {
			char str[3] = { 0 };
			if (i >= 0 && i <= 9)
				str[0] = '0' + i;
			else if (i > 99)
				strcpy(str, "**");
			else {
				str[0] = '0' + i / 10;
				str[1] = '0' + i % 10;
			}
			cct_showstr(pCGI->start_x + 1 + pCGI->CFI.block_width / 2 + i * pCGI->CFI.bwidth, pCGI->start_y - 1, str, pCGI->area_bgcolor, pCGI->area_fgcolor);
		}
	}
	cct_gotoxy(pCGI->start_x, pCGI->start_y);
	gmw_inner_print_every_line_of_kuang(pCGI, pCGI->CFI.top_left, pCGI->CFI.top_right, pCGI->CFI.h_normal, pCGI->CFI.h_top_separator);
	for (int i = 1; i <= pCGI->row_num; i++) {
		for (int j = 1; j <= pCGI->CFI.block_high; j++)
			gmw_inner_print_every_line_of_kuang(pCGI, pCGI->CFI.v_normal, pCGI->CFI.v_normal, "  ", pCGI->CFI.v_normal);
		if (pCGI->CFI.separator && i != pCGI->row_num)
			gmw_inner_print_every_line_of_kuang(pCGI, pCGI->CFI.v_left_separator, pCGI->CFI.v_right_separator, pCGI->CFI.h_normal, pCGI->CFI.mid_separator);
	}
	gmw_inner_print_every_line_of_kuang(pCGI, pCGI->CFI.lower_left, pCGI->CFI.lower_right, pCGI->CFI.h_normal, pCGI->CFI.h_lower_separator);
}

/*具体的打印一个色块*/
static void gmw_inner_a_block(const CONSOLE_GRAPHICS_INFO* const pCGI, int start_x, int start_y, int bgcolor, int fgcolor, char* content)
{
	//边框
	char top_left[CBI_LEN];			// "╔"
	char lower_left[CBI_LEN];		// "╚"
	char top_right[CBI_LEN];			// "╗"
	char lower_right[CBI_LEN];		// "╝"
	char h_normal[CBI_LEN];			// "═"	//Horizontal
	char v_normal[CBI_LEN];			// "║"	//Vertical
	strcpy(top_left, pCGI->CBI.block_border == true ? pCGI->CBI.top_left : "  ");
	strcpy(lower_left, pCGI->CBI.block_border == true ? pCGI->CBI.lower_left : "  ");
	strcpy(top_right, pCGI->CBI.block_border == true ? pCGI->CBI.top_right : "  ");
	strcpy(lower_right, pCGI->CBI.block_border == true ? pCGI->CBI.lower_right : "  ");
	strcpy(h_normal, pCGI->CBI.block_border == true ? pCGI->CBI.h_normal : "  ");
	strcpy(v_normal, pCGI->CBI.block_border == true ? pCGI->CBI.v_normal : "  ");
	int x, y;
	int left_blank = (pCGI->CFI.block_width - 4 * pCGI->CBI.block_border) / 2 - (strlen(content) + 1) / 2;
	int right_blank = pCGI->CFI.block_width - 4 * pCGI->CBI.block_border - left_blank - strlen(content);
	if (pCGI->CFI.block_high == 1)
		cct_showstr(start_x, start_y, content, bgcolor, fgcolor);
	else if (pCGI->CFI.block_high == 2) {
		cct_showch(start_x, start_y, ' ', bgcolor, fgcolor, pCGI->CFI.block_width);  //第一排
		cct_showch(start_x, start_y + 1, ' ', bgcolor, fgcolor, left_blank);
		cct_getxy(x, y);
		cct_showstr(x, y, content, bgcolor, fgcolor);
		cct_getxy(x, y);
		cct_showch(x, y, ' ', bgcolor, fgcolor, right_blank);
		cct_getxy(x, y);
	}
	else {
		//首排
		Sleep(pCGI->delay_of_draw_block);
		cct_showstr(start_x, start_y, top_left, bgcolor, fgcolor);
		cct_getxy(x, y);
		for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++) {
			cct_showstr(x, y, h_normal, bgcolor, fgcolor);
			cct_getxy(x, y);
		}
		cct_showstr(x, y, top_right, bgcolor, fgcolor);
		cct_getxy(x, y);
		y++;

		//中间
		for (int i = 0; i < (pCGI->CFI.block_high - 2); i++) {
			Sleep(pCGI->delay_of_draw_block);
			cct_showstr(start_x, y, v_normal, bgcolor, fgcolor);
			cct_getxy(x, y);
			if (i == (pCGI->CFI.block_high - 2)/2) {
				cct_showch(x, y, ' ', bgcolor, fgcolor, left_blank);
				cct_getxy(x, y);
				cct_showstr(x, y, content, bgcolor, fgcolor);
				cct_getxy(x, y);
				cct_showch(x, y, ' ', bgcolor, fgcolor, right_blank);
				cct_getxy(x, y);
			}
			else {
				cct_showch(x, y, ' ', bgcolor, fgcolor, (pCGI->CFI.block_width - 4));
				cct_getxy(x, y);
			}
			cct_showstr(x, y, v_normal, bgcolor, fgcolor);
			cct_getxy(x, y);
			y++;
		}

		//最后一排
		Sleep(pCGI->delay_of_draw_block);
		cct_showstr(start_x, y, lower_left, bgcolor, fgcolor);
		cct_getxy(x, y);
		for (int i = 0; i < (pCGI->CFI.block_width - 4) / 2; i++) {
			cct_showstr(x, y, h_normal, bgcolor, fgcolor);
			cct_getxy(x, y);
		}
		cct_showstr(x, y, lower_right, bgcolor, fgcolor);
		cct_getxy(x, y);
	}
}

/*根据传入的左上角x、y打印色块*/
static int gmw_inner__draw_block_by_xy(const CONSOLE_GRAPHICS_INFO* const pCGI, const int x, const int y, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//色块颜色
	int bgcolor, fgcolor;
	bgcolor = pCGI->area_bgcolor;
	fgcolor = pCGI->area_fgcolor;
	//色块中心图案
	char content[10] = { 0 };
	for (int i = 0; bdi[i].value != BDI_VALUE_END; i++) {
		if (bdi_value == bdi[i].value) {
			//色块颜色
			bgcolor = (bdi[i].bgcolor == -1 ? pCGI->CFI.bgcolor : bdi[i].bgcolor);
			fgcolor = (bdi[i].fgcolor == -1 ? pCGI->CFI.fgcolor : bdi[i].fgcolor);
			if (bdi[i].content == NULL)
				sprintf(content, "%d", bdi_value);
			else
				strcpy(content, bdi[i].content);
			break;
		}
	}
	/*打印一个色块*/
	if (bdi_value != BDI_VALUE_BLANK)
		gmw_inner_a_block(pCGI, x, y, bgcolor, fgcolor, content);
	else {
		for (int i = 0; i < pCGI->CFI.block_high; i++) {
			Sleep(2 * pCGI->delay_of_draw_block);
			cct_showch(x, y + i, ' ', bgcolor, fgcolor, pCGI->CFI.block_width);
		}
	}
	return 0; //此句可根据需要修改
}

/* -----------------------------------------------
		实现下面给出的函数（函数声明不准动）
   ----------------------------------------------- */
   /***************************************************************************
	  函数名称：
	  功    能：设置游戏主框架的行列数
	  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
				const int row						：行数(错误则为0，不设上限，人为保证正确性)
				const int col						：列数(错误则为0，不设上限，人为保证正确性)
	  返 回 值：
	  说    明：1、指消除类游戏的矩形区域的行列值
				2、行列的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
	***************************************************************************/
int gmw_set_rowcol(CONSOLE_GRAPHICS_INFO* const pCGI, const int row, const int col)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (row <= 0 || col <= 0) {
		pCGI->row_num = 0;
		pCGI->col_num = 0;
	}
	else {
		pCGI->row_num = row;
		pCGI->col_num = col;
	}
	pCGI->CFI.total_high = pCGI->row_num * pCGI->CFI.bhigh - pCGI->CFI.separator * 1 + 1 * 2;
	pCGI->CFI.total_width = pCGI->col_num * pCGI->CFI.bwidth - pCGI->CFI.separator * 2 + 2 * 2;
	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->top_status_line + pCGI->draw_frame_with_col_no + pCGI->CFI.total_high;
	pCGI->lines = pCGI->extern_up_lines + pCGI->top_status_line + pCGI->draw_frame_with_col_no + pCGI->CFI.total_high + pCGI->lower_status_line + pCGI->extern_down_lines + 4;
	pCGI->cols = pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.total_width + pCGI->extern_right_cols + 1;
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置整个窗口（含游戏区、附加区在内的整个cmd窗口）的颜色
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int bg_color					：前景色（缺省COLOR_BLACK）
		   const int fg_color					：背景色（缺省COLOR_WHITE）
		   const bool cascade					：是否级联（缺省为true-级联）
  返 回 值：
  说    明：1、cascade = true时
				同步修改游戏主区域的颜色
				同步修改上下状态栏的正常文本的背景色和前景色，醒目文本的背景色（前景色不变）
			2、不检查颜色值错误及冲突，需要人为保证
				例：颜色非0-15
					前景色背景色的值一致导致无法看到内容
					前景色正好是状态栏醒目前景色，导致无法看到醒目提示
					...
***************************************************************************/
int gmw_set_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int bgcolor, const int fgcolor, const bool cascade)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//整个窗口
	pCGI->area_bgcolor = bgcolor;
	pCGI->area_fgcolor = fgcolor;
	if (cascade) {
		/*游戏主区域*/
		pCGI->CFI.bgcolor = bgcolor;
		pCGI->CFI.fgcolor = fgcolor;
		/* 上状态栏正常信息配色 */
		pCGI->SLI.top_normal_bgcolor = bgcolor;
		pCGI->SLI.top_normal_fgcolor = fgcolor;
		/* 上状态栏醒目信息配色 */
		pCGI->SLI.top_catchy_bgcolor = bgcolor;
		/* 下状态栏正常信息配色 */
		pCGI->SLI.lower_normal_bgcolor = bgcolor;
		pCGI->SLI.lower_normal_fgcolor = fgcolor;
		/* 下状态栏醒目信息配色 */
		pCGI->SLI.lower_catchy_bgcolor = bgcolor;
	}
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置窗口的字体
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const char *fontname					：字体名称（只能是"Terminal"和"新宋体"两种，错误则返回-1，不改变字体）
		   const int fs_high					：字体高度（缺省及错误为16，不设其它限制，人为保证）
		   const int fs_width					：字体高度（缺省及错误为8，不设其它限制，人为保证）
  返 回 值：
  说    明：1、与cmd_console_tools中的setfontsize相似，目前只支持“点阵字体”和“新宋体”
			2、若设置其它字体则直接返回，保持原字体设置不变
***************************************************************************/
int gmw_set_font(CONSOLE_GRAPHICS_INFO* const pCGI, const char* fontname, const int fs_high, const int fs_width)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (strcmp(fontname, "Terminal") != 0 && strcmp(fontname, "新宋体") != 0)
		return -1;
	strcpy(pCGI->CFT.font_type, fontname);
	pCGI->CFT.font_size_width = fs_width;
	pCGI->CFT.font_size_high = fs_high;
	if (strcmp(fontname, "新宋体") == 0)
		pCGI->CFT.font_size_width = 0;
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置延时
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int type						：延时的类型（目前为3种）
		   const int delay_ms					：以ms为单位的延时
			   画边框的延时：0 ~ 不设上限，人为保证正确（<0则置0）
			   画色块的延时：0 ~ 不设上限，人为保证正确（<0则置0）
			   色块移动的延时：BLOCK_MOVED_DELAY_MS ~ 不设上限，人为保证正确（ <BLOCK_MOVED_DELAY_MS 则置 BLOCK_MOVED_DELAY_MS）
  返 回 值：
  说    明：
***************************************************************************/
int gmw_set_delay(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const int delay_ms)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == DELAY_OF_DRAW_FRAME) {
		if (delay_ms < 0)
			pCGI->delay_of_draw_frame = 0;
		else
			pCGI->delay_of_draw_frame = delay_ms;
	}
	else if (type == DELAY_OF_DRAW_BLOCK) {
		if (delay_ms < 0)
			pCGI->delay_of_draw_block = 0;
		else
			pCGI->delay_of_draw_block = delay_ms;
	}
	else if (type == DELAY_OF_BLOCK_MOVED) {
		if (delay_ms < BLOCK_MOVED_DELAY_MS)
			pCGI->delay_of_block_moved = 0;
		else
			pCGI->delay_of_block_moved = delay_ms;
	}
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  输入参数：设置游戏主框架结构之外需要保留的额外区域
  功    能：CONSOLE_GRAPHICS_INFO *const pCGI	：
		   const int up_lines					：上部额外的行（缺省及错误为0，不设上限，人为保证）
		   const int down_lines				：下部额外的行（缺省及错误为0，不设上限，人为保证）
		   const int left_cols					：左边额外的列（缺省及错误为0，不设上限，人为保证）
		   const int right_cols				：右边额外的列（缺省及错误为0，不设上限，人为保证）
  返 回 值：
  说    明：额外行列的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_ext_rowcol(CONSOLE_GRAPHICS_INFO* const pCGI, const int up_lines, const int down_lines, const int left_cols, const int right_cols)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (up_lines < 0)
		pCGI->extern_up_lines = 0;
	else
		pCGI->extern_up_lines = up_lines;
	if (down_lines < 0)
		pCGI->extern_down_lines = 0;
	else
		pCGI->extern_down_lines = down_lines;
	if (left_cols < 0)
		pCGI->extern_left_cols = 0;
	else
		pCGI->extern_left_cols = left_cols;
	if (right_cols < 0)
		pCGI->extern_right_cols = 0;
	else
		pCGI->extern_right_cols = right_cols;

	pCGI->SLI.top_start_x = pCGI->extern_left_cols;
	pCGI->SLI.top_start_y = pCGI->extern_up_lines;
	pCGI->SLI.lower_start_x = pCGI->extern_left_cols;
	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->top_status_line + pCGI->draw_frame_with_col_no + pCGI->CFI.total_high;

	pCGI->start_x = pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2;
	pCGI->start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->top_status_line;

	pCGI->lines = pCGI->extern_up_lines + pCGI->top_status_line + pCGI->draw_frame_with_col_no + pCGI->CFI.total_high + pCGI->lower_status_line + pCGI->extern_down_lines + 4;
	pCGI->cols = pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.total_width + pCGI->extern_right_cols + 1;
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_FRAME_TYPE 结构中的11种线型（缺省4种）
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：1 - 全线 2 - 全单线 3 - 横双竖单 4 - 横单竖双
  返 回 值：
  说    明：
***************************************************************************/
int gmw_set_frame_default_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const int type)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	const char* special[] = { "╔", "╚", "╗", "╝", "═", "║", "╦", "╩", "╠", "╣", "╬",
							"┏", "┗", "┓", "┛", "━", "┃", "┳", "┻", "┣", "┫", "╋",
							"╒", "╘", "╕", "╛", "═", "│", "╤", "╧", "╞", "╡", "╪",
							"╓", "╙", "╖", "╜", "─", "║", "╥", "╨", "╟", "╢", "╫",
							NULL
	};
	strcpy(pCGI->CFI.top_left, special[0 + (type - 1) * 11]);			// "╔"
	strcpy(pCGI->CFI.lower_left, special[1 + (type - 1) * 11]);		// "╚"
	strcpy(pCGI->CFI.top_right, special[2 + (type - 1) * 11]);			// "╗"
	strcpy(pCGI->CFI.lower_right, special[3 + (type - 1) * 11]);		// "╝"
	strcpy(pCGI->CFI.h_normal, special[4 + (type - 1) * 11]);			// "═"	//Horizontal
	strcpy(pCGI->CFI.v_normal, special[5 + (type - 1) * 11]);			// "║"	//Vertical
	strcpy(pCGI->CFI.h_top_separator, special[6 + (type - 1) * 11]);	// "╤"
	strcpy(pCGI->CFI.h_lower_separator, special[7 + (type - 1) * 11]);	// "╧"
	strcpy(pCGI->CFI.v_left_separator, special[8 + (type - 1) * 11]);	// "╟"
	strcpy(pCGI->CFI.v_right_separator, special[9 + (type - 1) * 11]);	// "╢"
	strcpy(pCGI->CFI.mid_separator, special[10 + (type - 1) * 11]);// "┼"
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_FRAME_TYPE 结构中的11种线型
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const char *...						：共11种，具体见.h，此处略
  返 回 值：
  说    明：约定为一个中文制表符，可以使用其它内容，人为保证2字节
			1、超过2字节则只取前2字节
			2、如果给NULL，用两个空格替代
			3、如果给1字节，则补一个空格，如果因此而导致显示乱，不算错
***************************************************************************/
int gmw_set_frame_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const char* top_left, const char* lower_left, const char* top_right,
	const char* lower_right, const char* h_normal, const char* v_normal, const char* h_top_separator,
	const char* h_lower_separator, const char* v_left_separator, const char* v_right_separator, const char* mid_separator)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	gmw_inner_deal_Chinese_character(pCGI->CFI.top_left, top_left);
	gmw_inner_deal_Chinese_character(pCGI->CFI.lower_left, lower_left);
	gmw_inner_deal_Chinese_character(pCGI->CFI.top_right, top_right);
	gmw_inner_deal_Chinese_character(pCGI->CFI.lower_right, lower_right);
	gmw_inner_deal_Chinese_character(pCGI->CFI.h_normal, h_normal);
	gmw_inner_deal_Chinese_character(pCGI->CFI.v_normal, v_normal);
	gmw_inner_deal_Chinese_character(pCGI->CFI.h_top_separator, h_top_separator);
	gmw_inner_deal_Chinese_character(pCGI->CFI.h_lower_separator, h_lower_separator);
	gmw_inner_deal_Chinese_character(pCGI->CFI.v_left_separator, v_left_separator);
	gmw_inner_deal_Chinese_character(pCGI->CFI.v_right_separator, v_right_separator);
	gmw_inner_deal_Chinese_character(pCGI->CFI.mid_separator, mid_separator);
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_FRAME_TYPE 结构中的色块数量大小、是否需要分隔线等
  输入参数：输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int block_width						：宽度（错误及缺省2，因为约定表格线为中文制表符，如果给出奇数，要+1）
			const int block_high						：高度（错误及缺省1）
			const bool separator						：是否需要分隔线（缺省为true，需要分隔线）
  返 回 值：
  说    明：框架大小/是否需要分隔线等的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_frame_style(CONSOLE_GRAPHICS_INFO* const pCGI, const int block_width, const int block_high, const bool separator)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (block_width < 0)
		pCGI->CFI.block_width = 2;
	else if (block_width % 2 == 1)
		pCGI->CFI.block_width = block_width + 1;
	else
		pCGI->CFI.block_width = block_width;
	if (block_high < 0)
		pCGI->CFI.block_high = 1;
	else
		pCGI->CFI.block_high = block_high;
	pCGI->CFI.separator = separator;
	/* 每个色块的附加的宽度和高度(有分隔线是分别为2/1)，由separator计算而来 */
	pCGI->CFI.block_width_ext = pCGI->CFI.separator * 2;
	pCGI->CFI.block_high_ext = pCGI->CFI.separator * 1;
	/* 每行/每列含分隔线的总宽度，由宽度/高度+分隔线计算而来 */
	pCGI->CFI.bhigh = pCGI->CFI.block_high + pCGI->CFI.block_high_ext;
	pCGI->CFI.bwidth = pCGI->CFI.block_width + pCGI->CFI.block_width_ext;
	/*游戏区域的总宽度和总高度*/
	pCGI->CFI.total_high = pCGI->row_num * pCGI->CFI.bhigh - pCGI->CFI.separator * 1 + 1 * 2;
	pCGI->CFI.total_width = pCGI->col_num * pCGI->CFI.bwidth - pCGI->CFI.separator * 2 + 2 * 2;
	/* cmd窗口的大小 */
	pCGI->lines = pCGI->extern_up_lines + pCGI->top_status_line + pCGI->draw_frame_with_col_no + pCGI->CFI.total_high + pCGI->lower_status_line + pCGI->extern_down_lines + 4;
	pCGI->cols = pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.total_width + pCGI->extern_right_cols + 1;
	/*下状态栏y值*/
	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->top_status_line + pCGI->draw_frame_with_col_no + pCGI->CFI.total_high;
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_BORDER_TYPE 结构中的颜色
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int bg_color					：背景色（缺省 -1表示用窗口背景色）
			const int fg_color					：前景色（缺省 -1表示用窗口前景色）
  返 回 值：
  说    明：不检查颜色值错误及冲突，需要人为保证
				例：颜色非0-15，前景色背景色的值一致导致无法看到内容等
***************************************************************************/
int gmw_set_frame_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int bgcolor, const int fgcolor)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->CFI.bgcolor = (bgcolor == -1 ? pCGI->area_bgcolor : bgcolor);
	pCGI->CFI.fgcolor = (fgcolor == -1 ? pCGI->area_fgcolor : fgcolor);
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_BLOCK_INFO 结构中的6种线型（缺省4种）
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：1 - 全双线 2 - 全单线 3 - 横双竖单 4 - 横单竖双
  返 回 值：
  说    明：
***************************************************************************/
int gmw_set_block_default_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const int type)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	const char* special[] = { "╔", "╚", "╗", "╝", "═", "║",
							"┏", "┗", "┓", "┛", "━", "┃",
							"╒", "╘", "╕", "╛", "═", "│",
							"╓", "╙", "╖", "╜", "─", "║",
							NULL
	};
	strcpy(pCGI->CBI.top_left, special[0 + (type - 1) * 6]);			// "╔"
	strcpy(pCGI->CBI.lower_left, special[1 + (type - 1) * 6]);		// "╚"
	strcpy(pCGI->CBI.top_right, special[2 + (type - 1) * 6]);			// "╗"
	strcpy(pCGI->CBI.lower_right, special[3 + (type - 1) * 6]);		// "╝"
	strcpy(pCGI->CBI.h_normal, special[4 + (type - 1) * 6]);			// "═"	//Horizontal
	strcpy(pCGI->CBI.v_normal, special[5 + (type - 1) * 6]);			// "║"	//Vertical*/
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_BLOCK_INFO 结构中的6种线型
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const char *...					：共6种，具体见.h，此处略
  返 回 值：
  说    明：约定为一个中文制表符，可以使用其它内容，人为保证2字节
			1、超过2字节则只取前2字节
			2、如果给NULL，用两个空格替代
			3、如果给1字节，则补一个空格，如果因此而导致显示乱，不算错
***************************************************************************/
int gmw_set_block_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const char* top_left, const char* lower_left, const char* top_right, const char* lower_right, const char* h_normal, const char* v_normal)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	gmw_inner_deal_Chinese_character(pCGI->CBI.top_left, top_left);
	gmw_inner_deal_Chinese_character(pCGI->CBI.lower_left, lower_left);
	gmw_inner_deal_Chinese_character(pCGI->CBI.top_right, top_right);
	gmw_inner_deal_Chinese_character(pCGI->CBI.lower_right, lower_right);
	gmw_inner_deal_Chinese_character(pCGI->CBI.h_normal, h_normal);
	gmw_inner_deal_Chinese_character(pCGI->CBI.v_normal, v_normal);
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置每个游戏色块(彩球)是否需要小边框
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const bool on_off					：true - 需要 flase - 不需要（缺省false）
  返 回 值：
  说    明：边框约定为中文制表符，双线
***************************************************************************/
int gmw_set_block_border_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->CBI.block_border = on_off;
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置是否显示上下状态栏
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：状态栏类型（上/下）
			const bool on_off					：true - 需要 flase - 不需要（缺省true）
  返 回 值：
  说    明：1、状态栏的相关约定如下：
			   1.1、上状态栏只能一行，在主区域最上方框线/列标的上面，为主区域的最开始一行（主区域的左上角坐标就是上状态栏的坐标）
			   1.2、下状态栏只能一行，在主区域最下方框线的下面
			   1.3、状态栏的宽度为主区域宽度，如果信息过长则截断
		   2、行列的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_status_line_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == TOP_STATUS_LINE) {
		pCGI->top_status_line = on_off;
		pCGI->SLI.is_top_status_line = on_off;
		pCGI->start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->top_status_line;
		pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->top_status_line + pCGI->draw_frame_with_col_no + pCGI->CFI.total_high;
	}
	else if (type == LOWER_STATUS_LINE) {
		pCGI->lower_status_line = on_off;
		pCGI->SLI.is_lower_status_line = on_off;
	}
	pCGI->lines = pCGI->extern_up_lines + pCGI->top_status_line + pCGI->draw_frame_with_col_no + pCGI->CFI.total_high + pCGI->lower_status_line + pCGI->extern_down_lines + 4;
	pCGI->cols = pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.total_width + pCGI->extern_right_cols + 1;
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置上下状态栏的颜色
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：状态栏类型（上/下）
			const int normal_bgcolor			：正常文本背景色（缺省 -1表示使用窗口背景色）
			const int normal_fgcolor			：正常文本前景色（缺省 -1表示使用窗口前景色）
			const int catchy_bgcolor			：醒目文本背景色（缺省 -1表示使用窗口背景色）
			const int catchy_fgcolor			：醒目文本前景色（缺省 -1表示使用亮黄色）
  输入参数：
  返 回 值：
  说    明：不检查颜色值错误及冲突，需要人为保证
				例：颜色非0-15，前景色背景色的值一致导致无法看到内容等
***************************************************************************/
int gmw_set_status_line_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const int normal_bgcolor, const int normal_fgcolor, const int catchy_bgcolor, const int catchy_fgcolor)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (type == TOP_STATUS_LINE) {
		pCGI->SLI.top_normal_bgcolor = (normal_bgcolor == -1 ? pCGI->area_bgcolor : normal_bgcolor);
		pCGI->SLI.top_normal_fgcolor = (normal_fgcolor == -1 ? pCGI->area_fgcolor : normal_fgcolor);
		pCGI->SLI.top_catchy_bgcolor = (catchy_bgcolor == -1 ? pCGI->area_bgcolor : catchy_bgcolor);
		pCGI->SLI.top_catchy_fgcolor = (catchy_fgcolor == -1 ? COLOR_HYELLOW : catchy_fgcolor);
	}
	else if (type == LOWER_STATUS_LINE) {
		pCGI->SLI.lower_normal_bgcolor = (normal_bgcolor == -1 ? pCGI->area_bgcolor : normal_bgcolor);
		pCGI->SLI.lower_normal_fgcolor = (normal_fgcolor == -1 ? pCGI->area_fgcolor : normal_fgcolor);
		pCGI->SLI.lower_catchy_bgcolor = (catchy_bgcolor == -1 ? pCGI->area_bgcolor : catchy_bgcolor);
		pCGI->SLI.lower_catchy_fgcolor = (catchy_fgcolor == -1 ? COLOR_HYELLOW : catchy_fgcolor);
	}
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置是否显示行号
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const bool on_off					：true - 显示 flase - 不显示（缺省false）
  返 回 值：
  说    明：1、行号约定为字母A开始连续排列（如果超过26，则从a开始，超过52的统一为*，实际应用不可能）
			2、是否显示行号的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_rowno_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1; 
	pCGI->draw_frame_with_row_no = on_off;

	pCGI->start_x = pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2;

	pCGI->cols = pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.total_width + pCGI->extern_right_cols + 1;
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置是否显示列标
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const bool on_off					：true - 显示 flase - 不显示（缺省false）
  返 回 值：
  说    明：1、列标约定为数字0开始连续排列（数字0-99，超过99统一为**，实际应用不可能）
			2、是否显示列标的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_colno_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->draw_frame_with_col_no = on_off;

	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->top_status_line + pCGI->draw_frame_with_col_no + pCGI->CFI.total_high;
	pCGI->start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->top_status_line;
	pCGI->lines = pCGI->extern_up_lines + pCGI->top_status_line + pCGI->draw_frame_with_col_no + pCGI->CFI.total_high + pCGI->lower_status_line + pCGI->extern_down_lines + 4;
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：打印 CONSOLE_GRAPHICS_INFO 结构体中的各成员值
  输入参数：
  返 回 值：
  说    明：1、仅供调试用，打印格式自定义
			2、本函数测试用例中未调用过，可以不实现
***************************************************************************/
int gmw_print(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：将 CONSOLE_GRAPHICS_INFO 结构体用缺省值进行初始化
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI：整体结构指针
		   const int row					：游戏区域色块行数（缺省10）
		   const int col					：游戏区域色块列数（缺省10）
		   const int bgcolor				：整个窗口背景色（缺省 COLOR_BLACK）
		   const int fgcolor				：整个窗口背景色（缺省 COLOR_WHITE）
  返 回 值：
  说    明：窗口背景黑/前景白，点阵16*8，上下左右无额外行列，上下状态栏均有，无行号/列标，框架线型为双线，色块宽度2/高度1/无小边框，颜色略
***************************************************************************/
int gmw_init(CONSOLE_GRAPHICS_INFO* const pCGI, const int row, const int col, const int bgcolor, const int fgcolor)
{
	/* 首先置标记 */
	pCGI->inited = CGI_INITED;
	//主框架行列数
	gmw_set_rowcol(pCGI, row, col);
	//窗口颜色
	gmw_set_color(pCGI, bgcolor, fgcolor);
	//字体
	gmw_set_font(pCGI,"新宋体");
	//额外行列
	gmw_set_ext_rowcol(pCGI);
	//框架线形
	gmw_set_frame_color(pCGI);
	gmw_set_frame_default_linetype(pCGI, 1);
	//色块参数
	gmw_set_frame_style(pCGI);
	gmw_set_block_border_switch(pCGI);
	gmw_set_block_default_linetype(pCGI, 1);
	//上下状态栏
	gmw_set_status_line_switch(pCGI, TOP_STATUS_LINE);
	gmw_set_status_line_switch(pCGI, LOWER_STATUS_LINE);
	gmw_set_status_line_color(pCGI, TOP_STATUS_LINE);
	gmw_set_status_line_color(pCGI, LOWER_STATUS_LINE);
	//行号、列标
	gmw_set_rowno_switch(pCGI);
	gmw_set_colno_switch(pCGI);
	//延时
	gmw_set_delay(pCGI, DELAY_OF_DRAW_FRAME, 0);
	gmw_set_delay(pCGI, DELAY_OF_DRAW_BLOCK, 0);
	gmw_set_delay(pCGI, DELAY_OF_BLOCK_MOVED, BLOCK_MOVED_DELAY_MS);
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：画主游戏框架
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
  返 回 值：
  说    明：具体可参考demo的效果
***************************************************************************/
int gmw_draw_frame(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//窗口初始设置
	cct_cls();
	cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);
	cct_setfontsize(pCGI->CFT.font_type, pCGI->CFT.font_size_high, pCGI->CFT.font_size_width);
	cct_setconsoleborder(pCGI->cols, pCGI->lines, pCGI->cols, pCGI->lines);
	//游戏框架打印
	gmw_inner_print_all_kuang(pCGI);
	//画行号
	if (pCGI->draw_frame_with_row_no) {
		for (int i = 0; i < pCGI->row_num; i++) {
			char ch;
			if (i >= 0 && i < 26)
				ch = 'A' + i;
			else if (i >= 26 && i < 52)
				ch = ('a' - 26) + i;
			else
				ch = '*';
			cct_showch(pCGI->start_x - 2, pCGI->start_y + (pCGI->CFI.block_high + 1) / 2 + i * pCGI->CFI.bhigh, ch, pCGI->area_bgcolor, pCGI->area_fgcolor);
		}
	}
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：在状态栏上显示信息
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int type							：指定是上/下状态栏
		   const char *msg						：正常信息
		   const char *catchy_msg					：需要特别标注的信息（在正常信息前显示）
  返 回 值：
  说    明：1、输出宽度限定为主框架的宽度（含行号列标位置），超出则截去
			2、如果最后一个字符是某汉字的前半个，会导致后面乱码，要处理
***************************************************************************/
int gmw_status_line(const CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const char* msg, const char* catchy_msg)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	int blank = 0;
	int max_len = pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.total_width;   //主区域的宽度
	int len1, len2;
	if (catchy_msg == NULL)
		len2 = 0;
	else
		len2 = strlen(catchy_msg);
	if (msg == NULL)
		len1 = 0;
	else
		len1 = strlen(msg);
	char* o_msg = new(nothrow) char[max_len - len2 + 1];
	if (o_msg == NULL)
		return -1;
	else {
		if (msg == NULL)
			o_msg = NULL;
		else {
			if ((len1 + len2) > max_len) {
				strncpy(o_msg, msg, max_len - len2);
				o_msg[max_len - len2] = '\0';
				blank = 0;
			}
			else {
				strncpy(o_msg, msg, len1 + 1);
				blank = max_len - len2 - len1;
			}
		}
	}
	if (type == TOP_STATUS_LINE) {
		if (pCGI->SLI.is_top_status_line) {
			cct_showstr(pCGI->SLI.top_start_x, pCGI->SLI.top_start_y, catchy_msg, pCGI->SLI.top_catchy_bgcolor, pCGI->SLI.top_catchy_fgcolor);
			int x, y;
			cct_getxy(x, y);
			cct_showstr(x, y, o_msg, pCGI->SLI.top_normal_bgcolor, pCGI->SLI.top_normal_fgcolor);
			cct_getxy(x, y);
			cct_showch(x, y, ' ', pCGI->SLI.top_normal_bgcolor, pCGI->SLI.top_normal_fgcolor, blank);
		}
	}
	if (type == LOWER_STATUS_LINE) {
		if (pCGI->SLI.is_lower_status_line) {
			cct_showstr(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y, catchy_msg, pCGI->SLI.lower_catchy_bgcolor, pCGI->SLI.lower_catchy_fgcolor);
			int x, y;
			cct_getxy(x, y);
			cct_showstr(x, y, o_msg, pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor);
			cct_getxy(x, y);
			cct_showch(x, y, ' ', pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor, blank);
		}
	}
	delete[] o_msg;
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：显示某一个色块(内容为字符串，坐标为row/col)
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int row_no						：行号（从0开始，人为保证正确性，程序不检查）
		   const int col_no						：列号（从0开始，人为保证正确性，程序不检查）
		   const int bdi_value						：需要显示的值
		   const BLOCK_DISPLAY_INFO *const bdi		：存放该值对应的显示信息的结构体数组
  返 回 值：
  说    明：1、BLOCK_DISPLAY_INFO 的含义见头文件，用法参考测试样例
			2、bdi_value为 BDI_VALUE_BLANK 表示空白块，要特殊处理
***************************************************************************/
int gmw_draw_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//色块左上角的坐标
	int x, y;
	x = pCGI->start_x + 2 + col_no * pCGI->CFI.bwidth;
	y = pCGI->start_y + 1 + row_no * pCGI->CFI.bhigh;
	int a = gmw_inner__draw_block_by_xy(pCGI, x, y, bdi_value, bdi);
	return a; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：移动某一个色块
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int row_no						：行号（从0开始，人为保证正确性，程序不检查）
		   const int col_no						：列号（从0开始，人为保证正确性，程序不检查）
		   const int bdi_value						：需要显示的值
		   const int blank_bdi_value				：移动过程中用于动画效果显示时用于表示空白的值（一般为0，此处做为参数代入，是考虑到可能出现的特殊情况）
		   const BLOCK_DISPLAY_INFO *const bdi		：存放显示值/空白值对应的显示信息的结构体数组
		   const int direction						：移动方向，一共四种，具体见cmd_gmw_tools.h
		   const int distance						：移动距离（从1开始，人为保证正确性，程序不检查）
  返 回 值：
  说    明：
***************************************************************************/
int gmw_move_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const int blank_bdi_value, const BLOCK_DISPLAY_INFO* const bdi, const int direction, const int distance)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//色块左上角的坐标
	int x, y;
	x = pCGI->start_x + 2 + col_no * pCGI->CFI.bwidth;
	y = pCGI->start_y + 1 + row_no * pCGI->CFI.bhigh;
	//下移
	if (direction == UP_TO_DOWN) {
		for (int i = 0; i < distance; i++) {
			for (int j = 1; j <= pCGI->CFI.bhigh; j++) {
				Sleep(pCGI->delay_of_block_moved);
				gmw_inner__draw_block_by_xy(pCGI, x, y + (j - 1) + i * pCGI->CFI.bhigh, blank_bdi_value, bdi);  //填补色块
				gmw_inner__draw_block_by_xy(pCGI, x, y + j + i * pCGI->CFI.bhigh, bdi_value, bdi);  //先画色块
			}
			if (pCGI->CFI.separator)
				cct_showstr(x, y + pCGI->CFI.block_high + i * pCGI->CFI.bhigh, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->CFI.block_width / 2);
		}
	}
	//上移
	if (direction == DOWN_TO_UP) {
		for (int i = 0; i < distance; i++) {
			for (int j = 1; j <= pCGI->CFI.bhigh; j++) {
				Sleep(pCGI->delay_of_block_moved);
				gmw_inner__draw_block_by_xy(pCGI, x, y - (j - 1) - i * pCGI->CFI.bhigh, blank_bdi_value, bdi);  //填补色块
				gmw_inner__draw_block_by_xy(pCGI, x, y - j - i * pCGI->CFI.bhigh, bdi_value, bdi);  //先画色块
			}
			if (pCGI->CFI.separator)
				cct_showstr(x, y - 1 - i * pCGI->CFI.bhigh, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->CFI.block_width / 2);
		}
	}
	//右移
	if (direction == LEFT_TO_RIGHT) {
		for (int i = 0; i < distance; i++) {
			for (int j = 1; j <= pCGI->CFI.bwidth / 2; j++) {
				Sleep(pCGI->delay_of_block_moved);
				gmw_inner__draw_block_by_xy(pCGI, x + 2 * (j - 1) + i * pCGI->CFI.bwidth, y, blank_bdi_value, bdi);  //填补色块
				gmw_inner__draw_block_by_xy(pCGI, x + 2 * j + i * pCGI->CFI.bwidth, y, bdi_value, bdi);  //先画色块
			}
			if (pCGI->CFI.separator) {
				for (int j = 0; j < pCGI->CFI.block_high; j++)
					cct_showstr(x + pCGI->CFI.block_width + i * pCGI->CFI.bwidth, y + j, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			}
		}
	}
	//左移
	if (direction == RIGHT_TO_LEFT) {
		for (int i = 0; i < distance; i++) {
			for (int j = 1; j <= pCGI->CFI.bwidth / 2; j++) {
				Sleep(pCGI->delay_of_block_moved);
				gmw_inner__draw_block_by_xy(pCGI, x - 2 * (j - 1) - i * pCGI->CFI.bwidth, y, blank_bdi_value, bdi);  //填补色块
				gmw_inner__draw_block_by_xy(pCGI, x - 2 * j - i * pCGI->CFI.bwidth, y, bdi_value, bdi);  //先画色块
			}
			if (pCGI->CFI.separator) {
				for (int j = 0; j < pCGI->CFI.block_high; j++)
					cct_showstr(x - 2 - i * pCGI->CFI.bwidth, y + j, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			}
		}
	}
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：读键盘或鼠标
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   int &MAction							：如果返回 CCT_MOUSE_EVENT，则此值有效，为 MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK/MOUSE_RIGHT_BUTTON_CLICK 三者之一
													   如果返回 CCT_KEYBOARD_EVENT，则此值无效
		   int &MRow								：如果返回 CCT_MOUSE_EVENT 且 MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK，则此值有效，表示左键选择的游戏区域的行号（从0开始）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   int &MCol								：如果返回 CCT_MOUSE_EVENT 且 MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK，则此值有效，表示左键选择的游戏区域的列号（从0开始）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   int &KeyCode1							：如果返回 CCT_KEYBOARD_EVENT，则此值有效，为读到的键码（如果双键码，则为第一个）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   int &KeyCode2							：如果返回 CCT_KEYBOARD_EVENT，则此值有效，为读到的键码（如果双键码，则为第二个，如果是单键码，则为0）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   const bool update_lower_status_line		：鼠标移动时，是否要在本函数中显示"[当前光标] *行*列/位置非法"的信息（true=显示，false=不显示，缺省为true）
  返 回 值：函数返回约定
		   1、如果是鼠标移动，得到的MRow/MCol与传入的相同(鼠标指针微小的移动)，则不返回，继续读
							  得到行列非法位置，则不返回，根据 update_lower_status_line 的设置在下状态栏显示"[当前光标] 位置非法"
							  得到的MRow/MCol与传入的不同(行列至少一个变化)，根据 update_lower_status_line 的设置在下状态栏显示"[当前光标] *行*列"，再返回MOUSE_ONLY_MOVED（有些游戏返回后要处理色块的不同颜色显示）
		   2、如果是按下鼠标左键，且当前鼠标指针停留在主游戏区域的*行*列上，则返回 CCT_MOUSE_EVENT ，MAction 为 MOUSE_LEFT_BUTTON_CLICK, MRow 为行号，MCol 为列标
								  且当前鼠标指针停留在非法区域（非游戏区域，游戏区域中的分隔线），则不返回，根据 update_lower_status_line 的设置在下状态栏显示"[当前光标] 位置非法"
		   3、如果是按下鼠标右键，则不判断鼠标指针停留区域是否合法，直接返回 CCT_MOUSE_EVENT ，MAction 为 MOUSE_RIGHT_BUTTON_CLICK, MRow、MCol取当前值（因为消灭星星的右键标记需要坐标）
		   4、如果按下键盘上的某键（含双键码按键），则直接返回 CCT_KEYBOARD_EVENT，KeyCode1/KeyCode2中为对应的键码值
 说    明：通过调用 cmd_console_tools.cpp 中的 read_keyboard_and_mouse 函数实现
***************************************************************************/
int gmw_read_keyboard_and_mouse(const CONSOLE_GRAPHICS_INFO* const pCGI, int& MAction, int& MRow, int& MCol, int& KeyCode1, int& KeyCode2, const bool update_lower_status_line)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	int newrow, newcol;    //新的行号、列表
	int MX, MY;
	bool add = 1;  //假设合法
	//有效位置的始、终 x,y值
	int start_x = pCGI->start_x + 2;
	int start_y = pCGI->start_y + 1;
	int end_x = pCGI->start_x + pCGI->CFI.total_width - 2;
	int end_y = pCGI->start_y + pCGI->CFI.total_high - 1;
	cct_enable_mouse();
	while (1) {
		int action = cct_read_keyboard_and_mouse(MX, MY, MAction, KeyCode1, KeyCode2);
		//键盘事件
		if (action == CCT_KEYBOARD_EVENT)
			return CCT_KEYBOARD_EVENT;

		//鼠标事件
		else {
			//右键直接返回
			if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
				MRow = (MY - start_y) / pCGI->CFI.bhigh;
				MCol = (MX - start_x) / pCGI->CFI.bwidth;
				return CCT_MOUSE_EVENT;
			}
			else {
				//判断位置是否合法
				bool condition_xy = (MX >= start_x && MX < end_x && MY >= start_y && MY < end_y);    //合法范围
				bool condition_else = pCGI->CFI.separator && (((MX - pCGI->start_x) % pCGI->CFI.bwidth == 0 || (MX - pCGI->start_x) % pCGI->CFI.bwidth == 1) || (MY - pCGI->start_x) % pCGI->CFI.bhigh == 0);   //在分割线上
				bool condition = condition_xy && !condition_else;

				//位置合法
				if (condition) {
					if (MAction == MOUSE_LEFT_BUTTON_CLICK) {
						MRow = (MY - start_y) / pCGI->CFI.bhigh;
						MCol = (MX - start_x) / pCGI->CFI.bwidth;
						return CCT_MOUSE_EVENT;
					}
					else if (MAction == MOUSE_ONLY_MOVED) {
						//计算行号，列标记
						newcol = (MX - start_x) / pCGI->CFI.bwidth;
						newrow = (MY - start_y) / pCGI->CFI.bhigh;
						if (newrow == MRow && newcol == MCol)
							continue;   //说明鼠标位置还在同一个色块
						else {
							MRow = newrow;
							MCol = newcol;
							char temp[256];
							sprintf(temp, "[当前光标] %c行%d列", char('A' + MRow), MCol);
							gmw_status_line(pCGI, LOWER_STATUS_LINE, temp, NULL);
							return CCT_MOUSE_EVENT;
						}
					}
					else
						continue;
				}
				else {
					if (add)
						gmw_status_line(pCGI, LOWER_STATUS_LINE, "[当前光标] 位置非法", NULL);
					else
						add = 0;
				}
			}
		}
	}
	return -1; //此句可根据需要修改
}
