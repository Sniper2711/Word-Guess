#include <bits/stdc++.h>
#include <fstream>
#include <windows.h>
#include "Header.h"
#include "Rank.h"
#include "GameEvent.h"
using namespace std;
int Main(vector<string>& args) {
	launchInit();
	start();
	while(true) {
		int gs = gameStatus();
		if(gs == 1) {
			ending("�ɹ�! ��ɲ´���ս", true);
			start();
			continue;
		}
		else if(gs == -1) {
			ending("ʧ�ܣ�����ֵ�ѹ���", false);
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
					int ret = update(target);
					ret += update(targeto);
					cnt += ret;
					hintUsed = true;
					CLS;
					printf("��ʾ��ʹ�ã������й�����%d����ĸ%c��%c��\n", ret, char(toupper(target)), char(tolower(target)));
					printf("����%d��δ֪��ĸ��", clen - cnt);
					Sleep(1500);
				}
				else {
					UserError("��Ч�Ĳ²�:��ʾδ��������ʹ�á�\n���β²ⲻ������");
				}
			}
			else if(curr[0] == '1') {
				showHelp();
			}
			else if(curr[0] == '2') {
				showHelp(2);
			}
			else if(!isalpha(curr[0])) {
				UserError("��Ч�Ĳ²�:�����ַ�����ĸ��\n���β²ⲻ������");
			}
			else if(guessed[curr[0]]) {
				UserError("��Ч�Ĳ²�:���Ѿ��¹������ĸ�ˡ�\n���β²ⲻ������");
			}
			else {
				guessed[toupper(curr[0])] = guessed[tolower(curr[0])] = true;
				int retU = update(toupper(curr[0]));
				int retL = update(tolower(curr[0]));
				CLS;
				if(retL + retU != 0) {
					cnt += retU + retL;
					printf("��ȷ! �����й�����%d����ĸ%c��%d����ĸ%c��\n", retU, char(toupper(curr[0])), retL, char(tolower(curr[0])));
					printf("����%d��δ֪��ĸ��", clen - cnt);
					if(settings["Flash"] == "1") dis_color(true, 1250);
					else Sleep(1250);
				}
				else {
					hp--;
					cout << "����! ʧȥ1������ֵ��";
					if(settings["Flash"] == "1") dis_color(false);
					else Sleep(1000);
				}
			}
		}
		else {
			if(curr == "-cmd") {
				string cmd;
				cout << endl << ">>";
				cin >> cmd;
				if(cmd == "-var") {
					string key;
					int value;
					cin >> key >> value;
					if(key == "hp") {
						hp = value;
					}
					else if(key == "hintUsed") {
						hintUsed = value;
					}
					else {
						cout << "Invaild key and value." << endl;
						system("pause");
					}
				}
				else if(cmd == "-set") {
					string key, value;
					cin >> key >> value;
					settings[key] = value;
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
					UserError("��Ч�Ĳ´�:�����ʽ�Ƿ���\n���β´ʲ�������");
				else {
					if(curr == word) {
						ending("��ϲ! ��ǰ�´ʳɹ�", true);
						start();
						continue;
					}
					else {
						cout << "�´�ʧ�ܣ�ʧȥ2������ֵ";
						if(settings["Flash"] == "1") dis_color(false);
						else Sleep(1000);
						hp -= 2;
					}
				}
			}
		}
		cin.sync();
		if(hp <= 5 && clen - cnt > 2 && !hintUsed)
			hintUnlock = true;
		else
			hintUnlock = false;
		CLS;
		if(settings["Debug"] == "1") showDebugInfo();
		printf("��ǰ����ֵ: %d/10\n", hp);
		printf("�³���ĸ/����ĸ����: %d/%d\n", cnt, clen);
		cout << "����״̬: ";
		for(int i = 0;i < len;i++) {
			if(Corr[i]) cout << word[i];
			else cout << '_';
		}
		cout << endl << "�Ѿ��¹����ַ�����ĸ������Сд��:" << endl;
		for(char c = 'a';c <= 'z';c++) {
			if(guessed[c]) cout << c << ' ';
		}
		cout << endl << "������а���ֱ�Ӳ³����������ﲢ�س�ȷ����" << endl;
		if(hintUnlock) cout << "**��ʾ�ѽ�������Ҫ��ʾ������0**" << endl;
		cout << "**�����֪����ô�棬������1**";
		cout << endl << "�����뵥����ĸ(�²�)/��������(ֱ�Ӳ´�)/��������(�������):";
	}
	return 0;
}
