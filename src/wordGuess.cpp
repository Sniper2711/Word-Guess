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
	while(getline(ifs, temp)) {
		if(temp[temp.length()-1] == '.') break;
		if(temp.length() <= 4 || temp.length() >= 21) continue;
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
			if(temp[i] == '=') {
				settings[temp.substr(0, i)] = temp.substr(i+1);
			}
		}
	}
	CLS;
	if(settings["Flash"] == "1") {
		cout << "**您已开启屏幕闪烁**" << endl;
		cout << "**你也可以在settings.txt中调整闪烁画面的开关。**\n" << endl;
		cout << "光敏性癫痫警告:" << endl;
		cout << "部分人群在游玩游戏时，如果看到特定的闪烁画面或受到刺激，可能出现类似癫痫一类的症状。" << endl;
		cout << "如果你在游戏中感到任何身体不适，包括但不限于：头晕、恶心、乏力、身体不受自主控制等" << endl;
		cout << "请立即停止游戏，如有需要，请咨询您的医师。" << endl;
		Sleep(3000);
	}
	CLS;
	cout << "欢迎游玩猜词游戏!" << endl;
	cout << "通过猜测一个单词中可能有的字符获胜，包括字母、符号" << endl;
	cout << "调整设置请至源文件目录下的settings.txt查看详情。" << endl;
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
	cout << "正在抽选词汇.";
	Sleep(250);
	cout << '.';
	Sleep(250);
	cout << '.';
	CLS;
	if(settings["Debug"] == "1") showDebugInfo();
	printf("你拥有%d点初始生命值。它归零时，游戏失败。\n", hp);
	cout << "当且仅当生命值低于6，未知字母有3个及以上时，提示将解锁。提示仅可使用一次。\n" << endl;
	cout << "单词长度: " << len << endl;
	for(int i = 0;i < len;i++) {
		if(!isalpha(word[i])) {
			cout << word[i];
			spCnt++;
		}
		else cout << '_';
	}
	cout << endl << "请输入单个字母或整个单词(0表示提示):";
}
void ending(string message, bool win = true) {
	CLS;
	cout << message << endl;
	if(settings["Flash"] == "1") dis_color(win, 750);
	cout << "正确的单词是:" << endl;
	cout << word << endl;
	printf("生命值: %d/10\n", hp);
	printf("猜出字母: %d/%d (%d%%)\n", cnt, len, (cnt * 100 / len));
	cout << "评级.";
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
			cout << "在所有评级中，这个评级的排名是: 1st!!!" << endl;
			break;
		case 'V':
			if(settings["Flash"] == "1") system("color 90");
			V();
			cout << "        V级!!" << endl;
			cout << "在所有评级中，这个评级的排名是: 2nd!!" << endl;
			break;
		case 'S':
			if(settings["Flash"] == "1") system("color B0");
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
		case 'F':
			if(settings["Flash"] == "1") system("color C0");
			F();
			cout << "     F级，失败" << endl;
			break;
	}
	cout << "退出游戏请关闭窗口，按任意键重新开始。" << endl;
	system("pause");
}
int main() {
	cout << "加载中..." << endl;
	launchInit();
	start();
	while(true) {
		int gs = gameStatus(cnt, spCnt, len, hp);
		if(gs == 1) {
			ending("通过! 完成猜词挑战", true);
			start();
			continue;
		}
		else if(gs == -1) {
			ending("未通过，生命值已归零", false);
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
					printf("提示已使用，单词中共包含%d个字母%c或%c。\n", ret, char(toupper(target)), char(tolower(target)));
					printf("还有%d个未知字母。", len - cnt - spCnt);
					Sleep(1500);
				}
				else {
					UserError("无效的猜测:提示未解锁或已使用。\n本次猜测不计数。");
				}
			}
			else if(!isalpha(curr[0])) {
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
					printf("正确! 单词中共包含%d个字母%c或%c。\n", ret, char(toupper(curro)), char(tolower(curro)));
					printf("还有%d个未知字母。", len - cnt - spCnt);
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
				if(c != ' ' && c != '-' && c != '\'' && !isalpha(c)) {
					flag = false;
					break;
				}
			}
			if(!flag || curr.length() != word.length())
				UserError("无效的猜词:输入格式非法。\n本次猜测不计数。");
			else {
				if(curr == word) {
					ending("恭喜! 提前猜词成功", true);
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
		if(settings["Debug"] == "1") showDebugInfo();
		printf("单词长度: %d\n", len);
		printf("当前生命值: %d/10\n", hp);
		for(int i = 0;i < len;i++) {
			if(Corr[i] || isalpha(word[i]) == 0) cout << word[i];
			else cout << '_';
		}
		cout << endl << "已经猜过的字符（字母包括大小写）:" << endl;
		for(char c = 'a';c <= 'z';c++) {
			if(guessed[c]) cout << c << ' ';
		}
		cout << endl << "如果你有把握直接猜出词语，输入词语并回车确定。\n";
		if(hp <= 5 && len - cnt > 2 && !hintUsed) {
			hintUnlock = true;
			cout << endl << "**提示已解锁，需要提示请输入0**\n";
		}
		else hintUnlock = false;
		cout << endl << "请输入单个字母或整个单词(0表示提示):";
	}
	return 0;
}
