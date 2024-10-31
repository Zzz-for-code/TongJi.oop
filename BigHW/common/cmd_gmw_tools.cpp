/* 2352847 �ž��� ������ */
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
		�˴����Ը�����Ҫ�ľ�̬ȫ�ֱ������������٣����û�У�����̬ȫ��ֻ������/�궨�壨�������ޣ���
   -------------------------------------------------- */

   /* --------------------------------------------------
		   �˴����Ը�����Ҫ���ڲ��������ߺ���
		   1�����������ޣ�����Ϊ gmw_inner_*
		   2����������
		   3��������static������ȷ��ֻ�ڱ�Դ�ļ���ʹ��
	  -------------------------------------------------- */
/*�������������Ʊ���Ĵ���*/
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

/*��ӡ��ܵ�һ��*/
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

/*��ӡ�������*/
static void gmw_inner_print_all_kuang(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	//���б�
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

/*����Ĵ�ӡһ��ɫ��*/
static void gmw_inner_a_block(const CONSOLE_GRAPHICS_INFO* const pCGI, int start_x, int start_y, int bgcolor, int fgcolor, char* content)
{
	//�߿�
	char top_left[CBI_LEN];			// "�X"
	char lower_left[CBI_LEN];		// "�^"
	char top_right[CBI_LEN];			// "�["
	char lower_right[CBI_LEN];		// "�a"
	char h_normal[CBI_LEN];			// "�T"	//Horizontal
	char v_normal[CBI_LEN];			// "�U"	//Vertical
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
		cct_showch(start_x, start_y, ' ', bgcolor, fgcolor, pCGI->CFI.block_width);  //��һ��
		cct_showch(start_x, start_y + 1, ' ', bgcolor, fgcolor, left_blank);
		cct_getxy(x, y);
		cct_showstr(x, y, content, bgcolor, fgcolor);
		cct_getxy(x, y);
		cct_showch(x, y, ' ', bgcolor, fgcolor, right_blank);
		cct_getxy(x, y);
	}
	else {
		//����
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

		//�м�
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

		//���һ��
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

/*���ݴ�������Ͻ�x��y��ӡɫ��*/
static int gmw_inner__draw_block_by_xy(const CONSOLE_GRAPHICS_INFO* const pCGI, const int x, const int y, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//ɫ����ɫ
	int bgcolor, fgcolor;
	bgcolor = pCGI->area_bgcolor;
	fgcolor = pCGI->area_fgcolor;
	//ɫ������ͼ��
	char content[10] = { 0 };
	for (int i = 0; bdi[i].value != BDI_VALUE_END; i++) {
		if (bdi_value == bdi[i].value) {
			//ɫ����ɫ
			bgcolor = (bdi[i].bgcolor == -1 ? pCGI->CFI.bgcolor : bdi[i].bgcolor);
			fgcolor = (bdi[i].fgcolor == -1 ? pCGI->CFI.fgcolor : bdi[i].fgcolor);
			if (bdi[i].content == NULL)
				sprintf(content, "%d", bdi_value);
			else
				strcpy(content, bdi[i].content);
			break;
		}
	}
	/*��ӡһ��ɫ��*/
	if (bdi_value != BDI_VALUE_BLANK)
		gmw_inner_a_block(pCGI, x, y, bgcolor, fgcolor, content);
	else {
		for (int i = 0; i < pCGI->CFI.block_high; i++) {
			Sleep(2 * pCGI->delay_of_draw_block);
			cct_showch(x, y + i, ' ', bgcolor, fgcolor, pCGI->CFI.block_width);
		}
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/* -----------------------------------------------
		ʵ����������ĺ���������������׼����
   ----------------------------------------------- */
   /***************************************************************************
	  �������ƣ�
	  ��    �ܣ�������Ϸ����ܵ�������
	  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
				const int row						������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
				const int col						������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
	  �� �� ֵ��
	  ˵    ����1��ָ��������Ϸ�ľ������������ֵ
				2�����еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
	***************************************************************************/
int gmw_set_rowcol(CONSOLE_GRAPHICS_INFO* const pCGI, const int row, const int col)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������������ڣ�����Ϸ�������������ڵ�����cmd���ڣ�����ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int bg_color					��ǰ��ɫ��ȱʡCOLOR_BLACK��
		   const int fg_color					������ɫ��ȱʡCOLOR_WHITE��
		   const bool cascade					���Ƿ�����ȱʡΪtrue-������
  �� �� ֵ��
  ˵    ����1��cascade = trueʱ
				ͬ���޸���Ϸ���������ɫ
				ͬ���޸�����״̬���������ı��ı���ɫ��ǰ��ɫ����Ŀ�ı��ı���ɫ��ǰ��ɫ���䣩
			2���������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15
					ǰ��ɫ����ɫ��ֵһ�µ����޷���������
					ǰ��ɫ������״̬����Ŀǰ��ɫ�������޷�������Ŀ��ʾ
					...
***************************************************************************/
int gmw_set_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int bgcolor, const int fgcolor, const bool cascade)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//��������
	pCGI->area_bgcolor = bgcolor;
	pCGI->area_fgcolor = fgcolor;
	if (cascade) {
		/*��Ϸ������*/
		pCGI->CFI.bgcolor = bgcolor;
		pCGI->CFI.fgcolor = fgcolor;
		/* ��״̬��������Ϣ��ɫ */
		pCGI->SLI.top_normal_bgcolor = bgcolor;
		pCGI->SLI.top_normal_fgcolor = fgcolor;
		/* ��״̬����Ŀ��Ϣ��ɫ */
		pCGI->SLI.top_catchy_bgcolor = bgcolor;
		/* ��״̬��������Ϣ��ɫ */
		pCGI->SLI.lower_normal_bgcolor = bgcolor;
		pCGI->SLI.lower_normal_fgcolor = fgcolor;
		/* ��״̬����Ŀ��Ϣ��ɫ */
		pCGI->SLI.lower_catchy_bgcolor = bgcolor;
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ô��ڵ�����
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const char *fontname					���������ƣ�ֻ����"Terminal"��"������"���֣������򷵻�-1�����ı����壩
		   const int fs_high					������߶ȣ�ȱʡ������Ϊ16�������������ƣ���Ϊ��֤��
		   const int fs_width					������߶ȣ�ȱʡ������Ϊ8�������������ƣ���Ϊ��֤��
  �� �� ֵ��
  ˵    ����1����cmd_console_tools�е�setfontsize���ƣ�Ŀǰֻ֧�֡��������塱�͡������塱
			2������������������ֱ�ӷ��أ�����ԭ�������ò���
***************************************************************************/
int gmw_set_font(CONSOLE_GRAPHICS_INFO* const pCGI, const char* fontname, const int fs_high, const int fs_width)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (strcmp(fontname, "Terminal") != 0 && strcmp(fontname, "������") != 0)
		return -1;
	strcpy(pCGI->CFT.font_type, fontname);
	pCGI->CFT.font_size_width = fs_width;
	pCGI->CFT.font_size_high = fs_high;
	if (strcmp(fontname, "������") == 0)
		pCGI->CFT.font_size_width = 0;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������ʱ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int type						����ʱ�����ͣ�ĿǰΪ3�֣�
		   const int delay_ms					����msΪ��λ����ʱ
			   ���߿����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ��ɫ�����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ɫ���ƶ�����ʱ��BLOCK_MOVED_DELAY_MS ~ �������ޣ���Ϊ��֤��ȷ�� <BLOCK_MOVED_DELAY_MS ���� BLOCK_MOVED_DELAY_MS��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_delay(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const int delay_ms)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ���������������Ϸ����ܽṹ֮����Ҫ�����Ķ�������
  ��    �ܣ�CONSOLE_GRAPHICS_INFO *const pCGI	��
		   const int up_lines					���ϲ�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int down_lines				���²�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int left_cols					����߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int right_cols				���ұ߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
  �� �� ֵ��
  ˵    �����������еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_ext_rowcol(CONSOLE_GRAPHICS_INFO* const pCGI, const int up_lines, const int down_lines, const int left_cols, const int right_cols)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�11�����ͣ�ȱʡ4�֣�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��1 - ȫ�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_frame_default_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const int type)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	const char* special[] = { "�X", "�^", "�[", "�a", "�T", "�U", "�j", "�m", "�d", "�g", "�p",
							"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��",
							"�V", "�\", "�Y", "�_", "�T", "��", "�h", "�k", "�b", "�e", "�n",
							"�W", "�]", "�Z", "�`", "��", "�U", "�i", "�l", "�c", "�f", "�o",
							NULL
	};
	strcpy(pCGI->CFI.top_left, special[0 + (type - 1) * 11]);			// "�X"
	strcpy(pCGI->CFI.lower_left, special[1 + (type - 1) * 11]);		// "�^"
	strcpy(pCGI->CFI.top_right, special[2 + (type - 1) * 11]);			// "�["
	strcpy(pCGI->CFI.lower_right, special[3 + (type - 1) * 11]);		// "�a"
	strcpy(pCGI->CFI.h_normal, special[4 + (type - 1) * 11]);			// "�T"	//Horizontal
	strcpy(pCGI->CFI.v_normal, special[5 + (type - 1) * 11]);			// "�U"	//Vertical
	strcpy(pCGI->CFI.h_top_separator, special[6 + (type - 1) * 11]);	// "�h"
	strcpy(pCGI->CFI.h_lower_separator, special[7 + (type - 1) * 11]);	// "�k"
	strcpy(pCGI->CFI.v_left_separator, special[8 + (type - 1) * 11]);	// "�c"
	strcpy(pCGI->CFI.v_right_separator, special[9 + (type - 1) * 11]);	// "�f"
	strcpy(pCGI->CFI.mid_separator, special[10 + (type - 1) * 11]);// "��"
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�11������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const char *...						����11�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
***************************************************************************/
int gmw_set_frame_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const char* top_left, const char* lower_left, const char* top_right,
	const char* lower_right, const char* h_normal, const char* v_normal, const char* h_top_separator,
	const char* h_lower_separator, const char* v_left_separator, const char* v_right_separator, const char* mid_separator)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�ɫ��������С���Ƿ���Ҫ�ָ��ߵ�
  ������������������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int block_width						����ȣ�����ȱʡ2����ΪԼ�������Ϊ�����Ʊ�����������������Ҫ+1��
			const int block_high						���߶ȣ�����ȱʡ1��
			const bool separator						���Ƿ���Ҫ�ָ��ߣ�ȱʡΪtrue����Ҫ�ָ��ߣ�
  �� �� ֵ��
  ˵    ������ܴ�С/�Ƿ���Ҫ�ָ��ߵȵı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_frame_style(CONSOLE_GRAPHICS_INFO* const pCGI, const int block_width, const int block_high, const bool separator)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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
	/* ÿ��ɫ��ĸ��ӵĿ�Ⱥ͸߶�(�зָ����Ƿֱ�Ϊ2/1)����separator������� */
	pCGI->CFI.block_width_ext = pCGI->CFI.separator * 2;
	pCGI->CFI.block_high_ext = pCGI->CFI.separator * 1;
	/* ÿ��/ÿ�к��ָ��ߵ��ܿ�ȣ��ɿ��/�߶�+�ָ��߼������ */
	pCGI->CFI.bhigh = pCGI->CFI.block_high + pCGI->CFI.block_high_ext;
	pCGI->CFI.bwidth = pCGI->CFI.block_width + pCGI->CFI.block_width_ext;
	/*��Ϸ������ܿ�Ⱥ��ܸ߶�*/
	pCGI->CFI.total_high = pCGI->row_num * pCGI->CFI.bhigh - pCGI->CFI.separator * 1 + 1 * 2;
	pCGI->CFI.total_width = pCGI->col_num * pCGI->CFI.bwidth - pCGI->CFI.separator * 2 + 2 * 2;
	/* cmd���ڵĴ�С */
	pCGI->lines = pCGI->extern_up_lines + pCGI->top_status_line + pCGI->draw_frame_with_col_no + pCGI->CFI.total_high + pCGI->lower_status_line + pCGI->extern_down_lines + 4;
	pCGI->cols = pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.total_width + pCGI->extern_right_cols + 1;
	/*��״̬��yֵ*/
	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->top_status_line + pCGI->draw_frame_with_col_no + pCGI->CFI.total_high;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BORDER_TYPE �ṹ�е���ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int bg_color					������ɫ��ȱʡ -1��ʾ�ô��ڱ���ɫ��
			const int fg_color					��ǰ��ɫ��ȱʡ -1��ʾ�ô���ǰ��ɫ��
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int gmw_set_frame_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int bgcolor, const int fgcolor)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->CFI.bgcolor = (bgcolor == -1 ? pCGI->area_bgcolor : bgcolor);
	pCGI->CFI.fgcolor = (fgcolor == -1 ? pCGI->area_fgcolor : fgcolor);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6�����ͣ�ȱʡ4�֣�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��1 - ȫ˫�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_block_default_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const int type)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	const char* special[] = { "�X", "�^", "�[", "�a", "�T", "�U",
							"��", "��", "��", "��", "��", "��",
							"�V", "�\", "�Y", "�_", "�T", "��",
							"�W", "�]", "�Z", "�`", "��", "�U",
							NULL
	};
	strcpy(pCGI->CBI.top_left, special[0 + (type - 1) * 6]);			// "�X"
	strcpy(pCGI->CBI.lower_left, special[1 + (type - 1) * 6]);		// "�^"
	strcpy(pCGI->CBI.top_right, special[2 + (type - 1) * 6]);			// "�["
	strcpy(pCGI->CBI.lower_right, special[3 + (type - 1) * 6]);		// "�a"
	strcpy(pCGI->CBI.h_normal, special[4 + (type - 1) * 6]);			// "�T"	//Horizontal
	strcpy(pCGI->CBI.v_normal, special[5 + (type - 1) * 6]);			// "�U"	//Vertical*/
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const char *...					����6�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
***************************************************************************/
int gmw_set_block_linetype(CONSOLE_GRAPHICS_INFO* const pCGI, const char* top_left, const char* lower_left, const char* top_right, const char* lower_right, const char* h_normal, const char* v_normal)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	gmw_inner_deal_Chinese_character(pCGI->CBI.top_left, top_left);
	gmw_inner_deal_Chinese_character(pCGI->CBI.lower_left, lower_left);
	gmw_inner_deal_Chinese_character(pCGI->CBI.top_right, top_right);
	gmw_inner_deal_Chinese_character(pCGI->CBI.lower_right, lower_right);
	gmw_inner_deal_Chinese_character(pCGI->CBI.h_normal, h_normal);
	gmw_inner_deal_Chinese_character(pCGI->CBI.v_normal, v_normal);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ÿ����Ϸɫ��(����)�Ƿ���ҪС�߿�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const bool on_off					��true - ��Ҫ flase - ����Ҫ��ȱʡfalse��
  �� �� ֵ��
  ˵    �����߿�Լ��Ϊ�����Ʊ����˫��
