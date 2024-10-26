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
		if(curr.length() == 0)
			UserError("��Ч��δ�������ݡ�");
		else if(curr.length() == 1) {
			if(settings["Debug"] == "1" && curr == "-") {
				debugCmd();
			}
			else if(curr[0] == '0') {
				if(hintUnlock) {
					useHint();
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
			else if(settings["Debug"] == "1" && curr[0] == '3') {
				showHelp(3);
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
					printf("��ȷ! �����й����� %d ����ĸ %c �� %d ����ĸ %c��\n", retU, char(toupper(curr[0])), retL, char(tolower(curr[0])));
					printf("����%d��δ֪��ĸ��", clen - cnt);
					if(settings["Flash"] == "1") dis_color(true, 1500);
					else Sleep(1500);
				}
				else {
					hp--;
					cout << "����! ʧȥ 1 ������ֵ��";
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
				UserError("��Ч�Ĳ´�:�����ʽ�Ƿ���\n���β´ʲ�������");
			else {
				if(curr == word) {
					ending("��ϲ! ��ǰ�´ʳɹ�", true);
					start();
					continue;
				}
				else {
					cout << "�´�ʧ�ܣ�ʧȥ 2 ������ֵ";
					if(settings["Flash"] == "1") dis_color(false);
					else Sleep(1000);
					hp -= 2;
				}
			}
		}
		cin.sync();
		newturn();
	}
	return 0;
}
