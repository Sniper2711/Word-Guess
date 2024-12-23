#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
#define CLS system("cls")
string word, temp, curr;
int len, clen, r, cnt, hp = 10;
bool Corr[15], hintUnlock = false, hintUsed = false;
unordered_map<char, bool> guessed;
unordered_map<string, string> settings;
unordered_map<string, string> meanings;
vector<string> words;
void dis_color(bool correct, int mtime = 1000) {
	system((correct ? "color 27" : "color 47"));
	Sleep(mtime);
	system("color 07");
}
void UserError(string info, int mtime = 1000) {
	system("cls");
	cout << "错误:" << info;
	Sleep(mtime);
}
int gameStatus() {
	if(cnt == clen) return 1;
	if(hp <= 0) {
		hp = 0;
		return -1;
	}
	return 0;
}
void showDebugInfo() {
	cout << "------Debug Info------" << endl;
	cout << "Word: " << word << endl;
	printf("Word length and alpha length: %d, %d\n", len, clen);
	printf("Health: %d\n", hp);
	printf("Guessed: %d/%d (%d%%)\n", cnt, clen, cnt * 100 / clen);
	printf("Hint Unlock and Used: %d, %d\n", hintUnlock, hintUsed);
	cout << "Characters guessed:" << endl;
	for(int i = 0;i < len;i++) printf("%d ", Corr[i]);
	cout << endl << "Guessed alphas:" << endl;
	for(char c = 'a';c <= 'z';c++) if(guessed[c]) cout << c << ' ';
	cout << endl << "Settings:" << endl;
	for(pair<string, string> s : settings) cout << s.first << '=' << s.second << endl;
	cout << endl << "To view debug command help, enter 3." << endl;
	cout << "------Debug Info------" << endl;
}
void showHelp(int type = 1) {
	switch(type) {
		case 1:
			system("cls");
			cout << "欢迎游玩猜词游戏!" << endl;
			cout << "游戏基本规则: 程序会给你一个单词的长度，通过猜这个单词里可能有的字母，最终猜出单词。" << endl;
			cout << "猜测机制: 输入单个字母后，系统会检查单词中所有的这个字母的大小写，如果均没有，则错误，反之则正确。" << endl;
			cout << "          简而言之，输入了一个字母就能猜测对应的所有大写和小写字母，且系统将记录猜过的字母，无需重复猜测。" << endl;
			cout << "生命值: 初始生命值为10点，每猜错一个字母-1，猜词失败-2，归零时游戏失败。";
			cout << "胜负判断: 猜出单词即为胜利，生命值归零即为失败。\n" << endl;
			cout << "进阶技巧: 如果你在猜测过程中通过已知字母知道了具体的单词，直接输入整个单词并确认，系统将判断正误。但失败也将扣除2点生命值。\n" << endl;
			cout << "提示: 当且仅当生命值低于6，未知字母有3个及以上时，提示将解锁。提示仅可使用一次。" << endl;
			cout << "提示效果: 输入0来使用提示，提示将显示单词中的所有与 第一个未知字母 相同的大小写字母。\n" << endl;
			cout << "等阶与评级系统: 单局游戏结束后，系统将根据剩余生命值和猜出字母个数给出等阶和评级。" << endl;
			cout << "查看关于等阶/评级的进一步信息，请返回并输入2。\n" << endl;
			cout << "游戏运行机制: 单局游戏结束后，按任意键直接开始下一局，退出游戏请直接关闭应用。" << endl;
			system("pause");
			break;
		case 2:
			system("cls");
			cout << "剩余生命值  评级" << endl;
			cout << "10          Excellent" << endl;
			cout << "9--7        A" << endl;
			cout << "6--4        B" << endl;
			cout << "3--1        C" << endl;
			cout << "0           Fail" << endl;
			cout << "其他        Unknown" << endl;
			system("pause");
			break;
		case 3:
			system("cls");
			cout << "How to open commend mode: enter \"-\"" << endl;
			cout << "Argument format: <Name:Type>" << endl;
			cout << "Mandatory / Optional arguments: <Mandatory>, [Optional]" << endl;
			cout << "Command usage:" << endl;
			cout << "-var <key:string> <value> : Assign variable <key:string> of <value>. Assignable variables: hp, hintUsed." << endl;
			system("pause");
			break;
	}
}
int update(char t) {
	int ret = 0;
	for(int i = 0;i < word.length();i++) {
		if(word.at(i) == t) {
			ret++;
			Corr[i] = true;
		}
	}
	return ret;
}
void useHint() {
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
	Sleep(2000);
}
void debugCmd() {
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
}
char judgeResult() {
	if(hp == 10) return 'E'; // Excellent
	else if(hp <= 9 && hp >= 7) return 'A';
	else if(hp <= 6 && hp >= 4) return 'B';
	else if(hp <= 3 && hp >= 1) return 'C';
	else if(hp == 0 || hp == -1) return 'F'; // Fail
	else return 'U'; // Unknown
}
