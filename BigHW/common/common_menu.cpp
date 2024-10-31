/* 大数据 2352847 张静敏 */
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
using namespace std;

struct detail {
	int number;   //菜单项数
	char start_word;  //菜单第一项字符
	char end_word;  //菜单最后一项字符
	char quit_word;  //退出字符
	char str[10][100];   //存放菜单内容
};

void print_menu(char content[][100])
{
	int i, len = (int)strlen(content[0]);
	for (i = 1; content[i][0] != '\0'; i++) {
		if ((int)strlen(content[i]) > len)
			len = strlen(content[i]);
	}
	for (i = 0; i < len; i++)
		cout << "-";
	cout << endl;
	for (i = 0; content[i][0] != '\0'; i++)
		cout << content[i] << endl;
	for (i = 0; i < len; i++)
		cout << "-";
	cout << endl;
	cout << "[请选择:]";
}

char menu(int option, int num)
{
	struct detail s[10];
	s[0] = { 10,'1','9','0', {
	"1.基本解",
	"2.基本解(步数记录)",
	"3.内部数组显示(横向)",
	"4.内部数组显示(纵向+横向)",
	"5.图形解-预备-画三个圆柱",
	"6.图形解-预备-在起始柱上画n个盘子",
	"7.图形解-预备-第一次移动",
	"8.图形解-自动移动版本",
	"9.图形解-游戏版",
	"0.退出" } };

	s[1] = { 10,'1','9','0',{
	" 1.内部数组，生成初始状态，寻找是否有初始可消除项",
	" 2.内部数组，消除初始可消除项后非0项下落并用0填充",
	" 3.内部数组，消除初始可消除项后查找消除提示",
	" 4.n*n的框架(无分隔线)，显示初始状态",
	" 5.n*n的框架(有分隔线)，显示初始状态",
	" 6.n*n的框架(无分隔线)，显示初始状态及初始可消除项",
	" 7.n*n的框架(有分隔线)，消除初始可消除项后显示消除提示",
	" 8.cmd图形界面完整版(有分隔线，鼠标移动时显示坐标，右键退出)",
	" 9.cmd图形界面完整版",
	" 0.退出" } };

	s[2] = { 8,'A','G','Q',{
	"A.命令行找出可消除项并标识",
	"B.命令行完成一次消除（分步骤显示）",
	"C.命令行完成一关（分步骤显示）",
	"D.伪图形界面下用鼠标选择一个色块（无分隔线）",
	"E.伪图形界面下用鼠标选择一个色块（有分隔线）",
	"F.伪图形界面完成一次消除（分步骤）",
	"G.伪图形界面完整版",
	"Q.退出" } };

	print_menu(s[option].str);
	char ch;
	ch = _getch();
	char word = ch;
	if (ch >= 'a' && ch <= 'z')
		ch += 'A' - 'a';
	if (ch == s[option].quit_word) {
		cout << word << endl;
		return ch;
	}
	else {
		if (ch >= s[option].start_word && ch <= s[option].end_word)
			cout << word << endl;
		while (ch < s[option].start_word || ch > s[option].end_word) {
			ch = _getch();
			char word = ch;
			if (ch >= 'a' && ch <= 'z')
				ch += 'A' - 'a';
			if (ch >= s[option].start_word && ch <= s[option].end_word) {
				cout << word << endl;
				break;
			}
		}
		Sleep(500);
		return ch;
	}
}

