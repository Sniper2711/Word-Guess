#include <bits/stdc++.h>
#include <fstream>
#include <windows.h>
#include "Header.h"
#include "Rank.h"
#include "WordGuessGame.h"
#include "Translator.h"
using namespace std;
WordGuessGame Game;
int Main(vector<string>& args) {
	string input;
	unordered_map<string, int> GameStatus;
	InteractResult result;
	translator.select(StringSettingList.get("Language"));
	START:
	CLS;
	color();
	cout << translator.translate("WordGuessGame.Text.Load:1");
	cout << translator.translate("WordGuessGame.Text.Load:2");
	cout << translator.translate("WordGuessGame.Text.Load:3");
	cout << translator.translate("WordGuessGame.Text.Load:4");
	system("pause");
	CLS;
	Game.Start();
	while(true) {
		TURN:
		color("white", "black");
		CLS;
		int gs = Game.step();
		GameStatus = Game.GetGameStatus();
		if(gs != 0) {
			END:
			result = Game.End();
			cout << translator.translate(result.id);
			if(IntSettingList.get("Flash") == 1) {
				switch(result.code) {
					case 1:
						color("white", "green");
						break;
					case 0:
						color("white", "red");
						break;
				}
			}
			Sleep(1000);
			color();
			cout << format(runtime_format(translator.translate("WordGuessGame.Text.End:1")), result.End_word);
			Sleep(250);
			cout << format(runtime_format(translator.translate("WordGuessGame.Text.End:2")), result.End_meaning);
			cout << format(runtime_format(translator.translate("WordGuessGame.Text.End:3")), GameStatus["hp"]);
			Sleep(250);
			cout << format(runtime_format(translator.translate("WordGuessGame.Text.End:4")), GameStatus["count"], GameStatus["alphalen"], (GameStatus["count"] * 100.0) / GameStatus["alphalen"]);
			Sleep(250);
			cout << translator.translate("WordGuessGame.Text.End:5", false);
			for(int i = 1;i <= 3;i++) {
				cout << '.';
				Sleep(500);
			}
			cout << '\n';
			switch(GameStatus["hp"]) {
				case 10:
				case 9:
					if(IntSettingList.get("Flash") == 1) color("black", "pale_blue");
					Ex();
					cout << translator.translate("WordGuessGame.Rank.Excellent");
					break;
				case 8:
				case 7:
				case 6:
					A();
					cout << translator.translate("WordGuessGame.Rank.A");
					break;
				case 5:
				case 4:
					B();
					cout << translator.translate("WordGuessGame.Rank.B");
					break;
				case 3:
				case 2:
				case 1:
					C();
					cout << translator.translate("WordGuessGame.Rank.C");
					break;
				case 0:
				case -1:
					if(IntSettingList.get("Flash") == 1) color("white", "pale_red");
					F();
					cout << translator.translate("WordGuessGame.Rank.Fail");
					break;
				default:
					U();
					cout << translator.translate("WordGuessGame.Rank.Unknown");
					cout << translator.translate("WordGuessGame.Rank.Unknown.Warn");
					break;
			}
			cout << translator.translate("WordGuessGame.Text.End:6");
			system("pause");
			goto START;
		}
		if(IntSettingList.get("Debug") == 1) cout << Game.DebugInfo();
		cout << format(runtime_format(translator.translate("WordGuessGame.Text.Turn:1")), GameStatus["hp"]);
		cout << format(runtime_format(translator.translate("WordGuessGame.Text.Turn:2")), GameStatus["count"], GameStatus["alphalen"]);
		cout << translator.translate("WordGuessGame.Text.Turn:3");
		cout << Game.GetWordStatus() << '\n';
		cout << translator.translate("WordGuessGame.Text.Turn:4");
		cout << Game.GetGuessedStatus();
		cout << translator.translate("WordGuessGame.Text.Turn:5");
		cout << translator.translate("WordGuessGame.Text.Turn:6");
		if(GameStatus["hintAvailable"] == 1) cout << translator.translate("WordGuessGame.Hint.Unlocked");
		cout << translator.translate("WordGuessGame.Text.Turn:7");
		getline(cin, input);
		CLS;
		if(input.length() == 0) {
			UserError("WordGuessGame.Input.Nothing");
			goto TURN;
		}
		if(input.length() == 1) {
			char Char = input[0];
			if(IntSettingList.get("Debug") == 1) {
				switch(Char) {
					// case '-':
					// 	debugCmd();
					// 	break;
					case '3':
						showhelp(3);
						break;
				}
			}
			if(Char >= '0' && Char <= '9') {
				switch(Char) {
					case '0':
						result = Game.Hint();
						if(result.code != 1) cout << translator.translate(result.id);
						else cout << format(runtime_format(translator.translate(result.id)), char(result.Hint_upper), char(result.Hint_lower));
						break;
					case '1':
					case '2':
						showhelp(Char - '0');
						goto TURN;
				}
			}
			else {
				result = Game.GuessAlpha(Char);
				switch(result.code) {
					case 1:
						color("white", "green");
						cout << format(runtime_format(translator.translate(result.id)), result.GuessAlpha_upper, char(toupper(Char)), result.GuessAlpha_lower, char(tolower(Char)));
						break;
					case 0:
						color("white", "red");
						cout << translator.translate(result.id);
						break;
					case -1:
						cout << translator.translate(result.id);
						break;
				}
			}
		}
		else {
			result = Game.GuessWord(input);
			cout << translator.translate(result.id);
			if(result.code == 1) {
				if(IntSettingList.get("Flash") == 1) color("white", "green");
				Sleep(1250);
				CLS;
				goto END;
			}
			else if(result.code == 0) if(IntSettingList.get("Flash") == 1) color("white", "red");
		}
		cin.sync();
		GameStatus = Game.GetGameStatus();
		cout << format(runtime_format(translator.translate("WordGuessGame.Text.Interact:1")), GameStatus["alphalen"] - GameStatus["count"]);
		Sleep(1750);
	}
	return 0;
}