***************************************************************************/
int gmw_set_block_border_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->CBI.block_border = on_off;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ����״̬��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��״̬�����ͣ���/�£�
			const bool on_off					��true - ��Ҫ flase - ����Ҫ��ȱʡtrue��
  �� �� ֵ��
  ˵    ����1��״̬�������Լ�����£�
			   1.1����״̬��ֻ��һ�У������������Ϸ�����/�б�����棬Ϊ��������ʼһ�У�����������Ͻ����������״̬�������꣩
			   1.2����״̬��ֻ��һ�У������������·����ߵ�����
			   1.3��״̬���Ŀ��Ϊ�������ȣ������Ϣ������ض�
		   2�����еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_status_line_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���������״̬������ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��״̬�����ͣ���/�£�
			const int normal_bgcolor			�������ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
			const int normal_fgcolor			�������ı�ǰ��ɫ��ȱʡ -1��ʾʹ�ô���ǰ��ɫ��
			const int catchy_bgcolor			����Ŀ�ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
			const int catchy_fgcolor			����Ŀ�ı�ǰ��ɫ��ȱʡ -1��ʾʹ������ɫ��
  ���������
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int gmw_set_status_line_color(CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const int normal_bgcolor, const int normal_fgcolor, const int catchy_bgcolor, const int catchy_fgcolor)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
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
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�к�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const bool on_off					��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���к�Լ��Ϊ��ĸA��ʼ�������У��������26�����a��ʼ������52��ͳһΪ*��ʵ��Ӧ�ò����ܣ�
			2���Ƿ���ʾ�кŵı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_rowno_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1; 
	pCGI->draw_frame_with_row_no = on_off;

	pCGI->start_x = pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2;

	pCGI->cols = pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.total_width + pCGI->extern_right_cols + 1;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�б�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const bool on_off					��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���б�Լ��Ϊ����0��ʼ�������У�����0-99������99ͳһΪ**��ʵ��Ӧ�ò����ܣ�
			2���Ƿ���ʾ�б�ı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_colno_switch(CONSOLE_GRAPHICS_INFO* const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->draw_frame_with_col_no = on_off;

	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->top_status_line + pCGI->draw_frame_with_col_no + pCGI->CFI.total_high;
	pCGI->start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->top_status_line;
	pCGI->lines = pCGI->extern_up_lines + pCGI->top_status_line + pCGI->draw_frame_with_col_no + pCGI->CFI.total_high + pCGI->lower_status_line + pCGI->extern_down_lines + 4;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡ CONSOLE_GRAPHICS_INFO �ṹ���еĸ���Աֵ
  ���������
  �� �� ֵ��
  ˵    ����1�����������ã���ӡ��ʽ�Զ���
			2������������������δ���ù������Բ�ʵ��
***************************************************************************/
int gmw_print(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��� CONSOLE_GRAPHICS_INFO �ṹ����ȱʡֵ���г�ʼ��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI������ṹָ��
		   const int row					����Ϸ����ɫ��������ȱʡ10��
		   const int col					����Ϸ����ɫ��������ȱʡ10��
		   const int bgcolor				���������ڱ���ɫ��ȱʡ COLOR_BLACK��
		   const int fgcolor				���������ڱ���ɫ��ȱʡ COLOR_WHITE��
  �� �� ֵ��
  ˵    �������ڱ�����/ǰ���ף�����16*8�����������޶������У�����״̬�����У����к�/�б꣬�������Ϊ˫�ߣ�ɫ����2/�߶�1/��С�߿���ɫ��
***************************************************************************/
int gmw_init(CONSOLE_GRAPHICS_INFO* const pCGI, const int row, const int col, const int bgcolor, const int fgcolor)
{
	/* �����ñ�� */
	pCGI->inited = CGI_INITED;
	//�����������
	gmw_set_rowcol(pCGI, row, col);
	//������ɫ
	gmw_set_color(pCGI, bgcolor, fgcolor);
	//����
	gmw_set_font(pCGI,"������");
	//��������
	gmw_set_ext_rowcol(pCGI);
	//�������
	gmw_set_frame_color(pCGI);
	gmw_set_frame_default_linetype(pCGI, 1);
	//ɫ�����
	gmw_set_frame_style(pCGI);
	gmw_set_block_border_switch(pCGI);
	gmw_set_block_default_linetype(pCGI, 1);
	//����״̬��
	gmw_set_status_line_switch(pCGI, TOP_STATUS_LINE);
	gmw_set_status_line_switch(pCGI, LOWER_STATUS_LINE);
	gmw_set_status_line_color(pCGI, TOP_STATUS_LINE);
	gmw_set_status_line_color(pCGI, LOWER_STATUS_LINE);
	//�кš��б�
	gmw_set_rowno_switch(pCGI);
	gmw_set_colno_switch(pCGI);
	//��ʱ
	gmw_set_delay(pCGI, DELAY_OF_DRAW_FRAME, 0);
	gmw_set_delay(pCGI, DELAY_OF_DRAW_BLOCK, 0);
	gmw_set_delay(pCGI, DELAY_OF_BLOCK_MOVED, BLOCK_MOVED_DELAY_MS);
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������Ϸ���
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
  �� �� ֵ��
  ˵    ��������ɲο�demo��Ч��
***************************************************************************/
int gmw_draw_frame(const CONSOLE_GRAPHICS_INFO* const pCGI)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//���ڳ�ʼ����
	cct_cls();
	cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);
	cct_setfontsize(pCGI->CFT.font_type, pCGI->CFT.font_size_high, pCGI->CFT.font_size_width);
	cct_setconsoleborder(pCGI->cols, pCGI->lines, pCGI->cols, pCGI->lines);
	//��Ϸ��ܴ�ӡ
	gmw_inner_print_all_kuang(pCGI);
	//���к�
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
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���״̬������ʾ��Ϣ
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int type							��ָ������/��״̬��
		   const char *msg						��������Ϣ
		   const char *catchy_msg					����Ҫ�ر��ע����Ϣ����������Ϣǰ��ʾ��
  �� �� ֵ��
  ˵    ����1���������޶�Ϊ����ܵĿ�ȣ����к��б�λ�ã����������ȥ
			2��������һ���ַ���ĳ���ֵ�ǰ������ᵼ�º������룬Ҫ����
***************************************************************************/
int gmw_status_line(const CONSOLE_GRAPHICS_INFO* const pCGI, const int type, const char* msg, const char* catchy_msg)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	int blank = 0;
	int max_len = pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.total_width;   //������Ŀ��
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
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʾĳһ��ɫ��(����Ϊ�ַ���������Ϊrow/col)
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value						����Ҫ��ʾ��ֵ
		   const BLOCK_DISPLAY_INFO *const bdi		����Ÿ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
  �� �� ֵ��
  ˵    ����1��BLOCK_DISPLAY_INFO �ĺ����ͷ�ļ����÷��ο���������
			2��bdi_valueΪ BDI_VALUE_BLANK ��ʾ�հ׿飬Ҫ���⴦��
***************************************************************************/
int gmw_draw_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//ɫ�����Ͻǵ�����
	int x, y;
	x = pCGI->start_x + 2 + col_no * pCGI->CFI.bwidth;
	y = pCGI->start_y + 1 + row_no * pCGI->CFI.bhigh;
	int a = gmw_inner__draw_block_by_xy(pCGI, x, y, bdi_value, bdi);
	return a; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ƶ�ĳһ��ɫ��
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value						����Ҫ��ʾ��ֵ
		   const int blank_bdi_value				���ƶ����������ڶ���Ч����ʾʱ���ڱ�ʾ�հ׵�ֵ��һ��Ϊ0���˴���Ϊ�������룬�ǿ��ǵ����ܳ��ֵ����������
		   const BLOCK_DISPLAY_INFO *const bdi		�������ʾֵ/�հ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
		   const int direction						���ƶ�����һ�����֣������cmd_gmw_tools.h
		   const int distance						���ƶ����루��1��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_move_block(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const int blank_bdi_value, const BLOCK_DISPLAY_INFO* const bdi, const int direction, const int distance)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//ɫ�����Ͻǵ�����
	int x, y;
	x = pCGI->start_x + 2 + col_no * pCGI->CFI.bwidth;
	y = pCGI->start_y + 1 + row_no * pCGI->CFI.bhigh;
	//����
	if (direction == UP_TO_DOWN) {
		for (int i = 0; i < distance; i++) {
			for (int j = 1; j <= pCGI->CFI.bhigh; j++) {
				Sleep(pCGI->delay_of_block_moved);
				gmw_inner__draw_block_by_xy(pCGI, x, y + (j - 1) + i * pCGI->CFI.bhigh, blank_bdi_value, bdi);  //�ɫ��
				gmw_inner__draw_block_by_xy(pCGI, x, y + j + i * pCGI->CFI.bhigh, bdi_value, bdi);  //�Ȼ�ɫ��
			}
			if (pCGI->CFI.separator)
				cct_showstr(x, y + pCGI->CFI.block_high + i * pCGI->CFI.bhigh, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->CFI.block_width / 2);
		}
	}
	//����
	if (direction == DOWN_TO_UP) {
		for (int i = 0; i < distance; i++) {
			for (int j = 1; j <= pCGI->CFI.bhigh; j++) {
				Sleep(pCGI->delay_of_block_moved);
				gmw_inner__draw_block_by_xy(pCGI, x, y - (j - 1) - i * pCGI->CFI.bhigh, blank_bdi_value, bdi);  //�ɫ��
				gmw_inner__draw_block_by_xy(pCGI, x, y - j - i * pCGI->CFI.bhigh, bdi_value, bdi);  //�Ȼ�ɫ��
			}
			if (pCGI->CFI.separator)
				cct_showstr(x, y - 1 - i * pCGI->CFI.bhigh, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, pCGI->CFI.block_width / 2);
		}
	}
	//����
	if (direction == LEFT_TO_RIGHT) {
		for (int i = 0; i < distance; i++) {
			for (int j = 1; j <= pCGI->CFI.bwidth / 2; j++) {
				Sleep(pCGI->delay_of_block_moved);
				gmw_inner__draw_block_by_xy(pCGI, x + 2 * (j - 1) + i * pCGI->CFI.bwidth, y, blank_bdi_value, bdi);  //�ɫ��
				gmw_inner__draw_block_by_xy(pCGI, x + 2 * j + i * pCGI->CFI.bwidth, y, bdi_value, bdi);  //�Ȼ�ɫ��
			}
			if (pCGI->CFI.separator) {
				for (int j = 0; j < pCGI->CFI.block_high; j++)
					cct_showstr(x + pCGI->CFI.block_width + i * pCGI->CFI.bwidth, y + j, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			}
		}
	}
	//����
	if (direction == RIGHT_TO_LEFT) {
		for (int i = 0; i < distance; i++) {
			for (int j = 1; j <= pCGI->CFI.bwidth / 2; j++) {
				Sleep(pCGI->delay_of_block_moved);
				gmw_inner__draw_block_by_xy(pCGI, x - 2 * (j - 1) - i * pCGI->CFI.bwidth, y, blank_bdi_value, bdi);  //�ɫ��
				gmw_inner__draw_block_by_xy(pCGI, x - 2 * j - i * pCGI->CFI.bwidth, y, bdi_value, bdi);  //�Ȼ�ɫ��
			}
			if (pCGI->CFI.separator) {
				for (int j = 0; j < pCGI->CFI.block_high; j++)
					cct_showstr(x - 2 - i * pCGI->CFI.bwidth, y + j, pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
			}
		}
	}
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������̻����
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   int &MAction							��������� CCT_MOUSE_EVENT�����ֵ��Ч��Ϊ MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK/MOUSE_RIGHT_BUTTON_CLICK ����֮һ
													   ������� CCT_KEYBOARD_EVENT�����ֵ��Ч
		   int &MRow								��������� CCT_MOUSE_EVENT �� MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &MCol								��������� CCT_MOUSE_EVENT �� MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode1							��������� CCT_KEYBOARD_EVENT�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ��һ����
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode2							��������� CCT_KEYBOARD_EVENT�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ�ڶ���������ǵ����룬��Ϊ0��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   const bool update_lower_status_line		������ƶ�ʱ���Ƿ�Ҫ�ڱ���������ʾ"[��ǰ���] *��*��/λ�÷Ƿ�"����Ϣ��true=��ʾ��false=����ʾ��ȱʡΪtrue��
  �� �� ֵ����������Լ��
		   1�����������ƶ����õ���MRow/MCol�봫�����ͬ(���ָ��΢С���ƶ�)���򲻷��أ�������
							  �õ����зǷ�λ�ã��򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
							  �õ���MRow/MCol�봫��Ĳ�ͬ(��������һ���仯)������ update_lower_status_line ����������״̬����ʾ"[��ǰ���] *��*��"���ٷ���MOUSE_ONLY_MOVED����Щ��Ϸ���غ�Ҫ����ɫ��Ĳ�ͬ��ɫ��ʾ��
		   2������ǰ������������ҵ�ǰ���ָ��ͣ��������Ϸ�����*��*���ϣ��򷵻� CCT_MOUSE_EVENT ��MAction Ϊ MOUSE_LEFT_BUTTON_CLICK, MRow Ϊ�кţ�MCol Ϊ�б�
								  �ҵ�ǰ���ָ��ͣ���ڷǷ����򣨷���Ϸ������Ϸ�����еķָ��ߣ����򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
		   3������ǰ�������Ҽ������ж����ָ��ͣ�������Ƿ�Ϸ���ֱ�ӷ��� CCT_MOUSE_EVENT ��MAction Ϊ MOUSE_RIGHT_BUTTON_CLICK, MRow��MColȡ��ǰֵ����Ϊ�������ǵ��Ҽ������Ҫ���꣩
		   4��������¼����ϵ�ĳ������˫���밴��������ֱ�ӷ��� CCT_KEYBOARD_EVENT��KeyCode1/KeyCode2��Ϊ��Ӧ�ļ���ֵ
 ˵    ����ͨ������ cmd_console_tools.cpp �е� read_keyboard_and_mouse ����ʵ��
***************************************************************************/
int gmw_read_keyboard_and_mouse(const CONSOLE_GRAPHICS_INFO* const pCGI, int& MAction, int& MRow, int& MCol, int& KeyCode1, int& KeyCode2, const bool update_lower_status_line)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	int newrow, newcol;    //�µ��кš��б�
	int MX, MY;
	bool add = 1;  //����Ϸ�
	//��Чλ�õ�ʼ���� x,yֵ
	int start_x = pCGI->start_x + 2;
	int start_y = pCGI->start_y + 1;
	int end_x = pCGI->start_x + pCGI->CFI.total_width - 2;
	int end_y = pCGI->start_y + pCGI->CFI.total_high - 1;
	cct_enable_mouse();
	while (1) {
		int action = cct_read_keyboard_and_mouse(MX, MY, MAction, KeyCode1, KeyCode2);
		//�����¼�
		if (action == CCT_KEYBOARD_EVENT)
			return CCT_KEYBOARD_EVENT;

		//����¼�
		else {
			//�Ҽ�ֱ�ӷ���
			if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
				MRow = (MY - start_y) / pCGI->CFI.bhigh;
				MCol = (MX - start_x) / pCGI->CFI.bwidth;
				return CCT_MOUSE_EVENT;
			}
			else {
				//�ж�λ���Ƿ�Ϸ�
				bool condition_xy = (MX >= start_x && MX < end_x && MY >= start_y && MY < end_y);    //�Ϸ���Χ
				bool condition_else = pCGI->CFI.separator && (((MX - pCGI->start_x) % pCGI->CFI.bwidth == 0 || (MX - pCGI->start_x) % pCGI->CFI.bwidth == 1) || (MY - pCGI->start_x) % pCGI->CFI.bhigh == 0);   //�ڷָ�����
				bool condition = condition_xy && !condition_else;

				//λ�úϷ�
				if (condition) {
					if (MAction == MOUSE_LEFT_BUTTON_CLICK) {
						MRow = (MY - start_y) / pCGI->CFI.bhigh;
						MCol = (MX - start_x) / pCGI->CFI.bwidth;
						return CCT_MOUSE_EVENT;
					}
					else if (MAction == MOUSE_ONLY_MOVED) {
						//�����кţ��б��
						newcol = (MX - start_x) / pCGI->CFI.bwidth;
						newrow = (MY - start_y) / pCGI->CFI.bhigh;
						if (newrow == MRow && newcol == MCol)
							continue;   //˵�����λ�û���ͬһ��ɫ��
						else {
							MRow = newrow;
							MCol = newcol;
							char temp[256];
							sprintf(temp, "[��ǰ���] %c��%d��", char('A' + MRow), MCol);
							gmw_status_line(pCGI, LOWER_STATUS_LINE, temp, NULL);
							return CCT_MOUSE_EVENT;
						}
					}
					else
						continue;
				}
				else {
					if (add)
						gmw_status_line(pCGI, LOWER_STATUS_LINE, "[��ǰ���] λ�÷Ƿ�", NULL);
					else
						add = 0;
				}
			}
		}
	}
	return -1; //�˾�ɸ�����Ҫ�޸�
}
