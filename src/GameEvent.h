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
	while(!ifs.eof() && getline(ifs, temp)) {
		if(temp[0] == '#') continue;
		for(int i = 0;i < temp.length();i++) {
			if(temp[i] == '=') {
				settings[temp.substr(0, i)] = temp.substr(i+1);
			}
		}
	}
	ifs.close();
	if(settings["Debug"] == "1") ifs.open(settings["DebugInputFile"]);
	else ifs.open("words.txt");
	if(!ifs.is_open()) {
		cout << "[Critical] Failed to open input file:Error opening words input file" << endl;
		cout << "发生致命错误，程序无法继续运行。" << endl;
		Sleep(3000);
		system("pause");
		exit(1);
	}
	while(!ifs.eof() && getline(ifs, temp)) {
		string wd, mn;
		for(int i = 0;i < temp.length();i++) {
			if(temp[i] == ' ') {
				wd = temp.substr(0, i);
				mn = temp.substr(i+1);
				break;
			}
		}
		if(wd.length() <= 5 || wd.length() >= 16) continue; // Single word length: 6-15
		words.push_back(wd);
		meanings[wd] = mn;
	}
	ifs.close();
	CLS;
	if(settings["Flash"] == "1") {
		cout << "**您已开启屏幕闪烁**" << endl;
		cout << "**你也可以在settings.txt中调整闪烁画面的开关。**\n" << endl;
		cout << "光敏性癫痫警告:" << endl;
		cout << "在特殊光线或灯光闪烁的刺激下，极个别人可能出现癫痫症状。" << endl;
		cout << "同时，当看到屏幕上的某类背景或图像以及玩某些游戏时，这类人有可能被诱发癫痫症状。" << endl;
		cout << "如果你在游戏中感到任何身体不适，包括但不限于以下症状：" << endl;
		cout << "头晕、视线模糊、眼部或肌肉抽搐、失去知觉、失去方向感、不由自主地移动、抽搐等" << endl;
		cout << "请立即停止游戏，如有需要，请咨询医生的建议。\n" << endl;
		system("pause");
	}
	CLS;
	cout << "欢迎游玩猜词游戏！" << endl;
	cout << endl << "游玩技巧: 猜测单词中可能有的字母，确定整个单词后进行最终猜测。" << endl;
	cout << "获取更多帮助信息，请稍后输入1。" << endl;
	cout << "调整设置请至源文件目录下的settings.txt查看详情。" << endl;
	Sleep(2000);
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
	if(settings["Debug"] == "1") showDebugInfo();
	cout << "游 戏 开 始!" << endl;
	cout << "初始生命值: 10" << endl;
	cout << "单词字母个数: " << clen << endl;
	cout << "单词状态: ";
	for(int i = 0;i < len;i++) {
		if(Corr[i]) cout << word[i];
		else cout << '_';
	}
	cout << endl << "\n**如果不知道怎么玩，请输入1**";
	cout << endl << "请输入单个字母(猜测)/整个单词(直接猜词)/数字命令(详见帮助):";
}
void ending(string message, bool win = true) {
	CLS;
	cout << message << endl;
	if(settings["Flash"] == "1") dis_color(win, 750);
	cout << "正确的单词是:" << endl;
	cout << word << endl;
	cout << "它的中文含义是：" << endl;
	cout << meanings[word] << endl;
	printf("生命值: %d/10\n", hp);
	printf("猜出字母: %d/%d (%d%%)\n", cnt, clen, (cnt * 100 / clen));
	cout << "等阶/评级.";
	Sleep(500);
	cout << '.';
	Sleep(500);
	cout << '.' << endl;
	char judge = judgeResult();
	switch(judge) {
		case 'E':
			if(settings["Flash"] == "1") system("color 90");
			Ex();
			cout << "   Excellent 排名第1" << endl;
			break;
		case 'A':
			A();
			cout << "     A 排名第2" << endl;
			break;
		case 'B':
			B();
			cout << "     B 排名第3" << endl;
			break;
		case 'C':
			C();
			cout << "     C 排名第4" << endl;
			break;
		case 'F':
			if(settings["Flash"] == "1") system("color C0");
			F();
			cout << "    Fail - 失败" << endl;
			break;
		default:
			U();
			cout << "      Unknown - 未知" << endl;
			cout << "**请注意：未知的评级，如果调试模式未开启，请向作者反馈此问题**" << endl;
			break;
	}
	cout << "退出游戏请关闭窗口，按任意键重新开始。" << endl;
	system("pause");
}
void newturn() {
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
