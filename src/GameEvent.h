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
		system("pause");
		exit(1);
	}
	while(getline(ifs, temp)) {
		if(temp.length() <= 4 || temp.length() >= 16) continue; // Single word length: 5-15
		words.push_back(temp);
		if(ifs.eof()) break;
	}
	ifs.close();
	CLS;
	if(settings["Flash"] == "1") {
		cout << "**���ѿ�����Ļ��˸**" << endl;
		cout << "**��Ҳ������settings.txt�е�����˸����Ŀ��ء�**\n" << endl;
		cout << "��������ﾯ��:" << endl;
		cout << "��������߻�ƹ���˸�Ĵ̼��£��������˿��ܳ������֢״��" << endl;
		cout << "ͬʱ����������Ļ�ϵ�ĳ�౳����ͼ���Լ���ĳЩ��Ϸʱ���������п��ܱ��շ����֢״��" << endl;
		cout << "���������Ϸ�ие��κ����岻�ʣ�����������������֢״��" << endl;
		cout << "ͷ�Ρ�����ģ�����۲�����鴤��ʧȥ֪����ʧȥ����С������������ƶ����鴤��" << endl;
		cout << "������ֹͣ��Ϸ��������Ҫ������ѯҽ���Ľ��顣\n" << endl;
		system("pause");
	}
	CLS;
	cout << "��ӭ����´���Ϸ��" << endl;
	cout << endl << "���漼��: �²ⵥ���п����е���ĸ��ȷ���������ʺ�������ղ²⡣" << endl;
	cout << "��ȡ���������Ϣ�����Ժ�����1��" << endl;
	cout << "������������Դ�ļ�Ŀ¼�µ�settings.txt�鿴���顣" << endl;
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
	cout << "�� Ϸ �� ʼ!" << endl;
	cout << "��ʼ����ֵ: 10" << endl;
	cout << "������ĸ����: " << clen << endl;
	cout << "����״̬: ";
	for(int i = 0;i < len;i++) {
		if(!isalpha(word[i])) cout << word[i];
		else cout << '_';
	}
	cout << endl << "\n**�����֪����ô�棬������1**";
	cout << endl << "�����뵥����ĸ(�²�)/��������(ֱ�Ӳ´�)/��������(�������):";
}
void ending(string message, bool win = true) {
	CLS;
	cout << message << endl;
	if(settings["Flash"] == "1") dis_color(win, 750);
	cout << "��ȷ�ĵ�����:" << endl;
	cout << word << endl;
	printf("����ֵ: %d/10\n", hp);
	printf("�³���ĸ: %d/%d (%d%%)\n", cnt, clen, (cnt * 100 / clen));
	cout << "�Ƚ�/����.";
	Sleep(500);
	cout << '.';
	Sleep(500);
	cout << '.' << endl;
	char judge = judgeResult();
	switch(judge) {
		case 'E':
			if(settings["Flash"] == "1") system("color 90");
			Ex();
			cout << "   Excellent - ����" << endl;
			break;
		case 'A':
			A();
			cout << "      A" << endl;
			break;
		case 'B':
			B();
			cout << "      B" << endl;
			break;
		case 'C':
			C();
			cout << "      C" << endl;
			break;
		case 'F':
			if(settings["Flash"] == "1") system("color C0");
			F();
			cout << "      Fail - ʧ��" << endl;
			break;
		default:
			U();
			cout << "      Unknown - δ֪" << endl;
			cout << "**δ֪���������������ģʽδ�������������߷���������**" << endl;
			break;
	}
	cout << "�˳���Ϸ��رմ��ڣ�����������¿�ʼ��" << endl;
	system("pause");
}
