#include <iostream>
#include <windows.h>
using namespace std;
#define CLS system("cls")
string word, temp, curr;
int len, clen, r, cnt, hp = 10;
bool Corr[15], hintUnlock = false, hintUsed = false;
unordered_map<char, bool> guessed;
unordered_map<string, string> settings;
vector<string> words;
void dis_color(bool correct, int mtime = 1000) {
	system((correct ? "color 27" : "color 47"));
	Sleep(mtime);
	system("color 07");
}
void UserError(string info, int mtime = 1000) {
	system("cls");
	cout << "����:" << info;
	Sleep(mtime);
}
int gameStatus() {
	if(cnt == clen) return 1;
	if(hp <= 0) {
		hp = 0;
		return -1;
	}
	return 0;
}
void showDebugInfo() {
	cout << "------Debug Info------" << endl;
	cout << "Word: " << word << endl;
	printf("Word length and alpha length: %d, %d\n", len, clen);
	printf("Health: %d\n", hp);
	printf("Guessed: %d/%d (%d%%)\n", cnt, clen, cnt * 100 / clen);
	printf("Hint Unlock and Used: %d, %d\n", hintUnlock, hintUsed);
	cout << "Characters guessed:" << endl;
	for(int i = 0;i < len;i++) printf("%d ", Corr[i]);
	cout << endl << "Guessed alphas:" << endl;
	for(char c = 'a';c <= 'z';c++) if(guessed[c]) cout << c << ' ';
	cout << endl << "Settings:" << endl;
	for(pair<string, string> s : settings) cout << s.first << '=' << s.second << endl;
	cout << endl << "To view debug command help, enter 3." << endl;
	cout << "------Debug Info------" << endl;
}
void showHelp(int type = 1) {
	switch(type) {
		case 1:
			system("cls");
			cout << "��ӭ����´���Ϸ!" << endl;
			cout << "��Ϸ��������: ��������һ�����ʵĳ��ȣ�ͨ�����������������е���ĸ�����ղ³����ʡ�" << endl;
			cout << "�²����: ���뵥����ĸ��ϵͳ���鵥�������е������ĸ�Ĵ�Сд�������û�У�����󣬷�֮����ȷ��" << endl;
			cout << "          �����֮��������һ����ĸ���ܲ²��Ӧ�����д�д��Сд��ĸ����ϵͳ����¼�¹�����ĸ�������ظ��²⡣" << endl;
			cout << "����ֵ: ��ʼ����ֵΪ10�㣬ÿ�´�һ����ĸ-1���´�ʧ��-2������ʱ��Ϸʧ�ܡ�";
			cout << "ʤ���ж�: �³����ʼ�Ϊʤ��������ֵ���㼴Ϊʧ�ܡ�\n" << endl;
			cout << "���׼���: ������ڲ²������ͨ����֪��ĸ֪���˾���ĵ��ʣ�ֱ�������������ʲ�ȷ�ϣ�ϵͳ���ж����󡣵�ʧ��Ҳ���۳�2������ֵ��\n" << endl;
			cout << "��ʾ: ���ҽ�������ֵ����6��δ֪��ĸ��3��������ʱ����ʾ����������ʾ����ʹ��һ�Ρ�" << endl;
			cout << "��ʾЧ��: ����0��ʹ����ʾ����ʾ����ʾ�����е������� ��һ��δ֪��ĸ ��ͬ�Ĵ�Сд��ĸ��\n" << endl;
			cout << "�Ƚ�������ϵͳ: ������Ϸ������ϵͳ������ʣ������ֵ�Ͳ³���ĸ���������Ƚ׺�������" << endl;
			cout << "�鿴���ڵȽ�/�����Ľ�һ����Ϣ���뷵�ز�����2��\n" << endl;
			cout << "��Ϸ���л���: ������Ϸ�����󣬰������ֱ�ӿ�ʼ��һ�֣��˳���Ϸ��ֱ�ӹر�Ӧ�á�" << endl;
			system("pause");
			break;
		case 2:
			system("cls");
			cout << "ʣ������ֵ  ����" << endl;
			cout << "10          Excellent" << endl;
			cout << "9--7        A" << endl;
			cout << "6--4        B" << endl;
			cout << "3--1        C" << endl;
			cout << "0           Fail" << endl;
			cout << "����        Unknown" << endl;
			system("pause");
			break;
		case 3:
			system("cls");
			cout << "How to open commend mode: enter \"-cmd\"" << endl;
			cout << "Argument format: <Name:Type>" << endl;
			cout << "Mandatory / Optional arguments: <Mandatory>, [Optional]" << endl;
			cout << "Command usage:" << endl;
			cout << "-var <key:string> <value> : Assign variable <key:string> of <value>. Assignable variables: hp, hintUsed." << endl;
			cout << "-set <key:string> <value:string> : Set system setting <key> to <value:string>, custom settings are acceptable(but useless)." << endl;
			system("pause");
			break;
	}
}
int update(char t) {
	int ret = 0;
	for(int i = 0;i < word.length();i++) {
		if(word.at(i) == t) {
			ret++;
			Corr[i] = true;
		}
	}
	return ret;
}
char judgeResult() {
	if(hp == 10) return 'E'; // Excellent
	else if(hp <= 9 && hp >= 7) return 'A';
	else if(hp <= 6 && hp >= 4) return 'B';
	else if(hp <= 1 && hp >= 3) return 'C';
	else if(hp == 0 || hp == -1) return 'F'; // Fail
	else return 'U'; // Unknown
}
