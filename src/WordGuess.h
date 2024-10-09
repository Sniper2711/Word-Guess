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
					printf("提示已使用，单词中共包含%d个字母%c或%c。\n", ret, char(toupper(target)), char(tolower(target)));
					printf("还有%d个未知字母。", clen - cnt);
					Sleep(1500);
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
					printf("正确! 单词中共包含%d个字母%c和%d个字母%c。\n", retU, char(toupper(curr[0])), retL, char(tolower(curr[0])));
					printf("还有%d个未知字母。", clen - cnt);
					if(settings["Flash"] == "1") dis_color(true, 1250);
					else Sleep(1250);
				}
				else {
					hp--;
					cout << "错误! 失去1点生命值。";
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
					UserError("无效的猜词:输入格式非法。\n本次猜词不计数。");
				else {
					if(curr == word) {
						ending("恭喜! 提前猜词成功", true);
						start();
						continue;
					}
					else {
						cout << "猜词失败，失去2点生命值";
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
		printf("当前生命值: %d/10\n", hp);
		printf("猜出字母/总字母个数: %d/%d\n", cnt, clen);
		cout << "单词状态: ";
		for(int i = 0;i < len;i++) {
			if(Corr[i]) cout << word[i];
			else cout << '_';
		}
		cout << endl << "已经猜过的字符（字母包括大小写）:" << endl;
		for(char c = 'a';c <= 'z';c++) {
			if(guessed[c]) cout << c << ' ';
		}
		cout << endl << "如果你有把握直接猜出词语，输入词语并回车确定。" << endl;
		if(hintUnlock) cout << "**提示已解锁，需要提示请输入0**" << endl;
		cout << "**如果不知道怎么玩，请输入1**";
		cout << endl << "请输入单个字母(猜测)/整个单词(直接猜词)/数字命令(详见帮助):";
	}
	return 0;
}
