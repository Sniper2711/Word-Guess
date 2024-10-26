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
			ending("成功! 完成猜词挑战", true);
			start();
			continue;
		}
		else if(gs == -1) {
			ending("失败，生命值已归零", false);
			start();
			continue;
		}
		getline(cin, curr);
		if(curr.length() == 0)
			UserError("无效：未输入内容。");
		else if(curr.length() == 1) {
			if(settings["Debug"] == "1" && curr == "-") {
				debugCmd();
			}
			else if(curr[0] == '0') {
				if(hintUnlock) {
					useHint();
				}
				else {
					UserError("无效的猜测:提示未解锁或已使用。\n本次猜测不计数。");
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
				UserError("无效的猜测:输入字符非字母。\n本次猜测不计数。");
			}
			else if(guessed[curr[0]]) {
				UserError("无效的猜测:你已经猜过这个字母了。\n本次猜测不计数。");
			}
			else {
				guessed[toupper(curr[0])] = guessed[tolower(curr[0])] = true;
				int retU = update(toupper(curr[0]));
				int retL = update(tolower(curr[0]));
				CLS;
				if(retL + retU != 0) {
					cnt += retU + retL;
					printf("正确! 单词中共包含 %d 个字母 %c 和 %d 个字母 %c。\n", retU, char(toupper(curr[0])), retL, char(tolower(curr[0])));
					printf("还有%d个未知字母。", clen - cnt);
					if(settings["Flash"] == "1") dis_color(true, 1500);
					else Sleep(1500);
				}
				else {
					hp--;
					cout << "错误! 失去 1 点生命值。";
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
				UserError("无效的猜词:输入格式非法。\n本次猜词不计数。");
			else {
				if(curr == word) {
					ending("恭喜! 提前猜词成功", true);
					start();
					continue;
				}
				else {
					cout << "猜词失败，失去 2 点生命值";
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
