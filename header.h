#include <iostream>
#include <windows.h>
using namespace std;
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
int gameStatus(int cnt, int len, int hp) {
	if(cnt == len) return 1;
	if(hp == 0) return -1;
	return 0;
}
int update(string word, bool *Corr, char t) {
	int ret = 0;
	for(int i = 0;i < word.length();i++) {
		if(word.at(i) == t) {
			ret++;
			Corr[i] = true;
		}
	}
	return ret;
}
char judgeResult(int len, int cnt, int hp) {
	if(hp == 0) return 'F';
	if(hp == 10) return 'P';
	double percent = cnt / len;
	switch(hp) {
		case 9:
		case 8:
			if(percent <= 0.25) return 'V';
			else if(percent > 0.25 && percent <= 0.4) return 'S';
			else return 'A';
			break;
		case 7:
		case 6:
		case 5:
			if(percent <= 0.25) return 'S';
			else if(percent > 0.25 && percent <= 0.4) return 'A';
			else return 'B';
			break;
		case 4:
		case 3:
			if(percent <= 0.5) return 'A';
			else if(percent > 0.5 && percent <= 0.65) return 'B';
			else return 'C';
			break;
		case 2:
		case 1:
			return 'C';
			break;
	}
}
