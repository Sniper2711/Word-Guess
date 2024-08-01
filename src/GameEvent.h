#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
#define CLS system("cls")
void launchInit() {
	ifstream ifs;
	ifs.open("settings.txt");
	if(!ifs.is_open()) {
		cout << "[Critical] Failed to open input file.Error opening file \"settings.txt\"" << endl;
		cout << "发生致命错误，程序无法继续运行。" << endl;
		Sleep(3000);
		system("pause");
		exit(1);
	}
	while(getline(ifs, temp)) {
		if(temp[0] == '#') continue;
		for(int i = 0;i < temp.length();i++) {
			if(temp[i] == '=') {
				settings[temp.substr(0, i)] = temp.substr(i+1);
			}
		}
		if(ifs.eof()) break;
	}
	ifs.close();
	if(settings["Debug"] == "1") ifs.open(settings["DebugInputFile"]);
	else ifs.open("words.txt");
	if(!ifs.is_open()) {
		cout << "[Critical] Failed to open input file:Error opening words input file" << endl;
		cout << "发生致命错误，程序无法继续运行。" << endl;
		Sleep(3000);
		exit(1);
	}
	while(getline(ifs, temp)) {
		if(temp.length() <= 4 || temp.length() >= 21) continue;
		words.push_back(temp);
		if(ifs.eof()) break;
	}
	ifs.close();
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
	len = clen = word.length();
	for(int i = 0;i < len;i++) {
		if(!isalpha(word[i])) {
			Corr[i] = true;
			clen--;
		}
	}
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
	cout << "单词字母个数: " << clen << endl;
	for(int i = 0;i < len;i++) {
		if(!isalpha(word[i])) cout << word[i];
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
	printf("猜出字母: %d/%d (%d%%)\n", cnt, clen, (cnt * 100 / clen));
	cout << "评级.";
	Sleep(500);
	cout << '.';
	Sleep(500);
	cout << '.' << endl;
	char judge = judgeResult();
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
