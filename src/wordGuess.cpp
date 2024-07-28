#include <bits/stdc++.h>
#include <fstream>
#include <windows.h>
#include "header.h"
#include "rank.h"
using namespace std;
#define CLS system("cls")
string word, temp, curr;
int len, r, cnt = 0, hp = 10;
bool Corr[15], hintUnlock = false, hintUsed = false;
map<char, bool> guessed;
vector<string> words;
void myInit() {
	srand(time(0));
	ifstream ifs;
	ifs.open("words.txt");
	if(!ifs.is_open()) {
		cout << "[Error] Failed to open input file." << endl;
		Sleep(3000);
		exit(1);
	}
	while(ifs >> temp) {
		if(temp[temp.length()-1] == '.') break;
		words.push_back(temp);
	}
	ifs.close();
	r = rand() % words.size();
	word = words.at(r);
	len = word.length();
	CLS;
	cout << "��ӭ����´���Ϸ!" << endl;
	cout << "ͨ���²�һ�������п����е�Ӣ����ĸ��ʤ" << endl;
	cout << "ע��:���ִ�Сд!" << endl;
	Sleep(1000);
	cout << "���ڳ�ѡ�ʻ�.";
	Sleep(500);
	cout << '.';
	Sleep(500);
	cout << '.';
	CLS;
	cout << "���ʳ���: " << len << endl;
	cout << "��ӵ��" << hp << "���ʼ����ֵ��������ʱ����Ϸʧ�ܡ�" << endl;
	for(int i = 0;i < len;i++) {
		cout << '_';
	}
	cout << endl << "����������Ϊ����������е��ַ�:";
}
int main() {
	cout << "������...";
	myInit();
	while(true) {
		int gs = gameStatus(cnt, len, hp);
		if(gs == 1) {
			CLS;
			system("color 27");
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
					break;
				case 'V':
					AP();
					cout << "        V��!!" << endl;
					break;
				case 'S':
					S();
					cout << "        S��!" << endl;
					break;
				case 'A':
					A();
					cout << "        A��" << endl;
					break;
				case 'B':
					B();
					cout << "        B��" << endl;
					break;
				case 'C':
					C();
					cout << "        C��" << endl;
					break;
				case 'F':
					F();
					cout << "     F����ʧ��" << endl;
					break;
			}
			system("pause");
			return 0;
		}
		else if(gs == -1) {
			CLS;
			system("color 47");
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
			system("pause");
			return 0;
		}
		cin >> curr;
		if(curr.length() == 1) {
			if(curr[0] == '0') {
				if(hintUnlock) {
					char target;
					for(int i = 0;i < len;i++) {
						if(!Corr[i]) {
							target = word[i];
							break;
						}
					}
					guessed[target] = true;
					int ret = update(word, Corr, target);
					cnt += ret;
					hintUsed = true;
					CLS;
					cout << "��ʾ��ʹ�ã������а���" << ret << "����ĸ" << target << "��" << endl;
					cout << "����" << len - cnt << "��δ֪��ĸ��";
					Sleep(1500);
				}
				else {
					UserError("��Ч�Ĳ²�:��ʾδ��������ʹ�á�\n���β²ⲻ������");
				}
			}
			else if((curr[0] < 'A' || curr[0] > 'Z') && (curr[0] < 'a' || curr[0] > 'z') && curr[0] != '-' && curr[0] != '\'') {
				UserError("��Ч�Ĳ²�:�����ַ��Ƿ���\n���β²ⲻ������");
			}
			else if(guessed[curr[0]]) {
				UserError("��Ч�Ĳ²�:���Ѿ��¹������ĸ�ˡ�\n���β²ⲻ������");
			}
			else {
				guessed[curr[0]] = true;
				int ret = update(word, Corr, curr[0]);
				if(ret != 0) {
					cnt += ret;
					CLS;
					cout << "��ȷ! �����а���" << ret << "����ĸ" << curr[0] << "��" << endl;
					cout << "����" << len - cnt << "��δ֪��ĸ��";
					dis_color(true, 1500);
				}
				else {
					hp--;
					CLS;
					cout << "����! ʧȥ1������ֵ��";
					dis_color(false);
				}
			}
		}
		else {
			CLS;
			if(curr.length() != word.length()) {
				UserError("��Ч�Ĳ´�:���ﳤ�Ȳ���ȡ�\n���β²ⲻ������");
			}
			else {
				if(curr == word) {
					system("color 27");
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
							break;
						case 'V':
							AP();
							cout << "        V��!!" << endl;
							break;
						case 'S':
							S();
							cout << "        S��!" << endl;
							break;
						case 'A':
							A();
							cout << "        A��" << endl;
							break;
						case 'B':
							B();
							cout << "        B��" << endl;
							break;
						case 'C':
							C();
							cout << "        C��" << endl;
							break;
						case 'F':
							F();
							cout << "     F����ʧ��" << endl;
							break;
					}
					system("pause");
					return 0;
				}
				else {
					cout << "�´�ʧ�ܣ�ʧȥ1������ֵ";
					dis_color(false);
					hp--;
				}
			}
		}
		CLS;
		cout << "��ǰ����ֵ: " << hp << endl;
		for(int i = 0;i < len;i++) {
			cout << (Corr[i] ? word[i] : '_');
		}
		cout << endl << "�Ѿ��¹����ַ�:" << endl;
		for(char c = 'a';c <= 'z';c++) {
			if(guessed[c]) cout << c << ' ';
		}
		for(char c = 'A';c <= 'Z';c++) {
			if(guessed[c]) cout << c << ' ';
		}
		if(guessed['-']) cout << '-' << ' ';
		if(guessed['\'']) cout << '\'' << ' ';
		cout << endl << "������а���ֱ�Ӳ³����������ﲢ�س�ȷ����";
		if(hp <= 5 && len - cnt > 2 && !hintUsed) {
			hintUnlock = true;
			cout << endl << "**��ʾ�ѽ�������Ҫ��ʾ������0**";
		}
		else hintUnlock = false;
		cout << endl << "����������Ϊ����������е��ַ�:";
	}
	return 0;
}
