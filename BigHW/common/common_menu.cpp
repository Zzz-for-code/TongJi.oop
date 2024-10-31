/* ������ 2352847 �ž��� */
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
using namespace std;

struct detail {
	int number;   //�˵�����
	char start_word;  //�˵���һ���ַ�
	char end_word;  //�˵����һ���ַ�
	char quit_word;  //�˳��ַ�
	char str[10][100];   //��Ų˵�����
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
	cout << "[��ѡ��:]";
}

char menu(int option, int num)
{
	struct detail s[10];
	s[0] = { 10,'1','9','0', {
	"1.������",
	"2.������(������¼)",
	"3.�ڲ�������ʾ(����)",
	"4.�ڲ�������ʾ(����+����)",
	"5.ͼ�ν�-Ԥ��-������Բ��",
	"6.ͼ�ν�-Ԥ��-����ʼ���ϻ�n������",
	"7.ͼ�ν�-Ԥ��-��һ���ƶ�",
	"8.ͼ�ν�-�Զ��ƶ��汾",
	"9.ͼ�ν�-��Ϸ��",
	"0.�˳�" } };

	s[1] = { 10,'1','9','0',{
	" 1.�ڲ����飬���ɳ�ʼ״̬��Ѱ���Ƿ��г�ʼ��������",
	" 2.�ڲ����飬������ʼ����������0�����䲢��0���",
	" 3.�ڲ����飬������ʼ������������������ʾ",
	" 4.n*n�Ŀ��(�޷ָ���)����ʾ��ʼ״̬",
	" 5.n*n�Ŀ��(�зָ���)����ʾ��ʼ״̬",
	" 6.n*n�Ŀ��(�޷ָ���)����ʾ��ʼ״̬����ʼ��������",
	" 7.n*n�Ŀ��(�зָ���)��������ʼ�����������ʾ������ʾ",
	" 8.cmdͼ�ν���������(�зָ��ߣ�����ƶ�ʱ��ʾ���꣬�Ҽ��˳�)",
	" 9.cmdͼ�ν���������",
	" 0.�˳�" } };

	s[2] = { 8,'A','G','Q',{
	"A.�������ҳ����������ʶ",
	"B.���������һ���������ֲ�����ʾ��",
	"C.���������һ�أ��ֲ�����ʾ��",
	"D.αͼ�ν����������ѡ��һ��ɫ�飨�޷ָ��ߣ�",
	"E.αͼ�ν����������ѡ��һ��ɫ�飨�зָ��ߣ�",
	"F.αͼ�ν������һ���������ֲ��裩",
	"G.αͼ�ν���������",
	"Q.�˳�" } };

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

