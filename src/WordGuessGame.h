#ifndef _WORDGUESSGAME_H
#define _WORDGUESSGAME_H


#include <iostream>
#include <unordered_map>
#include <vector>
#include <windows.h>
#include "SettingList.h"
#include "Header.h"
using namespace std;
struct InteractResult {
    string type, id;
    int code;
    int GuessAlpha_upper, GuessAlpha_lower;
    int Hint_upper, Hint_lower;
    string End_word, End_meaning;
    string GetWord_word;
    unordered_map<string, int> IntReturn;
    unordered_map<string, string> StringReturn;
    InteractResult(){}
    InteractResult(string type, int code, string id) {
        this->type = type, this->code = code, this->id = id;
    }
    InteractResult(string type, int code, string id, int upper, int lower) {
        this->type = type, this->code = code, this->id = id;
        if(type == "GuessAlpha") this->GuessAlpha_upper = upper, this->GuessAlpha_lower = lower;
        else if(type == "Hint") this->Hint_upper = upper, this->Hint_lower = lower;
    }
    InteractResult(string type, int code, string id, string S) {
        this->type = type, this->code = code, this->id = id;
        this->GetWord_word = S;
    }
    InteractResult(string type, int code, string id, string S1, string S2) {
        this->type = type, this->code = code, this->id = id;
        this->End_word = S1, this->End_meaning = S2;
    }
};
class WordGuessGame {
    private:
        int status, hp, len, alphalen, count = 0;
        string word;
        bool hintAvailable, hintUsed, show[15];
        unordered_map<char, bool> guessed;
        unordered_map<string, string> meanings;
        vector<string> words, languages = {"zh_cn", "en_us"};
        int guessupdate(char t) {
            int ret = 0;
            for(int i = 0;i < word.length();i++) {
                if(word.at(i) == t) {
                    ret++;
                    show[i] = true;
                }
            }
            return ret;
        }
    public:
        WordGuessGame() {
            string temp;
            ifstream ifs;
            ifs.open("settings.txt");
            if(!ifs.is_open()) {
                throw WordGuessException("Failed to open input file. Error opening file \"settings.txt\"");
                exit(1);
            }
            while(!ifs.eof()) {
                getline(ifs, temp);
                if(temp[0] == '#') continue;
                for(int i = 0;i < temp.length();i++) {
                    if(temp[i] == '=') {
                        string key = temp.substr(0, i), value = temp.substr(i+1);
                        if(value[0] >= '0' && value[0] <= '9')
                            IntSettingList.set(key, atoi(value.c_str()));
                        else
                            StringSettingList.set(key, value);
                        break;
                    }
                }
            }
            ifs.close();
            string language = "unknown", id, message;
            for(int i = 0;i < languages.size();i++) {
                ifs.open(languages[i] + ".txt");
                if(!ifs.is_open()) continue;
                while(!ifs.eof()) {
                    getline(ifs, temp);
                    if(temp[0] == '#') continue;
                    for(int i = 0;i < temp.length();i++) {
                        if(temp[i] == ';') {
                            language = temp.substr(0, i);
                            translator.add_language(language);
                            break;
                        }
                        if(temp[i] == '=') {
                            id = temp.substr(1, i-1);
                            message = temp.substr(i+1);
                            translator.add_message(language, id, message);
                            break;
                        }
                    }
                }
                ifs.close();
            }
            if(IntSettingList.get("Debug") == 1) ifs.open(StringSettingList.get("DebugInputFile"));
            else ifs.open("words.txt");
            if(!ifs.is_open()) {
                throw WordGuessException("Failed to open input file. Error opening words input file.");
                exit(1);
            }
            while(!ifs.eof()) {
                getline(ifs, temp);
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
        }
        int step() {
            if(count == alphalen) {
                return 1;
            }
            else if(hp <= 0) {
                hp = 0;
                return -1;
            }
            if(hp <= 5 && alphalen - count > 2 && !hintUsed) hintAvailable = true;
            else hintAvailable = false;
            return 0;
        }
        InteractResult Start() {
            if(status != 0) return InteractResult("Start", 0, "WordGuessGame.Start.Gameisrunning");
            status = 1;
            count = 0, hp = 10;
            for(int i = 0;i < 15;i++) show[i] = false;
            hintAvailable = hintUsed = false;
            for(char c = 'a';c <= 'z';c++) {
                guessed[c] = false;
                guessed[char(toupper(c))] = false;
            }
            srand(time(0));
            int r = rand() % words.size();
            word = words.at(r);
            len = alphalen = word.length();
            for(int i = 0;i < len;i++) {
                if(!isalpha(word[i])) {
                    show[i] = true;
                    alphalen--;
                }
            }
            return InteractResult("Start", 1, "WordGuessGame.Start.Success");
        }
        InteractResult End() {
            status = 0;
            if(hp == 0) return InteractResult("End", 0, "WordGuessGame.End.Lose", word, meanings[word]);
            if(count == alphalen) return InteractResult("End", 1, "WordGuessGame.End.Win", word, meanings[word]);
            return InteractResult("End", -1, "WordGuessGame.End.Invaild");
        }
        InteractResult GuessAlpha(char c) {
            if(!isalpha(c)) return InteractResult("GuessAlpha", -1, "WordGuessGame.GuessAlpha.Invaild");
            if(guessed[c]) return InteractResult("GuessAlpha", -1, "WordGuessGame.GuessAlpha.Guessed");
            guessed[toupper(c)] = guessed[tolower(c)] = true;
            int uppercount = guessupdate(toupper(c));
            int lowercount = guessupdate(tolower(c));
            if(uppercount + lowercount == 0) {
                hp--;
                return InteractResult("GuessAlpha", 0, "WordGuessGame.GuessAlpha.Fail");
            }
            count += uppercount + lowercount;
            return InteractResult("GuessAlpha", 1, "WordGuessGame.GuessAlpha.Success", uppercount, lowercount);
        }
        InteractResult GuessWord(string s) {
            InteractResult result;
            result.GuessAlpha_upper = result.GuessAlpha_lower;
            for(char c : s) {
				if(c != ' ' && c != '-' && c != '\'' && !isalpha(c)) return InteractResult("GuessWord", -1, "WordGuessGame.GuessWord.Invaild");
			}
            if(s.length() != word.length()) return InteractResult("GuessWord", -1, "WordGuessGame.GuessWord.Invaild");
            if(s == word) {
                count = alphalen;
                return InteractResult("GuessWord", 1, "WordGuessGame.GuessWord.Success");
            }
            else {
                hp -= 2;
                return InteractResult("GuessWord", 0, "WordGuessGame.GuessWord.Fail");
            }
        }
        InteractResult Hint() {
            if(!hintAvailable) return InteractResult("Hint", 0, "WordGuessGame.Hint.Unavailable");
            if(hintUsed) return InteractResult("Hint", 0, "WordGuessGame.Hint.Used");
            hintUsed = true;
            char hintupper, hintlower;
            for(int i = 0;i < len;i++) {
                if(!show[i]) {
                    hintupper = toupper(word[i]);
                    hintlower = tolower(word[i]);
                    break;
                }
            }
            guessed[hintupper] = guessed[hintlower] = true;
            int upper = guessupdate(hintupper);
            int lower = guessupdate(hintlower);
            count += upper + lower;
            return InteractResult("Hint", 1, "WordGuessGame.Hint.Success", hintupper, hintlower);
        }
        string GetWordStatus() {
            string result;
            for(int i = 0;i < len;i++) {
                if(show[i]) result += word[i];
                else result += '_';
            }
            return result;
        }
        unordered_map<string, int> GetGameStatus() {
            unordered_map<string, int> result;
            result["hp"] = hp, result["count"] = count, result["len"] = len, result["alphalen"] = alphalen;
            result["hintAvailable"] = hintAvailable, result["hintUsed"] = hintUsed;
            return result;
        }
        string GetGuessedStatus() {
            string result;
            for(char c = 'a';c <= 'z';c++) {
                if(guessed[c]) {
                    result.push_back(c);
                    result.push_back(' ');
                }
            }
            return result + '\n';
        }
        string DebugInfo() {
            if(IntSettingList.get("Debug") == 0) return "";
            string result;
            result += "------Debug Info------\n";
            result += format("Word: {}\n", word);
            result += format("Word length and alpha count: {}, {}\n", len, alphalen);
            result += format("HP: {}\n", hp);
            result += format("Guessed: {}, {}\n", count, alphalen);
            result += format("Hint Available and Used: {}, {}\n", hintAvailable, hintUsed);
            result += "Characters show or not:\n";
            for(int i = 0;i < len;i++) result += (show[i] ? "1 " : "0 ");
            result += "\nGuessed letters:\n";
            for(char c = 'a';c <= 'z';c++) if(guessed[c]) {
                result.push_back(c);
                result.push_back(' ');
            }
            result += "\n------Debug Info------\n";
            return result;
        }
};


#endif
