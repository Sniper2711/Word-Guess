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
	cout << "´íÎó:" << info;
	Sleep(time);
}
int gameStatus() {
	if(cnt == clen) return 1;
	if(hp == 0) return -1;
	return 0;
}
void showDebugInfo() {
	cout << "------Debug Info------" << endl;
	cout << "Word: " << word << endl;
	printf("Word length and alpha length: %d, %d\n", len, clen);
	printf("Guessed : %d/%d (%d%%)\n", cnt, clen, cnt * 100 / clen);
	cout << "Characters guessed:" << endl;
	for(int i = 0;i < len;i++) printf("%d ", Corr[i]);
	cout << endl << "Guessed chars:" << endl;
	for(char c = 'a';c <= 'z';c++) if(guessed[c]) cout << c << ' ';
	cout << endl << "Settings:" << endl;
	for(pair<string, string> s : settings) cout << s.first << '=' << s.second << endl;
	cout << "------Debug Info------" << endl;
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
	if(hp == 0) return 'F';
	if(hp == 10) return 'P';
	double percent = double(cnt * 1.0 / clen);
	switch(hp) {
		case 9:
		case 8:
			if(percent <= 0.6) return 'V';
			else if(percent > 0.6 && percent <= 0.725) return 'S';
			else return 'A';
			break;
		case 7:
		case 6:
		case 5:
			if(percent <= 0.6) return 'S';
			else if(percent > 0.6 && percent <= 0.725) return 'A';
			else return 'B';
			break;
		case 4:
		case 3:
			if(percent <= 0.6) return 'A';
			else if(percent > 0.6 && percent <= 0.725) return 'B';
			else return 'C';
			break;
		case 2:
		case 1:
			if(percent <= 0.75) return 'B';
			else return 'C';
			break;
	}
}
