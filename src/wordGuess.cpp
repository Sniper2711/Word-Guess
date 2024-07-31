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
		cout << "发生致命错误，程序无法继续运行。" << endl;
		Sleep(3000);
		exit(1);
	}
	while(ifs >> temp) {
		if(temp[temp.length()-1] == '.') break;
		if(temp.length() <= 4 || temp.length() >= 21) continue;
		for(char c : temp) {
			if(c == ' ') {
				cout << "[Critical] Cannot init words:Illegal words in words.txt" << endl;
				cout << "发生致命错误，程序无法继续运行。" << endl;
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
		cout << "发生致命错误，程序无法继续运行。" << endl;
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
		cout << "警告:" << endl;
		cout << "部分人群在游玩游戏时，如果看到特定的闪烁画面，可能出现类似于癫痫一类的症状。" << endl;
		cout << "如果你在游戏中感到任何身体不适，请立即停止游戏，如有需要，请咨询您的医师。" << endl;
		cout << "你也可以在设置中调整闪烁画面的开关。" << endl;
		Sleep(3000);
	}
	CLS;
	cout << "欢迎游玩猜词游戏!" << endl;
	cout << "通过猜测一个单词中可能有的字符获胜，包括字母、符号" << endl;
	cout << "调整设置请至源文件目录下的settings.txt查看详情。" << endl;
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
	cout << "正在抽选词汇.";
	Sleep(500);
	cout << '.';
	Sleep(500);
	cout << '.';
	CLS;
	cout << "单词长度: " << len << endl;
	cout << "你拥有" << hp << "点初始生命值。它归零时，游戏失败。" << endl;
	for(int i = 0;i < len;i++) {
		if(word[i] == '-' || word[i] == '\'') {
			cout << word[i];
			spCnt++;
		}
		else cout << '_';
	}
	cout << endl << "请输入字符或单词(0表示提示):";
}
int main() {
	cout << "加载中..." << endl;
	launchInit();
	start();
	while(true) {
		int gs = gameStatus(cnt, spCnt, len, hp);
		if(gs == 1) {
			CLS;
			if(settings["Flash"] == "1") system("color 27");
			cout << "通过! 完成猜词挑战" << endl;
			Sleep(750);
			cout << "正确的单词是:" << endl;
			for(char ch : word) cout << ch;
			cout << endl << "评级.";
			Sleep(500);
			cout << '.';
			Sleep(500);
			cout << '.' << endl;
			char judge = judgeResult(len, cnt, hp);
			switch(judge) {
				case 'P':
					AP();
					cout << "   All Perfect!!!" << endl;
					cout << "在所有评级中，这个评级的排名是: 1st!!!" << endl;
					break;
				case 'V':
					V();
					cout << "        V级!!" << endl;
					cout << "在所有评级中，这个评级的排名是: 2nd!!" << endl;
					break;
				case 'S':
					S();
					cout << "        S级!" << endl;
					cout << "在所有评级中，这个评级的排名是: 3rd!" << endl;
					break;
				case 'A':
					A();
					cout << "        A级" << endl;
					cout << "在所有评级中，这个评级的排名是: 4th" << endl;
					break;
				case 'B':
					B();
					cout << "        B级" << endl;
					cout << "在所有评级中，这个评级的排名是: 5th" << endl;
					break;
				case 'C':
					C();
					cout << "        C级" << endl;
					cout << "在所有评级中，这个评级的排名是: 6th" << endl;
					break;
			}
			cout << "退出游戏请关闭窗口，按任意键重新开始。" << endl;
			system("pause");
			start();
			continue;
		}
		else if(gs == -1) {
			CLS;
			if(settings["Flash"] == "1") system("color 47");
			cout << "未通过，生命值已归零。" << endl;
			Sleep(750);
			cout << "正确的单词是:" << endl;
			for(char ch : word) cout << ch;
			cout << endl << "评级.";
			Sleep(500);
			cout << '.';
			Sleep(500);
			cout << '.' << endl;
			F();
			cout << "     F级，失败" << endl;
			cout << "退出游戏请关闭窗口，按任意键重新开始。" << endl;
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
					cout << "提示已使用，单词中共包含" << ret << "个字母" << char(toupper(target)) << "或" << char(tolower(target)) << "。" << endl;
					cout << "还有" << len - cnt - spCnt << "个未知字母。";
					Sleep(1500);
				}
				else {
					UserError("无效的猜测:提示未解锁或已使用。\n本次猜测不计数。");
				}
			}
			else if((curr[0] < 'A' || curr[0] > 'Z') && (curr[0] < 'a' || curr[0] > 'z')) {
				UserError("无效的猜测:输入字符非字母。\n本次猜测不计数。");
			}
			else if(guessed[curr[0]]) {
				UserError("无效的猜测:你已经猜过这个字母了。\n本次猜测不计数。");
			}
			else {
				char curro = isupper(curr[0]) ? tolower(curr[0]) : toupper(curr[0]);
				guessed[curr[0]] = guessed[curro] = true;
				int ret = update(word, Corr, curr[0]);
				ret += update(word, Corr, curro);
				if(ret != 0) {
					cnt += ret;
					CLS;
					cout << "正确! 单词中共包含" << ret << "个字母" << char(toupper(curro)) << "或" << char(tolower(curro)) << "。" << endl;
					cout << "还有" << len - cnt - spCnt << "个未知字母。";
					if(settings["Flash"] == "1") dis_color(true, 1250);
					else Sleep(1250);
				}
				else {
					hp--;
					CLS;
					cout << "错误! 失去1点生命值。";
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
				UserError("无效的猜词:输入格式非法。\n本次猜测不计数。");
			else {
				if(curr == word) {
					if(settings["Flash"] == "1") system("color 27");
					cout << "恭喜! 提前猜词成功" << endl;
					Sleep(750);
					cout << "在此之前，你猜对了" << cnt << "个字符。" << endl;
					cout << "正确的单词是:" << endl;
					for(char ch : word) cout << ch;
					cout << endl << "评级.";
					Sleep(500);
					cout << '.';
					Sleep(500);
					cout << '.' << endl;
					char judge = judgeResult(len, cnt, hp);
					switch(judge) {
						case 'P':
							AP();
							cout << "   All Perfect!!!" << endl;
							cout << "在所有评级中，这个评级的排名是: 1st!!!" << endl;
							break;
						case 'V':
							V();
							cout << "        V级!!" << endl;
							cout << "在所有评级中，这个评级的排名是: 2nd!!" << endl;
							break;
						case 'S':
							S();
							cout << "        S级!" << endl;
							cout << "在所有评级中，这个评级的排名是: 3rd!" << endl;
							break;
						case 'A':
							A();
							cout << "        A级" << endl;
							cout << "在所有评级中，这个评级的排名是: 4th" << endl;
							break;
						case 'B':
							B();
							cout << "        B级" << endl;
							cout << "在所有评级中，这个评级的排名是: 5th" << endl;
							break;
						case 'C':
							C();
							cout << "        C级" << endl;
							cout << "在所有评级中，这个评级的排名是: 6th" << endl;
							break;
					}
					cout << "退出游戏请关闭窗口，按任意键重新开始。" << endl;
					system("pause");
					start();
					continue;
				}
				else {
					cout << "猜词失败，失去1点生命值";
					if(settings["Flash"] == "1") dis_color(false);
					else Sleep(1000);
					hp--;
				}
			}
		}
		CLS;
		cout << "单词长度: " << len << endl;
		cout << "当前生命值: " << hp << endl;
		for(int i = 0;i < len;i++) {
			if(Corr[i] || word[i] == '-' || word[i] == '\'') cout << word[i];
			else cout << '_';
		}
		cout << endl << "已经猜过的字符（字母包括大小写）:" << endl;
		for(char c = 'a';c <= 'z';c++) {
			if(guessed[c]) cout << c << ' ';
		}
		cout << endl << "如果你有把握直接猜出词语，输入词语并回车确定。";
		if(hp <= 5 && len - cnt > 2 && !hintUsed) {
			hintUnlock = true;
			cout << endl << "**提示已解锁，需要提示请输入0**";
		}
		else hintUnlock = false;
		cout << endl << "请输入字符或单词(0表示提示):";
	}
	return 0;
}
