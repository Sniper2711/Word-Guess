#include <bits/stdc++.h>
#include <fstream>
#include <windows.h>
#include "header.h"
#include "rank.h"
using namespace std;
#define CLS system("cls")
string word, temp, curr;
int len, r, cnt, spCnt, hp = 10;
bool Corr[15], hintUnlock = false, hintUsed = false;
unordered_map<char, bool> guessed;
unordered_map<string, string> settings;
vector<string> words;
ofstream logging;
void launchInit() {
	ifstream ifs;
	ifs.open("words.txt");
	if(!ifs.is_open()) {
		cout << "[Critical] Failed to open input file:Error opening file \"words.txt\"" << endl;
		cout << "�����������󣬳����޷��������С�" << endl;
		Sleep(3000);
		exit(1);
	}
	while(getline(ifs, temp)) {
		if(temp[temp.length()-1] == '.') break;
		if(temp.length() <= 4 || temp.length() >= 21) continue;
		words.push_back(temp);
	}
	ifs.close();
	ifs.open("settings.txt");
	if(!ifs.is_open()) {
		cout << "[Critical] Failed to open input file.Error opening file \"settings.txt\"" << endl;
		cout << "�����������󣬳����޷��������С�" << endl;
		Sleep(3000);
		system("pause");
		exit(1);
	}
	while(ifs >> temp) {
		if(temp[0] == '.') break;
		if(temp[0] == '#') continue;
		for(int i = 0;i < temp.length();i++) {
			if(temp[i] == '=') {
				settings[temp.substr(0, i)] = temp.substr(i+1);
			}
		}
	}
	CLS;
	if(settings["Flash"] == "1") {
		cout << "**���ѿ�����Ļ��˸**" << endl;
		cout << "**��Ҳ������settings.txt�е�����˸����Ŀ��ء�**\n" << endl;
		cout << "��������ﾯ��:" << endl;
		cout << "������Ⱥ��������Ϸʱ����������ض�����˸������ܵ��̼������ܳ����������һ���֢״��" << endl;
		cout << "���������Ϸ�ие��κ����岻�ʣ������������ڣ�ͷ�Ρ����ġ����������岻���������Ƶ�" << endl;
		cout << "������ֹͣ��Ϸ��������Ҫ������ѯ����ҽʦ��" << endl;
		Sleep(3000);
	}
	CLS;
	cout << "��ӭ����´���Ϸ!" << endl;
	cout << "ͨ���²�һ�������п����е��ַ���ʤ��������ĸ������" << endl;
	cout << "������������Դ�ļ�Ŀ¼�µ�settings.txt�鿴���顣" << endl;
	Sleep(1250);
}
void showDebugInfo() {
	cout << "------Debug Info------" << endl;
	cout << "Word: " << word << endl;
	printf("Word length: %d\n", len);
	printf("Guessed and special: %d, %d\n", cnt, spCnt);
	cout << "Guess info:" << endl;
	for(bool b : Corr) printf("%d ", b);
	cout << endl << "Guessed chars:" << endl;
	for(char c = 'a';c <= 'z';c++) if(guessed[c]) cout << c << ' ';
	cout << endl << "Settings:" << endl;
	for(pair<string, string> s : settings) cout << s.first << '=' << s.second << endl;
	cout << "------Debug Info------" << endl;
}
void start() {
	cnt = 0, hp = 10;
	memset(Corr, false, sizeof(Corr));
	hintUnlock = hintUsed = false;
	for(char c = 'a';c <= 'z';c++) {
		guessed[c] = false;
	}
	srand(time(0));
	r = rand() % words.size();
	word = words.at(r);
	len = word.length();
	CLS;
	system("color 07");
	cout << "���ڳ�ѡ�ʻ�.";
	Sleep(250);
	cout << '.';
	Sleep(250);
	cout << '.';
	CLS;
	if(settings["Debug"] == "1") showDebugInfo();
	printf("��ӵ��%d���ʼ����ֵ��������ʱ����Ϸʧ�ܡ�\n", hp);
	cout << "���ҽ�������ֵ����6��δ֪��ĸ��3��������ʱ����ʾ����������ʾ����ʹ��һ�Ρ�\n" << endl;
	cout << "���ʳ���: " << len << endl;
	for(int i = 0;i < len;i++) {
		if(!isalpha(word[i])) {
			cout << word[i];
			spCnt++;
		}
		else cout << '_';
	}
	cout << endl << "�����뵥����ĸ����������(0��ʾ��ʾ):";
}
void ending(string message, bool win = true) {
	CLS;
	cout << message << endl;
	if(settings["Flash"] == "1") dis_color(win, 750);
	cout << "��ȷ�ĵ�����:" << endl;
	cout << word << endl;
	printf("����ֵ: %d/10\n", hp);
	printf("�³���ĸ: %d/%d (%d%%)\n", cnt, len, (cnt * 100 / len));
	cout << "����.";
	Sleep(500);
	cout << '.';
	Sleep(500);
	cout << '.' << endl;
	char judge = judgeResult(len, cnt, hp);
	switch(judge) {
		case 'P':
			if(settings["Flash"] == "1") system("color E0");
			AP();
			cout << "   All Perfect!!!" << endl;
			cout << "�����������У����������������: 1st!!!" << endl;
			break;
		case 'V':
			if(settings["Flash"] == "1") system("color 90");
			V();
			cout << "        V��!!" << endl;
			cout << "�����������У����������������: 2nd!!" << endl;
			break;
		case 'S':
			if(settings["Flash"] == "1") system("color B0");
			S();
			cout << "        S��!" << endl;
			cout << "�����������У����������������: 3rd!" << endl;
			break;
		case 'A':
			A();
			cout << "        A��" << endl;
			cout << "�����������У����������������: 4th" << endl;
			break;
		case 'B':
			B();
			cout << "        B��" << endl;
			cout << "�����������У����������������: 5th" << endl;
			break;
		case 'C':
			C();
			cout << "        C��" << endl;
			cout << "�����������У����������������: 6th" << endl;
			break;
		case 'F':
			if(settings["Flash"] == "1") system("color C0");
			F();
			cout << "     F����ʧ��" << endl;
			break;
	}
	cout << "�˳���Ϸ��رմ��ڣ�����������¿�ʼ��" << endl;
	system("pause");
}
int main() {
	cout << "������..." << endl;
	launchInit();
	start();
	while(true) {
		int gs = gameStatus(cnt, spCnt, len, hp);
		if(gs == 1) {
			ending("ͨ��! ��ɲ´���ս", true);
			start();
			continue;
		}
		else if(gs == -1) {
			ending("δͨ��������ֵ�ѹ���", false);
			start();
			continue;
		}
		getline(cin, curr);
		if(curr.length() == 1) {
			if(curr[0] == '0') {
				if(hintUnlock) {
					char target, targeto;
					for(int i = 0;i < len;i++) {
						if(!Corr[i]) {
							target = word[i];
							targeto = isupper(target) ? tolower(target) : toupper(target);
							break;
						}
					}
					guessed[target] = guessed[targeto] = true;
					int ret = update(word, Corr, target);
					ret += update(word, Corr, targeto);
					cnt += ret;
					hintUsed = true;
					CLS;
					printf("��ʾ��ʹ�ã������й�����%d����ĸ%c��%c��\n", ret, char(toupper(target)), char(tolower(target)));
					printf("����%d��δ֪��ĸ��", len - cnt - spCnt);
					Sleep(1500);
				}
				else {
					UserError("��Ч�Ĳ²�:��ʾδ��������ʹ�á�\n���β²ⲻ������");
				}
			}
			else if(!isalpha(curr[0])) {
				UserError("��Ч�Ĳ²�:�����ַ�����ĸ��\n���β²ⲻ������");
			}
			else if(guessed[curr[0]]) {
				UserError("��Ч�Ĳ²�:���Ѿ��¹������ĸ�ˡ�\n���β²ⲻ������");
			}
			else {
				char curro = isupper(curr[0]) ? tolower(curr[0]) : toupper(curr[0]);
				guessed[curr[0]] = guessed[curro] = true;
				int ret = update(word, Corr, curr[0]);
				ret += update(word, Corr, curro);
				if(ret != 0) {
					cnt += ret;
					CLS;
					printf("��ȷ! �����й�����%d����ĸ%c��%c��\n", ret, char(toupper(curro)), char(tolower(curro)));
					printf("����%d��δ֪��ĸ��", len - cnt - spCnt);
					if(settings["Flash"] == "1") dis_color(true, 1250);
					else Sleep(1250);
				}
				else {
					hp--;
					CLS;
					cout << "����! ʧȥ1������ֵ��";
					if(settings["Flash"] == "1") dis_color(false);
					else Sleep(1000);
				}
			}
		}
		else {
			CLS;
			bool flag = true;
			for(char c : word) {
				if(c != ' ' && c != '-' && c != '\'' && !isalpha(c)) {
					flag = false;
					break;
				}
			}
			if(!flag || curr.length() != word.length())
				UserError("��Ч�Ĳ´�:�����ʽ�Ƿ���\n���β²ⲻ������");
			else {
				if(curr == word) {
					ending("��ϲ! ��ǰ�´ʳɹ�", true);
					start();
					continue;
				}
				else {
					cout << "�´�ʧ�ܣ�ʧȥ1������ֵ";
					if(settings["Flash"] == "1") dis_color(false);
					else Sleep(1000);
					hp--;
				}
			}
		}
		CLS;
		if(settings["Debug"] == "1") showDebugInfo();
		printf("���ʳ���: %d\n", len);
		printf("��ǰ����ֵ: %d/10\n", hp);
		for(int i = 0;i < len;i++) {
			if(Corr[i] || isalpha(word[i]) == 0) cout << word[i];
			else cout << '_';
		}
		cout << endl << "�Ѿ��¹����ַ�����ĸ������Сд��:" << endl;
		for(char c = 'a';c <= 'z';c++) {
			if(guessed[c]) cout << c << ' ';
		}
		cout << endl << "������а���ֱ�Ӳ³����������ﲢ�س�ȷ����\n";
		if(hp <= 5 && len - cnt > 2 && !hintUsed) {
			hintUnlock = true;
			cout << endl << "**��ʾ�ѽ�������Ҫ��ʾ������0**\n";
		}
		else hintUnlock = false;
		cout << endl << "�����뵥����ĸ����������(0��ʾ��ʾ):";
	}
	return 0;
}
