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
	while(ifs >> temp) {
		if(temp[temp.length()-1] == '.') break;
		if(temp.length() <= 4 || temp.length() >= 21) continue;
		for(char c : temp) {
			if(c == ' ') {
				cout << "[Critical] Cannot init words:Illegal words in words.txt" << endl;
				cout << "�����������󣬳����޷��������С�" << endl;
				Sleep(3000);
				system("pause");
				exit(1);
			}
		}
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
			if(temp[i] == '/') {
				settings[temp.substr(0, i)] = temp.substr(i+1);
			}
		}
	}
	CLS;
	if(settings["Flash"] == "1") {
		cout << "����:" << endl;
		cout << "������Ⱥ��������Ϸʱ����������ض�����˸���棬���ܳ������������һ���֢״��" << endl;
		cout << "���������Ϸ�ие��κ����岻�ʣ�������ֹͣ��Ϸ��������Ҫ������ѯ����ҽʦ��" << endl;
		cout << "��Ҳ�����������е�����˸����Ŀ��ء�" << endl;
		Sleep(3000);
	}
	CLS;
	cout << "��ӭ����´���Ϸ!" << endl;
	cout << "ͨ���²�һ�������п����е��ַ���ʤ��������ĸ������" << endl;
	cout << "������������Դ�ļ�Ŀ¼�µ�settings.txt�鿴���顣" << endl;
	Sleep(1250);
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
	Sleep(500);
	cout << '.';
	Sleep(500);
	cout << '.';
	CLS;
	cout << "���ʳ���: " << len << endl;
	cout << "��ӵ��" << hp << "���ʼ����ֵ��������ʱ����Ϸʧ�ܡ�" << endl;
	for(int i = 0;i < len;i++) {
		if(word[i] == '-' || word[i] == '\'') {
			cout << word[i];
			spCnt++;
		}
		else cout << '_';
	}
	cout << endl << "�������ַ��򵥴�(0��ʾ��ʾ):";
}
int main() {
	cout << "������..." << endl;
	launchInit();
	start();
	while(true) {
		int gs = gameStatus(cnt, spCnt, len, hp);
		if(gs == 1) {
			CLS;
			if(settings["Flash"] == "1") system("color 27");
			cout << "ͨ��! ��ɲ´���ս" << endl;
			Sleep(750);
			cout << "��ȷ�ĵ�����:" << endl;
			for(char ch : word) cout << ch;
			cout << endl << "����.";
			Sleep(500);
			cout << '.';
			Sleep(500);
			cout << '.' << endl;
			char judge = judgeResult(len, cnt, hp);
			switch(judge) {
				case 'P':
					AP();
					cout << "   All Perfect!!!" << endl;
					cout << "�����������У����������������: 1st!!!" << endl;
					break;
				case 'V':
					V();
					cout << "        V��!!" << endl;
					cout << "�����������У����������������: 2nd!!" << endl;
					break;
				case 'S':
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
			}
			cout << "�˳���Ϸ��رմ��ڣ�����������¿�ʼ��" << endl;
			system("pause");
			start();
			continue;
		}
		else if(gs == -1) {
			CLS;
			if(settings["Flash"] == "1") system("color 47");
			cout << "δͨ��������ֵ�ѹ��㡣" << endl;
			Sleep(750);
			cout << "��ȷ�ĵ�����:" << endl;
			for(char ch : word) cout << ch;
			cout << endl << "����.";
			Sleep(500);
			cout << '.';
			Sleep(500);
			cout << '.' << endl;
			F();
			cout << "     F����ʧ��" << endl;
			cout << "�˳���Ϸ��رմ��ڣ�����������¿�ʼ��" << endl;
			system("pause");
			start();
			continue;
		}
		cin >> curr;
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
					cout << "��ʾ��ʹ�ã������й�����" << ret << "����ĸ" << char(toupper(target)) << "��" << char(tolower(target)) << "��" << endl;
					cout << "����" << len - cnt - spCnt << "��δ֪��ĸ��";
					Sleep(1500);
				}
				else {
					UserError("��Ч�Ĳ²�:��ʾδ��������ʹ�á�\n���β²ⲻ������");
				}
			}
			else if((curr[0] < 'A' || curr[0] > 'Z') && (curr[0] < 'a' || curr[0] > 'z')) {
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
					cout << "��ȷ! �����й�����" << ret << "����ĸ" << char(toupper(curro)) << "��" << char(tolower(curro)) << "��" << endl;
					cout << "����" << len - cnt - spCnt << "��δ֪��ĸ��";
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
				if((curr[0] < 'A' || curr[0] > 'Z') && (curr[0] < 'a' || curr[0] > 'z')) {
					flag = false;
					break;
				}
			}
			if(!flag || curr.length() != word.length())
				UserError("��Ч�Ĳ´�:�����ʽ�Ƿ���\n���β²ⲻ������");
			else {
				if(curr == word) {
					if(settings["Flash"] == "1") system("color 27");
					cout << "��ϲ! ��ǰ�´ʳɹ�" << endl;
					Sleep(750);
					cout << "�ڴ�֮ǰ����¶���" << cnt << "���ַ���" << endl;
					cout << "��ȷ�ĵ�����:" << endl;
					for(char ch : word) cout << ch;
					cout << endl << "����.";
					Sleep(500);
					cout << '.';
					Sleep(500);
					cout << '.' << endl;
					char judge = judgeResult(len, cnt, hp);
					switch(judge) {
						case 'P':
							AP();
							cout << "   All Perfect!!!" << endl;
							cout << "�����������У����������������: 1st!!!" << endl;
							break;
						case 'V':
							V();
							cout << "        V��!!" << endl;
							cout << "�����������У����������������: 2nd!!" << endl;
							break;
						case 'S':
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
					}
					cout << "�˳���Ϸ��رմ��ڣ�����������¿�ʼ��" << endl;
					system("pause");
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
		cout << "���ʳ���: " << len << endl;
		cout << "��ǰ����ֵ: " << hp << endl;
		for(int i = 0;i < len;i++) {
			if(Corr[i] || word[i] == '-' || word[i] == '\'') cout << word[i];
			else cout << '_';
		}
		cout << endl << "�Ѿ��¹����ַ�����ĸ������Сд��:" << endl;
		for(char c = 'a';c <= 'z';c++) {
			if(guessed[c]) cout << c << ' ';
		}
		cout << endl << "������а���ֱ�Ӳ³����������ﲢ�س�ȷ����";
		if(hp <= 5 && len - cnt > 2 && !hintUsed) {
			hintUnlock = true;
			cout << endl << "**��ʾ�ѽ�������Ҫ��ʾ������0**";
		}
		else hintUnlock = false;
		cout << endl << "�������ַ��򵥴�(0��ʾ��ʾ):";
	}
	return 0;
}
