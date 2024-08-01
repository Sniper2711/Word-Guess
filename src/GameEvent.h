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
		cout << "�����������󣬳����޷��������С�" << endl;
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
		cout << "�����������󣬳����޷��������С�" << endl;
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
		cout << "**���ѿ�����Ļ��˸**" << endl;
		cout << "**��Ҳ������settings.txt�е�����˸����Ŀ��ء�**\n" << endl;
		cout << "��������ﾯ��:" << endl;
		cout << "������Ⱥ��������Ϸʱ����������ض�����˸������ܵ��̼������ܳ����������һ���֢״��" << endl;
		cout << "���������Ϸ�ие��κ����岻�ʣ������������ڣ�ͷ�Ρ����ġ����������岻���������Ƶ�" << endl;
		cout << "������ֹͣ��Ϸ��������Ҫ������ѯ����ҽʦ��" << endl;
		Sleep(3000);
	}
	CLS;
	cout << "��ӭ����´���Ϸ!" << endl;
	cout << "ͨ���²�һ�������п����е��ַ���ʤ��������ĸ������" << endl;
	cout << "������������Դ�ļ�Ŀ¼�µ�settings.txt�鿴���顣" << endl;
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
	cout << "���ڳ�ѡ�ʻ�.";
	Sleep(250);
	cout << '.';
	Sleep(250);
	cout << '.';
	CLS;
	if(settings["Debug"] == "1") showDebugInfo();
	printf("��ӵ��%d���ʼ����ֵ��������ʱ����Ϸʧ�ܡ�\n", hp);
	cout << "���ҽ�������ֵ����6��δ֪��ĸ��3��������ʱ����ʾ����������ʾ����ʹ��һ�Ρ�\n" << endl;
	cout << "������ĸ����: " << clen << endl;
	for(int i = 0;i < len;i++) {
		if(!isalpha(word[i])) cout << word[i];
		else cout << '_';
	}
	cout << endl << "�����뵥����ĸ����������(0��ʾ��ʾ):";
}
void ending(string message, bool win = true) {
	CLS;
	cout << message << endl;
	if(settings["Flash"] == "1") dis_color(win, 750);
	cout << "��ȷ�ĵ�����:" << endl;
	cout << word << endl;
	printf("����ֵ: %d/10\n", hp);
	printf("�³���ĸ: %d/%d (%d%%)\n", cnt, clen, (cnt * 100 / clen));
	cout << "����.";
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
			cout << "�����������У����������������: 1st!!!" << endl;
			break;
		case 'V':
			if(settings["Flash"] == "1") system("color 90");
			V();
			cout << "        V��!!" << endl;
			cout << "�����������У����������������: 2nd!!" << endl;
			break;
		case 'S':
			if(settings["Flash"] == "1") system("color B0");
			S();
			cout << "        S��!" << endl;
			cout << "�����������У����������������: 3rd!" << endl;
			break;
		case 'A':
			A();
			cout << "        A��" << endl;
			cout << "�����������У����������������: 4th" << endl;
			break;
		case 'B':
			B();
			cout << "        B��" << endl;
			cout << "�����������У����������������: 5th" << endl;
			break;
		case 'C':
			C();
			cout << "        C��" << endl;
			cout << "�����������У����������������: 6th" << endl;
			break;
		case 'F':
			if(settings["Flash"] == "1") system("color C0");
			F();
			cout << "     F����ʧ��" << endl;
			break;
	}
	cout << "�˳���Ϸ��رմ��ڣ�����������¿�ʼ��" << endl;
	system("pause");
}
