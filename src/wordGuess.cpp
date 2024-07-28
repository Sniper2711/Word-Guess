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
	cout << "欢迎游玩猜词游戏!" << endl;
	cout << "通过猜测一个单词中可能有的英语字母获胜" << endl;
	cout << "注意:区分大小写!" << endl;
	Sleep(1000);
	cout << "正在抽选词汇.";
	Sleep(500);
	cout << '.';
	Sleep(500);
	cout << '.';
	CLS;
	cout << "单词长度: " << len << endl;
	cout << "你拥有" << hp << "点初始生命值。它归零时，游戏失败。" << endl;
	for(int i = 0;i < len;i++) {
		cout << '_';
	}
	cout << endl << "请输入你认为这个单词里有的字符:";
}
int main() {
	cout << "加载中...";
	myInit();
	while(true) {
		int gs = gameStatus(cnt, len, hp);
		if(gs == 1) {
			CLS;
			system("color 27");
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
					break;
				case 'V':
					AP();
					cout << "        V级!!" << endl;
					break;
				case 'S':
					S();
					cout << "        S级!" << endl;
					break;
				case 'A':
					A();
					cout << "        A级" << endl;
					break;
				case 'B':
					B();
					cout << "        B级" << endl;
					break;
				case 'C':
					C();
					cout << "        C级" << endl;
					break;
				case 'F':
					F();
					cout << "     F级，失败" << endl;
					break;
			}
			system("pause");
			return 0;
		}
		else if(gs == -1) {
			CLS;
			system("color 47");
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
					cout << "提示已使用，单词中包含" << ret << "个字母" << target << "。" << endl;
					cout << "还有" << len - cnt << "个未知字母。";
					Sleep(1500);
				}
				else {
					UserError("无效的猜测:提示未解锁或已使用。\n本次猜测不计数。");
				}
			}
			else if((curr[0] < 'A' || curr[0] > 'Z') && (curr[0] < 'a' || curr[0] > 'z') && curr[0] != '-' && curr[0] != '\'') {
				UserError("无效的猜测:输入字符非法。\n本次猜测不计数。");
			}
			else if(guessed[curr[0]]) {
				UserError("无效的猜测:你已经猜过这个字母了。\n本次猜测不计数。");
			}
			else {
				guessed[curr[0]] = true;
				int ret = update(word, Corr, curr[0]);
				if(ret != 0) {
					cnt += ret;
					CLS;
					cout << "正确! 单词中包含" << ret << "个字母" << curr[0] << "。" << endl;
					cout << "还有" << len - cnt << "个未知字母。";
					dis_color(true, 1500);
				}
				else {
					hp--;
					CLS;
					cout << "错误! 失去1点生命值。";
					dis_color(false);
				}
			}
		}
		else {
			CLS;
			if(curr.length() != word.length()) {
				UserError("无效的猜词:词语长度不相等。\n本次猜测不计数。");
			}
			else {
				if(curr == word) {
					system("color 27");
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
							break;
						case 'V':
							AP();
							cout << "        V级!!" << endl;
							break;
						case 'S':
							S();
							cout << "        S级!" << endl;
							break;
						case 'A':
							A();
							cout << "        A级" << endl;
							break;
						case 'B':
							B();
							cout << "        B级" << endl;
							break;
						case 'C':
							C();
							cout << "        C级" << endl;
							break;
						case 'F':
							F();
							cout << "     F级，失败" << endl;
							break;
					}
					system("pause");
					return 0;
				}
				else {
					cout << "猜词失败，失去1点生命值";
					dis_color(false);
					hp--;
				}
			}
		}
		CLS;
		cout << "当前生命值: " << hp << endl;
		for(int i = 0;i < len;i++) {
			cout << (Corr[i] ? word[i] : '_');
		}
		cout << endl << "已经猜过的字符:" << endl;
		for(char c = 'a';c <= 'z';c++) {
			if(guessed[c]) cout << c << ' ';
		}
		for(char c = 'A';c <= 'Z';c++) {
			if(guessed[c]) cout << c << ' ';
		}
		if(guessed['-']) cout << '-' << ' ';
		if(guessed['\'']) cout << '\'' << ' ';
		cout << endl << "如果你有把握直接猜出词语，输入词语并回车确定。";
		if(hp <= 5 && len - cnt > 2 && !hintUsed) {
			hintUnlock = true;
			cout << endl << "**提示已解锁，需要提示请输入0**";
		}
		else hintUnlock = false;
		cout << endl << "请输入你认为这个单词里有的字符:";
	}
	return 0;
}
