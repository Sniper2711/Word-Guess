#include <iostream>
#include <windows.h>
using namespace std;
string word, temp, curr;
int len, clen, r, cnt, hp = 10;
bool Corr[15], hintUnlock = false, hintUsed = false;
unordered_map<char, bool> guessed;
unordered_map<string, string> settings;
vector<string> words;
ofstream logging;
void dis_color(bool correct, int mtime = 1000) {
	system((correct ? "color 27" : "color 47"));
	Sleep(mtime);
	system("color 07");
}
void UserError(string info, int time = 1000) {
	system("cls");
	cout << "����:" << info;
	Sleep(time);
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
	printf("Guessed : %d/%d (%d%%)\n", cnt, clen, cnt * 100 / clen);
	cout << "Characters guessed:" << endl;
	for(int i = 0;i < len;i++) printf("%d ", Corr[i]);
	cout << endl << "Guessed chars:" << endl;
	for(char c = 'a';c <= 'z';c++) if(guessed[c]) cout << c << ' ';
	cout << endl << "Settings:" << endl;
	for(pair<string, string> s : settings) cout << s.first << '=' << s.second << endl;
	cout << "------Debug Info------" << endl;
}
void showHelp(int type = 0) {
	switch(type) {
		case 0:
			system("cls");
			cout << "��ӭ����´���Ϸ!" << endl;
			cout << "��Ϸ��������: ��������һ�����ʵĳ��ȣ�ͨ�����������������е���ĸ�����ղ³����ʡ�" << endl;
			cout << "�²����: ���뵥����ĸ��ϵͳ���鵥�������е������ĸ�Ĵ�Сд�������û�У�����󣬷�֮����ȷ��" << endl;
			cout << "          �����֮��������һ����ĸ���ܲ²��Ӧ�����д�д��Сд��ĸ����ϵͳ����¼�¹�����ĸ�������ظ��²⡣" << endl;
			cout << "����ֵ: ��ʼ����ֵΪ10�㣬ÿ�´�һ����ĸ-1���´�ʧ��-2������ʱ��Ϸʧ�ܡ�";
			cout << "ʤ���ж�: �³����ʼ�Ϊʤ��������ֵ���㼴Ϊʧ�ܡ�\n" << endl;
			cout << "���׼���: ������ڲ²������ͨ����֪��ĸ֪���˾���ĵ��ʣ�ֱ�������������ʲ�ȷ�ϣ�ϵͳ���ж�����" << endl;
			cout << "��ǰ�´ʳɹ��ܰ������ø��ߵ��������³�ȫ����ĸֻ�ܻ�õ�ǰ״̬����͵�����������ʧ��Ҳ���۳�2������ֵ��\n" << endl;
			cout << "��ʾ: ���ҽ�������ֵ����6��δ֪��ĸ��3��������ʱ����ʾ����������ʾ����ʹ��һ�Ρ�" << endl;
			cout << "��ʾЧ��: ����0��ʹ����ʾ����ʾ����ʾ�����е������� ��һ��δ֪��ĸ ��ͬ�Ĵ�Сд��ĸ��" << endl;
			cout << "�Ƚ�������ϵͳ: ������Ϸ������ϵͳ������ʣ������ֵ�Ͳ³���ĸ���������Ƚ׺�������" << endl;
			cout << "�鿴���ڵȽ�/�����Ľ�һ����Ϣ���뷵�ز�����2��\n" << endl;
			cout << "��Ϸ���л���: ������Ϸ�����󣬰������ֱ�ӿ�ʼ��һ�֣��˳���Ϸ��ֱ�ӹر�Ӧ�á�" << endl;
			system("pause");
			break;
		case 1:
			system("cls");
			cout << "�Ƚ��������Ķ�Ӧ: " << endl;
			cout << "�Ƚ�   Perfect   Good   Fail" << endl;
			cout << "����   PC,Ex,S   A--C    F\n" << endl;
			cout << "���ڳ���С��10�ĵ��ʣ�ȡ��������Ҫ�ı�׼: " << endl;
			cout << "ʣ������ֵ   �³���ĸ�ٷֱ�   ����" << endl;
			cout << "10                ����         PC" << endl;
			cout << "9                 ����         Ex" << endl;
			cout << "7--8             0%--65%       S" << endl;
			cout << "7--8            65%--100%      A" << endl;
			cout << "4--6             0%--50%       S" << endl;
			cout << "4--6            50%--75%       A" << endl;
			cout << "4--6            75%--100%      B" << endl;
			cout << "2--3             0%--45%       A" << endl;
			cout << "2--3            45%--70%       B" << endl;
			cout << "2--3            70%--100%      C" << endl;
			cout << "1                 ����         C" << endl;
			cout << "0                0%--99%       F" << endl;
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
	double percent = double(cnt * 1.0 / clen);
	if(hp <= 0) return 'F'; // Fail
	if(hp == 10) return 'P'; // Perfectly Clear
	if(hp == 9) return 'E'; // Extreme
	if(hp == 1) return 'C';
	if(hp <= 8 && hp >= 7) {
		if(percent <= 0.65) return 'S';
		else return 'A';
	}
	else if(hp <= 6 && hp >= 4) {
		if(percent <= 0.5) return 'S';
		else if(percent > 0.5 && percent <= 0.75) return 'A';
		else return 'B';
	}
	else if(hp <= 3 && hp >= 2) {
		if(percent <= 0.45) return 'A';
		else if(percent > 0.45 && percent <= 0.7) return 'B';
		else return 'C';
	}
}
