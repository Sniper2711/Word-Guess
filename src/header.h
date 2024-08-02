#include <iostream>
#include <windows.h>
using namespace std;
string word, temp, curr;
int len, clen, r, cnt, hp = 10;
bool Corr[15], hintUnlock = false, hintUsed = false;
unordered_map<char, bool> guessed;
unordered_map<string, string> settings;
vector<string> words;
ofstream logging;
void dis_color(bool correct, int mtime = 1000) {
	system((correct ? "color 27" : "color 47"));
	Sleep(mtime);
	system("color 07");
}
void UserError(string info, int time = 1000) {
	system("cls");
	cout << "错误:" << info;
	Sleep(time);
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
	printf("Guessed : %d/%d (%d%%)\n", cnt, clen, cnt * 100 / clen);
	cout << "Characters guessed:" << endl;
	for(int i = 0;i < len;i++) printf("%d ", Corr[i]);
	cout << endl << "Guessed chars:" << endl;
	for(char c = 'a';c <= 'z';c++) if(guessed[c]) cout << c << ' ';
	cout << endl << "Settings:" << endl;
	for(pair<string, string> s : settings) cout << s.first << '=' << s.second << endl;
	cout << "------Debug Info------" << endl;
}
void showHelp(int type = 0) {
	switch(type) {
		case 0:
			system("cls");
			cout << "欢迎游玩猜词游戏!" << endl;
			cout << "游戏基本规则: 程序会给你一个单词的长度，通过猜这个单词里可能有的字母，最终猜出单词。" << endl;
			cout << "猜测机制: 输入单个字母后，系统会检查单词中所有的这个字母的大小写，如果均没有，则错误，反之则正确。" << endl;
			cout << "          简而言之，输入了一个字母就能猜测对应的所有大写和小写字母，且系统将记录猜过的字母，无需重复猜测。" << endl;
			cout << "生命值: 初始生命值为10点，每猜错一个字母-1，猜词失败-2，归零时游戏失败。";
			cout << "胜负判断: 猜出单词即为胜利，生命值归零即为失败。\n" << endl;
			cout << "进阶技巧: 如果你在猜测过程中通过已知字母知道了具体的单词，直接输入整个单词并确认，系统将判断正误。" << endl;
			cout << "提前猜词成功能帮助你获得更高的评级（猜出全部字母只能获得当前状态中最低的评级），但失败也将扣除2点生命值。\n" << endl;
			cout << "提示: 当且仅当生命值低于6，未知字母有3个及以上时，提示将解锁。提示仅可使用一次。" << endl;
			cout << "提示效果: 输入0来使用提示，提示将显示单词中的所有与 第一个未知字母 相同的大小写字母。" << endl;
			cout << "等阶与评级系统: 单局游戏结束后，系统将根据剩余生命值和猜出字母个数给出等阶和评级。" << endl;
			cout << "查看关于等阶/评级的进一步信息，请返回并输入2。\n" << endl;
			cout << "游戏运行机制: 单局游戏结束后，按任意键直接开始下一局，退出游戏请直接关闭应用。" << endl;
			system("pause");
			break;
		case 1:
			system("cls");
			cout << "等阶与评级的对应: " << endl;
			cout << "等阶   Perfect   Good   Fail" << endl;
			cout << "评级   PC,Ex,S   A--C    F\n" << endl;
			cout << "对于长度小于10的单词，取得评级需要的标准: " << endl;
			cout << "剩余生命值   猜出字母百分比   评级" << endl;
			cout << "10                任意         PC" << endl;
			cout << "9                 任意         Ex" << endl;
			cout << "7--8             0%--65%       S" << endl;
			cout << "7--8            65%--100%      A" << endl;
			cout << "4--6             0%--50%       S" << endl;
			cout << "4--6            50%--75%       A" << endl;
			cout << "4--6            75%--100%      B" << endl;
			cout << "2--3             0%--45%       A" << endl;
			cout << "2--3            45%--70%       B" << endl;
			cout << "2--3            70%--100%      C" << endl;
			cout << "1                 任意         C" << endl;
			cout << "0                0%--99%       F" << endl;
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
char judgeResult() {
	double percent = double(cnt * 1.0 / clen);
	if(hp <= 0) return 'F'; // Fail
	if(hp == 10) return 'P'; // Perfectly Clear
	if(hp == 9) return 'E'; // Extreme
	if(hp == 1) return 'C';
	if(hp <= 8 && hp >= 7) {
		if(percent <= 0.65) return 'S';
		else return 'A';
	}
	else if(hp <= 6 && hp >= 4) {
		if(percent <= 0.5) return 'S';
		else if(percent > 0.5 && percent <= 0.75) return 'A';
		else return 'B';
	}
	else if(hp <= 3 && hp >= 2) {
		if(percent <= 0.45) return 'A';
		else if(percent > 0.45 && percent <= 0.7) return 'B';
		else return 'C';
	}
}
